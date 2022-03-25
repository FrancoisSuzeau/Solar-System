/*
AUTHOR : SUZEAU François

DATE : 10/06/2021

MODULE : Objects::TexturedObjects::SquareTextured::Ring

NAMEFILE : Ring.hpp

PURPOSE : header of the Ring class
*/

#ifndef RING_H
#define RING_H


/********************************************************************* includes *********************************************************************/

        #include <string>
        #include <cassert>
        #include <vector>
        #include <iostream>

        #include <GL/glew.h>

        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include "../../../BasicObjects/Square.hpp"
        #include "../../../../Loader/Loader.hpp"
        

/********************************************************************* class definition *********************************************************************/

        class Ring: public Square
        {

            private:

                typedef Square super;

                // Texture         m_texture;
                // Texture         *m_normal_surf;
                // Texture         *m_disp_surf;
                // float           m_coord[12];
                // int             m_bytes_coord_size;
                // float heighhtScale;

            public:
                Ring(float size, std::vector<std::string> textures_path, std::string const type, int shininess);
                ~Ring();

                void transform(glm::vec3 ship_pos = glm::vec3(0.f), Input *input = nullptr) override;
                void sendToShader(DataManager &data_manager) override;

                // void display(RenderData &render_data);
                // void load();
                // void updatePosRing(glm::vec3 pos_plan);
                
        };


#endif