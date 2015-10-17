#include <QDebug>
#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>

#include "gameobject.h"

GameObject::GameObject()
{
    position = QVector3D(0.f,0.f,0.f);
    scale = QVector3D(0.f,0.f,0.f);
    rotation = QVector3D(0.f,0.f,0.f);

    nb_vertex = 0;
    vertex = new QVector3D[nb_vertex];
    normals = new QVector3D[nb_vertex];
}

GameObject::GameObject(QVector3D pos, QVector3D rot, QVector3D _scale)
{
    position = pos;
    rotation = rot;
    scale = _scale;

    nb_vertex = 0;
    vertex = new QVector3D[nb_vertex];
    normals = new QVector3D[nb_vertex];
}

GameObject::GameObject(QVector3D pos, QVector3D rot, QVector3D _scale, QString _localPath)
{
    position = pos;
    rotation = rot;
    scale = _scale;

    open(_localPath);
}

void GameObject::open(QString _localPath)
{

    QFile file(_localPath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Could not open " << _localPath;
        return;
    }

    if(file.readLine() == "ply\n"){
        file.close();
        openPLY(_localPath);
    }

}

void GameObject::display()
{
    glPushMatrix();

    glTranslatef(position.x(), position.y(), position.z());
    glScalef(scale.x(), scale.y(), scale.z());
    glRotatef(rotation.x(), 1.f, 0.f, 0.f);
    glRotatef(rotation.y(), 0.f, 1.f, 0.f);
    glRotatef(rotation.z(), 0.f, 0.f, 1.f);

    glBegin(GL_POINTS);
    glColor3f(1.f,0.f,0.f);
    for(int i = 0 ; i < nb_vertex ; i++){
        glVertex3f(vertex[i].x(), vertex[i].y(), vertex[i].z());
    }
    glEnd();

    glPopMatrix();
}

void GameObject::openPLY(QString _localPath)
{
    QFile file(_localPath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Could not open " << _localPath;
        return;
    }

    localPath = _localPath;
    format = Format::PLY;

    // read whole content
    QString content = file.readAll();
    // extract words
    QStringList lines = content.split("\n");

    int index = 0;

    for(int i = 0 ; i < lines.size() ; i++){
        if(lines[i].contains("element vertex")){
            QStringList words = lines[i].split(" ");
            nb_vertex = words[2].toInt();
        }else if(lines[i].contains("element face")){
            QStringList words = lines[i].split(" ");
            nb_ind = words[2].toInt();
        }

        if(lines[i].contains("end_header")){
            index = i+1;
            break;
        }
    }

    vertex = new QVector3D[nb_vertex];
    normals = new QVector3D[nb_vertex];
    int i = 0;
    while(i < nb_vertex){
        QStringList words = lines[index + i].split(" ");

        vertex[i].setX(words[0].toFloat());
        vertex[i].setY(words[1].toFloat());
        vertex[i].setZ(words[2].toFloat());

        normals[i].setX(words[3].toFloat());
        normals[i].setY(words[4].toFloat());
        normals[i].setZ(words[5].toFloat());

        i++;
    }
}
