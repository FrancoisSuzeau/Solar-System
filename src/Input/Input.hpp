/*
AUTHOR : SUZEAU François

DATE : 26/05/2021

MODULE : Input

NAMEFILE : Input.h

PURPOSE : header of the Input class
*/

#ifndef INPUT_H
#define INPUT_H


/********************************************************************* includes *********************************************************************/
        
        #include <SDL2/SDL.h>
        #include <iostream>
        #include <string>
        

/********************************************************************* class definition *********************************************************************/

        class Input
        {
            
            private:

                SDL_Event   m_event;
                bool        m_keys[SDL_NUM_SCANCODES];
                bool        m_mouse_button[8];
                int         m_x;
                int         m_y;
                int         m_rel_x;
                int         m_rel_y;
                bool        m_terminate;

                

                
            public:

                Input();
                ~Input();

                void updateEvents();
                bool getTerminate();

                bool getKey(const SDL_Scancode key) const;
                bool getMouseButton(const Uint8 button) const; //application crash with Uint32
                bool getMouseMotion() const;

                int getX() const;
                int getY() const;

                int getXRel() const;
                int getYRel() const;

                void displayPointer(bool response) const;

                void capturePointer(bool response) const;
                
        };


#endif