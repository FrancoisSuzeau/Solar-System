/*
AUTHOR : SUZEAU François

DATE : 10/06/2021

MODULE : Objects::TexturedObjects::SquareTextured::Ring

NAMEFILE : Ring.cpp

PURPOSE : class Ring

*/

#include "Ring.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Ring::Ring(float size, std::vector<std::string> textures_path, std::string const type, int shininess, float inclinaison_angle) : super(size, type)
{
    m_shininess = shininess;
    m_inclinaison_angle = inclinaison_angle;
    super::surface_tex_ids.push_back(Loader::loadTextureWithSDL(textures_path[0]));
    assert(super::surface_tex_ids[0] != 0);
}

Ring::~Ring()
{
    
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** clean ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Ring::clean()
{
    super::clean();
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** transform ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Ring::transform(glm::vec3 ship_pos, Input *input)
{
    super::m_model_mat = glm::mat4(1.0);

    super::translateObject(super::m_model_mat, (super::m_position + ship_pos));
    super::scaleObject(super::m_model_mat, super::m_size);

    super::inclineObject(super::m_model_mat, super::m_inclinaison_angle);
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** sendToShader ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Ring::sendToShader(DataManager &data_manager)
{
    if((data_manager.getShader(super::m_type) != nullptr) && (data_manager.getPass() == COLOR_FBO))
    {
        glUseProgram(data_manager.getShader(super::m_type)->getProgramID());
            data_manager.getShader(super::m_type)->setTexture("diffuseTexture", 0);
            data_manager.getShader(super::m_type)->setVec3("sunPos", data_manager.getSunPos());
            data_manager.getShader(super::m_type)->setVec3("viewPos", data_manager.getCamPos());
            data_manager.getShader(super::m_type)->setInt("shadows", data_manager.getRenderShadow());
            data_manager.getShader(super::m_type)->setFloat("far_plane", data_manager.getFar());
            data_manager.getShader(super::m_type)->setTexture("depthMap", 1);
            data_manager.getShader(super::m_type)->setInt("shininess", m_shininess);
        glUseProgram(0);
    }
    
    super::sendToShader(data_manager);
}