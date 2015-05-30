linux-g++ {
    include(/home/heefan/drone/drone_client/IDE/qt/common.pri)
}

macx{
    include(/Users/heefan/drone/drone_client/IDE/qt/common.pri)
}

TARGET = arnetwork
TEMPLATE = lib
CONFIG += static
CONFIG += debug
DESTDIR = $$SdkInstallPath_lib

SOURCES += \
    $$LibARNetwork_src/*.c

HEADERS += \
#    $$LibARNetwork_src/*.h \
#    $$LibARNetwork_inc/libARNetwork/*.h \

INCLUDEPATH += \
    $$SdkInstallPath_inc \
    $$LibARNetwork/Build   \ #config.h
    $$LibARNetwork_src \     #private header
#    $$LibARNetwork_inc \
#    $$LibARNetworkAL_inc \
#    $$LibARSAL_inc \

#LIBS += \
#    -L$$LibARSAL_lib_path -larsal \
#    -L$$LibARNetworkAL_lib_path -larnetworkal
