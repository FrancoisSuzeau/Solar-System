/*
AUTHOR : SUZEAU François

DATE : 27/06/2021

MODULE : CelestialBody.Planete

NAMEFILE : SimplePlaneteCreator.h

PURPOSE : header of the virtual SimplePlaneteCreator class
*/

#ifndef SIMPLEPLANCREATOR_H
#define SIMPLEPLANCREATOR_H


/********************************************************************* includes *********************************************************************/

        #include <string>
        #include <vector>
        #include <iostream>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include "PlaneteCreator.hpp"

        #include <SDL2/SDL.h>
        #include <SDL2/SDL_ttf.h>
       
/********************************************************************* class definition *********************************************************************/

        class SimplePlaneteCreator : public PlaneteCreator 
        {
            
            private:

                
                
            public:


                SimplePlanete* FactoryMethod(init_data data, TTF_Font *police) override
                {
                        puts("");
                        puts("");
                        std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Planete Creator : " << data.name << " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
                        return new SimplePlanete(data, police);
                }


        };


#endif