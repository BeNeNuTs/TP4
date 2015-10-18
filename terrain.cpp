#include "terrain.h"
#include "gameobject.h"
#include "gamewindow.h"

Terrain::Terrain()
{
    this->saison = "";
    this->c = color{0.f,0.f,0.f};
    this->nb_vertex_width = 0;
    this->nb_vertex_height = 0;

    vertex = new QVector3D[0];
}

Terrain::Terrain(QString season, color c, int nb_v_w, int nb_v_h, point *p, GameObject*** t)
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

    tree = new GameObject**[FileManager::NB_TERRAIN];
    tree[Saison::PRINTEMPS] = new GameObject*[GameWindow::NB_ARBRES];
    tree[Saison::ETE] = new GameObject*[GameWindow::NB_ARBRES];
    tree[Saison::AUTOMNE] = new GameObject*[GameWindow::NB_ARBRES];
    tree[Saison::HIVER] = new GameObject*[GameWindow::NB_ARBRES];

    for(unsigned int j = 0 ; j < FileManager::NB_TERRAIN ; j++){
        for(unsigned int i = 0 ; i < GameWindow::NB_ARBRES ; i++){
            tree[j][i] = t[j][i];
        }
    }
}

Terrain::Terrain(QString season, color c, int nb_v_w, int nb_v_h, QVector3D *v, GameObject*** t)
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

    tree = new GameObject**[FileManager::NB_TERRAIN];
    tree[Saison::PRINTEMPS] = new GameObject*[GameWindow::NB_ARBRES];
    tree[Saison::ETE] = new GameObject*[GameWindow::NB_ARBRES];
    tree[Saison::AUTOMNE] = new GameObject*[GameWindow::NB_ARBRES];
    tree[Saison::HIVER] = new GameObject*[GameWindow::NB_ARBRES];

    for(unsigned int j = 0 ; j < FileManager::NB_TERRAIN ; j++){
        for(unsigned int i = 0 ; i < GameWindow::NB_ARBRES ; i++){
            tree[j][i] = t[j][i];
        }
    }
}
