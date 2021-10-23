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
Camera::Camera() : m_phi(0.0f), m_theta(0.0f), m_orientation(), m_vertical_axe(0.0f, 0.0f, 1.0f),
m_lateral_move(), m_position(), m_target_point(), m_sensibility(0.0f), m_speed(0.0f), distance_from_ship(50.0f), angle_around_player(0.0f),
pitch(20.0f), yaw(0.0f)
{

}

Camera::Camera(glm::vec3 position, glm::vec3 target_point, glm::vec3 vertical_axe, float sensibility, float speed) : 
m_phi(0.0f), m_theta(0.0f), m_orientation(), m_vertical_axe(vertical_axe),
m_lateral_move(), m_position(position), m_target_point(target_point), m_sensibility(sensibility), m_speed(speed), distance_from_ship(50.0f), angle_around_player(0.0f),
pitch(20.0f), yaw(0.0f)
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
    if(m_phi > 89.0f)
    {
        m_phi = 89.0f;
    }
    else if (m_phi < -89.0f)
    {
        m_phi = -89.0f;
    }

    //===================================================================================================================
    
    /************************************************* calculate spheric coordonnate ********************************************************/
    float phi_rad = (float)(m_phi * M_PI / 180); 
    float theta_rad = (float) (m_theta * M_PI / 180);

    if(m_vertical_axe.x == 1.0f)
    {
        m_orientation.x = sin(phi_rad);
        m_orientation.y= cos(phi_rad) * cos(theta_rad);
        m_orientation.z = cos(phi_rad) * sin(theta_rad);
    }
    else if (m_vertical_axe.y == 1.0f)
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
    m_lateral_move = glm::cross(m_vertical_axe, m_orientation);
    m_lateral_move = glm::normalize(m_lateral_move);
    //===================================================================================================================

    /************************************************* calculate target point for openGL ********************************************************/
    m_target_point = m_position + m_orientation;
    //===================================================================================================================
}

void Camera::calculatePitch(Input const &input)
{
    if(input.getMouseButton(SDL_BUTTON_RIGHT))
    {
        float pitch_change = input.getYRel() * 0.5f;
        pitch -= pitch_change;
            
    }
}

void Camera::calculateAngleAroundShip(Input const &input)
{
    if(input.getMouseButton(SDL_BUTTON_RIGHT))
    {
        float angle_change = input.getXRel() * 0.5f;
        angle_around_player -= angle_change;
            
    }
}

float Camera::calculateHorizontalDistance()
{
    return (float) distance_from_ship * cos(glm::radians(pitch));
}

float Camera::calculateVerticalDistance()
{
    return (float) distance_from_ship * sin(glm::radians(pitch));
}

void Camera::calculateCameraPostion(float horizontal_distance, float vertical_distance, glm::vec3 ship_pos, float ship_rotY)
{
    float theta = ship_rotY + angle_around_player;
    float offset_x = (float) horizontal_distance * sin(glm::radians(theta));
    float offset_y = (float) horizontal_distance * cos(glm::radians(theta));
    m_position.x = ship_pos.x - offset_x;
    m_position.y = ship_pos.y - offset_y;
    m_position.z = ship_pos.z + vertical_distance;
}
/***********************************************************************************************************************************************************************/
/*************************************************************************************** move **************************************************************************/
/***********************************************************************************************************************************************************************/
void Camera::move(Input const &input, bool move, glm::vec3 ship_pos, float ship_rotY)
{
    if(move)
    {
        /************************************************* orientation managing ********************************************************/
        if(input.getMouseButton(SDL_BUTTON_RIGHT))
        {
            this->orientate(input.getXRel(), input.getYRel());
            
        }

        // this->calculatePitch(input);
        // this->calculateAngleAroundShip(input);
        // float horizontal_distance = this->calculateHorizontalDistance();
        // float vertical_distance = this->calculateVerticalDistance();
        // this->calculateCameraPostion(horizontal_distance, vertical_distance, ship);
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
    m_orientation = glm::normalize(m_orientation);
    //===================================================================================================================

    /************************************************* finding value angle ********************************************************/
    if(m_vertical_axe.x == 1.0f)
    {
        m_phi = asin(m_orientation.x);
        m_theta = acos(m_orientation.y / cos(m_phi));

        if(m_orientation.y < 0.0f)
        {
            m_theta *= -1;
        }
    }
    else if (m_vertical_axe.y == 1.0f)
    {
        m_phi = asin(m_orientation.y);
        m_theta = acos(m_orientation.z / cos(m_phi));

        if(m_orientation.z < 0.0f)
        {
            m_theta *= -1;
        }
    }
    else
    {
        m_phi = asin(m_orientation.x);
        m_theta = acos(m_orientation.z / cos(m_phi));

        if(m_orientation.z < 0.0f)
        {
            m_theta *= -1;
        }
    }
    //===================================================================================================================

    /************************************************* converting in degree ********************************************************/
    m_phi = (float) (m_phi * 180 / M_PI);
    m_theta = (float) (m_theta * 180 / M_PI);
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
    if(m_speed < 0.0f)
    {
        m_speed = 0.0f;
    }

    if(m_speed > 200.0f)
    {
        m_speed = 200.0f;
    }
}

void Camera::setMinimumSpeed()
{
    m_speed = 0.6f;
}

void Camera::setMaximumSpeed()
{
    m_speed = 200.0f;
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

glm::vec3 Camera::getVerticalaxe() const
{
    return m_vertical_axe;
}