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

                Sphere(float size);
                ~Sphere();

                void transform(Input *input = nullptr) override;
                void sendToShader(DataManager &data_manager) override;
        };


#endif