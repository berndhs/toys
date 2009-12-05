
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
#include <math.h>
#ifndef M_PI
#define M_PI 3.1415265
#endif
#include <QDesktopWidget>
#include "version.h"

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
    this->resize(ScreenWidth/10,ScreenHeight/10);
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
  eyes::MenuPopup ()
  { 
     QMessageBox box;
     QAbstractButton *quitButton 
            = box.addButton(tr("Quit"), QMessageBox::ActionRole);
     QAbstractButton *keepGoing
            = box.addButton(tr("Yes"), QMessageBox::AcceptRole);
     QAbstractButton *showVersion
            = box.addButton(tr("Version"), QMessageBox::ActionRole);
     box.setText (tr("Keep Going?"));
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
     if (result == showVersion) {
       ShowVersionWindow();
     }
  }
  
  void
  eyes::mousePressEvent(QMouseEvent *click)
  {
    MenuPopup();
  }


  void
  eyes::NotImplemented ()
  {
    QMessageBox msgBox;
    QTimer::singleShot(15000, &msgBox, SLOT(accept()));
    msgBox.setText(tr("not implemented at this time"));
    msgBox.exec();
  }
  
  void
  eyes::MyUpdate ()
  {
    this->update(); // encourage PaintEvent
  }
  
  void
  eyes::ShowSpot ()
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
  eyes::ShowPointer ()
  {
     QPoint mid (this->width()/2, this->height()/2);
     double midx = double(mid.x());
     double midy = double(mid.y());
     QPoint cursPoint (QCursor::pos());
     QPoint midGlobal = this->mapToGlobal(mid);
     double dx = double(cursPoint.x()) - double (midGlobal.x());
     double dy = double(cursPoint.y()) - double (midGlobal.y());
     double theta = -atan2(dx,dy) * 180.0/M_PI;
     double len = (midx > midy ? midy : midx);
     int    shortlen = int(len /10.0);
     QPainter paint(this);
     paint.setRenderHint(QPainter::HighQualityAntialiasing);
     paint.setBrush(Qt::NoBrush);
     QPen linePen;
     linePen.setColor(QColor(0,0,255,255));
     linePen.setWidth(len*0.05);
     linePen.setCapStyle(Qt::RoundCap);
     paint.setPen(linePen);
     paint.translate(mid);
     paint.rotate(theta);
     paint.save();
     paint.drawLine(0,0,0,int(len));
     paint.restore();
     paint.translate(0,int(len));
     paint.drawLine(0,0,-shortlen,-shortlen);
     paint.drawLine(0,0,shortlen, -shortlen);
  }
  

  void
  eyes::paintEvent (QPaintEvent *event)
  {
    ShowSpot ();
    ShowPointer ();
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
