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
        m_particle_data[i].active = true;
        m_particle_data[i].life = 1.0;

        m_particle_data[i].fade = myRand(0.01, 0.05);

        m_particle_data[i].xi = myRand(-10.0, 10.0);
        m_particle_data[i].yi = myRand(-10.0, 10.0);
        m_particle_data[i].zi = myRand(10.0, 20.0);

        m_particle_data[i].xg = 0.0;
        m_particle_data[i].yg = 0.0;
        m_particle_data[i].zg = -1.0;
        
    }
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** drawParticles ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Particule::drawParticles(glm::mat4 &projection, glm::mat4 &modelview)
{
    glm::mat4 save = modelview;

        modelview = translate(modelview, vec3(1, 8000, 1));
        modelview = scale(modelview, vec3(50, 50, 50));

        if((m_sphere_shader != nullptr) && (m_sphere_particle != nullptr))
        {
            m_sphere_particle->draw(projection, modelview, m_sphere_shader);
        }

    modelview = save;
}