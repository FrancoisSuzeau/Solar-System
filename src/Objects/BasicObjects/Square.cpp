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
Square::Square(float size) : super()
{
    super::m_size = glm::vec3(size);
    super::m_model_mat = glm::mat4(1.0);
    super::m_type = "square";
}

Square::~Square()
{
    
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
    if(data_manager.getShader(super::m_type) != nullptr)
    {
        //Activate the shader
        glUseProgram(data_manager.getShader(super::m_type)->getProgramID());

            //send matrices to shader
            data_manager.getShader(super::m_type)->setMat4("projection", data_manager.getProjMat());
            data_manager.getShader(super::m_type)->setMat4("view", data_manager.getViewMat());
            data_manager.getShader(super::m_type)->setMat4("model", super::getModelMat());
            data_manager.getShader(super::m_type)->setFloat("color", super::getColor());

            // data_manager.getShader(super::m_type)->setInt("hdr", data_manager.getHDR());

        glUseProgram(0);
    }
}