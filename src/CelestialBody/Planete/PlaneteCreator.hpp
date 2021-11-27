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

                void displayName(RenderData &render_data, glm::vec3 camPos, int threshold)
                {
                        m_planete->displayName(render_data, camPos, threshold);
                }

                void drawAtmoPlanete(RenderData &render_data, glm::vec3 &camPos)
                {
                       m_planete->displayAtmo(render_data, camPos);
                }

                void drawPlanete(RenderData &render_data, glm::vec3 &camPos)
                {
                        m_planete->display(render_data, camPos);
                }

                void UpdatePositionPlan()
                {
                        m_planete->updatePosition();
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