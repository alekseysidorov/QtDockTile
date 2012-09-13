import qbs.base 1.0
import "../DockTilePlugin.qbs" as DockTilePlugin

DockTilePlugin {
    name: "unity"
    condition: qbs.targetOS === "linux"

    Depends { name: "dbusmenu.qt" }    

    files: [
        "unitylauncher.h",
        "unitylauncher.cpp",
    ]


}



