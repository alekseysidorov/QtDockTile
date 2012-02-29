QT.docktile.VERSION = 1.0.0
QT.docktile.MAJOR_VERSION = 1
QT.docktile.MINOR_VERSION = 0
QT.docktile.PATCH_VERSION = 0

QT.docktile.name = QtDockTile
QT.docktile.bins = $$QT_MODULE_BIN_BASE
QT.docktile.includes = $$QT_MODULE_INCLUDE_BASE $$QT_MODULE_INCLUDE_BASE/QtDockTile
QT.docktile.private_includes = $$QT_MODULE_INCLUDE_BASE/QtDockTile/$$QT.docktile.VERSION
QT.docktile.sources = $$QT_MODULE_BASE/src/lib
QT.docktile.libs = $$QT_MODULE_LIB_BASE
QT.docktile.plugins = $$QT_MODULE_PLUGIN_BASE
QT.docktile.imports = $$QT_MODULE_IMPORT_BASE
QT.docktile.depends = gui
QT.docktile.DEFINES = QT_DOCKTILE_LIB

QT_CONFIG += docktile
