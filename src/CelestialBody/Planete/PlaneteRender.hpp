/*
AUTHOR : SUZEAU François

DATE : 15/06/2021

MODULE : CelestialBody.PlaneteRender

NAMEFILE : PlaneteRender.h

PURPOSE : header of the PlaneteRender class
*/

#ifndef SIMPPLANETE_H
#define SIMPPLANETE_H


/********************************************************************* includes *********************************************************************/

        #include "../Geometry/Sphere.hpp"
        #include "../../Texture/Texture.hpp"
        #include "../../Text/Text.hpp"
        #include "../../Atmosphere/Atmosphere.hpp"
        #include "../../PlaneteInformation/PlaneteInformation.hpp"
        #include "Planete.hpp"
        #include "../System/System.hpp"

        #include <string>
        #include <vector>
        #include <iostream>
        #include <cassert>

        #include <GL/glew.h>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>
        
        #include <SDL2/SDL.h>
        #include <SDL2/SDL_ttf.h>
        

/********************************************************************* class definition *********************************************************************/

        class PlaneteRender: public Sphere
        {
            
            protected:

                std::string     m_name;
                
            public:

                PlaneteRender();
                ~PlaneteRender();
                void display(RenderData &render_data, Planete *planete);
                void displayName(RenderData &render_data, int threshold, Planete *planete);
                void displayAtmo(RenderData &render_data);
                
        };


#endif