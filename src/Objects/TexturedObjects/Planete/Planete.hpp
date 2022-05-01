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

        #include "../../BasicObjects/Sphere.hpp"
        #include "../../../Loader/Loader.hpp"
        #include "../SquareTextured/Ring/Ring.hpp"

        #include <string>
        #include <vector>
        #include <iostream>
        #include <cassert>

        #include <GL/glew.h>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #if defined(IMGUI_IMPL_OPENGL_ES2)
        #include <SDL_opengles2.h>
        #else
        #include <SDL2/SDL_opengl.h>
        #endif


        #include "../../../../lib/imgui/imgui.h"
        #include "../../../../lib/imgui/imgui_impl_sdl.h"
        #include "../../../../lib/imgui/imgui_impl_opengl3.h"


/********************************************************************* class definition *********************************************************************/

        class Planete : public Sphere
        {
                private:

                        typedef Sphere super;
                        float   m_oppacity;
                        std::string     m_name;
                        Ring            *m_ring = nullptr;
                        Sphere          *m_atmosphere = nullptr;
                        float           light_strength;
                        
            
                protected:

                        
                public:

                        Planete(body_data datas);
                        ~Planete();

                        void transform(glm::vec3 ship_pos = glm::vec3(0.f), Input *input = nullptr) override;
                        void sendToShader(DataManager &data_manager) override;

                        Ring*   getRing() const;
                        Sphere  *getAmosphere() const;
                        void    makeOtherChanges(DataManager &data_manager);
                        void    clean();
                        void renderName(DataManager &data_manager);
                        void loadDiffuseTexture();
                        void loadNormalTexture();
                        
                        // std::string getName() const;
                        // float getRadiusFromCam(glm::vec3 camPos);
                        // float getPhiFromCam(glm::vec3 camPos);
                        // float getThetaFromCam(glm::vec3 camPos, float r);
                        // std::string getTypePlan() const;
                        // std::vector<Texture*> getPlanTexture() const;
                        // Texture* getNormalTexture() const;
                        // Texture* getDispTexture() const;

                        // glm::mat4 getModelMat() const;
                        // Text *getNameRender() const;
                        // glm::vec3 getPosition() const;
                        // float getOppacity() const;
                        // float getSize() const;

                        // Atmosphere *getAtmosphere() const;
                        // bool getProximity() const;
                        // void setProximity(bool change);

                        // void updatePosition(glm::vec3 shipPos = glm::vec3(0.0f));
                        // void updateHeightScale();
                        // float getHeightScale() const;
                
        };


#endif