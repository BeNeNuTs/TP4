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
    T = new Terrain*[4];
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

    out << T->saison << T->c.r << T->c.g << T->c.b << T->nb_vertex;
    for(int i = 0 ; i < T->nb_vertex ; i++){
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
        return;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_1);

    QString saison;
    color c;
    int nb_vertex;
    QVector3D* vertex;

    for(int t = 0 ; t < 4 ; t++){

        in >> saison;
        in >> c.r >> c.g >> c.b;
        in >> nb_vertex;

        vertex = new QVector3D[nb_vertex];
        for(int i = 0 ; i << nb_vertex ; i++){
            float x,y,z;
            in >> x >> y >> z;
            vertex[i].setX(x);
            vertex[i].setY(y);
            vertex[i].setZ(z);
        }

        T[t] = new Terrain(saison, c, nb_vertex, vertex);
    }
    file.close();
}

Terrain *FileManager::getTerrain() const
{
    return T[id];
    FileManager::id++;
}

