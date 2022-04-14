/*
AUTHOR : SUZEAU François

DATE : 17/06/2021

MODULE : System

NAMEFILE : System.hpp

PURPOSE : header of the virtual System class
*/

#ifndef SYSTEM_H
#define SYSTEM_H


/********************************************************************* includes *********************************************************************/

        #include <string>
        #include <vector>
        #include <iostream>
        #include <cstdlib>
        
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include "../Application/DataManager.hpp"

        #include "../Objects/TexturedObjects/Planete/Planete.hpp"
        #include "../Renderers/TexturedRenderers/PlaneteRenderer/PlaneteRenderer.hpp"
        #include "../Renderers/TexturedRenderers/RingRenderer/RingRenderer.hpp"

        // #include "../../PlaneteInformation/PlaneteInformation.hpp"
        // #include "../../OpenGlSketch/RenderData.hpp"
        // #include "../Physique/Physique.hpp"
        // #include "../../Spaceship/Spaceship.hpp"

        // #include "../../LensFlare/FlareManager.hpp"
       
/********************************************************************* class definition *********************************************************************/

        class System
        {
            
            protected:

                Renderer                        *m_planete_renderer = nullptr;
                Renderer                        *m_ring_renderer = nullptr;

                std::string                      m_system_name;
                // std::vector<sys_init_data>     sys_data;
                // bool mini_speed;
                // bool maxi_speed;
                // float current_speed;
                
            public:

                
                virtual ~System() {};
                virtual void loadSystem(/*int count, TTF_Font *police*/) = 0;
                virtual void makeChanges(DataManager &data_manager) = 0;
                virtual void render(DataManager &data_manager) = 0;
                virtual void clean() = 0;
                // virtual void displayName(RenderData &render_data) = 0;
                // virtual void displayAtmo(RenderData &render_data) = 0;
                // virtual void renderInfos(RenderData &render_data, PlaneteInformation *planete_info = nullptr) = 0;
                virtual void renderRing(DataManager &data_manager) = 0;
                // virtual void setMostGravInfluence(RenderData &render_data) = 0;
                // virtual void approchBody(Spaceship *ship) = 0;
                // virtual void renderFlareSun(RenderData &render_data) = 0;
                
        };


#endif