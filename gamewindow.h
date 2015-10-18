#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "openglwindow.h"
#include "filemanager.h"
#include "commonstruct.h"
#include "gameobject.h"

#include <QTcpSocket>
#include <QAbstractSocket>

struct particles
{
    float x, y ,z;
    float falling_speed;
    float min_z;
};

enum Saison { PRINTEMPS = 0, ETE = 1, AUTOMNE = 2, HIVER = 3, NONE = 4};


class GameWindow : public OpenGLWindow
{
signals:

public slots:
    void connected();
    void disconnected();
    void readyRead();

public:
    GameWindow(int refresh_rate, Camera* c = 0);
    ~GameWindow();

    void initialize();
    void render();
    bool event(QEvent *event);

    void keyPressEvent(QKeyEvent *event);

    void displayTriangles();
    void displayLines();
    void displayTrianglesC();
    void displayPoints();
    void displayTrianglesTexture();

    void displayColor(float);

    void loadMap(QString localPath);

    void animWindow();
    void restartTimer();

    void updateTitle();
    color seasonColor();

    void createParticles();
    particles newParticle();
    void displayParticles();

    void displayTree();

    void doConnect();

    void save();

private:
    updateEnumSaison();

public:
    static const unsigned int MAX_PARTICLES = 1000;

private:

    int m_frame;
    QImage m_image;
    point *p;
    int nb_vertex_width;
    int nb_vertex_height;

    int carte;
    int m_refresh_rate; 		// Taux de rafraîchissement de la fenêtre.

    bool share_cam;				// Permet de savoir si la caméra est partagée par plusieurs instances.
    Camera* m_camera;			// Pointeur vers la caméra de la fenêtre.

    QTimer* m_timer;			// Timer permettant un rafraîchissement à temps fixe de la fenêtre.

    float speed;				// Vitesse de rotation du terrain selon l'axe y quand animate = true.

    QString season;             // Contient le nom de la saison courante dans la fenêtre
    Saison saison;
    QTcpSocket *socket;         // QTcpSocket permettant de se connecter au serveur

    particles* tab_particles;   // Tableau contenant les particules de pluie/neige

    GameObject** tree;
};


#endif // GAMEWINDOW_H
