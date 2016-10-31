QT += widgets gui

CONFIG += c++11

HEADERS += \
    widget.h \
    connect.h \
    weather.h \
    settings.h \
    settingswidget.h \
    items.h \
    citytoip.h

SOURCES += \
    widget.cpp \
    main.cpp \
    connect.cpp \
    weather.cpp \
    settings.cpp \
    settingswidget.cpp \
    citytoip.cpp

FORMS += \
    settingswidget.ui
