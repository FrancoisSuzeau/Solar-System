/*
AUTHOR : SUZEAU François

DATE : 25/05/2021

NAMEFILE : Main.cpp

PURPOSE : main loop of the executable
*/

#include "OpenGlSketch/OpenGlSketch.hpp"


int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    
    

    OpenGlSketch sketch("Solar System", 1920, 1080);

    if((sketch.initWindow() == false) || (sketch.initGL() == false))
    {
        return EXIT_FAILURE;
    }

    sketch.initFrameBuffer();
    
    sketch.startLoop();
    
    sketch.mainLoop();
    
    return EXIT_SUCCESS;

}