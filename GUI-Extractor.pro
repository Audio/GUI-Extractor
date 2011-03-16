#-------------------------------------------------
#
# Project created by QtCreator 2011-03-07T19:16:22
#
#-------------------------------------------------

QT       += core gui

TARGET   = GUI-Extractor
TEMPLATE = app


SOURCES  += main.cpp \
    MainWindow.cpp \
    UIA/Client.cpp \
    UIA/Element.cpp \
    TopWindowsItem.cpp \
    ElementTreeItem.cpp \
    UIA/ElementArea.cpp \
    Highlighter.cpp \
    UIA/ElementFactory.cpp

HEADERS  += MainWindow.h \
    UIA/Client.h \
    UIA/includes.h \
    UIA/Element.h \
    TopWindowsItem.h \
    ElementTreeItem.h \
    UIA/ElementArea.h \
    Highlighter.h \
    UIA/ElementFactory.h

FORMS    += MainWindow.ui
