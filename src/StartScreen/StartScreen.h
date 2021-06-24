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

        #include "../Text/Text.h"

        
       
/********************************************************************* class definition *********************************************************************/

        class StartScreen
        {
            
            private:
            
                Text        m_text_loadScreen;
                
                
            public:
                
                StartScreen();
                ~StartScreen();

                void drawStartScreen(glm::mat4 &projection, glm::mat4 &modelview);

        };


#endif