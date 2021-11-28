/*
AUTHOR : SUZEAU François

DATE : 27/11/2021

MODULE : CelestialBody.Planete

NAMEFILE : Planete.h

PURPOSE : header of the Planete class
*/

#ifndef PLANETE_H
#define PLANETE_H


/********************************************************************* includes *********************************************************************/

        #include "../../Texture/Texture.hpp"
        #include "../../Text/Text.hpp"
        #include "../../Atmosphere/Atmosphere.hpp"
        #include "../Ring/Ring.hpp"
        #include "../System/System.hpp"

        #include <string>
        #include <vector>
        #include <iostream>
        #include <cassert>

        #include <GL/glew.h>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>
        

/********************************************************************* class definition *********************************************************************/

        class Planete
        {
            
            protected:

                std::vector<Texture*>           m_textures;
                Texture                         *m_normal_surface;
                std::string                     m_name;
                Text                            *m_name_renderer;
                Atmosphere                      *m_atmosphere;
                Ring                            *m_ring;
                float                           m_real_size;
                float                           m_size;
                float                           m_inclinaison_angle;
                float                           m_rotation_angle;
                float                           m_speed_rotation;
                glm::vec3                       m_current_position;
                glm::vec3                       m_initial_pos;
                glm::mat4                       m_model_mat;

                std::string                     m_type_plan;

                float                           m_oppacity;
                
            public:

                Planete(init_data data, TTF_Font *police);
                Planete();
                ~Planete();
                
                std::string getName() const;
                float getRadiusFromCam(glm::vec3 camPos);
                float getPhiFromCam(glm::vec3 camPos);
                float getThetaFromCam(glm::vec3 camPos, float r);
                std::string getTypePlan() const;
                std::vector<Texture*> getPlanTexture() const;
                Texture* getNormalTexture() const;

                glm::mat4 getModelMat() const;
                Text *getNameRender() const;
                glm::vec3 getPosition() const;
                float getOppacity() const;

                Ring *getRing() const;

                Atmosphere *getAtmosphere() const;

                void updatePosition();
                
        };


#endif