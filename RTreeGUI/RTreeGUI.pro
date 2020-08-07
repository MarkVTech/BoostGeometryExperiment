QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GraphicBox.cpp \
    GraphicPoint.cpp \
    RTreeScene.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    GraphicBox.h \
    GraphicPoint.h \
    MainWindow.h \
    RTreeScene.h

FORMS += \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += $$(BOOST_PATH)/include/boost-1_70
DEPENDPATH += $$(BOOST_PATH)/include/boost-1_70

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../RTreeContainer/release/ -lRTreeContainer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../RTreeContainer/debug/ -lRTreeContainer
else:unix:!macx: LIBS += -L$$OUT_PWD/../RTreeContainer/ -lRTreeContainer

INCLUDEPATH += $$PWD/../RTreeContainer
DEPENDPATH += $$PWD/../RTreeContainer

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../RTreeContainer/release/libRTreeContainer.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../RTreeContainer/debug/libRTreeContainer.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../RTreeContainer/release/RTreeContainer.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../RTreeContainer/debug/RTreeContainer.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../RTreeContainer/libRTreeContainer.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Common/release/ -lCommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Common/debug/ -lCommon
else:unix:!macx: LIBS += -L$$OUT_PWD/../Common/ -lCommon

INCLUDEPATH += $$PWD/../Common
DEPENDPATH += $$PWD/../Common

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Common/release/libCommon.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Common/debug/libCommon.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Common/release/Common.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Common/debug/Common.lib
else:unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../Common/libCommon.a
