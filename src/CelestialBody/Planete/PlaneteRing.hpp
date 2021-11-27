/*
AUTHOR : SUZEAU François

DATE : 07/06/2021

MODULE : CelestialBody.Planete

NAMEFILE : PlaneteRing.h

PURPOSE : header of the PlaneteRing class
*/

#ifndef PLANETERING_H
#define PLANETERING_H


/********************************************************************* includes *********************************************************************/

        #include "SimplePlanete.hpp"
        #include "../Ring/Ring.hpp"
        #include "../../Shader/Shader.hpp"

        #include <SDL2/SDL.h>
        #include <SDL2/SDL_ttf.h>

        #include <string>
        #include <vector>
        #include <iostream>
        #include <cassert>

        #include <GL/glew.h>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>
       

        

/********************************************************************* class definition *********************************************************************/

        class PlaneteRing: public SimplePlanete
        {
            
            private:
   
                Ring            *m_ring;
           
            public:

                PlaneteRing(init_data data, TTF_Font *police);
                PlaneteRing();
                ~PlaneteRing();
                void display(RenderData &render_data);
        };


#endif