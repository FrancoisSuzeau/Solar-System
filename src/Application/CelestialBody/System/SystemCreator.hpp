/*
AUTHOR : SUZEAU François

DATE : 17/06/2021

MODULE : CelestialBody.System

NAMEFILE : SystemCreator.h

PURPOSE : header of the virtual SystemCreator class
*/

#ifndef SYSTEMCREATOR_H
#define SYSTEMCREATOR_H


/********************************************************************* includes *********************************************************************/

        #include <string>
        #include <vector>
        #include <iostream>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include "System.hpp"
       
/********************************************************************* class definition *********************************************************************/

        class SystemCreator
        {
            
            protected:

                System *m_system;
                
            public:

                virtual ~SystemCreator() {delete m_system;};

                virtual System* FactoryMethod(sys_init_data data, TTF_Font *police) = 0;

                bool MakingSystem(sys_init_data data, TTF_Font *police) 
                {
                        m_system = this->FactoryMethod(data, police);
                        return true;
                }

                int loadSystem(int count, TTF_Font *police)
                {
                        m_system->loadSystem(count, police);
                        return 1;
                }

                void drawName(RenderData &render_data)
                {
                        m_system->displayName(render_data);
                }

                void drawAtmo(RenderData &render_data)
                {
                        m_system->displayAtmo(render_data);
                }

                void drawInfo(RenderData &render_data, PlaneteInformation *planete_info = nullptr)
                {
                        m_system->renderInfos(render_data, planete_info);
                }

                void drawSkybox(RenderData &render_data)
                {
                        m_system->displaySkybox(render_data);
                }

                void drawSystem(RenderData &render_data)
                {
                        m_system->display(render_data);
                }

                void drawAsteroidField(RenderData &render_data)
                {
                        m_system->displayAsteroidField(render_data);
                }

                void drawRing(RenderData &render_data)
                {
                        m_system->displayRing(render_data);
                }

                void setMostGravInfluence(RenderData &render_data)
                {
                        m_system->setMostGravInfluence(render_data);
                }

                void approchBody(Spaceship *ship)
                {
                        m_system->approchBody(ship);
                }

                void renderFlareSun(RenderData &render_data)
                {
                        m_system->renderFlareSun(render_data);
                }


        };


#endif