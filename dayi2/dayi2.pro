#-------------------------------------------------
#
# Project created by QtCreator 2019-10-06T10:22:55
#
#-------------------------------------------------

#QT       += core gui
qtHaveModule(printsupport):  QT+= core gui webchannel widgets websockets multimedia printsupport  webenginewidgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dayi2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += "BUILD_DIR=\"\\\""$$OUT_PWD"\\\"\""
SOURCES += \
        main.cpp \
        mainwindow.cpp \
    aliyun/osschannel.cpp \
    audioctl/audiorecorder.cpp \
    audioctl/qaudiolevel.cpp \
    print/fontPrint.cpp \
    print/orderpix.cpp \
    webchannel/shared/websocketclientwrapper.cpp \
    webchannel/shared/websockettransport.cpp \
    webchannel/channeldialog.cpp \
    basehelper.cpp \
    dispatchprocess.cpp \
    main.cpp \
    mainwindow.cpp \
    dyconfig.cpp

HEADERS += \
        mainwindow.h \
    aliyun/osschannel.h \
    audioctl/audiorecorder.h \
    audioctl/qaudiolevel.h \
    print/fontPrint.h \
    print/orderpix.h \
    webchannel/shared/websocketclientwrapper.h \
    webchannel/shared/websockettransport.h \
    webchannel/channeldialog.h \
    basehelper.h \
    dispatchprocess.h \
    mainwindow.h \
    dyconfig.h \
    common.h

FORMS += \
        mainwindow.ui
INCLUDEPATH += $$PWD/aliyun/include/curl
INCLUDEPATH += $$PWD/aliyun/include/apr
INCLUDEPATH += $$PWD/aliyun/include/aprutil
INCLUDEPATH += $$PWD/aliyun/include/mxml
INCLUDEPATH += $$PWD/aliyun/include
INCLUDEPATH += $$PWD/aliyun/include/oss_c_sdk

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/aliyun/lib/release/ -loss_c_sdk
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/aliyun/lib/debug/ -loss_c_sdk

INCLUDEPATH += $$PWD/aliyun/lib/Release
DEPENDPATH += $$PWD/aliyun/lib/Release

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/aliyun/lib/release/liboss_c_sdk.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/aliyun/lib/debug/liboss_c_sdk.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/aliyun/lib/release/oss_c_sdk.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/aliyun/lib/debug/oss_c_sdk.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/aliyun/lib/release/ -llibapr-1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/aliyun/lib/debug/ -llibapr-1

INCLUDEPATH += $$PWD/aliyun/lib/Release
DEPENDPATH += $$PWD/aliyun/lib/Release

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/aliyun/lib/release/liblibapr-1.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/aliyun/lib/debug/liblibapr-1.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/aliyun/lib/release/libapr-1.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/aliyun/lib/debug/libapr-1.lib

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/aliyun/lib/release/ -lcurl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/aliyun/lib/debug/ -lcurl
else:unix: LIBS += -L$$PWD/aliyun/lib/ -lcurl

INCLUDEPATH += $$PWD/aliyun/lib/Release
DEPENDPATH += $$PWD/aliyun/lib/Release

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/aliyun/lib/release/libcurl.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/aliyun/lib/debug/libcurl.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/aliyun/lib/release/curl.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/aliyun/lib/debug/curl.lib
else:unix: PRE_TARGETDEPS += $$PWD/aliyun/lib/libcurl.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/aliyun/lib/release/ -lmxml1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/aliyun/lib/debug/ -lmxml1
else:unix: LIBS += -L$$PWD/aliyun/lib/ -lmxml1

INCLUDEPATH += $$PWD/aliyun/lib/Release
DEPENDPATH += $$PWD/aliyun/lib/Release

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/aliyun/lib/release/libmxml1.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/aliyun/lib/debug/libmxml1.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/aliyun/lib/release/mxml1.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/aliyun/lib/debug/mxml1.lib
else:unix: PRE_TARGETDEPS += $$PWD/aliyun/lib/libmxml1.a

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/aliyun/lib/release/ -llibaprutil-1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/aliyun/lib/debug/ -llibaprutil-1
else:unix: LIBS += -L$$PWD/aliyun/lib/ -llibaprutil-1

INCLUDEPATH += $$PWD/aliyun/lib/Release
DEPENDPATH += $$PWD/aliyun/lib/Release

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/aliyun/lib/release/liblibaprutil-1.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/aliyun/lib/debug/liblibaprutil-1.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/aliyun/lib/release/libaprutil-1.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/aliyun/lib/debug/libaprutil-1.lib
else:unix: PRE_TARGETDEPS += $$PWD/aliyun/lib/liblibaprutil-1.a

