#-------------------------------------------------
#
# Project created by QtCreator 2018-05-28T10:46:13
#
#-------------------------------------------------

QT       += core gui network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SocialAPP
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    signinandsignup.cpp \
    signin.cpp \
    signup.cpp \
    email.cpp \
    emailaddress.cpp \
    smtpclient.cpp \
    confirmemail.cpp \
    interface.cpp \
    creategroup.cpp \
    createchannel.cpp \
    confirmlogout.cpp \
    send_user.cpp \
    send_group.cpp \
    send_channel.cpp

HEADERS += \
        mainwindow.h \
    signinandsignup.h \
    signin.h \
    signup.h \
    email.h \
    emailaddress.h \
    smtpclient.h \
    confirmemail.h \
    interface.h \
    creategroup.h \
    createchannel.h \
    confirmlogout.h \
    send_user.h \
    send_group.h \
    send_channel.h

FORMS += \
        mainwindow.ui \
    signinandsignup.ui \
    signin.ui \
    signup.ui \
    confirmemail.ui \
    getusers.ui \
    interface.ui \
    creategroup.ui \
    createchannel.ui \
    confirmlogout.ui \
    send_user.ui \
    send_group.ui \
    send_channel.ui

RESOURCES += \
    resource.qrc
