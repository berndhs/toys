#include "eyeconfig.h"
#include "eyes.h"
#include "version.h"
#include <QDesktopServices>
#include <QUrl>
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

namespace eyespace {

EyeConfig::EyeConfig (eyes *parent) 
:pEyes(parent)
{
  setupUi(this);
  
  connect (cancelBut,SIGNAL(clicked()),this,SLOT(DoCancel()));
  connect (okBut,SIGNAL(clicked()),this,SLOT(DoOk()));
  connect (applyBut, SIGNAL(clicked()),this,SLOT(DoApply()));
  connect (quitBut, SIGNAL(clicked()),this,SLOT(quit()));
  
  
  connect (versionButton, SIGNAL(clicked()),
            this,SLOT(DoShowVersion()));
  connect (authorButton, SIGNAL(clicked()),
            this,SLOT(DoLinkAuthor()));
  
  connect (eyesCheck, SIGNAL(stateChanged(int)),
             this,SLOT(DoCheckEyes(int)));
  connect (arrowCheck, SIGNAL(stateChanged(int)),
             this,SLOT(DoCheckArrow(int)));
  connect (bubbleCheck, SIGNAL(stateChanged(int)),
             this,SLOT(DoCheckBubble(int)));
  connect (frameCheck, SIGNAL(stateChanged(int)),
            this,SLOT(DoCheckFrame(int)));
}

void
EyeConfig::update ()
{
   eyesCheck->setCheckState(MyCheckState(tempstate.showEyes));
   arrowCheck->setCheckState(MyCheckState(tempstate.showArrow));
   bubbleCheck->setCheckState(MyCheckState(tempstate.showBubble));
   frameCheck->setCheckState(MyCheckState(tempstate.showFrame));
}


void
EyeConfig::DoShowVersion ()
{
  ShowVersionWindow();
}

void
EyeConfig::DoLinkAuthor ()
{
  QDesktopServices::openUrl
  (QUrl(QString("http://www.bernd-stramm.com/freestuff.php")));
}

void
EyeConfig::DoCheckEyes (int state)
{
  tempstate.showEyes = (state == Qt::Checked);
}
void
EyeConfig::DoCheckArrow (int state)
{
  tempstate.showArrow = (state == Qt::Checked);
}

void
EyeConfig::DoCheckBubble (int state)
{
  tempstate.showBubble = (state == Qt::Checked);
}

void
EyeConfig::DoCheckFrame (int state)
{
  tempstate.showFrame = (state == Qt::Checked);
}


void
EyeConfig::DoApply ()
{
  bool frameChanged = (state.showFrame != tempstate.showFrame);
  state = tempstate;
  if (frameChanged) {
    if (pEyes) {
      pEyes->SetFrameConf();
    } else {
      exit(1);  // lost parent, no point continuing
    }
  }
}

void
EyeConfig::DoCancel ()
{
  tempstate = state;
  CloseWin();
}

void
EyeConfig::OpenWin ()
{
  tempstate = state;
  this->show();
}

void
EyeConfig::CloseWin()
{
  this->hide();
}

void 
EyeConfig::DoOk ()
{
  DoApply();
  CloseWin();
}

void
EyeConfig::quit ()
{
   if (pEyes) {
     pEyes->quit();
   } else {
     exit(1);
   }
}

}
