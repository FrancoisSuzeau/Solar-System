/*
AUTHOR : SUZEAU François

DATE : 06/02/2022

MODULE : FlareTexture

NAMEFILE : FlareTexture.hpp

PURPOSE : Interface FlareTexture
*/

#ifndef FLARETEXTURE_H
#define FLARETEXTURE_H


/********************************************************************* includes *********************************************************************/

        #include <iostream>

        #include "../CelestialBody/Geometry/Disk.hpp"
        #include "../OpenGlSketch/RenderData.hpp"
        #include <cassert>

/********************************************************************* class definition *********************************************************************/
        
        class FlareTexture: public Disk
        {
            private:
            
                int             m_bytes_coord_size;
                float           m_coord[12];

                glm::mat4       transform_mat;
                glm::vec3       m_pos;
                int             texture_w;
                int             texture_h;
                GLuint          texture_id;

                void load();

                bool loadTextureFromFile(std::string text_path);
                
            public:

                FlareTexture(float size, std::string const text_path);
                FlareTexture();
                ~FlareTexture();

                void display(RenderData &render_data, float brightness);

                void setPositionFlareText(glm::vec3 new_pos);
                void transformMat();
            
        };


#endif