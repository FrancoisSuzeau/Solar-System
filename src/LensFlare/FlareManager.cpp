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
    flare_textures.push_back(new FlareTexture(0.02f, "../../assets/textures/lensFlareTextures/tex6.png"));
    flare_textures.push_back(new FlareTexture(0.2f, "../../assets/textures/lensFlareTextures/tex4.png"));
    flare_textures.push_back(new FlareTexture(0.2f, "../../assets/textures/lensFlareTextures/tex2.png"));
    flare_textures.push_back(new FlareTexture(0.2f, "../../assets/textures/lensFlareTextures/tex7.png"));
    flare_textures.push_back(new FlareTexture(0.02f, "../../assets/textures/lensFlareTextures/tex3.png"));
    flare_textures.push_back(new FlareTexture(0.02f, "../../assets/textures/lensFlareTextures/tex5.png"));
    flare_textures.push_back(new FlareTexture(0.2f, "../../assets/textures/lensFlareTextures/tex7.png"));
    flare_textures.push_back(new FlareTexture(0.02f, "../../assets/textures/lensFlareTextures/tex3.png"));
    flare_textures.push_back(new FlareTexture(0.02f, "../../assets/textures/lensFlareTextures/tex5.png"));
    flare_textures.push_back(new FlareTexture(0.2f, "../../assets/textures/lensFlareTextures/tex4.png"));
    flare_textures.push_back(new FlareTexture(0.2f, "../../assets/textures/lensFlareTextures/tex8.png"));

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

        render_data.lockViewMat(glm::vec3(0.0f, 0.0f, 1.71f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

        //calculate sun position on the screen
        glm::vec2 sunScreenCoords = convertToScreenSpace(render_data.getSunPos(), tmp_view_mat, render_data.getProjectionMat());

        if(sunScreenCoords == glm::vec2(-100))
        {
            return;
        }
        // std::cout << "sun pos x = " << sunScreenCoords.x << std::endl;
        // std::cout << "sun pos y = " << sunScreenCoords.y << std::endl;

        if((sunScreenCoords.y < 0.0) || sunScreenCoords.y > 1.0)
        {
            return;
        }

        if((sunScreenCoords.x < 0.0) || (sunScreenCoords.x > 1.0))
        {
            return;
        }

        //calculate line form sun through center screen
        glm::vec2 sunToCenter = glm::vec2(0.0f) - sunScreenCoords;

        float brightness = 1 - (glm::length(sunToCenter) / 0.99f);
        // float brightness = 0.4;
        std::cout << brightness << std::endl;
        // std::cout << -1*sunToCenter.x << std::endl;
        // std::cout << -1*sunToCenter.y << std::endl;
        
        if(brightness > 0)
        {
            int i(0);
            for(std::vector<FlareTexture*>::iterator it = flare_textures.begin(); it != flare_textures.end(); it++)
            {
                if(*it != nullptr)
                {
                    calculateFlarePos(sunToCenter, sunScreenCoords, it[0], i);
                    it[0]->display(render_data, brightness);
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
        glm::vec2 flarePos = glm::vec2(sunCoords + direction);
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