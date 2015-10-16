#include "terrain.h"

Terrain::Terrain()
{
    this->saison = "";
    this->c = color{0.f,0.f,0.f};
    this->nb_vertex = 0;

    vertex = new QVector3D[nb_vertex];
}

Terrain::Terrain(QString season, color c, int nb_v, point *p)
{
    this->saison = season;
    this->c = c;
    this->nb_vertex = nb_v;

    vertex = new QVector3D[nb_vertex];
    for(int i = 0 ; i < nb_vertex ; i++){
        vertex[i].setX(p[i].x);
        vertex[i].setY(p[i].y);
        vertex[i].setZ(p[i].z);
    }
}

Terrain::Terrain(QString season, color c, int nb_v, QVector3D *v)
{
    this->saison = season;
    this->c = c;
    this->nb_vertex = nb_v;

    vertex = new QVector3D[nb_vertex];
    for(int i = 0 ; i < nb_vertex ; i++){
        vertex[i].setX(v[i].x());
        vertex[i].setY(v[i].y());
        vertex[i].setZ(v[i].z());
    }
}
