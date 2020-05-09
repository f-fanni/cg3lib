TARGET = cg3lib

TEMPLATE = lib
#CONFIG += staticlib

CONFIG += CG3_STATIC CG3_ALL
QMAKE_CXXFLAGS += -std=gnu++11

include (../cg3.pri)

