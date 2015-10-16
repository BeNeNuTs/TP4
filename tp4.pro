INCLUDEPATH += $$PWD
SOURCES += $$PWD/openglwindow.cpp \
    gamewindow.cpp \
    camera.cpp \
    mytcpserver.cpp \
    filemanager.cpp \
    terrain.cpp
HEADERS += $$PWD/openglwindow.h \
    gamewindow.h \
    camera.h \
    mytcpserver.h \
    filemanager.h \
    terrain.h \
    commonstruct.h

SOURCES += \
    main.cpp

target.path = .
INSTALLS += target

RESOURCES += \
    gestionnaire.qrc

QT += network

QMAKE_CXXFLAGS += -fopenmp -std=c++11
LIBS += -fopenmp -std=c++11

