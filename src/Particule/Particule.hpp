/*
AUTHOR : SUZEAU François

DATE : 27/09/2021

MODULE : Particule

NAMEFILE : Particule.hpp

PURPOSE : header of the Particule class
*/

#ifndef PARTICULE_H
#define PARTICULE_H


/********************************************************************* includes *********************************************************************/

        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>
        #include <glm/gtc/matrix_inverse.hpp>
        #include <glm/gtx/string_cast.hpp>

        #include <iostream>
        #include <string>
        #include <math.h>
        #include <Windows.h>

        #include "../Shader/Shader.hpp"
        #include "../CelestialBody/Geometry/Sphere.hpp"

        #define MAX_PARTICLES 1000

        typedef struct particles {

                    double  x;
                    double  y;
                    double  z;

        } particles;
        

/********************************************************************* class definition *********************************************************************/

        class Particule
        {
            
            private:

                particles   m_particle_data[MAX_PARTICLES];

                Sphere      *m_sphere_particle;
                Shader      *m_sphere_shader;

                int screen_width;
                int screen_height;

                double myRand(double const min, double const max);
                void moveParticle(particles &particle);
                void initParticles();

            public:
            
                Particule();
                ~Particule();

                
                void drawParticles(glm::mat4 &projection, glm::mat4 &modelview);
                

                

                


        };


#endif