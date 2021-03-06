# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

# This is a reminder that you are using a generated .pro file.
# Remove it when you are finished editing this file.
message("You are running qmake on a generated .pro file. This may not work!")


HEADERS += ./src/controller.h \
    ./src/entities/bond.h \
    ./src/entities/elements.h \
    ./src/entities/particle.h \
    ./src/entities/structure.h \
    ./src/fileio/fileutils.h \
    ./src/fileio/objreader.h \
    ./src/fileio/qeIO.h \
    ./src/graphics/camera.h \
    ./src/graphics/generator.h \
    ./src/graphics/GL.h \
    ./src/graphics/light.h \
    ./src/graphics/shader.h \
    ./src/renderables/Cube.h \
    ./src/renderables/cylinder.h \
    ./src/renderables/renderable3D.h \
    ./src/renderables/sphere.h \
    ./gdismainwindow.h \
    ./src/graphics/glwidget.h
SOURCES += ./gdismainwindow.cpp \
    ./main.cpp \
    ./src/controller.cpp \
    ./src/entities/bond.cpp \
    ./src/entities/particle.cpp \
    ./src/entities/structure.cpp \
    ./src/fileio/objreader.cpp \
    ./src/fileio/qeIO.cpp \
    ./src/graphics/camera.cpp \
    ./src/graphics/generator.cpp \
    ./src/graphics/glwidget.cpp \
    ./src/graphics/shader.cpp \
    ./src/renderables/Cube.cpp \
    ./src/renderables/cylinder.cpp \
    ./src/renderables/renderable3D.cpp \
    ./src/renderables/sphere.cpp
FORMS += ./gdismainwindow.ui
RESOURCES += gdismainwindow.qrc
