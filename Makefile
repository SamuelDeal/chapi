#############################################################################
# Makefile for building: chapi
# Generated by qmake (3.0) (Qt 5.2.1)
# Project:  chapi.pro
# Template: app
# Command: /usr/lib/i386-linux-gnu/qt5/bin/qmake -o Makefile chapi.pro
#############################################################################

MAKEFILE      = Makefile

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = 
CFLAGS        = -pipe -O2 -Wall -W -fPIE $(DEFINES)
CXXFLAGS      = -pipe -std=c++11 -Wall -Wextra -O2 -Wall -W -fPIE $(DEFINES)
INCPATH       = -I/usr/lib/i386-linux-gnu/qt5/mkspecs/linux-g++ -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/lib/i386-linux-gnu/qt5/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = src/main.cpp \
		src/helloer.cpp \
		src/networkconfig.cpp \
		src/etime.cpp \
		src/nlprotocol.cpp \
		src/config.cpp \
		src/systemutils.cpp \
		src/log.cpp \
		src/videohub.cpp \
		src/server.cpp \
		src/servercnx.cpp \
		src/chapi.cpp 
OBJECTS       = main.o \
		helloer.o \
		networkconfig.o \
		etime.o \
		nlprotocol.o \
		config.o \
		systemutils.o \
		log.o \
		videohub.o \
		server.o \
		servercnx.o \
		chapi.o
DIST          = /usr/lib/i386-linux-gnu/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/common/shell-unix.conf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/common/unix.conf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/common/linux.conf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/common/g++-base.conf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/common/g++-unix.conf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/qconfig.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_platformsupport_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_qml.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_qmltest.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_quick.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/qt_functions.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/qt_config.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/linux-g++/qmake.conf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/spec_post.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/default_pre.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/resolve_config.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/default_post.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/warn_on.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/testcase_targets.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/exceptions.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/yacc.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/lex.prf \
		chapi.pro \
		chapi.pro
QMAKE_TARGET  = chapi
DESTDIR       = #avoid trailing-slash linebreak
TARGET        = chapi


first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: chapi.pro /usr/lib/i386-linux-gnu/qt5/mkspecs/linux-g++/qmake.conf /usr/lib/i386-linux-gnu/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/common/shell-unix.conf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/common/unix.conf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/common/linux.conf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/common/g++-base.conf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/common/g++-unix.conf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/qconfig.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_platformsupport_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_qml.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_qmltest.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_quick.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/qt_functions.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/qt_config.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/linux-g++/qmake.conf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/spec_post.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/default_pre.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/resolve_config.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/default_post.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/warn_on.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/testcase_targets.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/exceptions.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/yacc.prf \
		/usr/lib/i386-linux-gnu/qt5/mkspecs/features/lex.prf \
		chapi.pro
	$(QMAKE) -o Makefile chapi.pro
/usr/lib/i386-linux-gnu/qt5/mkspecs/features/spec_pre.prf:
/usr/lib/i386-linux-gnu/qt5/mkspecs/common/shell-unix.conf:
/usr/lib/i386-linux-gnu/qt5/mkspecs/common/unix.conf:
/usr/lib/i386-linux-gnu/qt5/mkspecs/common/linux.conf:
/usr/lib/i386-linux-gnu/qt5/mkspecs/common/gcc-base.conf:
/usr/lib/i386-linux-gnu/qt5/mkspecs/common/gcc-base-unix.conf:
/usr/lib/i386-linux-gnu/qt5/mkspecs/common/g++-base.conf:
/usr/lib/i386-linux-gnu/qt5/mkspecs/common/g++-unix.conf:
/usr/lib/i386-linux-gnu/qt5/mkspecs/qconfig.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_concurrent_private.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_core.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_core_private.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_dbus_private.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_gui.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_gui_private.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_network.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_network_private.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_opengl_private.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_platformsupport_private.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_printsupport_private.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_qml.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_qmltest.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_quick.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_sql.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_sql_private.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_testlib_private.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_widgets_private.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_xml.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/modules/qt_lib_xml_private.pri:
/usr/lib/i386-linux-gnu/qt5/mkspecs/features/qt_functions.prf:
/usr/lib/i386-linux-gnu/qt5/mkspecs/features/qt_config.prf:
/usr/lib/i386-linux-gnu/qt5/mkspecs/linux-g++/qmake.conf:
/usr/lib/i386-linux-gnu/qt5/mkspecs/features/spec_post.prf:
/usr/lib/i386-linux-gnu/qt5/mkspecs/features/exclusive_builds.prf:
/usr/lib/i386-linux-gnu/qt5/mkspecs/features/default_pre.prf:
/usr/lib/i386-linux-gnu/qt5/mkspecs/features/resolve_config.prf:
/usr/lib/i386-linux-gnu/qt5/mkspecs/features/default_post.prf:
/usr/lib/i386-linux-gnu/qt5/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/lib/i386-linux-gnu/qt5/mkspecs/features/warn_on.prf:
/usr/lib/i386-linux-gnu/qt5/mkspecs/features/testcase_targets.prf:
/usr/lib/i386-linux-gnu/qt5/mkspecs/features/exceptions.prf:
/usr/lib/i386-linux-gnu/qt5/mkspecs/features/yacc.prf:
/usr/lib/i386-linux-gnu/qt5/mkspecs/features/lex.prf:
chapi.pro:
qmake: FORCE
	@$(QMAKE) -o Makefile chapi.pro

qmake_all: FORCE

dist: 
	@test -d .tmp/chapi1.0.0 || mkdir -p .tmp/chapi1.0.0
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/chapi1.0.0/ && (cd `dirname .tmp/chapi1.0.0` && $(TAR) chapi1.0.0.tar chapi1.0.0 && $(COMPRESS) chapi1.0.0.tar) && $(MOVE) `dirname .tmp/chapi1.0.0`/chapi1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/chapi1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: 

####### Compile

main.o: src/main.cpp src/chapi.h \
		src/config.h \
		src/helloer.h \
		src/etime.h \
		src/server.h \
		src/videohub.h \
		src/nlprotocol.h \
		src/log.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o src/main.cpp

helloer.o: src/helloer.cpp src/helloer.h \
		src/etime.h \
		src/const.h \
		src/log.h \
		src/systemutils.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o helloer.o src/helloer.cpp

networkconfig.o: src/networkconfig.cpp src/networkconfig.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o networkconfig.o src/networkconfig.cpp

etime.o: src/etime.cpp src/etime.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o etime.o src/etime.cpp

nlprotocol.o: src/nlprotocol.cpp src/nlprotocol.h \
		src/stringutils.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o nlprotocol.o src/nlprotocol.cpp

config.o: src/config.cpp src/config.h \
		src/const.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o config.o src/config.cpp

systemutils.o: src/systemutils.cpp src/systemutils.h \
		src/log.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o systemutils.o src/systemutils.cpp

log.o: src/log.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o log.o src/log.cpp

videohub.o: src/videohub.cpp src/videohub.h \
		src/nlprotocol.h \
		src/const.h \
		src/log.h \
		src/systemutils.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o videohub.o src/videohub.cpp

server.o: src/server.cpp src/server.h \
		src/const.h \
		src/servercnx.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o server.o src/server.cpp

servercnx.o: src/servercnx.cpp src/servercnx.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o servercnx.o src/servercnx.cpp

chapi.o: src/chapi.cpp src/chapi.h \
		src/config.h \
		src/helloer.h \
		src/etime.h \
		src/server.h \
		src/videohub.h \
		src/nlprotocol.h \
		src/log.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o chapi.o src/chapi.cpp

####### Install

install_target: first FORCE
	@test -d $(INSTALL_ROOT)/usr/bin/chapi || mkdir -p $(INSTALL_ROOT)/usr/bin/chapi
	-$(INSTALL_PROGRAM) "$(QMAKE_TARGET)" "$(INSTALL_ROOT)/usr/bin/chapi/$(QMAKE_TARGET)"
	-$(STRIP) "$(INSTALL_ROOT)/usr/bin/chapi/$(QMAKE_TARGET)"

uninstall_target: FORCE
	-$(DEL_FILE) "$(INSTALL_ROOT)/usr/bin/chapi/$(QMAKE_TARGET)"
	-$(DEL_DIR) $(INSTALL_ROOT)/usr/bin/chapi/ 


install:  install_target  FORCE

uninstall: uninstall_target   FORCE

FORCE:

