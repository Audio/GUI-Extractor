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
    UIA/ElementFactory.cpp \
    UIA/EButton.cpp \
    UIA/EUnknown.cpp \
    UIA/ESlider.cpp \
    UIA/EScrollBar.cpp \
    UIA/ERadio.cpp \
    UIA/EProgressBar.cpp \
    UIA/EMenuItem.cpp \
    UIA/EMenuBar.cpp \
    UIA/EEdit.cpp \
    UIA/EComboBox.cpp \
    UIA/ECheckBox.cpp \
    ElementHolder.cpp

HEADERS  += MainWindow.h \
    UIA/Client.h \
    UIA/includes.h \
    UIA/Element.h \
    TopWindowsItem.h \
    ElementTreeItem.h \
    UIA/ElementArea.h \
    Highlighter.h \
    UIA/ElementFactory.h \
    UIA/EButton.h \
    UIA/EUnknown.h \
    UIA/ESlider.h \
    UIA/EScrollBar.h \
    UIA/ERadio.h \
    UIA/EProgressBar.h \
    UIA/EMenuItem.h \
    UIA/EMenuBar.h \
    UIA/EEdit.h \
    UIA/EComboBox.h \
    UIA/ECheckBox.h \
    ElementHolder.h

FORMS    += MainWindow.ui

RESOURCES += \
    images/icons.qrc
