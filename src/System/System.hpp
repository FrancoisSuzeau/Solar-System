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

        // #include "../../PlaneteInformation/PlaneteInformation.hpp"
        // #include "../../OpenGlSketch/RenderData.hpp"
        // #include "../Physique/Physique.hpp"
        // #include "../../Spaceship/Spaceship.hpp"

        // #include "../../LensFlare/FlareManager.hpp"


        typedef struct body_data {

                float                           size;
                std::vector<std::string>        textures_path;
                std::string                     type;
                int                             shininess;
                float                           oppacity;
                // std::vector<std::string> nom_disp_path;
                // std::string name;
                // float   inclinaison_angle;
                // float   speed_rotation;

        } body_data;

        // typedef struct sys_init_data {

        //         std::string     name_sys;
        //         int     companion_count;

        // } sys_init_data;
       
/********************************************************************* class definition *********************************************************************/

        class System
        {
            
            protected:

                Renderer                        *m_planete_renderer = nullptr;

                // std::string                 m_system_name;
                // int                         m_companion_count;

                std::vector<body_data>          m_bodys_data;
                // std::vector<sys_init_data>     sys_data;
                // bool mini_speed;
                // bool maxi_speed;
                // float current_speed;

                virtual void    initDatas() = 0;
                
            public:

                
                virtual ~System() {};
                virtual void loadSystem(/*int count, TTF_Font *police*/) = 0;
                virtual void makeChanges(DataManager &data_manager) = 0;
                virtual void render(DataManager &data_manager) = 0;
                // virtual void displayName(RenderData &render_data) = 0;
                // virtual void displayAtmo(RenderData &render_data) = 0;
                // virtual void renderInfos(RenderData &render_data, PlaneteInformation *planete_info = nullptr) = 0;
                // virtual void displayRing(RenderData &render_data) = 0;
                // virtual void setMostGravInfluence(RenderData &render_data) = 0;
                // virtual void approchBody(Spaceship *ship) = 0;
                // virtual void renderFlareSun(RenderData &render_data) = 0;
                
        };


#endif