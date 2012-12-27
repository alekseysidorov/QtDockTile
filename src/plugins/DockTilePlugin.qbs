import qbs.base 1.0
import qbs.fileinfo 1.0 as FileInfo

Product {
    type: ["dynamiclibrary"]

    destination: "bin/docktile"
    cpp.visibility: "hidden"

    targetName: {
        if (qbs.debugInformation) {
            switch (qbs.targetOS) {
            case "windows":
                return name + "d";
            case "mac":
                return name + "_debug";
            }
        }
        return name;
    }

    Depends { name: "cpp" }
    Depends { name: "qt.core" }
    Depends { name: "qt.gui" }
    Depends { name: "qt.widgets" }
    Depends { name: "qtdocktile" }
}

