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
        #include "../Spaceship/Spaceship.hpp"

        #include <string>
        #include <math.h>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>
        #include <vector>
        

/********************************************************************* class definition *********************************************************************/

        class Camera
        {

            private:

                glm::vec3   m_vertical_axe;
                glm::vec3   m_lateral_move;

                glm::vec3   m_position;
                glm::vec3   m_target_point;
                glm::vec3 AB;

                float           distance_from_ship;
                float           angle_around_player;
                float           pitch;

                Spaceship *m_ship;

                void calculatePitch(Input const &input);
                void calculateYaw(Input const &input);
                void calculateAngleAroundShip(Input const &input);
                float calculateHorizontalDistance(Input const &input);
                float calculateVerticalDistance(Input const &input);
                void calculateCameraPostion(float horizontal_distance, float vertical_distance, Input const &input);

                void correctTarget(Input const &input);
                

            public:
            
                Camera();
                Camera(glm::vec3 position, glm::vec3 target_point, glm::vec3 vertical_axe, Spaceship *ship = nullptr);
                ~Camera();


                void move(Input const &input, bool move);
                void lookAt(glm::mat4 &model_view);

        
                glm::vec3 getPosition() const;

                glm::vec3 getVerticalaxe() const;
                glm::vec3 getTargetPoint() const;

                void setDistFromShip(float const new_val);
                float getDistFromShip() const;

                
        };


#endif