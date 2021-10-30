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
        #include "../Input/Input.hpp"
        #include "../Spaceship/Spaceship.hpp"

        #define MAX_PARTICLES 1000

        typedef struct particles {

                    double      x;
                    double      y;
                    double      z;

                    int         id;

        } particles;
        

/********************************************************************* class definition *********************************************************************/

        class Particule
        {
            
            private:

                particles   m_particle_data1[MAX_PARTICLES];
                particles   m_particle_data2[MAX_PARTICLES];

                Sphere      *m_sphere_particle;
                Shader      *m_sphere_shader;
                Spaceship       *m_ship;
                float x_change;
                float y_change;
                float z_change;
                glm::vec3 ship_pos;

                double myRand(double const min, double const max);
                void moveParticleFandB(particles &particle); // forward and backward
                void moveParticleLandR(particles &particle); //left and right
                
                void drawOneParticle(glm::mat4 &projection, glm::mat4 &modelview, particles &particle, bool is_moving);
                void determineOrientation(glm::mat4 &projection, glm::mat4 &modelview, Input input);

                int             m_directionFandB;
                int             m_directionLandR;
                float           m_speed;

            public:
            
                Particule(Spaceship *ship);
                ~Particule();

                void initParticles(glm::vec3 target_point);
                void drawParticles(glm::mat4 &projection, glm::mat4 &modelview, Input input, bool is_moving, glm::vec3 target_point);
                
                

                

                


        };


#endif