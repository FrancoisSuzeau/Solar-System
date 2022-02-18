/*
AUTHOR : SUZEAU François

DATE : 27/09/2021

MODULE : ParticuleManager

NAMEFILE : ParticuleManager.hpp

PURPOSE : header of the ParticuleManager class
*/

#ifndef PARTICULEMANAGER_H
#define PARTICULEMANAGER_H


/********************************************************************* includes *********************************************************************/

        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>
        #include <glm/gtc/matrix_inverse.hpp>
        #include <glm/gtx/string_cast.hpp>

        #include <iostream>
        #include <string>
        #include <math.h>
        #include <Windows.h>

        #include "Particule.hpp"
        #include "../OpenGlSketch/RenderData.hpp"
        #include "../Spaceship/Spaceship.hpp"
        #include "../Input/Input.hpp"
        

/********************************************************************* class definition *********************************************************************/

        class ParticuleManager
        {
            
            private:

                Particule       *m_particule;

                void orienteParticules(Spaceship *ship);

                

            public:
            
                ParticuleManager();
                ~ParticuleManager();

                void renderParticules(RenderData &render_data, Spaceship *ship);
                void initParticules(glm::vec3 posShip);

        };


#endif