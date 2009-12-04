#include "eyes.h"



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

  eyes::eyes TheEyes(&App);

  TheEyes.SetDelay(100);

  TheEyes.show();
  App.exec();

}
