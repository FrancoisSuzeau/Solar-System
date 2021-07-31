/*
AUTHOR : SUZEAU François

DATE : 21/07/2021

MODULE : Overlay

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

MusicOverlay::MusicOverlay() : m_black_rect(0.05, "../src/Shader/Shaders/couleur3D.vert", "../src/Shader/Shaders/couleur3D.frag", 0.100),
m_grey_rect(0.05, "../src/Shader/Shaders/couleur3D.vert", "../src/Shader/Shaders/couleur3D.frag", 0.750)
{
    // m_grey_rect = new Square(0.05, "../src/Shader/Shaders/couleur3D.vert", "../src/Shader/Shaders/couleur3D.frag", 0.750);
    // m_black_rect = new Square(0.05, "../src/Shader/Shaders/couleur3D.vert", "../src/Shader/Shaders/couleur3D.frag", 0.100);
}

MusicOverlay::~MusicOverlay()
{
    // delete m_grey_rect;
    // delete m_black_rect;
}

/***********************************************************************************************************************************************************************/
/************************************************************************************ display **************************************************************************/
/***********************************************************************************************************************************************************************/
void MusicOverlay::display(glm::mat4 &projection, glm::mat4 &modelview)
{   
    glm::mat4 save = modelview;

        // for (int i = 0; i < 4 * 3; i++)
        // {
        //         modelview = translate(modelview, vec3((i - 12.2) * 0.05, -0.3, 0.0));
        //         m_black_rect->display(projection, modelview);

        //     modelview = save;

        //         modelview = translate(modelview, vec3((i - 11.2) * 0.05, -0.3, 0.0));
        //         m_grey_rect->display(projection, modelview);

        //     modelview = save;

        //         modelview = translate(modelview, vec3((i - 10.2) * 0.05, -0.3, 0.0));
        //         m_black_rect->display(projection, modelview);

        //     modelview = save;
        // }

        modelview = translate(modelview, vec3(0.0, 0.0, 0.0));
        m_black_rect.display(projection, modelview);

    modelview = save;

        modelview = translate(modelview, vec3(0.01, 0.0, 0.0));
        m_grey_rect.display(projection, modelview);

    modelview = save;
}