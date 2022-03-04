/*
AUTHOR : SUZEAU François

DATE : 27/09/2021

MODULE : ParticuleManager

NAMEFILE : ParticuleManager.cpp

PURPOSE : class ParticuleManager
*/

#include "ParticuleManager.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
ParticuleManager::ParticuleManager()
{
   m_particule = new Particule(1.0, 5, 5);
   assert(m_particule);

   amount = 100;
   dist_from_ship = new float[amount];
   offset = new glm::vec3[amount];

   float min = -5.0f;
   float max = 5.0f;
   for(int i(0); i < amount; i++)
   {
       this->initParticule(i, min, max);
   }

   directions[0] = false;
   directions[1] = false;
//    directions[2] = false;
//    directions[3] = false;
}

ParticuleManager::~ParticuleManager()
{
    if(m_particule != nullptr)
    {
        delete m_particule;
        m_particule = nullptr;
    }

    if(dist_from_ship != nullptr)
    {
        delete [] dist_from_ship;
    }

    if(offset != nullptr)
    {
        delete [] offset;
    }
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** renderParticules ************************************************************************/
/***********************************************************************************************************************************************************************/
void ParticuleManager::renderParticules(RenderData &render_data, Spaceship *ship, Input input)
{
    render_data.initSaveMat();

    if((render_data.getShader("particule") != nullptr) && (m_particule != nullptr))
    {
        if(ship->getSpeed() > 5.0f)
        {
            for(int i(0); i < amount; i++)
            {
                this->moveParticule(input, ship->getSpeed(), i);
                this->orienteParticules(ship, i);
                m_particule->transformMat();
                m_particule->renderParticule(render_data);
            }
        }
        else
        {
            directions[0] = false;
            directions[1] = false;
            // directions[2] = false;
            // directions[3] = false;
        }
    }

    render_data.saveViewMat();
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** initParticule ***************************************************************************/
/***********************************************************************************************************************************************************************/
void ParticuleManager::initParticule(int i, float min, float max)
{
    dist_from_ship[i] = min + ((float) rand() / RAND_MAX * (max - min + 1.0));
        
    float x = -2.0 + ((float) rand() / RAND_MAX * (2.0 - -2.0 + 1.0));
    float y = -2.0 + ((float) rand() / RAND_MAX * (2.0 - -2.0 + 1.0));
    float z = -2.0 + ((float) rand() / RAND_MAX * (2.0 - -2.0 + 1.0));
    
    offset[i] = glm::vec3(x, y, z);
}

/***********************************************************************************************************************************************************************/
/************************************************************************** orienteParticules **************************************************************************/
/***********************************************************************************************************************************************************************/
void ParticuleManager::orienteParticules(Spaceship *ship, int i)
{

    float vertical_angle = ship->getRotY() - 90.0f;
    float horizontal_dist = dist_from_ship[i] * cos(glm::radians(vertical_angle));
    float vertical_dist = dist_from_ship[i] * sin(glm::radians(vertical_angle));

    float horizontal_angle = ship->getRotX() - 90.0f;

    float x = offset[i].x + (float) horizontal_dist * cos(glm::radians(horizontal_angle));
    float y = offset[i].y + (float) horizontal_dist * sin(glm::radians(horizontal_angle));

    m_particule->setPositionParticule(glm::vec3(x, y, -(vertical_dist + offset[i].z))); //along Ur unit vectcor
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** moveParticule **************************************************************************/
/***********************************************************************************************************************************************************************/
void ParticuleManager::moveParticule(Input input, float ship_speed, int i)
{
    float percent_speed = ship_speed / 200.0f;
    if(input.getKey(SDL_SCANCODE_W))
    {
        dist_from_ship[i] -= 0.1 * percent_speed;
        if(dist_from_ship[i] < -5.0f)
        {
            this->initParticule(i, 0.0f, 5.0f);
        }

        directions[0] = true;
    }
    else if(!input.getKey(SDL_SCANCODE_W) && directions[0])
    {
        dist_from_ship[i] -= 0.1 * percent_speed;
    }

    if(input.getKey(SDL_SCANCODE_S))
    {
        dist_from_ship[i] += 0.1 * percent_speed;
        if(dist_from_ship[i] > 5.0f)
        {
            this->initParticule(i, -5.0f, 0.0f);
        }
        directions[1] = true;
    }
    else if(!input.getKey(SDL_SCANCODE_S) && directions[1])
    {
        dist_from_ship[i] += 0.1 * percent_speed;
    }

    // if(input.getKey(SDL_SCANCODE_A))
    // {
    //     directions[2] = true;
    // }
    // else if(!input.getKey(SDL_SCANCODE_A) && directions[2])
    // {

    // }

    // if(input.getKey(SDL_SCANCODE_D))
    // {
    //     directions[3] = true;
    // }
    // else if(!input.getKey(SDL_SCANCODE_D) && directions[3])
    // {

    // }
}