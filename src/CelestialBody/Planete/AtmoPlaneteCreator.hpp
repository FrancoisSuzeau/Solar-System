/*
AUTHOR : SUZEAU François

DATE : 27/06/2021

MODULE : CelestialBody.Planete

NAMEFILE : AtmoPlaneteCreator.h

PURPOSE : header of the virtual AtmoPlaneteCreator class
*/

#ifndef ATMOPLANCREATOR_H
#define ATMOPLANCREATOR_H


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
        #include "AtmoPlanete.hpp"
       
/********************************************************************* class definition *********************************************************************/

        class AtmoPlaneteCreator : public PlaneteCreator 
        {
            
            private:

                
                
            public:


                SimplePlanete* FactoryMethod(init_data data, TTF_Font *police) override
                {
                        puts("");
                        puts("");
                        std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Planete Creator : " << data.name << " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
                        return new AtmoPlanete(data, police);
                }


        };


#endif