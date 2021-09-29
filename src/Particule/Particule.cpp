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
Particule::Particule() : m_senseFandB(0), m_senseLandR(0), m_speed(0)
{
    initParticles();

    m_sphere_particle = new Sphere(1, 5, 5);
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

        m_particle_data1[i].x = myRand(-5.0, 5.0);
        m_particle_data1[i].y = myRand(-5.0, 5.0);
        m_particle_data1[i].z = myRand(-3.0, 0.0);
        m_particle_data1[i].id = 1;

        m_particle_data2[i].x = myRand(-5.0, 5.0);
        m_particle_data2[i].y = myRand(-5.0, 5.0);
        m_particle_data2[i].z = myRand(-3.0, 0.0);
        m_particle_data2[i].id = 2;

    }
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** drawParticles ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Particule::drawParticles(glm::mat4 &projection, glm::mat4 &modelview, Input input, float speed)
{
    glm::mat4 save = modelview;

        determineOrientation(projection, modelview, input);
        m_speed = 1 * speed / 200;
        if(m_speed < 0.188)
        {
            m_speed = 0.188;
        }

        for (int i(0); i < MAX_PARTICLES; i++)
        {

            drawOneParticle(projection, modelview, m_particle_data1[i]);
            drawOneParticle(projection, modelview, m_particle_data2[i]);

            moveParticleFandB(m_particle_data1[i]);
            moveParticleFandB(m_particle_data2[i]);

            moveParticleLandR(m_particle_data1[i]);
            moveParticleLandR(m_particle_data2[i]);
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
void Particule::moveParticleFandB(particles &particle)
{
    if((particle.z >= -3.0) && (particle.z <= 0.0))
    {
        switch(particle.id)
        {
            case 1:
                particle.z = particle.z + (0.06 * m_senseFandB * m_speed);
                break;
            case 2:
                particle.z = particle.z + (0.02 * m_senseFandB * m_speed);
                break;
            default:
                break;
        }
    }
    

    if((particle.z > 0.0) || (particle.z < -3.0))
    {
        particle.x = myRand(-5.0, 5.0);
        particle.y = myRand(-5.0, 5.0);
        particle.z = myRand(-3.0, 0.0);
    }
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** moveParticle ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Particule::moveParticleLandR(particles &particle)
{
    if((particle.x >= -5.0) && (particle.x <= 5.0))
    {
        switch(particle.id)
        {
            case 1:
                particle.x = particle.x + (0.06 * m_senseLandR * m_speed);
                break;
            case 2:
                particle.x = particle.x + (0.02 * m_senseLandR * m_speed);
                break;
            default:
                break;
        }
    }
    

    if((particle.x > 5.0) || (particle.x < -5.0))
    {
        particle.x = myRand(-5.0, 5.0);
        particle.y = myRand(-5.0, 5.0);
        particle.z = myRand(-3.0, 0.0);
    }
    

    
}

/***********************************************************************************************************************************************************************/
/*********************************************************************** determineOrientation **************************************************************************/
/***********************************************************************************************************************************************************************/
void Particule::determineOrientation(glm::mat4 &projection, glm::mat4 &modelview, Input input)
{
    if(input.getKey(SDL_SCANCODE_A))
    {
        m_senseLandR = 1;
        m_senseFandB = 0;

    }
    else if(input.getKey(SDL_SCANCODE_D))
    {
        m_senseLandR = -1;
        m_senseFandB = 0;

    }
    else if(input.getKey(SDL_SCANCODE_S))
    {
        m_senseFandB = -1;
        m_senseLandR = 0;

    }
    else if(input.getKey(SDL_SCANCODE_W))
    {
        m_senseFandB = 1;
        m_senseLandR = 0;

    }
    else
    {
        m_senseLandR = 0;
        m_senseFandB = 0;
    }
}