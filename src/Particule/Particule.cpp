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

        m_particle_data1[i].x = myRand(-10.0, 10.0);
        m_particle_data1[i].y = myRand(-10.0, 10.0);
        m_particle_data1[i].z = myRand(-2.5, 2.5);
        m_particle_data1[i].id = 1;

        m_particle_data2[i].x = myRand(-15.0, 15.0);
        m_particle_data2[i].y = myRand(-15.0, 15.0);
        m_particle_data2[i].z = myRand(-3.0, 3.5);
        m_particle_data2[i].id = 2;

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

            drawOneParticle(projection, modelview, m_particle_data1[i]);
            drawOneParticle(projection, modelview, m_particle_data2[i]);

            moveParticle(m_particle_data1[i]);
            moveParticle(m_particle_data2[i]);
        }
        

    modelview = save;
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** drawOneParticle ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Particule::drawOneParticle(glm::mat4 &projection, glm::mat4 &modelview, particles &particle)
{
    glm::mat4 save = modelview;

        modelview = translate(modelview, vec3(particle.x, particle.y, particle.z));
        modelview = scale(modelview, (vec3(0.002)));

        if((m_sphere_particle != nullptr) && (m_sphere_shader != nullptr))
        {
            m_sphere_particle->draw(projection, modelview, 1.0, m_sphere_shader);
        }

        modelview = save;

    modelview = save;
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** moveParticle ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Particule::moveParticle(particles &particle)
{
    switch(particle.id)
    {
        case 1:
            if((particle.z >= -2.5) && (particle.z <= 2.5))
            {
                particle.z = particle.z + 0.1;
            }
            if(particle.z > 2.5)
            {
                particle.x = myRand(-10.0, 10.0);
                particle.y = myRand(-10.0, 10.0);
                particle.z = myRand(-2.5, 2.5);
            }
            break;
        case 2:
            if((particle.z >= -3.0) && (particle.z <= 3.5))
            {
                particle.z = particle.z + 0.04;
            }
            if(particle.z > 3.5)
            {
                particle.x = myRand(-15.0, 15.0);
                particle.y = myRand(-15.0, 15.0);
                particle.z = myRand(-3.0, 3.5);
            }
            break;
        default:
            break;
    }
    

    
}