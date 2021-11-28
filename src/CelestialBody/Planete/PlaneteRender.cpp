/*
AUTHOR : SUZEAU François

DATE : 15/06/2021

MODULE : CelestialBody.PlaneteRender

NAMEFILE : PlaneteRender.cpp

PURPOSE : class SimplePlanete
*/

//usefull macro for VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)0 + (offset))
#endif
#define VERT_NUM_FLOATS 8


#include "PlaneteRender.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
PlaneteRender::PlaneteRender() :
Sphere(1, 70, 70)
{
    
    
}

PlaneteRender::~PlaneteRender()
{
    
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* display *******************************************************************************/
/***********************************************************************************************************************************************************************/
void PlaneteRender::display(RenderData &render_data, Planete *planete)
{
    
    if(render_data.getShader(planete->getTypePlan()) != nullptr)
    {
        //Activate the shader
        glUseProgram(render_data.getShader(planete->getTypePlan())->getProgramID());

        //lock VBO and Index Buffer Object
        glBindBuffer(GL_ARRAY_BUFFER,         m_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glTexCoordPointer(2,  GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(sizeof(GLfloat) * 3 * 2));
        glNormalPointer(      GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(sizeof(GLfloat) * 3));
        glVertexPointer(  3,  GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(0));

            render_data.getShader(planete->getTypePlan())->setMat4("view", render_data.getViewMat());
            render_data.getShader(planete->getTypePlan())->setMat4("projection", render_data.getProjectionMat());
            render_data.getShader(planete->getTypePlan())->setMat4("model", planete->getModelMat());
        
            render_data.getShader(planete->getTypePlan())->setTexture("material.texture0", 0);
            render_data.getShader(planete->getTypePlan())->setTexture("material.texture1", 1);
            render_data.getShader(planete->getTypePlan())->setFloat("oppacity", planete->getOppacity());

            render_data.getShader(planete->getTypePlan())->setVec3("viewPos", render_data.getCamPos());

            std::cout << planete->getName() << std::endl;

            render_data.getShader(planete->getTypePlan())->setInt("hdr", render_data.getHDR());
            if(planete->getName() == "Jupiter")
            {
                render_data.getShader(planete->getTypePlan())->setInt("material.shininess", 8);
            }
            else
            {
                render_data.getShader(planete->getTypePlan())->setInt("material.shininess", 32);
            }
            
            if(planete->getNormalTexture() != nullptr)
            {
                render_data.getShader(planete->getTypePlan())->setInt("has_normal", true);
                render_data.getShader(planete->getTypePlan())->setTexture("material.normalMap", planete->getPlanTexture().size());
                
                glActiveTexture(GL_TEXTURE0 + planete->getPlanTexture().size());
                glBindTexture(GL_TEXTURE_2D, planete->getNormalTexture()->getID());
            }
            else
            {
                render_data.getShader(planete->getTypePlan())->setInt("has_normal", false);

            }

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, planete->getPlanTexture()[0]->getID());

            if(planete->getTypePlan() == "multi_texture_p")
            {
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, planete->getPlanTexture()[1]->getID());
            }
            
            glDrawElements(GL_TRIANGLES, m_element_count, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

            glActiveTexture(GL_TEXTURE0 + planete->getPlanTexture().size());
            glBindTexture(GL_TEXTURE_2D, 0);
            
            if(planete->getTypePlan() == "multi_texture_p")
            {
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, 0);
            }

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);
            
        /************************************************* unbind VBO and IBO ********************************************************/
        glBindBuffer(GL_ARRAY_BUFFER,         0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
        //===================================================================================================================================

        glUseProgram(0);
    }
    
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* displayName2 ***************************************************************************/
/***********************************************************************************************************************************************************************/
void PlaneteRender::displayName(RenderData &render_data, int threshold, Planete *planete)
{
    if(render_data.getShader("text") != nullptr)
    {
        /*
            CamPos is the M point in spherical coordinate, so we already have his x, y, z coordinate
            but this coordinate are relative to the world reference
            so we add the planete position to the cam position to have the coordinate reference opposite to the planete
            we only use the parametrical coordinate to find the r radius
        */
           
        float r = planete->getRadiusFromCam(render_data.getCamPos());
        float phi = planete->getPhiFromCam(render_data.getCamPos());
        float theta = planete->getThetaFromCam(render_data.getCamPos(), r);
        float y = render_data.getCamPos()[1] - planete->getPosition()[1];
        
        if(r >= threshold * planete->getSize())
        {
            planete->getNameRender()->updatePosition(planete->getPosition());
            planete->getNameRender()->renderMovingText(render_data, planete->getSize(), r, phi, theta, y);

            planete->setProximity(false);
        }
        else
        {
            planete->setProximity(true);
        }

    }
    
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* displayAtmo ***************************************************************************/
/***********************************************************************************************************************************************************************/
void PlaneteRender::displayAtmo(RenderData &render_data, Planete *planete)
{
    if( (render_data.getShader("atmosphere") != nullptr) && (planete->getAtmosphere() != nullptr) )
    {
        planete->getAtmosphere()->updatePosAtmo(planete->getPosition());
        planete->getAtmosphere()->display(render_data);
    }
    
}

/***********************************************************************************************************************************************************************/
/******************************************************************************* renderRing ****************************************************************************/
/***********************************************************************************************************************************************************************/
void PlaneteRender::renderRing(RenderData &render_data, Planete *planete)
{
    if((planete->getRing() != nullptr) && (render_data.getShader("ring") != nullptr))
    {
        planete->getRing()->setPosition(planete->getPosition());
        planete->getRing()->updatePosition();
        planete->getRing()->display(render_data);
    }
}