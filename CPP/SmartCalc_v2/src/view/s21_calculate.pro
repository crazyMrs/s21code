QT       += core gui widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
TARGET = SmartCalc_v2.0

SOURCES += \
    ../model/model.cc \
    ../model/kredit_model.cc \
    kredit.cc \
    main.cc \
    mainwindow.cc \
    qcustomplot.cpp

HEADERS += \
    ../controller/controller.h \
    ../controller/kredit_controller.h \
    ../model/model.h \
    ../model/kredit_model.h \
    kredit.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    kredit.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
