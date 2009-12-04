#include "eyes.h"
#include <QLocale>
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


int 
main (int argc, char *argv[])
{
  QApplication App(argc, argv);
  QTranslator  trans;
  QString locale = QLocale::system().name();
  QString filename = QString(":eyes_") + locale ;
  qDebug() << " language file " << filename;
  bool ok = trans.load (filename);
  qDebug ()  << " ok is " << ok;
  App.installTranslator(&trans);

  eyes::eyes TheEyes(&App);

  TheEyes.SetDelay(100);
qDebug() << " we are in " << locale;
  TheEyes.show();
  App.exec();

}
