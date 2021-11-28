/*
AUTHOR : SUZEAU François

DATE : 23/06/2021

MODULE : StartScreen

NAMEFILE : StartScreen.h

PURPOSE : header of the virtual StartScreen class
*/

#ifndef STARTSCREEN_H
#define STARTSCREEN_H


/********************************************************************* includes *********************************************************************/

        #include <string>
        #include <vector>
        #include <iostream>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>
        #include <cassert>

        #include <SDL2/SDL_ttf.h>

        #include "../Text/Text.hpp"
        #include "../OpenGlSketch/RenderData.hpp"

        
       
/********************************************************************* class definition *********************************************************************/

        class StartScreen
        {
            
            private:
            
                Text        m_text_loadScreen;
                
                
            public:
                
                StartScreen(TTF_Font *police);
                ~StartScreen();

                void drawStartScreen(RenderData &render_data);

        };


#endif