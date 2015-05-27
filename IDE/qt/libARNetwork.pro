TARGET = arnetwork
TEMPLATE = lib
CONFIG = static

linux-g++ {
    include(/home/heefan/drone/drone_client/IDE/qt/common.pri)
}

macx{
    include(/Users/heefan/drone/drone_client/IDE/qt/common.pri)
}

SOURCES += \
    $$LibARNetwork_src/*.c

HEADERS += \
    $$LibARNetwork_src/*.h \

INCLUDEPATH += \
    /usr/include/ \
    /usr/local/include \
    $$LibARNetworkRoot/Build   #config.h

LIBS += -L/usr/local/lib  -lssl -lcrypto -pthreadss
