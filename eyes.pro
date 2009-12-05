# eyes Qt4 projext file

# //
# //  Copyright (C) 2009 - Bernd H Stramm
# //
#
# // This program is distributed under the terms of 
# // the GNU General Public License version 3 
# //
# // This software is distributed in the hope that it will be useful, 
# // but WITHOUT ANY WARRANTY; without even the implied warranty 
# // of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
# //


CONFIG += qt
LIBS += 
TARGET = eyes

# these next two lines are to get qmake to suppress debug symbols
QMAKE_CFLAGS_RELEASE -= -g
QMAKE_CXXFLAGS_RELEASE -= -g

FORMS += eyes.ui

TRANSLATIONS += eyes_en_US.ts \
	eyes_de_DE.ts \
	eyes_en_CA.ts

RESOURCES += eyes.qrc

SOURCES += eyes.cpp \
	runeyes.cpp \
	version.cpp

HEADERS += eyes.h \
	version.h
	

