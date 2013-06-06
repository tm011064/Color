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
    //eglView->setFrameSize(260, 480);
    //eglView->setFrameSize(320, 240);
    //eglView->setFrameSize(320, 432);
    //eglView->setFrameSize(320, 480);
    //eglView->setFrameSize(240, 320);

    //eglView->setFrameSize(1536, 2048);  // 1536 x 2048: IPad HD (3:4)
    //eglView->setFrameSize(768, 1280);   // 768  x 1280: Nexus 4
    //eglView->setFrameSize(720, 1280);   // 720  x 1280: Galaxy SIII (9:16)
    //eglView->setFrameSize(640, 960);    // 640  x  960: IPhone 4
    //eglView->setFrameSize(480, 800);    // 480  x  800: HTC Desire HD 
    
    eglView->setFrameSize(320, 480);    // 320  x  480: IPhone (2:3)
    //eglView->setFrameSize(270, 480);      // 270  x  480: 9:16
    //eglView->setFrameSize(360, 480);    // 360  x  480: 3:4
    //eglView->setFrameSize(288, 432);    // 360  x  480: 2:3
    
    //eglView->setFrameSize(240, 320);    // 240  x  320: Various (3:4)
    
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
