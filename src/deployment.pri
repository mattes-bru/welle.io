# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/welle-io
!isEmpty(target.path): INSTALLS += target
