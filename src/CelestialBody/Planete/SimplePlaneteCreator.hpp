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
       
/********************************************************************* class definition *********************************************************************/

        class SimplePlaneteCreator : public PlaneteCreator 
        {
            
            private:

                
                
            public:


                SimplePlanete* FactoryMethod(std::string const texture, std::string const name, float const real_size, float inclinaison_angle, glm::vec3 initial_pos) override
                {
                        puts("");
                        puts("");
                        std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Planete Creator : " << name << " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
                        return new SimplePlanete(texture, name, real_size, inclinaison_angle, initial_pos);
                }


        };


#endif