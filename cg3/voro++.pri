#
# This file is part of cg3lib: https://github.com/cg3hci/cg3lib
# This Source Code Form is subject to the terms of the GNU GPL 3.0
#
# @author Alessandro Muntoni (muntoni.alessandro@gmail.com)
# @author Stefano Nuvoli (stefano.nuvoli@gmail.com)
#
isEmpty(VOROPLUSPLUS_PATH) {
    exists($$(VOROPLUSPLUS_HOME)) {
        VOROPLUSPLUS_PATH = $$(VOROPLUSPLUS_HOME)
    }
}

exists($$VOROPLUSPLUS_PATH){
    !contains(DEFINES, CG3_CORE_DEFINED){
        error(Voro++ module requires Core module)
    }

    DEFINES += CG3_VORO_DEFINED
    MODULES += CG3_VORO++

    #voro++
    INCLUDEPATH += $$VOROPLUSPLUS_PATH
    LIBS += -L$$VOROPLUSPLUS_PATH/ -lvoro++

    HEADERS += \
        $$PWD/voro++/voronoi_cell3.h \
        $$PWD/voro++/voronoi_diagram3.h \
        $$PWD/voro++/internal/voro_parser.h

    SOURCES += \
        $$PWD/voro++/voronoi_cell3.cpp \
        $$PWD/voro++/voronoi_diagram3.cpp \
        $$PWD/voro++/internal/voro_parser.cpp
}