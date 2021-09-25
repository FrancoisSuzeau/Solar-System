/*
AUTHOR : SUZEAU François

DATE : 30/05/2021

MODULE : Camera

NAMEFILE : Camera.h

PURPOSE : class Camera
*/

#include "Camera.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Camera::Camera() : m_phi(0.0), m_theta(0.0), m_orientation(), m_vertical_axe(0, 0, 1),
m_lateral_move(), m_position(), m_target_point(), m_sensibility(0.0), m_speed(0.0)
{

}

Camera::Camera(glm::vec3 position, glm::vec3 target_point, glm::vec3 vertical_axe, float sensibility, float speed) : 
m_phi(0.0), m_theta(0.0), m_orientation(), m_vertical_axe(vertical_axe),
m_lateral_move(), m_position(position), m_target_point(target_point), m_sensibility(sensibility), m_speed(speed)
{
    this->setTargetPoint(target_point);
}

Camera::~Camera()
{

}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** orientate *************************************************************************/
/***********************************************************************************************************************************************************************/
void Camera::orientate(int x_rel, int y_rel)
{
    /************************************************* change angles ********************************************************/
    m_phi += -y_rel * m_sensibility;
    m_theta += -x_rel * m_sensibility;

    //limitate phi angle
    if(m_phi > 89.0)
    {
        m_phi = 89.0;
    }
    else if (m_phi < -89.0)
    {
        m_phi = -89.0;
    }

    //===================================================================================================================
    
    /************************************************* calculate spheric coordonnate ********************************************************/
    float phi_rad = m_phi * M_PI / 180; 
    float theta_rad = m_theta * M_PI / 180;

    if(m_vertical_axe.x == 1.0)
    {
        m_orientation.x = sin(phi_rad);
        m_orientation.y= cos(phi_rad) * cos(theta_rad);
        m_orientation.z = cos(phi_rad) * sin(theta_rad);
    }
    else if (m_vertical_axe.y == 1.0)
    {
        m_orientation.x = cos(phi_rad) * sin(theta_rad);
        m_orientation.y= sin(phi_rad);
        m_orientation.z = cos(phi_rad) * cos(theta_rad);
    }
    else
    {
        m_orientation.x = cos(phi_rad) * cos(theta_rad);
        m_orientation.y = cos(phi_rad) * sin(theta_rad);
        m_orientation.z = sin(phi_rad);
    }
    //===================================================================================================================

    /************************************************* normalize moving vector ********************************************************/
    m_lateral_move = cross(m_vertical_axe, m_orientation);
    m_lateral_move = normalize(m_lateral_move);
    //===================================================================================================================

    /************************************************* calculate target point for openGL ********************************************************/
    m_target_point = m_position + m_orientation;
    //===================================================================================================================
}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** move **************************************************************************/
/***********************************************************************************************************************************************************************/
void Camera::move(Input const &input, bool move)
{
    if(move)
    {
        /************************************************* orientation managing ********************************************************/
        if(input.getMouseButton(SDL_MOUSEBUTTONDOWN))
        {
            this->orientate(input.getXRel(), input.getYRel());
        }
        //===================================================================================================================

        /************************************************* moving camera ********************************************************/
        if(input.getKey(SDL_SCANCODE_W))
        {
            m_position = m_position + m_orientation * m_speed;
            m_target_point = m_position + m_orientation;
        }

        if(input.getKey(SDL_SCANCODE_S))
        {
            m_position = m_position - m_orientation * m_speed;
            m_target_point = m_position + m_orientation;
        }

        if(input.getKey(SDL_SCANCODE_A))
        {
            m_position = m_position + m_lateral_move * m_speed;
            m_target_point = m_position + m_orientation;
        }

        if(input.getKey(SDL_SCANCODE_D))
        {
            m_position = m_position - m_lateral_move * m_speed;
            m_target_point = m_position + m_orientation;
        }
        if(input.getKey(SDL_SCANCODE_LCTRL))
        {
            m_position = m_position - m_vertical_axe * m_speed;
            m_target_point = m_position + m_orientation;
        }
        if(input.getKey(SDL_SCANCODE_LSHIFT))
        {
            m_position = m_position + m_vertical_axe * m_speed;
            m_target_point = m_position + m_orientation;
        }
        //===================================================================================================================
    }
    
}

/***********************************************************************************************************************************************************************/
/************************************************************************************* lookAt **************************************************************************/
/***********************************************************************************************************************************************************************/
void Camera::lookAt(glm::mat4 &model_view)
{
    model_view = glm::lookAt(m_position, m_target_point, m_vertical_axe);
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** setTargetPoint ********************************************************************/
/***********************************************************************************************************************************************************************/
void Camera::setTargetPoint(glm::vec3 target_point)
{
    /************************************************* calculate orientation vector ********************************************************/
    m_orientation = m_target_point - m_position;
    m_orientation = normalize(m_orientation);
    //===================================================================================================================

    /************************************************* finding value angle ********************************************************/
    if(m_vertical_axe.x == 1.0)
    {
        m_phi = asin(m_orientation.x);
        m_theta = acos(m_orientation.y / cos(m_phi));

        if(m_orientation.y < 0)
        {
            m_theta *= -1;
        }
    }
    else if (m_vertical_axe.y == 1.0)
    {
        m_phi = asin(m_orientation.y);
        m_theta = acos(m_orientation.z / cos(m_phi));

        if(m_orientation.z < 0)
        {
            m_theta *= -1;
        }
    }
    else
    {
        m_phi = asin(m_orientation.x);
        m_theta = acos(m_orientation.z / cos(m_phi));

        if(m_orientation.z < 0)
        {
            m_theta *= -1;
        }
    }
    //===================================================================================================================

    /************************************************* converting in degree ********************************************************/
    m_phi = m_phi * 180 / M_PI;
    m_theta = m_theta * 180 / M_PI;
    //===================================================================================================================

}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** setPosition ***********************************************************************/
/***********************************************************************************************************************************************************************/
void Camera::setPosition(glm::vec3 position)
{
    /************************************************* update position ********************************************************/
    m_position = position;
    //===================================================================================================================

    /************************************************* actualizing target point ********************************************************/
    m_target_point = m_position + m_orientation;
    //===================================================================================================================
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** getters/setters *******************************************************************/
/***********************************************************************************************************************************************************************/
float Camera::getSensibility() const
{
    return m_sensibility;
}

void Camera::setSensibility(float sensibility)
{
    m_sensibility = sensibility;
}

float Camera::getSpeed() const
{
    return m_speed;
}

void Camera::setSpeed(float speed)
{
    m_speed = m_speed + speed;
    if(m_speed < 0)
    {
        m_speed = 0;
    }

    if(m_speed > 200)
    {
        m_speed = 200;
    }
}

void Camera::setMinimumSpeed()
{
    m_speed = 0.6;
}

void Camera::setMaximumSpeed()
{
    m_speed = 200;
}

glm::vec3 Camera::getPosition() const
{
    return m_position;
}

glm::vec3 Camera::getOrientation() const
{
    return m_orientation;
}

float Camera::getPhi() const
{
    return m_phi;
}

float Camera::getTheta() const
{
    return m_theta;
}

glm::vec3 Camera::getTargetPoint() const
{
    return m_target_point;
}