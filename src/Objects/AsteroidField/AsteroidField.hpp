/*
AUTHOR : SUZEAU François

DATE : 30/10/2021

MODULE : Object::AsteroidField

NAMEFILE : AsteroidField.hpp

PURPOSE : header of the AsteroidField class
*/

#ifndef ASTEROIDFIELD_H
#define ASTEROIDFIELD_H


/********************************************************************* includes *********************************************************************/

        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>
        #include <glm/gtc/matrix_inverse.hpp>
        #include <glm/gtx/string_cast.hpp>

        #include <GL/glew.h>

        #include <iostream>
        #include <cassert>

        #include "../../Model/Model.hpp"
        #include "../Object.hpp"

       

/********************************************************************* class definition *********************************************************************/

        class AsteroidField : public Object
        {
            
            private:

                typedef Object super;

                Model                           *asteroid;
                unsigned int                    m_amount;
                glm::mat4                       *model_matrices;
                glm::vec3                       *m_positions;
                float                           *rotAngle;
                float                           *scaleM;
                // Texture                         *m_noramal_surface;
                // Texture                         *m_disp_surface;
                glm::vec3                       *m_rot_vector;

                unsigned int                    vbo;

                // float   heightScale;
 
                void                            initTransformations();
                void                            initInstances();

            public:
            
                AsteroidField(std::string const type);
                ~AsteroidField();

                void transform(glm::vec3 ship_pos = glm::vec3(0.f), Input *input = nullptr) override;
                void sendToShader(DataManager &data_manager) override;
                void clean();

                void render(DataManager &data_manager);

                // void updateCount(RenderData &render_data);

                // void updatePostion(glm::vec3 shipPos);

              

                
        };


#endif