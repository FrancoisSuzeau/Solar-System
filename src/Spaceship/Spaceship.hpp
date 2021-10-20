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

        #include <assimp/Importer.hpp>
        #include <assimp/scene.h>
        #include <assimp/postprocess.h>

        

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
        #include "../Camera/Camera.hpp"

       

/********************************************************************* class definition *********************************************************************/

        class Spaceship
        {
            
            private:

                Model                   *m_spaceship_model;
                std::vector<glm::mat4>  m_model_light_matrice; //Use a vector to avoid passing the matrice in parameter list
                                                                //there only will be two : model matrice of the ship and light matrice of the diffuse light

                float cam_phi;
                float cam_theta;

                glm::vec3               m_current_pos_from_cam; //x = 0.0f, y = -4.8f, z = -1.2f


                
                void positioningShip(Camera *camera, Input input);
                void setCartesianCoordinate(glm::vec3 cam_pos);

                void orientateShip(Camera *camera);

                void scalingShip();

                
            public:
            
                Spaceship(std::string const path);
                ~Spaceship();

                void drawSpaceship(std::vector<glm::mat4> projection_view_mat, bool hdr, Shader *model_shader, Camera *camera, Input input);

                
        };


#endif