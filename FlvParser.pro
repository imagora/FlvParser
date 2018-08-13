#---------------------------------------------------------------------
# PART 1: General Setting

TEMPLATE = app
CONFIG += c++11
TARGET = FlvParser
OBJECTS_DIR = .objs
QT += core gui widgets

include(gitversion.pri)

#---------------------------------------------------------------------
# PART 2: target, library, flags
TARGET = bin/Gump
INCLUDEPATH += src
INCLUDEPATH += /usr/local/include
LIBS += -L/usr/lib -L/usr/local/lib -llog4cplus
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += BUILD_VERSION=\\\"$$VERSION\\\"

#---------------------------------------------------------------------
# PART 3: Clean
QMAKE_CLEAN += $(TARGET) $(QMAKE_TARGET) bin/Gump

#---------------------------------------------------------------------
# PART 4: Input
SOURCES += \
    src/main.cpp \
    src/view/main_widget.cpp
HEADERS  += \
    src/view/main_widget.h
RESOURCES += \
    resource.qrc
ICON = icon.icns
