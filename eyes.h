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
#include <QTranslator>
#include <QTimer>
#include <QProcess>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPointF>

#include "eyeconfig.h"


namespace eyespace {

  class eyes : public QWidget, public Ui_EyeWindow {

Q_OBJECT

public:
 
   eyes (QApplication *app);

   void SetDelay (int msecs);
   int  delay();
   void SetFrameConf();
   
   public slots:

     
     void quit();
     void update();
     void NotImplemented ();
     void paintEvent(QPaintEvent *event);
     void mousePressEvent(QMouseEvent *click);
     
  private:
  
     void MenuPopup ();
     void ShowSpot ();
     void ShowPointer ();
     void ShowEyes ();
     void DrawOneEye (QPoint mid, 
                      double theta, 
                      double r, 
                      double wid);
   
     QApplication *pApp;
     QPainter     *painter;
     
     Qt::WindowFlags  defaultWinFlags;
     
     EyeConfig  *config;
     
     double    ScreenHeight;
     double    ScreenWidth;
     QPointF   VirtualCursor;
     

     QTimer    againTimer;
     int       againDelay;
};


}

#endif
