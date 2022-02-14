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
void ParticuleManager::renderParticules(RenderData &render_data)
{
    render_data.initSaveMat();

    if((render_data.getShader("particule") != nullptr) && (m_particule != nullptr))
    {
       m_particule->setPositionParticule(glm::vec3(0.0, 8000.0, 0.0) - render_data.getShipPos());
       m_particule->transformMat();

       m_particule->renderParticule(render_data);
    }

    render_data.saveViewMat();
}