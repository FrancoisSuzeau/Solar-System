/*
AUTHOR : SUZEAU François

DATE : 12/01/2022

MODULE : Physique

NAMEFILE : Physique.hpp

PURPOSE : Interface Physique
*/

#ifndef PHYSIQUE_H
#define PHYSIQUE_H


/********************************************************************* includes *********************************************************************/

        #include <string>
        #include <vector>
        #include <map>
        #include <iostream>
        #include <math.h>
        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        typedef struct body_datas {

                glm::vec3 host_position;
                double host_mass; // in kilograme
                // std::vector<glm::vec3> companion_position;
                std::vector<double> mass_companion;

        } planete_datas;

/********************************************************************* class definition *********************************************************************/
        
        class Physique
        {
            private:
            
                
                

            public:

                static float G_const;
                static std::map<std::string, body_datas> bodys_data;

                Physique();
                ~Physique();
                static void InitPhysique();
                static float getDistanceFromCam(std::string name_body, glm::vec3 ship_pos);
                static std::vector<double> getGravInfluence(std::string name_body, std::vector<float> distance);
                
                
            
        };


#endif