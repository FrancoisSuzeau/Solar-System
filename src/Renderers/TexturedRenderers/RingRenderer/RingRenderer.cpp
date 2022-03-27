/*
AUTHOR : SUZEAU François

DATE : 24/03/2022

MODULE : Renderer::TexturedRenderer::RingRenderer

NAMEFILE : RingRenderer.cpp

PURPOSE : class RingRenderer
*/


#include "RingRenderer.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
RingRenderer::RingRenderer() : super(0.0)
{
    
}

RingRenderer::~RingRenderer()
{
    
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** clean ******************************************************************************/
/***********************************************************************************************************************************************************************/
void RingRenderer::clean()
{
    super::clean();
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** render ******************************************************************************/
/***********************************************************************************************************************************************************************/
void RingRenderer::render(DataManager &data_manager, Object *ring)
{
    GLuint t_id = ring->getTextureID(0);
    if(glIsTexture(t_id) == GL_TRUE)
    {
        ring->sendToShader(data_manager);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, t_id);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, data_manager.getDepthMapTexture());

        super::render(data_manager, ring);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

}

/***********************************************************************************************************************************************************************/
/******************************************************************************* display *******************************************************************************/
/***********************************************************************************************************************************************************************/
// void RingRenderer::display(RenderData &render_data, Planete *planete)
// {
    
//     if(render_data.getShader(planete->getTypePlan()) != nullptr)
//     {
//         //Activate the shader
//         glUseProgram(render_data.getShader(planete->getTypePlan())->getProgramID());

//         //lock VBO and Index Buffer Object
//         glBindBuffer(GL_ARRAY_BUFFER,         m_vbo);
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

//         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//         glEnableClientState(GL_NORMAL_ARRAY);
//         glEnableClientState(GL_VERTEX_ARRAY);
//         glTexCoordPointer(2,  GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(sizeof(GLfloat) * 3 * 2));
//         glNormalPointer(      GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(sizeof(GLfloat) * 3));
//         glVertexPointer(  3,  GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(0));

//             render_data.getShader(planete->getTypePlan())->setMat4("view", render_data.getViewMat());
//             render_data.getShader(planete->getTypePlan())->setMat4("projection", render_data.getProjectionMat());
//             render_data.getShader(planete->getTypePlan())->setMat4("model", planete->getModelMat());
        
//             render_data.getShader(planete->getTypePlan())->setTexture("material.texture0", 0);
//             render_data.getShader(planete->getTypePlan())->setTexture("material.texture1", 1);
//             render_data.getShader(planete->getTypePlan())->setFloat("oppacity", planete->getOppacity());

//             render_data.getShader(planete->getTypePlan())->setVec3("viewPos", render_data.getCamPos());
//             render_data.getShader(planete->getTypePlan())->setVec3("sunPos", render_data.getSunPos());

//             render_data.getShader(planete->getTypePlan())->setInt("hdr", render_data.getHDR());
//             if(planete->getName() == "Jupiter")
//             {
//                 render_data.getShader(planete->getTypePlan())->setInt("material.shininess", 8);
//             }
//             else
//             {
//                 render_data.getShader(planete->getTypePlan())->setInt("material.shininess", 32);
//             }
            
//             if(planete->getDispTexture() != nullptr)
//             {
//                 planete->updateHeightScale();
//                 render_data.getShader(planete->getTypePlan())->setFloat("heightScale", planete->getHeightScale());
//                 render_data.getShader(planete->getTypePlan())->setInt("has_disp", render_data.getDispMapRender());
//                 render_data.getShader(planete->getTypePlan())->setTexture("material.dispMap", planete->getPlanTexture().size() + 1); // nb surface texture + normal texture + displacement texture
                
//                 glActiveTexture(GL_TEXTURE0 + planete->getPlanTexture().size() + 1);
//                 glBindTexture(GL_TEXTURE_2D, planete->getDispTexture()->getID());
//             }
//             else
//             {
//                 render_data.getShader(planete->getTypePlan())->setInt("has_disp", false);
//             }

//             if(planete->getNormalTexture() != nullptr)
//             {
//                 render_data.getShader(planete->getTypePlan())->setInt("has_normal", render_data.getShadowGround());
//                 render_data.getShader(planete->getTypePlan())->setTexture("material.normalMap", planete->getPlanTexture().size());

//                 glActiveTexture(GL_TEXTURE0 + planete->getPlanTexture().size());
//                 glBindTexture(GL_TEXTURE_2D, planete->getNormalTexture()->getID());
//             }
//             else
//             {
//                 render_data.getShader(planete->getTypePlan())->setInt("has_normal", false);
//                 render_data.getShader(planete->getTypePlan())->setInt("has_disp", false);

//             }

//             glActiveTexture(GL_TEXTURE0);
//             glBindTexture(GL_TEXTURE_2D, planete->getPlanTexture()[0]->getID());

//             if(planete->getTypePlan() == "multi_texture_p")
//             {
//                 glActiveTexture(GL_TEXTURE1);
//                 glBindTexture(GL_TEXTURE_2D, planete->getPlanTexture()[1]->getID());
//             }
            
//             glDrawElements(GL_TRIANGLES, m_element_count, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

//             if(planete->getDispTexture() != nullptr)
//             {
//                 glActiveTexture(GL_TEXTURE0 + planete->getPlanTexture().size() + 1);
//                 glBindTexture(GL_TEXTURE_2D, 0);
//             }

//             if(planete->getNormalTexture() != nullptr)
//             {
//                 glActiveTexture(GL_TEXTURE0 + planete->getPlanTexture().size());
//                 glBindTexture(GL_TEXTURE_2D, 0);
//             }
            
            
//             if(planete->getTypePlan() == "multi_texture_p")
//             {
//                 glActiveTexture(GL_TEXTURE1);
//                 glBindTexture(GL_TEXTURE_2D, 0);
//             }

//             glActiveTexture(GL_TEXTURE0);
//             glBindTexture(GL_TEXTURE_2D, 0);
            
//         /************************************************* unbind VBO and IBO ********************************************************/
//         glBindBuffer(GL_ARRAY_BUFFER,         0);
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//         glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//         glDisableClientState(GL_NORMAL_ARRAY);
//         glDisableClientState(GL_VERTEX_ARRAY);
//         //===================================================================================================================================

//         glUseProgram(0);
//     }
    
// }

// /***********************************************************************************************************************************************************************/
// /******************************************************************************* displayName2 ***************************************************************************/
// /***********************************************************************************************************************************************************************/
// void RingRenderer::displayName(RenderData &render_data, int threshold, Planete *planete)
// {
//     if(render_data.getShader("text") != nullptr)
//     {
//         /*
//             CamPos is the M point in spherical coordinate, so we already have his x, y, z coordinate
//             but this coordinate are relative to the world reference
//             so we add the planete position to the cam position to have the coordinate reference opposite to the planete
//             we only use the parametrical coordinate to find the r radius
//         */
           
//         float r = planete->getRadiusFromCam(render_data.getShipPos());
//         float phi = planete->getPhiFromCam(render_data.getShipPos());
//         float theta = planete->getThetaFromCam(render_data.getShipPos(), r);
//         float y = render_data.getShipPos()[1] - planete->getPosition()[1];
        
//         if(r >= threshold * planete->getSize())
//         {
//             glm::vec3 pos = planete->getPosition() - render_data.getShipPos();
//             pos.z += (4.0f + planete->getSize());
//             planete->getNameRender()->updatePosition(pos);
//             planete->getNameRender()->renderMovingText(render_data, r, phi, theta, y);

//             planete->setProximity(false);
//         }
//         else
//         {
//             planete->setProximity(true);
//         }

//     }
    
// }

// /***********************************************************************************************************************************************************************/
// /******************************************************************************* displayAtmo ***************************************************************************/
// /***********************************************************************************************************************************************************************/
// void RingRenderer::displayAtmo(RenderData &render_data, Planete *planete)
// {
//     if( (render_data.getShader("atmosphere") != nullptr) && (planete->getAtmosphere() != nullptr) )
//     {
//         planete->getAtmosphere()->updatePosAtmo(planete->getPosition() - render_data.getShipPos());
//         planete->getAtmosphere()->display(render_data);
//     }
    
// }

// /***********************************************************************************************************************************************************************/
// /******************************************************************************* renderRing ****************************************************************************/
// /***********************************************************************************************************************************************************************/
// void RingRenderer::renderRing(RenderData &render_data, Planete *planete)
// {
//     if((planete->getRing() != nullptr) && (render_data.getShader("ring") != nullptr))
//     {
//         planete->getRing()->setPosition(planete->getPosition() - render_data.getShipPos());
//         planete->getRing()->updatePosition();
//         planete->getRing()->display(render_data);
//     }
// }