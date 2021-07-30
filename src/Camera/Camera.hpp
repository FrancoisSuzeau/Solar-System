/*
AUTHOR : SUZEAU François

DATE : 29/05/2021

MODULE : Camera

NAMEFILE : Camera.h

PURPOSE : header of the Camera class
*/

#ifndef CAMERA_H
#define CAMERA_H


/********************************************************************* includes *********************************************************************/

        #include "../Input/Input.hpp"

        #include <string>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>
        

/********************************************************************* class definition *********************************************************************/

        class Camera
        {

            private:

                float       m_phi;
                float       m_theta;
                glm::vec3   m_orientation;

                glm::vec3   m_vertical_axe;
                glm::vec3   m_lateral_move;

                glm::vec3   m_position;
                glm::vec3   m_target_point;

                float       m_sensibility;
                float       m_speed;
                

            public:
            
                Camera();
                Camera(glm::vec3 position, glm::vec3 target_point, glm::vec3 vertical_axe, float sensibility, float speed);
                ~Camera();


                void orientate(int x_rel, int y_rel);
                void move(Input const &input);
                void lookAt(glm::mat4 &model_view);

                void setPosition(glm::vec3 position);
                glm::vec3 getPosition() const;

                float getSensibility() const;
                void setSensibility(float sensibility);

                float getSpeed() const;
                void setSpeed(float speed);

                glm::vec3 getOrientation() const;

                float getPhi() const;
                float getTheta() const;

                void setTargetPoint(glm::vec3 target_point);
                glm::vec3 getTargetPoint() const;

                
        };


#endif