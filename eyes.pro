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


CONFIG += qt release
LIBS += 
TARGET = eyes

  QMAKE_CFLAGS_RELEASE -= -g
  QMAKE_CXXFLAGS_RELEASE -= -g

FORMS += eyes.ui

SOURCES += eyes.cpp runeyes.cpp vec2.cpp

HEADERS += eyes.h vec2.h


