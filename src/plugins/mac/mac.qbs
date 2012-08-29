import qbs.base 1.0
import "../DockTilePlugin.qbs" as DockTilePlugin

DockTilePlugin {
    name: "macdocktile"
    condition: qbs.targetOS === "mac"

    Depends { name: "cocoa" }

    files: [
        "macdocktile.h",
        "macdocktile.mm",
    ]

}


