#include <QDebug>
#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>

#include <vector>

#include "gameobject.h"

using namespace std;

GameObject::GameObject()
{
    position = QVector3D(0.f,0.f,0.f);
    scale = QVector3D(0.f,0.f,0.f);
    rotation = QVector3D(0.f,0.f,0.f);

    nb_vertex = 0;
    vertex = new QVector3D[nb_vertex];
    normals = new QVector3D[nb_vertex];

    nb_ind = 0;
    index = new QVector3D[nb_ind];
}

GameObject::GameObject(QVector3D pos, QVector3D rot, QVector3D _scale)
{
    position = pos;
    rotation = rot;
    scale = _scale;

    nb_vertex = 0;
    vertex = new QVector3D[nb_vertex];
    normals = new QVector3D[nb_vertex];

    nb_ind = 0;
    index = new QVector3D[nb_ind];
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
    }else if(file.readLine() == "solid\n"){
        file.close();
        openSTL(_localPath);
    }

}

void GameObject::display()
{
    glPushMatrix();

    glTranslatef(position.x(), position.y(), position.z());
    glScalef(scale.x(), scale.y(), scale.z());
    glRotatef(rotation.x(), 1.f, 0.f, 0.f);
    glRotatef(rotation.y(), 0.f, 0.f, 1.f);
    glRotatef(rotation.z(), 0.f, 1.f, 0.f);

    glColor3f(0.f,0.5f,0.f);

    if(format == Format::PLY){
        displayPLY();
    }else if(format == Format::STL){
        displaySTL();
    }

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

    file.close();

    int ind = 0;

    for(int i = 0 ; i < lines.size() ; i++){
        if(lines[i].contains("element vertex")){
            QStringList words = lines[i].split(" ");
            nb_vertex = words[2].toInt();
        }else if(lines[i].contains("element face")){
            QStringList words = lines[i].split(" ");
            nb_ind = words[2].toInt();
        }

        if(lines[i].contains("end_header")){
            ind = i+1;
            break;
        }
    }

    vertex = new QVector3D[nb_vertex];
    normals = new QVector3D[nb_vertex];
    index = new QVector3D[nb_ind];

    int i = 0;
    while(i < nb_vertex){
        QStringList words = lines[ind + i].split(" ");

        vertex[i].setX(words[0].toFloat());
        vertex[i].setY(words[1].toFloat());
        vertex[i].setZ(words[2].toFloat());

        normals[i].setX(words[3].toFloat());
        normals[i].setY(words[4].toFloat());
        normals[i].setZ(words[5].toFloat());

        i++;
    }

    ind += i;
    i = 0;
    while(i < nb_ind){
        QStringList words = lines[ind + i].split(" ");

        index[i].setX(words[1].toInt());
        index[i].setY(words[2].toInt());
        index[i].setZ(words[3].toInt());

        i++;
    }

}

void GameObject::openSTL(QString _localPath)
{
    QFile file(_localPath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Could not open " << _localPath;
        return;
    }

    localPath = _localPath;
    format = Format::STL;

    // read whole content
    QString content = file.readAll();
    // extract words
    QStringList lines = content.split("\n");

    file.close();

    vector<QVector3D> v_normals;
    vector<QVector3D> v_vertex;

    for(int i = 0 ; i < lines.size() ; i++){
        if(lines[i].contains("facet normals")){
            QStringList words = lines[i].split(" ");
            v_normals.push_back(QVector3D(words[2].toFloat(), words[3].toFloat(), words[4].toFloat()));
        }else if(lines[i].contains("vertex")){
            QStringList words = lines[i].split(" ");
            v_vertex.push_back(QVector3D(words[1].toFloat(), words[2].toFloat(), words[3].toFloat()));
        }
    }

    vertex = new QVector3D[v_vertex.size()];
    normals = new QVector3D[v_normals.size()];

    for(unsigned int i = 0 ; i < v_vertex.size() ; i++){
        vertex[i] = v_vertex[i];
    }

    for(unsigned int i = 0 ; i < v_normals.size() ; i++){
        normals[i] = v_normals[i];
    }
}

void GameObject::displayPLY()
{
    glBegin(GL_TRIANGLES);
    for(int i = 0 ; i < nb_ind ; i++){
        glNormal3f(normals[(int)index[i].x()].x(), normals[(int)index[i].x()].y(), normals[(int)index[i].x()].z());
        glVertex3f(vertex[(int)index[i].x()].x(), vertex[(int)index[i].x()].y(), vertex[(int)index[i].x()].z());

        glNormal3f(normals[(int)index[i].y()].x(), normals[(int)index[i].y()].y(), normals[(int)index[i].y()].z());
        glVertex3f(vertex[(int)index[i].y()].x(), vertex[(int)index[i].y()].y(), vertex[(int)index[i].y()].z());

        glNormal3f(normals[(int)index[i].z()].x(), normals[(int)index[i].z()].y(), normals[(int)index[i].z()].z());
        glVertex3f(vertex[(int)index[i].z()].x(), vertex[(int)index[i].z()].y(), vertex[(int)index[i].z()].z());

    }
    glEnd();
}

void GameObject::displaySTL()
{

}

