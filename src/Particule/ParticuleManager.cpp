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
}

ParticuleManager::~ParticuleManager()
{
    if(m_particule != nullptr)
    {
        delete m_particule;
    }
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** renderParticules ************************************************************************/
/***********************************************************************************************************************************************************************/
void ParticuleManager::renderParticules(RenderData &render_data, Spaceship *ship)
{
    render_data.initSaveMat();

    if((render_data.getShader("particule") != nullptr) && (m_particule != nullptr))
    {
        // m_particule->updatePosParticule(glm::vec3(0.0, 1.0, 0.0));
        this->orienteParticules(ship);
        m_particule->transformMat();
        m_particule->renderParticule(render_data);
    }

    render_data.saveViewMat();
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** initParticules **************************************************************************/
/***********************************************************************************************************************************************************************/
void ParticuleManager::initParticules(glm::vec3 posShip)
{
    m_particule->setPositionParticule(glm::vec3(0.0, 8000.0, 0.0) - posShip);
}

/***********************************************************************************************************************************************************************/
/************************************************************************** orienteParticules **************************************************************************/
/***********************************************************************************************************************************************************************/
void ParticuleManager::orienteParticules(Spaceship *ship)
{
    float vertical_angle = 90.0f - ship->getRotY();

    float horizontal_dist = 3.0f * cos(glm::radians((ship->getRotY() - 90.0f + vertical_angle)));
    float vertical_dist = 3.0f * sin(glm::radians((ship->getRotY() - 90.0f + vertical_angle)));

    float horizontal_angle = ship->getRotX();

    float off_x = (float) horizontal_dist * sin(glm::radians(horizontal_angle));
    float off_y = (float) horizontal_dist * -cos(glm::radians(horizontal_angle));

    m_particule->setPositionParticule(glm::vec3(off_x, off_y, vertical_dist));
}