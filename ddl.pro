QT       += core gui
QT   +=network
QT+=widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
include (qmarkdowntextedit-main/qmarkdowntextedit-headers.pri)
include (qmarkdowntextedit-main/qmarkdowntextedit-sources.pri)
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QXLSX_PARENTPATH=./         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./source/  # current QXlsx source path is ./source/
include(./QXlsx.pri)
SOURCES += \
    about.cpp \
    addclasstable.cpp\
    addmyclass.cpp \
    establishquest.cpp \
    life.cpp \
    main.cpp \
    mainwindow.cpp \
    myclass.cpp \
    note.cpp \
    task.cpp \
    weekreport.cpp \
    deletemyclass.cpp \
     deletenotecheck.cpp \
       changetabname.cpp\
       innernote.cpp \
innertab.cpp\
apiclient.cpp\
datacollector.cpp\
reportgenerator.cpp\
innermarkdown.cpp

HEADERS += \
    about.h \
    addclasstable.h\
    addmyclass.h \
    establishquest.h \
    life.h \
    mainwindow.h \
    myclass.h \
    note.h \
    task.h \
    weekreport.h\
    deletemyclass.h \
     deletenotecheck.h \
       changetabname.h\
       innernote.h \
innertab.h\
apiclient.h\
datacollector.h\
reportgenerator.h\
innermarkdown.h

FORMS += \
    about.ui \
    addmyclass.ui \
    addclasstable.ui \
    establishquest.ui \
    life.ui \
    mainwindow.ui \
    myclass.ui \
    note.ui \
    task.ui \
    weekreport.ui \
    deletemyclass.ui \
     deletenotecheck.ui\
       changetabname.ui\
       innernote.ui \
innertab.ui\
innermarkdown.ui\

TRANSLATIONS += \
    ddl_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    hh.qrc \
    title.qrc \
    22.png


