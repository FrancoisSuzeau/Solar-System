/*
AUTHOR : SUZEAU François

DATE : 30/10/2021

MODULE : AsteroidField

NAMEFILE : AsteroidField.hpp

PURPOSE : header of the AsteroidField class
*/

#ifndef ASTEROFIELD_H
#define ASTEROFIELD_H


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
        

        #include "../../Shader/Shader.hpp"
        #include "../../Model/Model.hpp"

       

/********************************************************************* class definition *********************************************************************/

        class AsteroidField
        {
            
            private:

                Model                           *asteroid;
                Shader                          *m_model_shader;
                unsigned int                    m_amount;
                glm::mat4                       *modelMatrices;

                unsigned int buffer1;
 
                void initModel();
                void initInstanced(glm::mat4 *Matrices);
                void rotateAsteroid(glm::mat4 &view);

            public:
            
                AsteroidField(Shader *model_shader);
                ~AsteroidField();

                void drawAsteroidField(std::vector<glm::mat4> projection_view_mat, bool hdr);

              

                
        };


#endif