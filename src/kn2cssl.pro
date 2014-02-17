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
    aibase/coach.cpp \
    aibase/strategy.cpp \
    ai/strategy/strategydefault.cpp \
    ai/knowledge.cpp \
    aibase/skill.cpp \
    ai/strategy/strategytest.cpp \
    ai/skill/skillgotoposition.cpp \
    aibase/formationparser.cpp \
    ssl/formationdata.cpp \
    aibase/role.cpp \
    aibase/tactic.cpp \
    ai/tactic/tacticgoalie.cpp \
    ai/tactic/tacticcenterback.cpp \
    ai/tactic/tacticcenterforward.cpp \
    ai/tactic/tacticcentermidfielder.cpp \
    ai/tactic/tacticleftback.cpp \
    ai/tactic/tacticrightback.cpp \
    ai/tactic/tacticrightmidfielder.cpp \
    ai/tactic/tacticleftmidfielder.cpp \
    ai/tactic/tacticleftforward.cpp \
    ai/tactic/tacticrightforward.cpp \
    ai/navigation/navigationdefault.cpp \
    ai/navigation/rrt/tree.cpp \
    ai/navigation/rrt/rrtplan.cpp \
    ai/navigation/rrt/obstacle.cpp \
    ai/skill/skillkickball.cpp \
    aibase/behavior.cpp \
    ai/behavior/behaviorfreekick.cpp \
    ai/behavior/behaviorstop.cpp \
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
    geom/formation_dt.cpp \
    ai/behavior/behaviorkickoff.cpp \
    ssl/sslrefbox/game_state_our_UI.cpp \
    ai/behavior/behaviorpass.cpp \
    ai/behavior/behaviorshoot.cpp \
    ai/skill/skillturntopoint.cpp \
    ai/behavior/behaviorgotostaticball.cpp \
    ai/skill/skillturntoangle.cpp \
    ai/behavior/behaviorpenalty.cpp \
    ai/skill/skillmoveoncircle.cpp

HEADERS  += \
    etc/settings.h \
    etc/logger.h \
    etc/constants.h \
    etc/base.h \
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
    aibase/robotcommand.h \
    aibase/coach.h \
    aibase/strategy.h \
    ai/strategy/strategydefault.h \
    ai/knowledge.h \
    aibase/skill.h \
    ai/Skills.h \
    ai/strategy/strategytest.h \
    ai/skill/skillgotoposition.h \
    aibase/formationparser.h \
    ssl/formationdata.h \
    aibase/role.h \
    aibase/tactic.h \
    ai/Tactics.h \
    ai/tactic/tacticgoalie.h \
    ai/tactic/tacticcenterback.h \
    ai/tactic/tacticcenterforward.h \
    ai/tactic/tacticcentermidfielder.h \
    ai/tactic/tacticleftback.h \
    ai/tactic/tacticrightback.h \
    ai/tactic/tacticrightmidfielder.h \
    ai/tactic/tacticleftmidfielder.h \
    ai/tactic/tacticleftforward.h \
    ai/tactic/tacticrightforward.h \
    ai/navigation/navigationdefault.h \
    ai/navigation/rrt/tree.h \
    ai/navigation/rrt/rrtplan.h \
    ai/navigation/rrt/rrtools.h \
    ai/navigation/rrt/obstacle.h \
    ai/skill/skillkickball.h \
    aibase/behavior.h \
    ai/behavior/behaviorfreekick.h \
    ai/behavior/behaviorstop.h \
    ai/Behaviors.h \
    geom/voronoi_diagram_original.h \
    geom/voronoi_diagram.h \
    geom/vector_2d.h \
    geom/triangle_2d.h \
    geom/size_2d.h \
    geom/segment_2d.h \
    geom/sector_2d.h \
    geom/region_type.h \
    geom/region_2d.h \
    geom/rect_2d.h \
    geom/ray_2d.h \
    geom/polygon_2d.h \
    geom/matrix_2d.h \
    geom/line_2d.h \
    geom/geom.h \
    geom/formation_dt.h \
    geom/delaunay_triangulation.h \
    geom/convex_hull.h \
    geom/composite_region_2d.h \
    geom/circle_2d.h \
    geom/angle_deg.h \
    ai/behavior/behaviorkickoff.h \
    ssl/sslrefbox/game_state_our_UI.h \
    ai/behavior/behaviorpass.h \
    ai/behavior/behaviorshoot.h \
    ai/skill/skillturntopoint.h \
    ai/behavior/behaviorgotostaticball.h \
    ai/skill/skillturntoangle.h \
    ai/behavior/behaviorpenalty.h \
    ai/skill/skillmoveoncircle.h


FORMS    +=	ui/mainwindow.ui

OTHER_FILES += \
    ../config/settings.ini

RESOURCES += \
    resources.qrc




































































































































































