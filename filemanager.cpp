#include <QFile>
#include <QDataStream>
#include <QMap>
#include <iostream>
#include <QDebug>

#include "filemanager.h"

using namespace std;

FileManager FileManager::m_instance = FileManager();
int FileManager::id = 0;

FileManager::FileManager()
{
    T = new Terrain*[NB_TERRAIN];
    for(int i = 0 ; i < NB_TERRAIN ; i++){
        T[i] = new Terrain();
    }
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

void FileManager::saveCustomMap(QString localPath, Terrain* T)
{
    QFile file(localPath);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug() << "Could not open " << localPath;
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_1);

    out << T->saison << T->c.r << T->c.g << T->c.b << T->nb_vertex_width << T->nb_vertex_height;
    for(int i = 0 ; i < T->nb_vertex_width * T->nb_vertex_height ; i++){
        out << T->vertex[i].x() << T->vertex[i].y() << T->vertex[i].z();
    }

    file.flush();
    file.close();
}

void FileManager::loadCustomMap(QString localPath)
{
    QFile file(localPath);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Could not open " << localPath;
        return;
    }

    if(file.size() == 0){
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

        /*qDebug() << saison;
        cout << nb_vertex << endl;
        qDebug() << vertex[0].x() << " " << vertex[0].y() << " " << vertex[0].z();
        qDebug() << vertex[nb_vertex-1].x() << " " << vertex[nb_vertex-1].y() << " " << vertex[nb_vertex-1].z();*/


        T[t] = new Terrain(saison, c, nb_vertex_w, nb_vertex_h, vertex);
    }
    file.close();
}

Terrain *FileManager::getTerrain()
{
    if(FileManager::id > NB_TERRAIN)
        return new Terrain();

    FileManager::id++;
    return T[id-1];

}

