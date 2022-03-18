/*
AUTHOR : SUZEAU François

DATE : 16/06/2021

MODULE : CelestialBody.Star

NAMEFILE : Star.h

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
        #include "../../../Application/Texture/Texture.hpp"

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

                Texture         m_texure_surface;
                // std::vector<flare_data>      m_flares;
                // std::string     m_name;

                // void calculateFlarePos(glm::vec2 sunToCenter, glm::vec2 sunCoords, flare_data f_d);

                // glm::vec2 convertToScreenSpace(glm::vec3 sunPos, glm::mat4 viewMat, glm::mat4 projMat);
                // bool displayTexture(RenderData &render_data);
               
        
            public:

                // Star(const float radius, const unsigned int longSegs, const unsigned int latSegs, std::string const texture_surf, std::string const name, float const real_size);
                Star(float size);
                ~Star();
                // void display(RenderData &render_data);
                
                // void renderFlare(RenderData &render_data);
                
        };


#endif