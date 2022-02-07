/*
AUTHOR : SUZEAU François

DATE : 06/02/2021

MODULE : FlareManager

NAMEFILE : FlareManager.cpp

PURPOSE : class FlareManager
*/

#include "FlareManager.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
FlareManager::FlareManager()
{
    flare_textures.push_back(new FlareTexture(0.8f, "../../assets/textures/lensFlareTextures/tex8.png"));
    flare_textures.push_back(new FlareTexture(0.5f, "../../assets/textures/lensFlareTextures/tex4.png"));
    flare_textures.push_back(new FlareTexture(0.4f, "../../assets/textures/lensFlareTextures/tex5.png"));
    flare_textures.push_back(new FlareTexture(0.04f, "../../assets/textures/lensFlareTextures/tex3.png"));
    flare_textures.push_back(new FlareTexture(0.05f, "../../assets/textures/lensFlareTextures/tex9.png"));
    flare_textures.push_back(new FlareTexture(0.1f, "../../assets/textures/lensFlareTextures/tex10.png"));
    flare_textures.push_back(new FlareTexture(0.02f, "../../assets/textures/lensFlareTextures/tex1.png"));
    flare_textures.push_back(new FlareTexture(0.1f, "../../assets/textures/lensFlareTextures/tex5.png"));
    flare_textures.push_back(new FlareTexture(0.04f, "../../assets/textures/lensFlareTextures/tex3.png"));
    flare_textures.push_back(new FlareTexture(0.15f, "../../assets/textures/lensFlareTextures/tex2.png"));
    flare_textures.push_back(new FlareTexture(0.15f, "../../assets/textures/lensFlareTextures/tex10.png"));
    flare_textures.push_back(new FlareTexture(0.33f, "../../assets/textures/lensFlareTextures/tex4.png"));

    spacing = 0.4f;
   
   for(std::vector<FlareTexture*>::iterator it = flare_textures.begin(); it != flare_textures.end(); it++)
   {
       assert(it[0]);
   }


}

FlareManager::~FlareManager()
{
    for(std::vector<FlareTexture*>::iterator it = flare_textures.begin(); it != flare_textures.end(); it++)
    {
        if(*it != nullptr)
        {
            delete *it;
        }
    }
}

/***********************************************************************************************************************************************************************/
/**************************************************************************** renderLensFlare **************************************************************************/
/***********************************************************************************************************************************************************************/
void FlareManager::renderLensFlare(RenderData &render_data)
{
    glm::mat4 tmp_view_mat = render_data.getViewMat();
    render_data.initSaveMat();

        render_data.lockViewMat(glm::vec3(0.0f, 0.0f, 1.7f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

        //calculate sun position on the screen
        glm::vec2 sunScreenCoords = convertToScreenSpace(render_data.getSunPos(), tmp_view_mat, render_data.getProjectionMat());

        if(sunScreenCoords == glm::vec2(-100))
        {
            return;
        }

        //calculate line form sun through center screen
        glm::vec2 sunToCenter = glm::vec2(0.5f) - sunScreenCoords;

        float brightness = 1 - (glm::length(sunToCenter) / 0.6f);
        
        if(brightness > 0)
        {

            int i = -3; //make it more align with sun and deplace it more to the opposite border
            for(std::vector<FlareTexture*>::iterator it = flare_textures.begin(); it != flare_textures.end(); it++)
            {
                if(*it != nullptr)
                {
                    calculateFlarePos(sunToCenter, sunScreenCoords, it[0], i);
                    it[0]->display(render_data, brightness*0.005);
                }

                i++;
   
            }
        }
    render_data.saveViewMat();
}

/***********************************************************************************************************************************************************************/
/**************************************************************************** calculateFlarePos **************************************************************************/
/***********************************************************************************************************************************************************************/
void FlareManager::calculateFlarePos(glm::vec2 sunToCenter, glm::vec2 sunCoords, FlareTexture *flare_text, int i)
{
    if(flare_text != nullptr)
    {
        glm::vec2 direction = glm::vec2(sunToCenter);
        direction = direction * (i * spacing);

        // direction.x *= -1;
        
        /*
            Just a reminder : we calculate the sun coord on the screen with origin at the left hight corner of the screen (with 0.5, 0.5 as the center)
            but the position of the flares are calculate with the OpenGL screen coord with origin in the center of the screen because of the lock on the view matrice
            so we had to substract 0.5 at each calculation of the flare position
        */

        glm::vec2 flarePos = glm::vec2(sunCoords + direction - glm::vec2(0.5));

        flarePos.x *= -1;

        flare_text->setPositionFlareText(glm::vec3(flarePos, -0.2));
        flare_text->transformMat();
    }
}

/***********************************************************************************************************************************************************************/
/*********************************************************************** convertToScreenSpace **************************************************************************/
/***********************************************************************************************************************************************************************/
glm::vec2 FlareManager::convertToScreenSpace(glm::vec3 sunPos, glm::mat4 viewMat, glm::mat4 projMat)
{

    glm::vec4 clipSpacePos = projMat * (viewMat * glm::vec4(sunPos, 1.0f));

    if(clipSpacePos.w <= 0)
    {
        return glm::vec2(-100); // NULL
    }

    float x = (clipSpacePos.x / clipSpacePos.w + 1) / 2.0f; 
    float y = 1 - ((clipSpacePos.y / clipSpacePos.w + 1) / 2.0f);

    return glm::vec2(x, y);
}