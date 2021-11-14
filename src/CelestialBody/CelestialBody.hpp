/*
AUTHOR : SUZEAU François

DATE : 29/05/2021

MODULE : CelestialBody

NAMEFILE : CelestialBody.h

PURPOSE : Interface CelestialBody
*/

#ifndef FORME_H
#define FORME_H


/********************************************************************* includes *********************************************************************/

        #include "../Shader/Shader.hpp"

        #include <string>
        #include <vector>
        #include <iostream>
        #include <GL/glew.h>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

/********************************************************************* class definition *********************************************************************/
        using namespace glm;

        class CelestialBody
        {
            protected:
            
                
                float       m_real_size;
                float       m_size;
                float       m_inclinaison_angle;
                float       m_rotation_angle;
                float       m_speed_rotation;
                glm::vec3   m_current_position;
                glm::vec3   m_initial_pos;
                glm::mat4   m_model_mat;

            public:

                virtual void display(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, bool hdr, Shader *body_shader = nullptr, Shader *ring_shader = nullptr) = 0;

                void setPosition(glm::vec3 new_position)
                {
                    m_current_position = new_position;
                }

                void setInclinaisonAngle(float inclinaison)
                {
                    m_inclinaison_angle = inclinaison;
                }
                
                void rotateCelestialBody(glm::mat4 &model, float angle)
                {
                    model = rotate(model, glm::radians(angle), vec3(0.0, 0.0, 1.0));
                }

                void inclineCelestialBody(glm::mat4 &model, float angle)
                {
                    model = rotate(model, glm::radians(angle), vec3(0.0, 1.0, 0.0));
                }

                void translateCelestialBody(glm::mat4 &model, glm::vec3 new_position)
                {
                    model = translate(model, new_position);
                }

                void scaleCelestialBody(glm::mat4 &model, float size)
                {
                    model = scale(model, vec3(size, size, size));
                }

                float getInclineAngle() const
                {
                    return m_inclinaison_angle;
                }

                glm::vec3 getCurrentPos()
                {
                    return m_current_position;
                }

                float getRealSize() const
                {
                    return m_real_size;
                }

                void updatePosition()
                {
                    m_model_mat = glm::mat4(1.0f);
                    // m_current_position = m_initial_pos;
                    //postionning body
                    translateCelestialBody(m_model_mat, m_current_position);

                    //making the planete inclinaison
                    inclineCelestialBody(m_model_mat, m_inclinaison_angle);

                    //making the planete rotation
                    m_rotation_angle += m_speed_rotation;
                    if(m_rotation_angle >= 360)
                    {
                        m_rotation_angle -= 360;
                    }
                    rotateCelestialBody(m_model_mat, m_rotation_angle);

                    //scaling on his real size
                    scaleCelestialBody(m_model_mat, m_real_size);

                    // std::cout << m_name << std::endl;
                }

                virtual ~CelestialBody() {}
                
            
        };


#endif