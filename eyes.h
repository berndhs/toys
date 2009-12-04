#ifndef EYES_H
#define EYES_H

#include "ui_eyes.h"
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

#include <QApplication>
#include <QTimer>
#include <QProcess>
#include <QWidget>


namespace eyes {

  class eyes : public QWidget,  public Ui_EyesWindow {

Q_OBJECT

public:
 
   eyes (QApplication *app);

   void SetDelay (int msecs) { againDelay = msecs; }
   void SetCommand (QString cmd) { fortuneCommand = cmd; }

   public slots:

     
     void quit();
     void NotImplemented ();
     void MyUpdate();
     
  private:

   
     QApplication *pApp;
     QProcess     *pShell;

     QTimer    againTimer;
     int       againDelay;

     QString   fortuneCommand;


};


}

#endif
