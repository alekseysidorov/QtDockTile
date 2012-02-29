%modules = ( # path to module name map
    "QtDocktile" => "$basedir/src/lib",
); 

%moduleheaders = ( # restrict the module headers to those found in relative path
);

%classnames = (
    "qtdocktile.h" => "QtDocktile",
    "qtdockprovider.h" => "QtDockProvider",
);

%mastercontent = (
    "core" => "#include <QtCore/QtCore>\n",
);

%modulepris = (
    "QtDockTile" => "$basedir/modules/qt_docktile.pri",
);
