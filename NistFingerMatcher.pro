QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle
linux: {
    INCLUDEPATH += /usr/lib/jvm/default-java/include/
    INCLUDEPATH += /usr/lib/jvm/default-java/include/linux/
    LIBS+=-L/usr/lib/jvm/default-java/lib/server/ -ljvm
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        javahandler.cpp \
        main.cpp \
        matchhandler.cpp \
        paramhandler.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=

HEADERS += \
    javahandler.h \
    matchhandler.h \
    paramhandler.h
