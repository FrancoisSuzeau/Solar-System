/*
AUTHOR : SUZEAU François

DATE : 29/05/2021

MODULE : Objects

NAMEFILE : Object.hpp

PURPOSE : class Object
*/

#include "Object.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Object::Object() : m_rotation_vector(glm::vec3(0.f, 0.f, 1.f)), m_inclinaison_vector(glm::vec3(0.f, 1.f, 0.f))
{
    
}

Object::~Object()
{
   
}

/***********************************************************************************************************************************************************************/
/************************************************************************** shared methods *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Object::updatePosition(glm::vec3 const new_pos)
{
    m_position = new_pos;
}

void Object::rotateObject(glm::mat4 &model, float angle)
{
    model = glm::rotate(model, glm::radians(angle), m_rotation_vector);
}

void Object::inclineObject(glm::mat4 &model, float angle)
{
    model = glm::rotate(model, glm::radians(angle), m_inclinaison_vector);
}

void Object::translateObject(glm::mat4 &model, glm::vec3 pos)
{
    model = glm::translate(model, pos);
}

void Object::scaleObject(glm::mat4 &model, glm::vec3 size)
{
    model = glm::scale(model, size);
}

glm::vec3 Object::getPosition() const
{
    return m_position;
}

void Object::updateSize(glm::vec3 const new_size)
{
    m_size = new_size;
}

glm::vec3 Object::getSize() const
{
    return m_size;
}

glm::mat4 Object::getModelMat()
{
    return m_model_mat;
}

void Object::updateColor(float const new_color)
{
    m_color = new_color;
}

float Object::getColor() const
{
    return m_color;
}

std::string Object::getType() const
{
    return m_type;
}