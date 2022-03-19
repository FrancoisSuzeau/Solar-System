/*
AUTHOR : SUZEAU François

DATE : 16/06/2021

MODULE : Objects::TexturedObjects::Star

NAMEFILE : Star.hpp

PURPOSE : header of the Star class
*/

#ifndef STAR_H
#define STAR_H


/********************************************************************* includes *********************************************************************/

        // #include "../Geometry/Sphere.hpp"

        // #include "../../OpenGlSketch/RenderData.hpp"

        // #include "../../LensFlare/FlareTexture.hpp"

        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include <GL/glew.h>
        #include <iostream>
        #include <string>
        #include <cstring>
        #include <vector>
        #include <cassert>

        #include "../../BasicObjects/Sphere.hpp"
        #include "../../../Loader/Loader.hpp"
        // #include "../../../Application/Texture/Texture.hpp"

        // typedef struct flare_data {

        //         FlareTexture    *flare;
        //         glm::vec3       size;
        //         float           depth_size;
        //         float           strenght;

        // } flare_data;
        

/********************************************************************* class definition *********************************************************************/

        class Star : public Sphere
        {
            
            private:

                // Texture         m_texure_surface;
                typedef         Sphere super;
                // std::vector<flare_data>      m_flares;
                // std::string     m_name;

                // void calculateFlarePos(glm::vec2 sunToCenter, glm::vec2 sunCoords, flare_data f_d);

                // glm::vec2 convertToScreenSpace(glm::vec3 sunPos, glm::mat4 viewMat, glm::mat4 projMat);
               
        
            public:

                Star(float size);
                ~Star();

                void transform(Input *input = nullptr) override;
                void sendToShader(DataManager &data_manager) override;

                


                // void display(RenderData &render_data);
                
                // void renderFlare(RenderData &render_data);
                
        };


#endif