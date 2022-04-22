/*
AUTHOR : SUZEAU François

DATE : 29/05/2021

MODULE : Object

NAMEFILE : Object.hpp

PURPOSE : Interface Object
*/

#ifndef OBJECTS_H
#define OBJECTS_H


/********************************************************************* includes *********************************************************************/

        #include <iostream>

        #include <GL/glew.h>

        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include <vector>

        #include "../Application/DataManager.hpp"
        #include "../ErrorHandler/ErrorHandler.hpp"
        #include "../InOut/Input/Input.hpp"

        

/********************************************************************* class definition ***************************************************************/

        class Object
        {
            protected:

                glm::vec3   m_position;
                glm::mat4   m_model_mat;
                glm::vec3   m_size;
                glm::vec3   m_inclinaison_vector;
                glm::vec3   m_rotation_vector;
                float           m_color;
                glm::vec3       m_color_vector;
                float           m_inclinaison_angle;
                float           m_speed_rotation;
                float           m_rotation_angle;
                std::string     m_type;

                int             m_shininess = 0;

                std::vector<GLuint>          surface_tex_ids;
                GLuint                          normal_texture_id = 0;

            public:

                Object(std::string const type);
                ~Object();

                virtual void transform(glm::vec3 ship_pos = glm::vec3(0.f), Input *input = nullptr) = 0;
                virtual void sendToShader(DataManager &data_manager) = 0;

                void updatePosition(glm::vec3 const new_val);
                void rotateObject(glm::mat4 &model, float angle);
                void inclineObject(glm::mat4 &model, float angle);
                void translateObject(glm::mat4 &model, glm::vec3 pos);
                void scaleObject(glm::mat4 &model, glm::vec3 size);
                void updateColor(float const color);
                void updateColor(glm::vec3 const new_color);
                void updateSize(glm::vec3 const new_size);

                glm::vec3 getSize() const;
                glm::vec3 getPosition() const;
                glm::mat4 getModelMat();
                float getColor() const;
                std::string getType() const;

                GLuint getTextureID(int index) const;
                GLuint getNormalTextureID() const;
                GLuint getDispTextureID()   const;

                void clean();
            
        };


#endif