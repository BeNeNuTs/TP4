#ifndef TERRAIN_H
#define TERRAIN_H

#include <QVector3D>
#include <QString>

#include "commonstruct.h"

class Terrain
{
public:
    Terrain();
    Terrain(QString season, color c, int nb_v_w, int nb_v_h, point* p);
    Terrain(QString season, color c, int nb_v_w, int nb_v_h, QVector3D* v);

public:
    QString saison;
    color c;

    int nb_vertex_width;
    int nb_vertex_height;
    QVector3D* vertex;


signals:

public slots:
};

#endif // TERRAIN_H
