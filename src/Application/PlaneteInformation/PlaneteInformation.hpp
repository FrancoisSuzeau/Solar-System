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
        #include <vector>
        #include <cassert>
        
        #include "../OpenGlSketch/RenderData.hpp"
        

/********************************************************************* class definition *********************************************************************/

        class PlaneteInformation
        {
            
            private:

                std::map<std::string, ImVec4> map_color;

            public:
            
                PlaneteInformation();
                ~PlaneteInformation();

                void renderInfo(RenderData &render_data, std::string name_body);
        };


#endif