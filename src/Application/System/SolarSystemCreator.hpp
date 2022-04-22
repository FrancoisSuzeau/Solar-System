/*
AUTHOR : SUZEAU François

DATE : 17/06/2021

MODULE : System

NAMEFILE : SolarSystemCreator.hpp

PURPOSE : header of the virtual SolarSystemCreator class
*/

#ifndef SSSYSTEMCREATOR_H
#define SSSYSTEMCREATOR_H


/********************************************************************* includes *********************************************************************/

        #include <string>
        #include <vector>
        #include <iostream>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include "SystemCreator.hpp"
        #include "SolarSystem.hpp"
       
/********************************************************************* class definition *********************************************************************/

        class SolarSystemCreator : public SystemCreator 
        {
            
            private:

                
                
            public:

                ~SolarSystemCreator() override {
                        if(m_system != nullptr)
                        {
                                delete m_system;
                                m_system = nullptr;
                                std::cout << ">> SOLAR SYSTEM : DESTROY COMPLETE" << std::endl;
                        }
                }


                System* FactoryMethod(Renderer *planete_renderer, Renderer *ring_renderer,  Renderer *sphere_renderer, std::string const system_name) override
                {
                        // puts("");
                        // puts("");
                        // std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> System Creator : " << data.name_sys << " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
                        return new SolarSystem(planete_renderer, ring_renderer, sphere_renderer, system_name);
                }


        };


#endif