/*
AUTHOR : SUZEAU François

DATE : 06/06/2021

MODULE : Objects::BasicObjects

NAMEFILE : Sphere.cpp

PURPOSE : class Sphere
*/

//usefull macro for VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)0 + (offset))
#endif
#define VERT_NUM_FLOATS 8


#include "Sphere.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/

Sphere::Sphere(float size) : super()
{
    super::m_size = glm::vec3(size);
    super::m_model_mat = glm::mat4(1.0);
    super::m_type = "atmosphere";
}


Sphere::~Sphere()
{
   
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** transform ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Sphere::transform(Input *input)
{
    super::m_model_mat = glm::mat4(1.0);

    super::translateObject(super::m_model_mat, super::m_position);
    // super::scaleObject(super::m_model_mat, super::m_size);
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** sendToShader ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Sphere::sendToShader(DataManager &data_manager)
{
    if(data_manager.getShader(super::m_type) != nullptr)
    {
        glUseProgram(data_manager.getShader(super::m_type)->getProgramID());

        data_manager.getShader(super::m_type)->setMat4("view", data_manager.getViewMat());
        data_manager.getShader(super::m_type)->setMat4("projection", data_manager.getProjMat());
        data_manager.getShader(super::m_type)->setMat4("model", super::getModelMat());

        // data_manager.getShader(super::m_type)->setVec3("viewPos", data_manager.getCamPos());
        // data_manager.getShader(super::m_type)->setVec3("sunPos", data_manager.getSunPos());
        // data_manager.getShader(super::m_type)->setFloat("transparency", 1.0f);

        // data_manager.getShader(super::m_type)->setInt("hdr", data_manager.getHDR());

        glUseProgram(0);
    }
}