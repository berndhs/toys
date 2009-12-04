
#include "eyes.h"
#include <QMessageBox>
#include <QAbstractButton>
#include <QPushButton>
#include <QDebug>
#include <QPainter>

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
#include <cmath>
#include <QDesktopWidget>

using namespace std;

namespace eyes {

  eyes::eyes (QApplication *app)
    :pApp(app)
    ,againDelay(1000)        
  {
    setupUi (this);
    connect (&againTimer, SIGNAL(timeout()), this, SLOT(MyUpdate()));
    
    setCursor (Qt::CrossCursor);
    
    againTimer.start(againDelay);
    QDesktopWidget *dt = app->desktop();
    QRect screen = dt->screenGeometry();
    ScreenHeight = screen.height();
    ScreenWidth  = screen.width();
  }
  
  void
  eyes::SetDelay (int msec) {
    againDelay = msec;
    againTimer.stop();
    againTimer.start(againDelay);
  }
  
  int
  eyes::delay () {
    return againDelay;
  }
  
  void
  eyes::mousePressEvent(QMouseEvent *click)
  {
     QMessageBox box;
     QAbstractButton *quitButton 
            = box.addButton("Quit", QMessageBox::ActionRole);
     QAbstractButton *keepGoing
            = box.addButton("Yes", QMessageBox::AcceptRole);
     box.setText ("Keep Going?");
     QTimer::singleShot(5000,&box,SLOT(accept()));
     box.exec();
     QAbstractButton *result = box.clickedButton();
     if (result == 0) {
        return;
     }
     if (result == quitButton) {
       quit();
     }
     if (result == keepGoing) {
       return;
     }
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
    this->update();
  }

  void
  eyes::paintEvent (QPaintEvent *event)
  {
    
    QPointF lastCur(QCursor::pos());
    double relHi = lastCur.y()/ScreenHeight;
    double relWid = lastCur.x()/ScreenWidth;
    relHi *= this->height();
    relWid *= this->width();
    
    QPainter paint(this);
    paint.setBrush(Qt::NoBrush);
    paint.setPen(QColor(200,10,10,255));
    paint.translate(0,0);
    paint.drawEllipse(QPointF(relWid,relHi),5,5);
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
