/*
AUTHOR : SUZEAU François

DATE : 14/01/2021

MODULE : CelestialBody.Physique

NAMEFILE : Physique.cpp

PURPOSE : class Physique
*/

#include "Physique.hpp"

float Physique::G_const = 0;
float Physique::Sun_emittance = 0;
int Physique::sun_radius = 0;
std::map<std::string, body_datas> Physique::bodys_data;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Physique::Physique()
{

}

Physique::~Physique()
{

}

/***********************************************************************************************************************************************************************/
/****************************************************************************** InitPhysique ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Physique::InitPhysique()
{
    G_const = 6.6742 * pow(10.0f, -11.0f);

    Sun_emittance = 63200000; //W * m^-2
    sun_radius = 696342; //Km

    bodys_data["Sun"] = {glm::vec3(0.0f, 0.0f, 0.0f), 1.989 * pow(10, 30), {0.0}};
    bodys_data["Mercury"] = {glm::vec3(5790.0f, 0.0f, 0.0f), 3.285 * pow(10, 23), {0.0}};
    bodys_data["Venus"] = {glm::vec3(0.0f, -10820.0f, 0.0f), 4.867 * pow(10, 24), {0.0}};
    bodys_data["Earth"] = {glm::vec3(-15000.0f, 0.0f, 0.0f), 5.972 * pow(10, 24), {7.36 * pow(10, 22)}};
    bodys_data["Mars"] = {glm::vec3(0.0f, 22790.0f, 0.0f), 6.39 * pow(10, 23), {0.0}};
    bodys_data["Jupiter"] = {glm::vec3(77834.0f, 0.0f, 0.0f), 1.898 * pow(10, 27), {4.8 * pow(10, 22), 1.481 * pow(10, 23), 8.931 * pow(10, 22), 1.075 * pow(10, 23)}};
    bodys_data["Saturn"] = {glm::vec3(0.0f, -14267.0f, 0.0f), 5.683 * pow(10, 26), {3.84 * pow(10, 19), 8.6 * pow(10, 19), 1.345 * pow(10, 23)}};
    bodys_data["Uranus"] = {glm::vec3(-28707.0f, 0.0f, 0.0f), 8.681 * pow(10, 25), {0.0}};
    bodys_data["Neptune"] = {glm::vec3(0.0f, 44984.0f, 0.0f), 1.024 * pow(10, 26), {0.0}};
}

/***********************************************************************************************************************************************************************/
/************************************************************************ getDistanceFromCam ***************************************************************************/
/***********************************************************************************************************************************************************************/
float Physique::getDistanceFromCam(std::string body_name, glm::vec3 ship_pos)
{
    float x = ship_pos.x - bodys_data[body_name].host_position.x;
    float y = ship_pos.y - bodys_data[body_name].host_position.y;
    float z = ship_pos.z - bodys_data[body_name].host_position.z;

    float r_squarre = std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2);
            
    return std::sqrt(r_squarre);
}

/***********************************************************************************************************************************************************************/
/************************************************************************ getGravInfluence ***************************************************************************/
/***********************************************************************************************************************************************************************/
std::vector<double> Physique::getGravInfluence(std::string body_name, std::vector<float> distance)
{
    std::vector<double> Fab = {0.0}; //with object a making influence on object b (ship)

    Fab[0] = G_const * ( (bodys_data[body_name].host_mass * 1) / pow(distance[0], 2.0f) );
    Fab[0] /= pow(10, 10);

    int i = 1;
    
    for(std::vector<double>::iterator it = bodys_data[body_name].mass_companion.begin(); it != bodys_data[body_name].mass_companion.end(); it++)
    {
        Fab.push_back(G_const * ( (bodys_data[body_name].mass_companion[i - 1] * 1) / pow(distance[i], 2.0f) ));
        Fab[i] /= pow(10, 6);
        i++;
    }

    return Fab;
}

/***********************************************************************************************************************************************************************/
/************************************************************************ getSolarConst ***************************************************************************/
/***********************************************************************************************************************************************************************/
float Physique::getSolarConst(glm::vec3 ship_pos)
{
    float rad_from_sun = getDistanceFromCam("Sun", ship_pos);

    float value = Sun_emittance * pow((sun_radius / rad_from_sun), 2); //solar const : W * m^-2

    return value;
}