/*
AUTHOR : SUZEAU François

DATE : 29/05/2021

MODULE : Application::Camera

NAMEFILE : Camera.hpp

PURPOSE : header of the Camera class

*/

#ifndef CAMERA_H
#define CAMERA_H


/********************************************************************* includes *********************************************************************/

        #include "../../InOut/Input/Input.hpp"
        #include "../../Objects/Spaceship/Spaceship.hpp"

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
                glm::vec3   m_position;
                glm::vec3   m_target_point;

                float           distance_from_ship;
                float           angle_around_player;
                float           pitch;

                Spaceship       *m_ship;

                void    calculatePitch(Input *input);
                void    calculateAngleAroundShip(Input *input);
                float   calculateHorizontalDistance();
                float   calculateVerticalDistance();
                void    calculateCameraPostion(float horizontal_distance, float vertical_distance);
                void    correctTarget(Input *input);
                

            public:
            
                Camera(glm::vec3 position, glm::vec3 target_point, glm::vec3 vertical_axe, Spaceship *ship = nullptr);
                ~Camera();


                void    move(Input *input, bool move);
                void    lookAt(glm::mat4 &view);
                void    setDistFromShip(float const new_val);
                glm::vec3 getPosition() const;

                
        };


#endif