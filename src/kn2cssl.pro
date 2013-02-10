#-------------------------------------------------
#
# Project created by QtCreator 2012-01-29T16:05:56
#
#-------------------------------------------------

QT       += core gui network script scripttools # xml opengl

TARGET = kn2cssl
TEMPLATE = app
#CONFIG   += qt warn_on incremental link_prl
#MAKEFILE_GENERATOR = UNIX
#TARGET_PLATFORM  = unix
#QMAKE_INCREMENTAL_STYLE = sublib
QMAKE_CXXFLAGS += -std=c++0x

CONFIG += debug
#QMAKE_CXXFLAGS += --coverage
#QMAKE_LFLAGS += --coverage

#CONFIG   += release

#QMAKE_CFLAGS    -= -O2 -O1
#QMAKE_CXXFLAGS  -= -O2 -O1
##QMAKE_CFLAGS  += -O3 -m64
##QMAKE_LFLAGS  += -O3 -m64
#QMAKE_CFLAGS  += -O3
#QMAKE_LFLAGS  += -O3
#QMAKE_CXXFLAGS += -O3

#QMAKE_CXXFLAGS += -O3
#QMAKE_CXXFLAGS += -m64
#QMAKE_CXXFLAGS += -pipe
#QMAKE_CXXFLAGS += -mmmx -msse -msse2 -msse3 -mssse3 -msse4 -msse4.1 -msse4.2 -mpclmul # -mavx -mavx2 -maes -mfsgsbase -mrdrnd
#QMAKE_CXXFLAGS += -mfpmath=sse
#QMAKE_CXXFLAGS += -fargument-noalias-global
#QMAKE_CXXFLAGS += -fomit-frame-pointer
##QMAKE_CXXFLAGS += -fwhole-program #fail!
#QMAKE_CXXFLAGS += -march=native
#QMAKE_CXXFLAGS += -mtune=native


#load(qt_config)


DESTDIR = ../bin
OBJECTS_DIR = ../tmp/.obj
MOC_DIR = ../tmp/.moc
RCC_DIR = ../tmp/.rcc
UI_DIR = ../tmp/.ui

LIBS += -lprotobuf

INCLUDEPATH += ssl
INCLUDEPATH += ssl/sslvision
INCLUDEPATH += ssl/sslvision/messages
INCLUDEPATH += ssl/sslrefbox
INCLUDEPATH += etc
INCLUDEPATH += ui
INCLUDEPATH += util
INCLUDEPATH += qextserialport
INCLUDEPATH += geom
INCLUDEPATH += output
INCLUDEPATH += grSim
INCLUDEPATH += ai
INCLUDEPATH += aibase
INCLUDEPATH += ai/skill
INCLUDEPATH += ai/role
INCLUDEPATH += ai/tactic
INCLUDEPATH += ai/play
INCLUDEPATH += ai/navigation
INCLUDEPATH += ai/strategy

SOURCES +=	main.cpp \
    etc/logger.cpp \
    geom/voronoi_diagram_original.cpp \
    geom/vector_2d.cpp \
    geom/triangle_2d.cpp \
    geom/segment_2d.cpp \
    geom/sector_2d.cpp \
    geom/rect_2d.cpp \
    geom/ray_2d.cpp \
    geom/polygon_2d.cpp \
    geom/matrix_2d.cpp \
    geom/line_2d.cpp \
    geom/delaunay_triangulation.cpp \
    geom/convex_hull.cpp \
    geom/composite_region_2d.cpp \
    geom/circle_2d.cpp \
    geom/angle_deg.cpp \
    grSim/grSim_Replacement.pb.cc \
    grSim/grSim_Packet.pb.cc \
    grSim/grSim_Commands.pb.cc \
    qextserialport/serialport.cpp \
    qextserialport/qextserialport.cpp \
    qextserialport/qextserialenumerator_unix.cpp \
    qextserialport/posix_qextserialport.cpp \
    ssl/sslreceiver.cpp \
    ssl/sslrefbox.cpp \
    ssl/sslvision.cpp \
    ssl/sslvision/messages/messages_robocup_ssl_wrapper.pb.cc \
    ssl/sslvision/messages/messages_robocup_ssl_refbox_log.pb.cc \
    ssl/sslvision/messages/messages_robocup_ssl_geometry.pb.cc \
    ssl/sslvision/messages/messages_robocup_ssl_detection.pb.cc \
    ui/mainwindow.cpp \
    ui/renderarea.cpp \
    util/fpscounter.cpp \
    aibase/soccer.cpp \
    ssl/worldmodel.cpp \
    ssl/visionrecorder.cpp \
    aibase/agent.cpp \
    output/wpacket.cpp \
    output/transmitter.cpp \
    output/grsim.cpp \
    output/grpacket.cpp \
    aibase/scriptengine.cpp \
    ssl/sslrefbox/game_state.cpp \
    ssl/sslvision/visionresult.cpp \
    ssl/mobileobject.cpp \
    ssl/ball.cpp \
    ssl/robot.cpp \
    ssl/visiontracker.cpp \
    output/controller.cpp \
    aibase/ai.cpp \
    aibase/statemachine.cpp \
    aibase/navigation.cpp \
    aibase/skill.cpp \
    ai/skill/skillnull.cpp \
    ai/skill/skillballtracking.cpp \
    aibase/coach.cpp \
    ai/skill/skillgotoposition.cpp \
    aibase/tactic.cpp \
    aibase/play.cpp \
    aibase/strategy.cpp \
    ai/strategy/strategydefault.cpp \
    ai/navigation/navigationdefault.cpp \
    aibase/role.cpp \
    ai/skill/skillcircle.cpp \
    ai/role/rolegoalie.cpp \
    ai/tactic/tacticnull.cpp \
    ai/role/rolenull.cpp \
    ai/play/playnull.cpp \
    ai/play/playstop.cpp \
    ai/knowledge.cpp \
    ai/tactic/tacticstop.cpp \
    ai/tactic/tacticdefend.cpp \
    ai/skill/skillgoalie.cpp \
    ai/tactic/tacticgoalie.cpp \
    ai/role/roledefender.cpp \
    ai/play/playhalt.cpp \
    ai/play/playkickoffour.cpp \
    ai/play/playkickoffopp.cpp \
    ai/play/playpenaltyour.cpp \
    ai/play/playpenaltyopp.cpp \
    ai/play/playgameon.cpp \
    ai/play/playfreekickour.cpp \
    ai/play/playfreekickopp.cpp \
    ai/role/roleattacker.cpp \
    ai/tactic/tacticattack.cpp \
    ai/tactic/tacticblock.cpp \
    ai/skill/skillwait.cpp \
    ai/skill/skillkick.cpp \
    ai/tactic/tactictest.cpp \
    ai/play/playtest.cpp \
    ai/skill/skillgoaliepenalty.cpp

HEADERS  += \
    etc/settings.h \
    etc/logger.h \
    etc/constants.h \
    etc/base.h \
    geom/voronoi_diagram_original.h \
    geom/voronoi_diagram.h \
    geom/vector_2d.h \
    geom/triangle_2d.h \
    geom/size_2d.h \
    geom/segment_2d.h \
    geom/sector_2d.h \
    geom/region_2d.h \
    geom/rect_2d.h \
    geom/ray_2d.h \
    geom/polygon_2d.h \
    geom/matrix_2d.h \
    geom/line_2d.h \
    geom/geom.h \
    geom/delaunay_triangulation.h \
    geom/convex_hull.h \
    geom/composite_region_2d.h \
    geom/circle_2d.h \
    geom/angle_deg.h \
    grSim/grSim_Replacement.pb.h \
    grSim/grSim_Packet.pb.h \
    grSim/grSim_Commands.pb.h \
    qextserialport/serialport.h \
    qextserialport/qextserialport_global.h \
    qextserialport/qextserialport.h \
    qextserialport/qextserialenumerator.h \
    ssl/worldmodel.h \
    ssl/sslreceiver.h \
    ssl/sslrefbox.h \
    ssl/sslrefbox/ref_protocol.h \
    ssl/sslrefbox/game_state.h \
    ssl/sslrefbox/commands.h \
    ssl/sslvision/visionframe.h \
    ssl/sslvision.h \
    ssl/sslvision/messages/messages_robocup_ssl_wrapper.pb.h \
    ssl/sslvision/messages/messages_robocup_ssl_refbox_log.pb.h \
    ssl/sslvision/messages/messages_robocup_ssl_geometry.pb.h \
    ssl/sslvision/messages/messages_robocup_ssl_detection.pb.h \
    ui/mainwindow.h \
    ui/renderarea.h \
    util/util.h \
    util/fpscounter.h \
    ssl/sslvision/visionobject.h \
    aibase/soccer.h \
    ssl/visionrecorder.h \
    aibase/agent.h \
    output/wpacket.h \
    output/transmitter.h \
    output/grsim.h \
    output/outputbuffer.h \
    output/grpacket.h \
    aibase/scriptengine.h \
    ssl/sslvision/visionresult.h \
    ssl/sslvision/visionball.h \
    ssl/sslvision/visionrobot.h \
    ssl/mobileobject.h \
    ssl/ball.h \
    ssl/robot.h \
    ssl/visiontracker.h \
    output/controller.h \
    ssl/position.h \
    aibase/ai.h \
    aibase/statemachine.h \
    aibase/navigation.h \
    aibase/skill.h \
    aibase/robotcommand.h \
    ai/skill/skillnull.h \
    ai/skill/skillballtracking.h \
    aibase/coach.h \
    ai/skill/skillgotoposition.h \
    aibase/tactic.h \
    ai/skills.h \
    ai/tactics.h \
    aibase/play.h \
    ai/plays.h \
    ai/roles.h \
    aibase/strategy.h \
    ai/strategy/strategydefault.h \
    ai/navigation/navigationdefault.h \
    aibase/role.h \
    ai/strategies.h \
    ai/skill/skillcircle.h \
    ai/role/rolegoalie.h \
    ai/tactic/tacticnull.h \
    ai/role/rolenull.h \
    ai/play/playnull.h \
    ai/play/playstop.h \
    ai/knowledge.h \
    ai/tactic/tacticstop.h \
    ai/tactic/tacticdefend.h \
    ai/skill/skillgoalie.h \
    ai/tactic/tacticgoalie.h \
    ai/role/roledefender.h \
    ai/play/playhalt.h \
    ai/play/playkickoffour.h \
    ai/play/playkickoffopp.h \
    ai/play/playpenaltyour.h \
    ai/play/playpenaltyopp.h \
    ai/play/playgameon.h \
    ai/play/playfreekickour.h \
    ai/play/playfreekickopp.h \
    ai/role/roleattacker.h \
    ai/tactic/tacticattack.h \
    ai/tactic/tacticblock.h \
    ai/skill/skillwait.h \
    aibase/strategyresult.h \
    ai/skill/skillkick.h \
    ai/tactic/tactictest.h \
    ai/play/playtest.h \
    ai/skill/skillgoaliepenalty.h

FORMS    +=	ui/mainwindow.ui

OTHER_FILES += \
    ../config/settings.ini

RESOURCES += \
    resources.qrc





































































































































































