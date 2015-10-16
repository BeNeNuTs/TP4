#ifndef TERRAIN_H
#define TERRAIN_H

#include <QVector3D>
#include <QString>

#include "commonstruct.h"

class Terrain
{
public:
    Terrain();
    Terrain(QString season, color c, int nb_v, point* p);
    Terrain(QString season, color c, int nb_v, QVector3D* v);

public:
    QString saison;
    color c;

    int nb_vertex;
    QVector3D* vertex;


signals:

public slots:
};

#endif // TERRAIN_H
