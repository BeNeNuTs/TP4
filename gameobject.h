#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QVector3D>
#include <QString>
#include <QFile>

enum Format { PLY };

class GameObject
{
public:
    GameObject();
    GameObject(QVector3D pos, QVector3D rot, QVector3D _scale);
    GameObject(QVector3D pos, QVector3D rot, QVector3D _scale, QString localPath);

    void open(QString localPath);
    void display();

private:
    void openPLY(QString localPath);


public:
    QVector3D position;
    QVector3D scale;
    QVector3D rotation;

    QString localPath;
    Format format;

    QVector3D* vertex;
    int nb_vertex;
    QVector3D* normals;

    int nb_ind;

signals:

public slots:
};

#endif // GAMEOBJECT_H
