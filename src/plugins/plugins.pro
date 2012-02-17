TEMPLATE=subdirs

unix:!mac {
    SUBDIRS += dockmanager\
        unity
}
mac: SUBDIRS += mac
win32: SUBDIRS += windows
