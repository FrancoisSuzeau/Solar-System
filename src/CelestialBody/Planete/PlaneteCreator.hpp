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

        #include "SimplePlanete.hpp"
        #include "../../Shader/Shader.hpp"
        #include "../System/System.hpp"
       
/********************************************************************* class definition *********************************************************************/

        class PlaneteCreator
        {
            
            protected:

                SimplePlanete       *m_planete;
                
            public:

                virtual ~PlaneteCreator() {delete m_planete;};

                virtual SimplePlanete* FactoryMethod(init_data data, TTF_Font *police) = 0;

                bool MakingPlanete(init_data data, TTF_Font *police) 
                {
                        m_planete = this->FactoryMethod(data, police);
                        return true;
                }

                void displayName(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 camPos, int threshold, Shader *name_render_shader = nullptr)
                {
                        m_planete->displayName(projection, modelview, camPos, threshold, name_render_shader);
                }

                void drawAtmoPlanete(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos, bool hdr, Shader *atmo_shader = nullptr)
                {
                       m_planete->displayAtmo(projection, modelview, light_src, camPos, hdr, atmo_shader);
                }

                void drawPlanete(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos, bool hdr, Shader *m_plan_shader = nullptr, Shader *ring_shader = nullptr)
                {
                        m_planete->display(projection, modelview, light_src, camPos, hdr, m_plan_shader, ring_shader);
                }

                void UpdatePositionPlan(glm::mat4 &projection, glm::mat4 &modelview)
                {
                        m_planete->updatePosition(projection, modelview);
                }

                void updatePosLight(glm::mat4 &projection, glm::mat4 &modelview)
                {
                        m_planete->updatePositionLight(projection, modelview);
                }

                vec3 getPostion() const
                {
                       return m_planete->getCurrentPos();
                }

                float getSizePlan() const
                {
                        return m_planete->getRealSize();
                }

                std::string getName() const
                {
                        return m_planete->getName();
                }

                float getRadius(glm::vec3 camPos)
                {
                        return m_planete->getRadiusFromCam(camPos);
                }


        };

#endif