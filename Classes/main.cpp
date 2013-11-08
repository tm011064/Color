#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"

USING_NS_CC;

// uncomment below line, open debug console
// #define USE_WIN32_CONSOLE

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef USE_WIN32_CONSOLE
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
#endif

    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    
    /*
        1536 x 2048: IPad HD (3:4)
        768  x 1280: Nexus 4 (5:8)
        720  x 1280: Galaxy SIII (9:16)
        640  x  960: IPhone 4 (2:3)
        480  x  800: HTC Desire HD (3:5)
        320  x  480: IPhone (3:4)
        240  x  320: Various (3:4)
    */
        
    // 360 x 480, small
    // ----------------------------------------------------------
    // eglView->setFrameSize(243, 324);   // Ratio = 3:4
    // eglView->setFrameSize(182, 324);   // Ratio = 9:16
    // eglView->setFrameSize(203, 324);   // Ratio = 5:8
    // eglView->setFrameSize(194, 324);   // Ratio = 3:5
    // eglView->setFrameSize(216, 324);   // Ratio = 2:3
    
    // 360 x 480, middle
    // ----------------------------------------------------------
    // eglView->setFrameSize(300, 400);   // Ratio = 3:4
    // eglView->setFrameSize(225, 400);   // Ratio = 9:16
    // eglView->setFrameSize(250, 400);   // Ratio = 5:8
    // eglView->setFrameSize(240, 400);   // Ratio = 3:5
    // eglView->setFrameSize(267, 400);   // Ratio = 2:3
    
    // 360 x 480, large
    // ----------------------------------------------------------
    // eglView->setFrameSize(360, 480);   // Ratio = 3:4
    // eglView->setFrameSize(270, 480);   // Ratio = 9:16
    // eglView->setFrameSize(300, 480);   // Ratio = 5:8
    // eglView->setFrameSize(288, 480);   // Ratio = 3:5
    // eglView->setFrameSize(320, 480);   // Ratio = 2:3


    // 960 x 1280, small
    // ----------------------------------------------------------
    // eglView->setFrameSize(735, 980);   // Ratio = 3:4    -> 0.75
    // eglView->setFrameSize(551, 980);   // Ratio = 9:16   -> 0.5625
    // eglView->setFrameSize(613, 980);   // Ratio = 5:8    -> 0.625
    // eglView->setFrameSize(588, 980);   // Ratio = 3:5    -> 0.6
     eglView->setFrameSize(653, 980);   // Ratio = 2:3    -> 0.66
     
    // 960 x 1280, middle
    // ----------------------------------------------------------
    // eglView->setFrameSize(840, 1120);   // Ratio = 3:4
    // eglView->setFrameSize(630, 1120);   // Ratio = 9:16
    // eglView->setFrameSize(700, 1120);   // Ratio = 5:8
    // eglView->setFrameSize(672, 1120);   // Ratio = 3:5
    // eglView->setFrameSize(747, 1120);   // Ratio = 2:3
     
    // 960 x 1280, large
    // ----------------------------------------------------------
    // eglView->setFrameSize(960, 1280);   // Ratio = 3:4
    // eglView->setFrameSize(720, 1280);   // Ratio = 9:16
    // eglView->setFrameSize(800, 1280);   // Ratio = 5:8
    // eglView->setFrameSize(768, 1280);   // Ratio = 3:5
    // eglView->setFrameSize(853, 1280);   // Ratio = 2:3




    // eglView->setFrameSize(720, 960);   // Ratio = 3:4
    // eglView->setFrameSize(540, 960);   // Ratio = 9:16
    // eglView->setFrameSize(600, 960);   // Ratio = 5:8
    // eglView->setFrameSize(576, 960);   // Ratio = 3:5
    // eglView->setFrameSize(640, 960);   // Ratio = 2:3

    
    /* 3:4 sizes    
1536 x 2048
960 x 1280
720 x 960
360 x 480
240 x 320
    */

    int ret = CCApplication::sharedApplication()->run();

#ifdef USE_WIN32_CONSOLE
    FreeConsole();
#endif

    return ret;
}
