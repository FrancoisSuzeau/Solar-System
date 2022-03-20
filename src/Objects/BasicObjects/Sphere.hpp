/*
AUTHOR : SUZEAU François

DATE : 06/06/2021

MODULE : Objects::BasicObjects

NAMEFILE : Sphere.hpp

PURPOSE : header of the Sphere class
*/

#ifndef SPHERE_H
#define SPHERE_H


/********************************************************************* includes *********************************************************************/

        #include "../Object.hpp"

/********************************************************************* class definition *********************************************************************/

        class Sphere: public Object
        {
            private:

                typedef Object super;
 
                
            public:

                Sphere(float size, std::string const type);
                ~Sphere();

                void transform(glm::vec3 ship_pos = glm::vec3(0.f), Input *input = nullptr) override;
                void sendToShader(DataManager &data_manager) override;
        };


#endif