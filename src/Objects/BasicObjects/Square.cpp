/*
AUTHOR : SUZEAU François

DATE : 29/06/2021

MODULE : Objects::BasicObjects

NAMEFILE : Square.cpp

PURPOSE : class Square
*/

#include "Square.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Square::Square(float size, std::string const type) : super(type)
{
    super::m_size = glm::vec3(size);
    super::m_model_mat = glm::mat4(1.0);
}

Square::~Square()
{
    
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** clean ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Square::clean()
{
    super::clean();
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** transform ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Square::transform(glm::vec3 ship_pos, Input *input)
{
    super::m_model_mat = glm::mat4(1.0);

    super::scaleObject(super::m_model_mat, super::m_size);
    super::translateObject(super::m_model_mat, (super::m_position + ship_pos));
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** sendToShader ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Square::sendToShader(DataManager &data_manager)
{
    switch (data_manager.getPass())
    {
        case DEPTH_FBO:
            if(data_manager.getShader("depth_map") != nullptr)
            {
                glUseProgram(data_manager.getShader("depth_map")->getProgramID());
                    data_manager.getShader("depth_map")->setMat4("model", super::getModelMat());
                glUseProgram(0);
            }
            break;
        case COLOR_FBO:
            if(data_manager.getShader(super::m_type) != nullptr)
            {
                glUseProgram(data_manager.getShader(super::m_type)->getProgramID());
                    data_manager.getShader(super::m_type)->setMat4("view", data_manager.getViewMat());
                    data_manager.getShader(super::m_type)->setMat4("projection", data_manager.getProjMat());
                    data_manager.getShader(super::m_type)->setMat4("model", super::getModelMat());
                    data_manager.getShader(super::m_type)->setFloat("color", super::getColor());
                    // data_manager.getShader(super::super::m_type)->setVec3("viewPos", data_manager.getCamPos());
                    // data_manager.getShader(super::super::m_type)->setVec3("sunPos", data_manager.getSunPos());
                    // data_manager.getShader(super::super::m_type)->setFloat("transparency", 1.0f);
                    // data_manager.getShader(super::super::m_type)->setInt("hdr", data_manager.getHDR());
                glUseProgram(0);
            }
            break;
        default:
            break;
    }
}