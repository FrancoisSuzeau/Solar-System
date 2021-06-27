/*
AUTHOR : SUZEAU François

DATE : 27/06/2021

MODULE : CelestialBody.Planete

NAMEFILE : PlaneteCreator.h

PURPOSE : header of the virtual PlaneteCreator class
*/

#ifndef PLANCREATOR
#define PLANCREATOR


/********************************************************************* includes *********************************************************************/

        #include <string>
        #include <vector>
        #include <iostream>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include "SimplePlanete.h"
       
/********************************************************************* class definition *********************************************************************/

        class PlaneteCreator
        {
            
            protected:

                SimplePlanete       *m_planete;
                
            public:

                virtual ~PlaneteCreator() {delete m_planete;};

                virtual SimplePlanete* FactoryMethod(std::string const texture, std::string const name, float const real_size, float inclinaison_angle, glm::vec3 initial_pos) = 0;

                bool MakingPlanete(std::string const texture, std::string const name, float const real_size, float inclinaison_angle, glm::vec3 initial_pos) 
                {
                        m_planete = this->FactoryMethod(texture, name, real_size, inclinaison_angle, initial_pos);
                        puts("");
                        puts("");
                        std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Planete Creator : " << name << " <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
                        return true;
                }

                void drawPlanete(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos)
                {
                        m_planete->display(projection, modelview, light_src, camPos);
                }

                void drawNamePlan(glm::mat4 &projection, glm::mat4 &modelview)
                {
                        m_planete->displayName(projection, modelview);
                }

                void UpdatePositionPlan(glm::mat4 &projection, glm::mat4 &modelview)
                {
                        m_planete->updatePosition(projection, modelview);
                }

                void updatePosLight(glm::mat4 &projection, glm::mat4 &modelview)
                {
                        m_planete->updatePositionLight(projection, modelview);
                }


        };

#endif