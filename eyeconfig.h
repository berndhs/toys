#ifndef EYECONFIG_H
#define EYECONFIG_H

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

#include "ui_eyeconfig.h"
#include <QDialog>


namespace eyespace {

class eyes;

class EyeConfig : public QDialog, public Ui_EyeConfig {

Q_OBJECT

public:

   EyeConfig (eyes * parent);
   
   void OpenWin();
   void CloseWin();
   
   
public slots:

  void update();
  void quit();

  void DoApply ();
  void DoCancel ();
  void DoOk ();
  void DoCheckEyes (int state);
  void DoCheckArrow (int state);
  void DoCheckBubble (int state);
  void DoCheckFrame (int state);
  
  void DoShowVersion ();
  void DoLinkAuthor ();
  
  bool ShowEyes() { return state.showEyes; }
  bool ShowArrow() { return state.showArrow; }
  bool ShowBubble() { return state.showBubble; }
  bool ShowFrame() { return state.showFrame; }
  
  
private:

  Qt::CheckState  MyCheckState (bool st) // no tristate nonsense
      { 
        return st ? Qt::Checked : Qt::Unchecked;
      }

  class State {
  public:
   
    State():showEyes(true),
            showArrow(true),
            showBubble(true),
            showFrame(true){}

    State(const State& s) {
                     showEyes = s.showEyes;
                     showArrow = s.showArrow;
                     showBubble = s.showBubble;
                     showFrame = s.showFrame;
                     }
    bool showEyes;
    bool showArrow;
    bool showBubble;
    bool showFrame;
    
  };
  
  eyes* pEyes;

  State state;
  State tempstate;


};

}

#endif
