import qbs.base 1.0

Project {

    moduleSearchPaths: "qbs/modules"

    references: [
        "src/lib.qbs",
        "src/plugins/mac/mac.qbs",
        "src/plugins/windows/windows.qbs",
        "src/plugins/unity/unity.qbs",
    ]
}

