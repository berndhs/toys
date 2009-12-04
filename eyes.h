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
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPointF>


namespace eyes {

  class eyes : public QWidget, public Ui_EyeWindow {

Q_OBJECT

public:
 
   eyes (QApplication *app);

   void SetDelay (int msecs);
   int  delay();

   public slots:

     
     void quit();
     void NotImplemented ();
     void MyUpdate();
     void paintEvent(QPaintEvent *event);
     void mousePressEvent(QMouseEvent *click);
     
  private:
  
     void MenuPopup ();
     void ShowSpot ();
     void ShowPointer ();
   
     QApplication *pApp;
     QPainter     *painter;
     
     double    ScreenHeight;
     double    ScreenWidth;
     QPointF   VirtualCursor;
     

     QTimer    againTimer;
     int       againDelay;
};


}

#endif
