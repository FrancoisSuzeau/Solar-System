/*
AUTHOR : SUZEAU François

DATE : 06/02/2022

MODULE : Objects::TexturedObjects::SquareTextured::LensFlare

NAMEFILE : FlareTexture.hpp

PURPOSE : 
*/

#ifndef FLARETEXTURE_H
#define FLARETEXTURE_H


/********************************************************************* includes *********************************************************************/

        #include <iostream>
        #include "../../../BasicObjects/Square.hpp"
        #include "../../../../Loader/Loader.hpp"
        #include <cassert>

/********************************************************************* class definition *********************************************************************/
        
        class FlareTexture: public Square
        {
            private:

                typedef Square super;
            
                // int             m_bytes_coord_size;
                // float           m_coord[12];

                // glm::mat4       transform_mat;
                // glm::vec3       m_pos;
                int             texture_w;
                int             texture_h;
                // GLuint          texture_id;

                // void load();

                // bool loadTextureFromFile(std::string text_path);
                
            public:

                FlareTexture(float size, std::string const type, std::string const texture_path);
                ~FlareTexture();

                void transform(glm::vec3 ship_pos = glm::vec3(0.f), Input *input = nullptr) override;
                void sendToShader(DataManager &data_manager) override;
                void clean();

                // void display(RenderData &render_data, float brightness);

                // void setPositionFlareText(glm::vec3 new_pos);
                // void transformMat(bool do_scale = false, glm::vec3 scale = glm::vec3(1.0));
            
        };


#endif