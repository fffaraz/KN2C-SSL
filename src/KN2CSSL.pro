#-------------------------------------------------
#
# Project created by QtCreator 2014-02-21T14:51:19
#
#-------------------------------------------------

QT       += core gui network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KN2CSSL
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11
LIBS += -lprotobuf

DESTDIR = ../bin
OBJECTS_DIR = ../tmp/.obj
MOC_DIR = ../tmp/.moc
RCC_DIR = ../tmp/.rcc
UI_DIR = ../tmp/.ui

SOURCES += main.cpp\
        ui/mainwindow.cpp \
    util/counter.cpp \
    etc/logger.cpp \
    geom/angle_deg.cpp \
    geom/circle_2d.cpp \
    geom/composite_region_2d.cpp \
    geom/convex_hull.cpp \
    geom/delaunay_triangulation.cpp \
    geom/line_2d.cpp \
    geom/matrix_2d.cpp \
    geom/polygon_2d.cpp \
    geom/ray_2d.cpp \
    geom/rect_2d.cpp \
    geom/sector_2d.cpp \
    geom/segment_2d.cpp \
    geom/test_convex_hull.cpp \
    geom/test_matrix_2d.cpp \
    geom/test_polygon_2d.cpp \
    geom/test_rect_2d.cpp \
    geom/test_rundom_convex_hull.cpp \
    geom/test_segment_2d.cpp \
    geom/test_triangle_2d.cpp \
    geom/test_vector_2d.cpp \
    geom/test_voronoi_diagram.cpp \
    geom/triangle_2d.cpp \
    geom/triangulation.cpp \
    geom/vector_2d.cpp \
    geom/voronoi_diagram_original.cpp \
    geom/voronoi_diagram_triangle.cpp

HEADERS  += ui/mainwindow.h \
    util/util.h \
    util/counter.h \
    etc/base.h \
    etc/constants.h \
    etc/logger.h \
    etc/settings.h \
    geom/angle_deg.h \
    geom/circle_2d.h \
    geom/composite_region_2d.h \
    geom/convex_hull.h \
    geom/delaunay_triangulation.h \
    geom/line_2d.h \
    geom/matrix_2d.h \
    geom/polygon_2d.h \
    geom/ray_2d.h \
    geom/rect_2d.h \
    geom/region_2d.h \
    geom/sector_2d.h \
    geom/segment_2d.h \
    geom/size_2d.h \
    geom/triangle_2d.h \
    geom/triangulation.h \
    geom/vector_2d.h \
    geom/voronoi_diagram.h \
    geom/voronoi_diagram_original.h \
    geom/voronoi_diagram_triangle.h

FORMS    += ui/mainwindow.ui

OTHER_FILES += \
    geom/Makefile.am \
    geom/Makefile.in
