/*
AUTHOR : SUZEAU François

DATE : 30/05/2021

MODULE : Camera

NAMEFILE : Camera.h

PURPOSE : class Camera
*/

#include "Camera.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Camera::Camera() : m_vertical_axe(0.0f, 0.0f, 1.0f),
m_lateral_move(), m_position(), m_target_point(), distance_from_ship(3.0f), angle_around_player(0.0f),
pitch(20.0f)
{

}

Camera::Camera(glm::vec3 position, glm::vec3 target_point, glm::vec3 vertical_axe, Spaceship *ship) : 
 m_vertical_axe(vertical_axe),
m_lateral_move(), m_position(position), m_target_point(target_point), distance_from_ship(3.0f), angle_around_player(180.0f),
pitch(0.0f)
{
   if(ship != nullptr)
   {
       m_ship = ship;
   }
}

Camera::~Camera()
{
    
}
/***********************************************************************************************************************************************************************/
/********************************************************************************** calculatePitch *********************************************************************/
/***********************************************************************************************************************************************************************/

void Camera::calculatePitch(Input const &input)
{
    if(input.getMouseButton(SDL_BUTTON_RIGHT))
    {
        float pitch_change = input.getYRel() * 0.5f;
        pitch += pitch_change;

        //limitate phi angle
        if(pitch > 89.0f)
        {
            pitch = 89.0f;
        }
        else if (pitch < -89.0f)
        {
            pitch = -89.0f;
        }
            
    }
}

/***********************************************************************************************************************************************************************/
/************************************************************************** calculateAngleAroundShip *******************************************************************/
/***********************************************************************************************************************************************************************/
void Camera::calculateAngleAroundShip(Input const &input)
{
    if(input.getMouseButton(SDL_BUTTON_RIGHT))
    {
        float angle_change = input.getXRel() * 0.5f;
        angle_around_player -= angle_change;
    }
}

/***********************************************************************************************************************************************************************/
/************************************************************************** calculateHorizontalDistance*****************************************************************/
/***********************************************************************************************************************************************************************/
float Camera::calculateHorizontalDistance(Input const &input)
{
    return (float) distance_from_ship * cos(glm::radians((m_ship->getRotY() - 90.0f + pitch)));
}

/***********************************************************************************************************************************************************************/
/*************************************************************************** calculateHorizontalDistance ***************************************************************/
/***********************************************************************************************************************************************************************/
float Camera::calculateVerticalDistance(Input const &input)
{
    return (float) distance_from_ship * sin(glm::radians((m_ship->getRotY() - 90.0f + pitch)));
}

/***********************************************************************************************************************************************************************/
/**************************************************************************** calculateCameraPosition ******************************************************************/
/***********************************************************************************************************************************************************************/
void Camera::calculateCameraPostion(float horizontal_distance, float vertical_distance, Input const &input)
{
    if(m_ship != nullptr)
    {
        float theta =  angle_around_player + m_ship->getRotX();
        float offset_x = (float) horizontal_distance * sin(glm::radians(theta));
        float offset_y = (float) horizontal_distance * -cos(glm::radians(theta));

        m_position.x = m_ship->getPosition().x + offset_x;
        m_position.y = m_ship->getPosition().y + offset_y;
        m_position.z = m_ship->getPosition().z + vertical_distance;

        // m_position.x = 0.0f + offset_x;
        // m_position.y = 0.0f + offset_y;
        // m_position.z = 0.0f + vertical_distance;

    }
    
}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** move **************************************************************************/
/***********************************************************************************************************************************************************************/
void Camera::move(Input const &input, bool move)
{
    if(!move)
    {
        this->calculatePitch(input);
        this->calculateAngleAroundShip(input);
        float horizontal_distance = this->calculateHorizontalDistance(input);
        float vertical_distance = this->calculateVerticalDistance(input);
        this->calculateCameraPostion(horizontal_distance, vertical_distance, input);
    
        m_target_point = m_ship->getPosition();
        // m_target_point = glm::vec3(0.0);
        this->correctTarget(input);
    }
}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** correctTarget **************************************************************************/
/***********************************************************************************************************************************************************************/
void Camera::correctTarget(Input const &input)
{
    float correct_value_y = -cos(glm::radians(m_ship->getRotX()));
    float correct_value_x = sin(glm::radians(m_ship->getRotX()));
    float correct_value_z = cos(glm::radians(m_ship->getRotY()));
    float speed = m_ship->getSpeed();

    if(input.getKey(SDL_SCANCODE_W))
    {
        glm::vec3 to_add = glm::normalize(glm::vec3(correct_value_x, correct_value_y, correct_value_z));
        m_target_point += to_add * speed;
        m_position += to_add * speed;
    }

    if(input.getKey(SDL_SCANCODE_S))
    {
        glm::vec3 to_add = glm::normalize(glm::vec3(correct_value_x, correct_value_y, correct_value_z));
        m_target_point -= to_add * speed;
        m_position -= to_add * speed;
    }

    if(input.getKey(SDL_SCANCODE_A))
    {
        glm::vec3 to_cross = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(correct_value_x, correct_value_y, correct_value_z));
        glm::vec3 to_add = glm::normalize(to_cross);
        m_target_point += to_add * speed;
        m_position += to_add * speed;
    }

    if(input.getKey(SDL_SCANCODE_D))
    {
        glm::vec3 to_cross = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(correct_value_x, correct_value_y, correct_value_z));
        glm::vec3 to_add = glm::normalize(to_cross);
        m_target_point -= to_add * speed;
        m_position -= to_add * speed;
    }

    if(input.getKey(SDL_SCANCODE_LSHIFT))
    {
        glm::vec3 to_add = glm::normalize(glm::vec3(0.0f, 0.0f, m_ship->getSpeed()));
        m_target_point += to_add * speed;
        m_position += to_add * speed;
    }
    if(input.getKey(SDL_SCANCODE_LCTRL))
    {
        glm::vec3 to_add = glm::normalize(glm::vec3(0.0f, 0.0f, -m_ship->getSpeed()));
        m_target_point += to_add * speed;
        m_position += to_add * speed;
    }
}

/***********************************************************************************************************************************************************************/
/************************************************************************************* lookAt **************************************************************************/
/***********************************************************************************************************************************************************************/
void Camera::lookAt(glm::mat4 &view)
{
    view = glm::lookAt(m_position, m_target_point, m_vertical_axe);
}


/***********************************************************************************************************************************************************************/
/*********************************************************************************** getters/setters *******************************************************************/
/***********************************************************************************************************************************************************************/
glm::vec3 Camera::getPosition() const
{
    return m_position;
}

glm::vec3 Camera::getVerticalaxe() const
{
    return m_vertical_axe;
}

glm::vec3 Camera::getTargetPoint() const
{
    return m_target_point;
}

void Camera::setDistFromShip(float const new_val)
{
    distance_from_ship = new_val;
}

float Camera::getDistFromShip() const
{
    return distance_from_ship;
}