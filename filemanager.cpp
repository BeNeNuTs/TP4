#include <QFile>
#include <QDataStream>
#include <QMap>
#include <iostream>
#include <QDebug>

#include "filemanager.h"
#include "gamewindow.h"
#include "terrain.h"
#include "camera.h"

using namespace std;

FileManager FileManager::m_instance = FileManager();
int FileManager::id = 0;

FileManager::FileManager()
{
    T = new Terrain*[NB_TERRAIN];
    for(int i = 0 ; i < NB_TERRAIN ; i++){
        T[i] = new Terrain();
    }

    camera = nullptr;
    cout<<"Creation"<<endl;
}

FileManager::~FileManager()
{
    cout<<"Destruction"<<endl;
}

FileManager& FileManager::Instance()
{
    return m_instance;
}

void FileManager::saveCustomMap(Terrain* T)
{
    QFile file(localPath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug() << "FileManager : Could not open " << localPath;
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_1);

    out << T->saison << T->c.r << T->c.g << T->c.b << T->nb_vertex_width << T->nb_vertex_height;
    for(int i = 0 ; i < T->nb_vertex_width * T->nb_vertex_height ; i++){
        out << T->vertex[i].x() << T->vertex[i].y() << T->vertex[i].z();
    }

    out << T->tree->localPath;
    out << T->tree->position.x() << T->tree->position.y() << T->tree->position.z();
    out << T->tree->rotation.x() << T->tree->rotation.y() << T->tree->rotation.z();
    out << T->tree->scale.x() << T->tree->scale.y() << T->tree->scale.z();

    file.flush();
    file.close();
}

void FileManager::loadCustomMap(QString _localPath)
{
    localPath = _localPath;

    QFile file(localPath);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "FileManager : Could not open " << localPath;
        return;
    }

    if(file.size() == 0){
        qDebug() << "FileManager : Empty file";
        file.close();
        return;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_1);

    QString saison;
    color c;
    int nb_vertex_w;
    int nb_vertex_h;
    QVector3D* vertex;

    GameObject* tree;

    camera = new Camera();
    in >> camera->etat >> camera->rotX >> camera->rotY >> camera->ss;

    for(int t = 0 ; t < NB_TERRAIN ; t++){

        in >> saison;
        in >> c.r >> c.g >> c.b;
        in >> nb_vertex_w >> nb_vertex_h;

        vertex = new QVector3D[nb_vertex_w * nb_vertex_h];
        for(int i = 0 ; i < nb_vertex_w * nb_vertex_h ; i++){
            float x,y,z;
            in >> x >> y >> z;
            vertex[i].setX(x);
            vertex[i].setY(y);
            vertex[i].setZ(z);
        }
        tree = new GameObject();
        float x,y,z;

        in >> tree->localPath;

        in >> x >> y >> z;
        tree->position.setX(x);
        tree->position.setY(y);
        tree->position.setZ(z);

        in >> x >> y >> z;
        tree->rotation.setX(x);
        tree->rotation.setY(y);
        tree->rotation.setZ(z);

        in >> x >> y >> z;
        tree->scale.setX(x);
        tree->scale.setY(y);
        tree->scale.setZ(z);

        T[t] = new Terrain(saison, c, nb_vertex_w, nb_vertex_h, vertex, tree);
    }
    file.flush();
    file.close();
}

Terrain *FileManager::getTerrain()
{
    if(FileManager::id > NB_TERRAIN)
        return new Terrain();

    FileManager::id++;
    return T[id-1];

}

