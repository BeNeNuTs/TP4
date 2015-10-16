#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include "gamewindow.h"
#include "terrain.h"

class FileManager
{
public:
    static FileManager& Instance();

    void saveCustomMap(QString localPath, Terrain* T);
    void loadCustomMap(QString localPath);

    Terrain* getTerrain() const;

private:
    static FileManager m_instance;
    static int id;
    FileManager();
    ~FileManager();

    Terrain** T;
};

#endif // FILEMANAGER_H
