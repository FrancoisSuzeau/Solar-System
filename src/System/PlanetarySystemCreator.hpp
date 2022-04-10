/*
AUTHOR : SUZEAU François

DATE : 17/06/2021

MODULE : System

NAMEFILE : PlanetarySystemCreator.hpp

PURPOSE : header of the virtual PlanetarySystemCreator class
*/

#ifndef PLSYSTEMCREATOR_H
#define PLSYSTEMCREATOR_H


/********************************************************************* includes *********************************************************************/

        #include <string>
        #include <vector>
        #include <iostream>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include "SystemCreator.hpp"
        #include "PlanetarySystem.hpp"
       
/********************************************************************* class definition *********************************************************************/

        class PlanetarySystemCreator : public SystemCreator 
        {
            
            private:

                
                
            public:


                System* FactoryMethod(/*sys_init_data data, TTF_Font *police, */ Renderer *planete_renderer) override
                {
                        // puts("");
                        // puts("");
                        // std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> System Creator : " << data.name_sys << " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
                        return new PlanetarySystem(/*data, police,*/ planete_renderer);
                }


        };


#endif