//
//  CarObserver.h
//  
//
//  Created by Yufeng Wu on 12/1/22.

//  Demonstrate how a Car observer would work
//  This observer waits for the space bar key;
//  after the user presses (and releases) the space bar
//  it displays a car in the middle of the window!

//  In this lab we will add functionality such that if you press
//  the right arrow, the car moves and if you press the left
//  arrow, the car moves left


//  This code is meant to demonstrate the functionalities
//  especially the Observer pattern implemented in
//  ECGraphicViewImp.
//

#ifndef CarObserver_h
#define CarObserver_h

#include "ECObserver.h"
#include "ECGraphicViewImp.h"


//************************************************************

class ECCarObserver : public ECObserver
{
public:
    ECCarObserver( ECGraphicViewImp &viewIn );
    virtual void Update();
    
private:
    ECGraphicViewImp &view;
    bool fIsSpaceBarPressed;
    bool fIsLeftArrowPressed;
    bool fIsRightArrowPressed;
    int x1,y1,r1,x2,y2,r2;
    int x3,y3,x4,y4;
    int x5,y5,x6,y6;
};

#endif /* CarObserver_h */
