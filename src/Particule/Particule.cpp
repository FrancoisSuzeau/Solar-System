/*
AUTHOR : SUZEAU François

DATE : 27/09/2021

MODULE : Particule

NAMEFILE : Particule.cpp

PURPOSE : class Particule
*/

#include "Particule.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Particule::Particule()
{
    initParticles();

    screen_width = GetSystemMetrics(SM_CXSCREEN);
    screen_height = GetSystemMetrics(SM_CYSCREEN);

    m_sphere_particle = new Sphere(1, 20, 20);
    if(m_sphere_particle == nullptr)
    {
        exit(EXIT_FAILURE);
    }

    m_sphere_shader = new Shader("../src/Shader/Shaders/sphereShader.vert", "../src/Shader/Shaders/simpleSphereShader.frag");
    if(m_sphere_shader == nullptr)
    {
        exit(EXIT_FAILURE);
    }
    m_sphere_shader->loadShader();
}

Particule::~Particule()
{
    if(m_sphere_shader != nullptr)
    {
        delete m_sphere_shader;
    }

    if(m_sphere_particle != nullptr)
    {
        delete m_sphere_particle;
    }
}

/***********************************************************************************************************************************************************************/
/************************************************************************************ myRand ***************************************************************************/
/***********************************************************************************************************************************************************************/
double Particule::myRand(double const min, double const max)
{
    return (double) (min + ((float) rand() / RAND_MAX * (max - min + 1.0)));
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** initParticles ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Particule::initParticles()
{
    for (int i(0); i < MAX_PARTICLES; i++)
    {

        m_particle_data[i].x = myRand(-10.0, 10.0);
        m_particle_data[i].y = myRand(-10.0, 10.0);
        m_particle_data[i].z = myRand(-2.5, 0.0);

        
        
    }
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** drawParticles ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Particule::drawParticles(glm::mat4 &projection, glm::mat4 &modelview)
{
    glm::mat4 save = modelview;

        for (int i(0); i < MAX_PARTICLES; i++)
        {

            modelview = translate(modelview, vec3(m_particle_data[i].x, m_particle_data[i].y, m_particle_data[i].z));
            modelview = scale(modelview, (vec3(0.002)));

            if((m_sphere_particle != nullptr) && (m_sphere_shader != nullptr))
            {
                m_sphere_particle->draw(projection, modelview, 1.0, m_sphere_shader);
            }

            modelview = save;

            moveParticle(m_particle_data[i]);
        }
        

    modelview = save;
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** moveParticle ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Particule::moveParticle(particles &particle)
{
    if((particle.z >= -2.5) && (particle.z <= 0.0))
    {
        particle.z = particle.z + 0.05;
    }

    if(particle.z > 0.0)
    {
        particle.x = myRand(-10.0, 10.0);
        particle.y = myRand(-10.0, 10.0);
        particle.z = myRand(-2.5, 0.0);
    }
}