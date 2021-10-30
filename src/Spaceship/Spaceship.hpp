/*
AUTHOR : SUZEAU François

DATE : 17/10/2021

MODULE : Spaceship

NAMEFILE : Spaceship.hpp

PURPOSE : header of the Spaceship class
*/

#ifndef SPACESHIP_H
#define SPACESHIP_H


/********************************************************************* includes *********************************************************************/

        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>
        #include <glm/gtc/matrix_inverse.hpp>
        #include <glm/gtx/string_cast.hpp>

        #include <GL/glew.h>

        #include <iostream>
        #include <fstream>
        #include <sstream>
        #include <iostream>
        #include <map>
        #include <string>
        #include <math.h>
        #include <vector>
        #include <Windows.h>
        

        #include "../Shader/Shader.hpp"
        #include "../Model/Model.hpp"
        #include "../Input/Input.hpp"

       

/********************************************************************* class definition *********************************************************************/

        class Spaceship
        {
            
            private:

                Model                   *m_spaceship_model;
                std::vector<glm::mat4>  m_model_light_matrice; //Use a vector to avoid passing the two matrice in parameter list
                                                                //there only will be two : model matrice of the ship and light matrice of the diffuse light

                float m_pitch;
                float m_yaw;
                float           m_sensibility;
                float           m_speed;

                glm::vec3 m_current_pos;
                glm::vec3 m_ship_orientation;
                glm::vec3 m_lateral_move;

                glm::mat4 yaw_mat;
                glm::mat4 pitch_mat;

                void positioningShip();

                void orientateShip(Input input);
                void rotateFromPitch(Input input);
                void rotateFromYaw(Input input);

                void scalingShip();

                void computeMatrice();

                void move(Input input);

                
            public:
            
                Spaceship(std::string const path);
                ~Spaceship();

                void drawSpaceship(std::vector<glm::mat4> projection_view_mat, bool hdr, Shader *model_shader, Input input);
                float getRotX() const;
                float getRotY() const;
                glm::vec3       getPosition() const;
                glm::vec3       getOrientation() const;
                glm::vec3       getLateralMove() const;
                float getSpeed() const;
                void setSpeed(float speed);
                void setMinimumSpeed();
                void setMaximumSpeed();

                
        };


#endif