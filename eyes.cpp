
#include "eyes.h"
#include <QMessageBox>
#include <QByteArray>
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
#include <iostream>
using namespace std;

namespace eyes {

  eyes::eyes (QApplication *app)
    :pApp(app)
    ,pShell(0)
    ,againDelay(1000)           // 10 minutes
    ,fortuneCommand (QString("fortune"))
  {
    setupUi (this);

    connect (quitButton, SIGNAL(clicked()), this, SLOT(quit()));
    connect (optionsButton, SIGNAL(clicked()), this, SLOT(NotImplemented()));
    connect (againButton, SIGNAL(clicked()), this, SLOT(NotImplemented()));

    connect (&againTimer, SIGNAL(timeout()), this, SLOT(MyUpdate()));
    setCursor (Qt::WhatsThisCursor);
    theLabel->setCursor(Qt::CrossCursor);
    againTimer.start(againDelay);
    pShell = new QProcess(this);
  }


  void
  eyes::NotImplemented ()
  {
    QMessageBox msgBox;
    QTimer::singleShot(15000, &msgBox, SLOT(accept()));
    msgBox.setText("not implemented at this time");
    msgBox.exec();
  }
  
  void
  eyes::MyUpdate ()
  {
    qDebug() << " my update at " << QCursor::pos();
  }

  void
  eyes::quit ()
  {
    againTimer.stop();
    if (pApp) {
      pApp->quit();
    }
  }



} // namespace
