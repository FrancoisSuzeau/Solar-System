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
Particule::Particule(Spaceship *ship) : m_directionFandB(0), m_directionLandR(0), m_speed(0)
{
    

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

    m_ship = ship;
    if(m_ship == nullptr)
    {
        exit(EXIT_FAILURE);
    }

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
void Particule::initParticles(glm::vec3 target_point)
{
    for (int i(0); i < MAX_PARTICLES; i++)
    {

        m_particle_data1[i].x = target_point.x + myRand(-5.0, 5.0);
        m_particle_data1[i].y = target_point.y + myRand(-200.0, 200.0);
        m_particle_data1[i].z = target_point.z + myRand(-5.0, 5.0);
        m_particle_data1[i].id = 1;

        m_particle_data2[i].x = target_point.x + myRand(-5.0, 5.0);
        m_particle_data2[i].y = target_point.y + myRand(-10.0, 10.0);
        m_particle_data2[i].z = target_point.z + myRand(-5.0, 5.0);
        m_particle_data2[i].id = 2;

    }
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** drawParticles ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Particule::drawParticles(glm::mat4 &projection, glm::mat4 &modelview, Input input, bool is_moving, glm::vec3 target_point)
{
    glm::mat4 save = modelview;

        determineOrientation(projection, modelview, input);
        m_speed = 1 * m_ship->getSpeed() / 200;
        ship_pos = target_point;
        x_change = m_speed * sin(glm::radians(m_ship->getRotX()));
        y_change = m_speed * -cos(glm::radians(m_ship->getRotX()));
        z_change = m_speed * cos(glm::radians(m_ship->getRotY()));

        if(m_speed < 0.3)
        {
            m_speed = 0.3;
        }

        for (int i(0); i < MAX_PARTICLES; i++)
        {
            moveParticleFandB(m_particle_data1[i]);
            moveParticleFandB(m_particle_data2[i]);

            // moveParticleLandR(m_particle_data1[i]);
            // moveParticleLandR(m_particle_data2[i]);

            drawOneParticle(projection, modelview, m_particle_data1[i], is_moving);
            drawOneParticle(projection, modelview, m_particle_data2[i], is_moving);

        }
        

    modelview = save;
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** drawOneParticle ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Particule::drawOneParticle(glm::mat4 &projection, glm::mat4 &modelview, particles &particle, bool is_moving)
{
    glm::mat4 save = modelview;

    if(is_moving)
    {
        modelview = translate(modelview, vec3(particle.x, particle.y, particle.z));
        modelview = scale(modelview, (vec3(0.002f)));

        if((m_sphere_particle != nullptr) && (m_sphere_shader != nullptr))
        {
            glm::mat4 light(1.0f);
            glm::vec3 campos(0.0f);
            m_sphere_particle->display(projection, modelview, campos, true, m_sphere_shader);

            modelview = save;

        }
    }   

    modelview = save;
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** moveParticle ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Particule::moveParticleFandB(particles &particle)
{
    if((particle.y >= -10.0f + ship_pos.y) && (particle.y <= 10.0 + ship_pos.y))
    {
        switch(particle.id)
        {
            case 1:
                // particle.x += 0.06 * m_directionFandB * m_speed;
                particle.y += 0.006 * m_directionFandB;
                // particle.z += 0.06 * m_directionFandB * m_speed;
                break;
            case 2:
                // particle.x += 0.02 * m_directionFandB * m_speed;
                particle.y += 0.002 * m_directionFandB;
                // particle.z += 0.02 * m_directionFandB * m_speed;
                break;
            default:
                break;
        }
    }
    
    if((particle.y > 200.0f + ship_pos.y) || (particle.y < -200.0 + ship_pos.y))
    {
        particle.y = ship_pos.y + myRand(-200.0, 200.0);
    }
    
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** moveParticle ****************************************************************************/
/***********************************************************************************************************************************************************************/
void Particule::moveParticleLandR(particles &particle)
{
    // if((particle.x >= -5.0) && (particle.x <= 5.0))
    // {
    //     switch(particle.id)
    //     {
    //         case 1:
    //             particle.x += (0.06 * m_directionFandB * x_change);
    //             particle.y += (0.06 * m_directionFandB * y_change);
    //             particle.z += (0.06 * m_directionFandB * z_change);
    //             break;
    //         case 2:
    //             particle.x += (0.02 * m_directionFandB * x_change);
    //             particle.y += (0.02 * m_directionFandB * y_change);
    //             particle.z += (0.02 * m_directionFandB * z_change);
    //             break;
    //         default:
    //             break;
    //     }
    // }
    

    // if((particle.x > 5.0) || (particle.x < -5.0))
    // {
    //     particle.x = ship_pos.x + myRand(-5.0 , 5.0);
    //     particle.y = ship_pos.y + myRand(-5.0, 5.0);
    //     particle.z = ship_pos.z + myRand(-3.0, 0.0);
    // }
    

    
}

/***********************************************************************************************************************************************************************/
/*********************************************************************** determineOrientation **************************************************************************/
/***********************************************************************************************************************************************************************/
void Particule::determineOrientation(glm::mat4 &projection, glm::mat4 &modelview, Input input)
{
    if(input.getKey(SDL_SCANCODE_A))
    {
        m_directionLandR = 1;
        m_directionFandB = 0;

    }
    else if(input.getKey(SDL_SCANCODE_D))
    {
        m_directionLandR = -1;
        m_directionFandB = 0;

    }
    else if(input.getKey(SDL_SCANCODE_S))
    {
        m_directionFandB = -1;
        m_directionLandR = 0;

    }
    else if(input.getKey(SDL_SCANCODE_W))
    {
        m_directionFandB = 1;
        m_directionLandR = 0;

    }
    else
    {
        m_directionLandR = 0;
        m_directionFandB = 0;
    }
}