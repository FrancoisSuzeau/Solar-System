/*
AUTHOR : SUZEAU François

DATE : 21/07/2021

MODULE : MusicOverlay

NAMEFILE : MusicOverlay.cpp

PURPOSE : class MusicOverlay
*/

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#include "MusicOverlay.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/

MusicOverlay::MusicOverlay()
{
    m_grey_rect = new Square(0.05, "../src/Shader/Shaders/couleur3D.vert", "../src/Shader/Shaders/couleur3D.frag", 0.750);
    m_black_rect = new Square(0.05, "../src/Shader/Shaders/couleur3D.vert", "../src/Shader/Shaders/couleur3D.frag", 0.100);
}

MusicOverlay::~MusicOverlay()
{
    delete m_grey_rect;
    delete m_black_rect;
}

/***********************************************************************************************************************************************************************/
/************************************************************************************ display **************************************************************************/
/***********************************************************************************************************************************************************************/
void MusicOverlay::display(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos, glm::vec3 &target)
{   
    //********************************************** calculate rectangle orientation and position ************************************************************
    float x = target[0];
    float y = target[1];
    float z = target[2];

    //========================================================================================================================================================

    glm::mat4 save = modelview;

        modelview = translate(modelview, vec3(x, y, z));
        modelview = rotate(modelview, 90.0f, vec3(1, 0, 0));
        m_grey_rect->drawLoad(4, projection, modelview);

    modelview = save;
}