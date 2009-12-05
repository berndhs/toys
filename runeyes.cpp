#include "eyes.h"
#include "version.h"
#include <QLocale>
#include <QString>
#include <QDebug>


//
//  Copyright (C) 2009 - Bernd H Stramm 
//
// This program is distributed under the terms of 
// the GNU General Public License version 3 
//
// This software is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY; without even the implied warranty 
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
//
//

bool
checkversiononly (int argc, char*argv[])
{
   if (argc < 2) {
     return false;
   }
   QString a1(argv[1]);
   if (a1 == "-v" || a1 == "--version") {
     return true;
   }
   return false;
}

int 
main (int argc, char *argv[])
{
  QApplication App(argc, argv);
  if (checkversiononly(argc,argv)) {
    eyes::CLIVersion();
    exit(0);
  }
  QTranslator  trans;
  QString locale = QLocale::system().name();
  QString filename = QString("eyes_") + locale ;
  
  bool ok = trans.load (":" + filename);
  if (!ok) {
    trans.load(filename);
  }
  App.installTranslator(&trans);

  eyes::eyes TheEyes(&App);

  TheEyes.SetDelay(100);
  TheEyes.show();
  App.exec();

}
