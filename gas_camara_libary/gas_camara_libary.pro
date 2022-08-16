QT -= gui

TEMPLATE = lib
DEFINES += GAS_CAMARA_LIBARY_LIBRARY

CONFIG += c++11
#LIBS += -L/usr/lib/x86_64-linux-gnu/libjpeg.so -ljpeg
LIBS += -L/usr/lib/x86_64-linux-gnu  -lavcodec -lavformat -lavutil -lavcodec -ljpeg


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    capture.c \
    encode.c \
    func_tool.c \
    gas_camara_libary.c \
    libary_handler.c \
    queue.c \
    rgb_converter.c \
    save_snapshot.c \
    stage.c \
    write.c \
    yuv_converter.c

HEADERS += \
    capture.h \
    encode.h \
    func_tool.h \
    gas_camara_libary.h \
    libary_handler.h \
    queue.h \
    rgb_converter.h \
    save_snapshot.h \
    stage.h \
    write.h \
    yuv_converter.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
