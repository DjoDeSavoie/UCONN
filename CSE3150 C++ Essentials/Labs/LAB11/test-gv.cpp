//
//  Created by Yufeng Wu on 3/2/22.
//
#include "ECGraphicViewImp.h"
#include "CarObserver.h"

// to compile
// g++ ECGraphicViewImp.cpp CarObserver.cpp test-gv.cpp -lallegro -lallegro_font -lallegro_primitives -lallegro_image -lallegro_main


// Test graphical view code
int real_main(int argc, char **argv)
{
    const int widthWin = 1000, heightWin = 1000;
    ECGraphicViewImp view(widthWin, heightWin);
  
    // create a simple observer
    ECCarObserver carObs(view);

    // view.Attach(&obs);

    view.Attach(&carObs);
    
    view.Show();
  
  
    return 0;
}

int main(int argc, char **argv)
{
    return real_main(argc, argv);
    //return al_run_main(argc, argv, real_main);
}

