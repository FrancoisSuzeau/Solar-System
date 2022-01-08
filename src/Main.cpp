/*
AUTHOR : SUZEAU François

DATE : 25/05/2021

NAMEFILE : Main.cpp

PURPOSE : main loop of the executable
*/


#include <Windows.h>
#include "OpenGlSketch/OpenGlSketch.hpp"


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    
    int cx = GetSystemMetrics(SM_CXSCREEN);
    int cy = GetSystemMetrics(SM_CYSCREEN);

    //std::cout << "width : " << cx << " height : " << cy << std::endl;

    OpenGlSketch sketch("Solar System", cx, cy);

    if((sketch.initWindow() == false) || (sketch.initGL() == false))
    {
        return EXIT_FAILURE;
    }

    sketch.initImGUI();
  
    sketch.startLoop();

    sketch.initFrameBuffer();
    
    sketch.mainLoop();
    
    return EXIT_SUCCESS;

}