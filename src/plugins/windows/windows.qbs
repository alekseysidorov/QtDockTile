import qbs.base 1.0
import "../DockTilePlugin.qbs" as DockTilePlugin

DockTilePlugin {
    name: "windowstaskbar"
    condition: qbs.targetOS === "windows"

    files: [
        "./jumplistsmenuexporter.h",
        "./temporaryicon.h",
        "./windowstaskbar.h",
        "./wrapper/handling.h",
        "./wrapper/_ICustomDestinationList.h",
        "./wrapper/_ITaskbarList4.h",
        "./wrapper/jumplistsmanager.h",
        "./wrapper/taskbar.h",
        "./wrapper/_winapi.h",
        "./jumplistsmenuexporter_p.h",
        "./jumplistsmenuexporter.cpp",
        "./temporaryicon.cpp",
        "./windowstaskbar.cpp",
        "./wrapper/handling.cpp",
        "./wrapper/jumplistsmanager.cpp",
        "./wrapper/taskbar.cpp",
        "./wrapper/_winapi.cpp"
    ]
}



