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
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

/********************************************************************* class definition *********************************************************************/
        using namespace glm;

        class CelestialBody
        {
            protected:
            
                Shader      m_shader;
                float       m_real_size;
                float       m_size;
                float       m_inclinaison_angle;
                float       m_rotation_angle;
                float       m_speed_rotation;
                glm::vec3   m_current_position;
                glm::vec3   m_initial_pos;

            public:

                virtual void display(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos) = 0;
                

                void rotateCelestialBody(glm::mat4 &modelview, float angle)
                {
                    modelview = rotate(modelview, angle, vec3(0.0, 0.0, 1.0));
                }

                void inclineCelestialBody(glm::mat4 &modelview, float angle)
                {
                    modelview = rotate(modelview, angle, vec3(0.0, 1.0, 0.0));
                }

                void translateCelestialBody(glm::mat4 &modelview, glm::vec3 new_position)
                {
                    modelview = translate(modelview, new_position);
                }

                void scaleCelestialBody(glm::mat4 &modelview, float size)
                {
                    modelview = scale(modelview, vec3(size, size, size));
                }

                float getInclineAngle() const
                {
                    return m_inclinaison_angle;
                }

                glm::vec3 getCurrentPos()
                {
                    return m_current_position;
                }

                virtual ~CelestialBody() {}
                
            
        };


#endif