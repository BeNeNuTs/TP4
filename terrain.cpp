#include "terrain.h"
#include "gameobject.h"

Terrain::Terrain()
{
    this->saison = "";
    this->c = color{0.f,0.f,0.f};
    this->nb_vertex_width = 0;
    this->nb_vertex_height = 0;

    vertex = new QVector3D[0];
}

Terrain::Terrain(QString season, color c, int nb_v_w, int nb_v_h, point *p, GameObject* t)
{
    this->saison = season;
    this->c = c;
    this->nb_vertex_width = nb_v_w;
    this->nb_vertex_height = nb_v_h;

    vertex = new QVector3D[nb_vertex_width * nb_vertex_height];
    for(int i = 0 ; i < nb_vertex_width * nb_vertex_height ; i++){
        vertex[i].setX(p[i].x);
        vertex[i].setY(p[i].y);
        vertex[i].setZ(p[i].z);
    }

    tree = t;
}

Terrain::Terrain(QString season, color c, int nb_v_w, int nb_v_h, QVector3D *v, GameObject* t)
{
    this->saison = season;
    this->c = c;
    this->nb_vertex_width = nb_v_w;
    this->nb_vertex_height = nb_v_h;

    vertex = new QVector3D[nb_vertex_width * nb_vertex_height];
    for(int i = 0 ; i < nb_vertex_width * nb_vertex_height ; i++){
        vertex[i].setX(v[i].x());
        vertex[i].setY(v[i].y());
        vertex[i].setZ(v[i].z());
    }

    tree = t;
}
