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
    ElementHolder.cpp \
    XUL/Item.cpp \
    XUL/Exporter.cpp \
    UIA/EWindow.cpp \
    UIA/ETreeItem.cpp \
    UIA/ETree.cpp \
    UIA/EToolTip.cpp \
    UIA/EToolBar.cpp \
    UIA/ETitleBar.cpp \
    UIA/EThumb.cpp \
    UIA/ETable.cpp \
    UIA/ETabItem.cpp \
    UIA/ETab.cpp \
    UIA/EStatusBar.cpp \
    UIA/ESplitButton.cpp \
    UIA/ESeparator.cpp \
    UIA/EPane.cpp \
    UIA/EListItem.cpp \
    UIA/EList.cpp \
    UIA/EImage.cpp \
    UIA/EHyperlink.cpp \
    UIA/EHeaderItem.cpp \
    UIA/EHeader.cpp \
    UIA/EGroup.cpp \
    UIA/EDocument.cpp \
    UIA/EDataItem.cpp \
    UIA/EDataGrid.cpp \
    UIA/ECalendar.cpp \
    UIA/EMenu.cpp \
    UIA/ESpinner.cpp \
    UIA/EText.cpp \
    XUL/MenuExporter.cpp \
    AboutDialog.cpp

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
    ElementHolder.h \
    XUL/Item.h \
    XUL/Exporter.h \
    UIA/EImage.h \
    UIA/EHyperlink.h \
    UIA/EHeaderItem.h \
    UIA/EHeader.h \
    UIA/EGroup.h \
    UIA/EDocument.h \
    UIA/EDataItem.h \
    UIA/EDataGrid.h \
    UIA/ECalendar.h \
    UIA/EWindow.h \
    UIA/ETreeItem.h \
    UIA/ETree.h \
    UIA/EToolTip.h \
    UIA/EToolBar.h \
    UIA/ETitleBar.h \
    UIA/EThumb.h \
    UIA/ETable.h \
    UIA/ETabItem.h \
    UIA/ETab.h \
    UIA/EStatusBar.h \
    UIA/ESplitButton.h \
    UIA/ESeparator.h \
    UIA/EPane.h \
    UIA/EListItem.h \
    UIA/EList.h \
    UIA/EMenu.h \
    UIA/ESpinner.h \
    UIA/EText.h \
    LogType.h \
    XUL/MenuExporter.h \
    AboutDialog.h

FORMS    += MainWindow.ui \
    AboutDialog.ui

RESOURCES += resources/icons.qrc \
    resources/styles.qrc
