/*
AUTHOR : SUZEAU François

DATE : 27/06/2021

MODULE : CelestialBody.Planete

NAMEFILE : PlaneteRingCreator.h

PURPOSE : header of the virtual PlaneteRingCreator class
*/

#ifndef RINGPLANCREATOR_H
#define RINGPLANCREATOR_H


/********************************************************************* includes *********************************************************************/

        #include <string>
        #include <vector>
        #include <iostream>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include <SDL2/SDL.h>
        #include <SDL2/SDL_ttf.h>

        #include "PlaneteCreator.hpp"
        #include "PlaneteRing.hpp"
       
/********************************************************************* class definition *********************************************************************/

        class PlaneteRingCreator : public PlaneteCreator 
        {
            
            private:

                
                
            public:


                SimplePlanete* FactoryMethod(std::string const texture, std::string const name, float const real_size, float inclinaison_angle, glm::vec3 initial_pos, TTF_Font *police) override
                {
                        puts("");
                        puts("");
                        std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Planete Creator : " << name << " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
                        return new PlaneteRing(texture, name, real_size, inclinaison_angle, initial_pos, police);
                }


        };


#endif