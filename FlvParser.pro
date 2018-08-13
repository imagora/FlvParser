#---------------------------------------------------------------------
# PART 1: General Setting

TEMPLATE = app
CONFIG += c++11
TARGET = FlvParser
OBJECTS_DIR = .objs
QT += core gui widgets network

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
    src/view/main_widget.cpp \
    src/controller/http_client.cpp \
    src/model/flv_header.cpp \
    src/model/flv_body.cpp \
    src/model/flv_body.cpp \
    src/model/flv_tag.cpp \
    src/model/flv_video.cpp \
    src/model/flv_audio.cpp \
    src/controller/flv_parser.cpp
HEADERS  += \
    src/view/main_widget.h \
    src/controller/http_client.h \
    src/model/flv_header.h \
    src/model/flv_body.h \
    src/model/flv_body.h \
    src/model/flv_tag.h \
    src/model/flv_data.h \
    src/model/flv_video.h \
    src/model/flv_audio.h \
    src/commons/error_code.h \
    src/controller/flv_parser.h
RESOURCES += \
    resource.qrc
ICON = icon.icns
