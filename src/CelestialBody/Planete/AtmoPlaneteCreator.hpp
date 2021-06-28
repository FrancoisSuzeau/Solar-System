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

        #include "PlaneteCreator.hpp"
        #include "AtmoPlanete.hpp"
       
/********************************************************************* class definition *********************************************************************/

        class AtmoPlaneteCreator : public PlaneteCreator 
        {
            
            private:

                
                
            public:


                SimplePlanete* FactoryMethod(std::string const texture, std::string const name, float const real_size, float inclinaison_angle, glm::vec3 initial_pos) override
                {
                        puts("");
                        puts("");
                        std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Planete Creator : " << name << " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
                        return new AtmoPlanete(texture, name, real_size, inclinaison_angle, initial_pos);
                }


        };


#endif