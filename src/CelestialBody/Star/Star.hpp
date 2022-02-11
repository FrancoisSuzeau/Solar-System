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

        #include "../Geometry/Sphere.hpp"
        #include "../../Texture/Texture.hpp"

        #include "../../OpenGlSketch/RenderData.hpp"

        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include <GL/glew.h>
        #include <iostream>
        #include <string>
        #include <cstring>
        #include <vector>
        #include <cassert>
        

/********************************************************************* class definition *********************************************************************/

        class Star: public Sphere
        {
            
            private:

                Texture         m_cloud_texture;
                std::string     m_name;
        
            public:

                Star(const float radius, const unsigned int longSegs, const unsigned int latSegs, std::string const texture_surf, std::string const name, float const real_size);
                Star();
                ~Star();
                void display(RenderData &render_data);
                bool displayTexture(RenderData &render_data);
                
                
        };


#endif