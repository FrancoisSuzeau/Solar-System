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
                float           m_inclinaison_angle;
                float           m_speed_rotation;
                float           m_rotation_angle;

            public:

                Object();
                virtual ~Object();

                virtual void transform(Input *input = nullptr) = 0;

                void updatePosition(glm::vec3 const new_pos);
                void rotateObject(glm::mat4 &model, float angle);
                void inclineObject(glm::mat4 &model, float angle);
                void translateObject(glm::mat4 &model, glm::vec3 pos);
                void scaleObject(glm::mat4 &model, glm::vec3 size);
                void updateColor(float const color);
                void updateSize(glm::vec3 const new_size);

                glm::vec3 getSize() const;
                glm::vec3 getPosition() const;
                glm::mat4 getModelMat();
                float getColor() const;
            
        };


#endif