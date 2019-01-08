TEMPLATE = subdirs
SUBDIRS = src/welle-gui

!android: {
SUBDIRS += \
    src/welle-cli \
    src/tests
}

DISTFILES += \
    $$PWD/README.md \
    $$PWD/RASPBERRY-PI.md\

macx {
    QMAKE_INFO_PLIST = $$(PWD)/welle-io.plist
}
