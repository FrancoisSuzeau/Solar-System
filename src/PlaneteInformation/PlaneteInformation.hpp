/*
AUTHOR : SUZEAU François

DATE : 06/08/2021

MODULE : PlaneteInformation

NAMEFILE : PlaneteInformation.hpp

PURPOSE : header of the PlaneteInformation class
*/

#ifndef PLANETEINFO_H
#define PLANETEINFO_H


/********************************************************************* includes *********************************************************************/

        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>
        #include <glm/gtc/matrix_inverse.hpp>
        #include <glm/gtx/string_cast.hpp>

        #include <iostream>
        #include <string>
        #include <Windows.h>

        #include <SDL2/SDL_ttf.h>
        
        #include "../CelestialBody/Geometry/Square.hpp"
        #include "../Text/Text.hpp"
        #include "../Shader/Shader.hpp"
        

/********************************************************************* class definition *********************************************************************/

        class PlaneteInformation
        {
            
            private:

                Square          m_grey_rect;
                Square          m_black_rect;

                Text            m_text_name;
                
                std::string     m_name_plan;
                glm::vec3       m_plan_pos;

                int             screen_w;
                int             screen_h;

                glm::vec3       colorGrey;
                glm::vec3       colorBlack;

            public:
            
                PlaneteInformation(std::string const name_plan, TTF_Font *police);
                PlaneteInformation();
                ~PlaneteInformation();

                void renderInfo(glm::mat4 &projection, glm::mat4 &modelview, bool hdr, Shader *text_shader = nullptr, Shader *square_shader = nullptr);
                void setPosPlan(glm::vec3 const &posPlan);
                void changeNamePlan(std::string const name);
                std::string getInfoName() const;


        };


#endif