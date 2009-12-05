
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
#include "eyeconfig.h"

using namespace std;

namespace eyespace {

  eyes::eyes (QApplication *app)
    :pApp(app)
    ,againDelay(1000)        
  {
    setupUi (this);
    defaultWinFlags = this->windowFlags();
    config = new EyeConfig(this);
    if (config == 0) {
      exit(1);
    }
    connect (&againTimer, SIGNAL(timeout()), this, SLOT(update()));
    
    setCursor (Qt::CrossCursor);
    
    againTimer.start(againDelay);
    QDesktopWidget *dt = app->desktop();
    QRect screen = dt->screenGeometry();
    ScreenHeight = screen.height();
    ScreenWidth  = screen.width();
    this->resize(ScreenWidth/10,ScreenHeight/10);
    SetFrameConf();
    config->show();
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
  eyes::SetFrameConf()
  {
    if (config) {
      if (config->ShowFrame()) {
         setWindowFlags(defaultWinFlags);
         this->show();
      } else {
         Qt::WindowFlags flags = defaultWinFlags;
         flags |= Qt::FramelessWindowHint;
         setWindowFlags(flags);
         this->show();
      }
    } else {
      exit(1); // no config - something broken bad
    }
  }
  
  void
  eyes::MenuPopup ()
  { 
    if (config) {
      config->OpenWin();
    } else { // no config, we are in trouble
      exit(1);
    }
  }
  
  void
  eyes::mousePressEvent(QMouseEvent *click)
  {
    if (click) {
      Qt::MouseButton but = click->button();
      if (but != Qt::NoButton && but != Qt::LeftButton) {
        MenuPopup();
      }
    }
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
  eyes::update ()
  {
    if (config) {
      config->update();
    }
    QWidget::update();
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
     double dist = sqrt(dx*dx + dy*dy);
     double theta = -atan2(dx,dy) * 180.0/M_PI;
     double len = (midx > midy ? midy : midx);
     if (len > dist) { len = dist; }
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
  eyes::ShowEyes ()
  {
    double h = this->height();
    double w = this->width();
    QPoint midL (w*0.25, h*0.5);
    QPoint midR (w*0.75, h*0.5);
    double rx = w * 0.22;
    double ry = h * 0.4;
    double rmin = (rx > ry ? ry : rx);
    QPointF cursPoint (QCursor::pos());
    QPoint gloMidL(this->mapToGlobal(midL));
    QPoint gloMidR(this->mapToGlobal(midR));
    double dirLx = cursPoint.x() - double(gloMidL.x());
    double dirLy = cursPoint.y() - double(gloMidL.y());
    double thetaL = -atan2(dirLx,dirLy) * 180.0/M_PI;
    double dirRx = cursPoint.x() - double(gloMidR.x());
    double dirRy = cursPoint.y() - double(gloMidR.y());
    double thetaR = -atan2(dirRx,dirRy) * 180.0/M_PI;
    
    DrawOneEye (midL,thetaL,rmin*0.5,rmin*0.15);
    DrawOneEye (midR,thetaR,rmin*0.5,rmin*0.15);
    
  }
  
  void 
  eyes::DrawOneEye (QPoint mid, double theta, double r, double wid)
  {
    QColor eyecolor(QColor(0,255,0,255));
    
    QPainter paint(this);
    paint.setRenderHint(QPainter::HighQualityAntialiasing);
    paint.setBrush(Qt::NoBrush);
    QPen linePen;
    linePen.setColor(eyecolor);
    linePen.setWidth(wid);
    paint.setPen(linePen);
    paint.save();
    paint.translate(mid);
    paint.rotate(theta);
    paint.translate(0,r);
    paint.setBrush(eyecolor);
    paint.drawEllipse (QPoint(0,0),r*0.8,r*0.8);
    paint.restore();
    paint.drawEllipse (mid,r*2.0,r*2.0);
  
  }
  

  void
  eyes::paintEvent (QPaintEvent *event)
  {
    if (config) {
       if (config->ShowEyes()) {
         ShowEyes();
       }
       if (config->ShowArrow()) {
         ShowPointer();
       }
       if (config->ShowBubble()) {
          ShowSpot();
       }
    }
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
