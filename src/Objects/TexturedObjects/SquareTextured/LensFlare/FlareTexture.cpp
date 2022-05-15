/*
AUTHOR : SUZEAU François

DATE : 06/02/2021

MODULE : Objects::TexturedObjects::SquareTextured::LensFlare

NAMEFILE : FlareTexture.cpp

PURPOSE : class FlareTexture
*/

#include "FlareTexture.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
FlareTexture::FlareTexture(float size, std::string const type, std::string const texture_path) : super(size, type)
{
    super::surface_tex_ids.push_back(Loader::loadFlareTexture(texture_path, texture_w, texture_h));
    assert(super::surface_tex_ids[0] != 0);
}

FlareTexture::~FlareTexture()
{
    
}

/***********************************************************************************************************************************************************************/
/************************************************************************************ clean *****************************************************************************/
/***********************************************************************************************************************************************************************/
void FlareTexture::clean()
{
    super::clean();
}

/***********************************************************************************************************************************************************************/
/************************************************************************************ transform *****************************************************************************/
/***********************************************************************************************************************************************************************/
void FlareTexture::transform(glm::vec3 ship_pos, Input *input)
{
    super::m_model_mat = glm::mat4(1.0);

    super::translateObject(super::m_model_mat, (super::m_position + ship_pos));
    super::scaleObject(super::m_model_mat, super::m_size);
}

/***********************************************************************************************************************************************************************/
/************************************************************************************ sendToShader *********************************************************************/
/***********************************************************************************************************************************************************************/
void FlareTexture::sendToShader(DataManager &data_manager)
{
    if((data_manager.getShader(super::m_type) != nullptr) && (data_manager.getPass() == COLOR_FBO))
    {
        glUseProgram(data_manager.getShader(super::m_type)->getProgramID());
            data_manager.getShader(super::m_type)->setTexture("texture0", 0);
            data_manager.getShader(super::m_type)->setFloat("brightness", m_brightness);
        glUseProgram(0);
    }
    
    super::sendToShader(data_manager);
}

/***********************************************************************************************************************************************************************/
/************************************************************************************ getters/setters ******************************************************************/
/***********************************************************************************************************************************************************************/
void FlareTexture::updateBrightness(float const new_val)
{
    m_brightness = new_val;
}