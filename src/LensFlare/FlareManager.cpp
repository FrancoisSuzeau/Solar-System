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
   flare_textures.push_back(new FlareTexture(0.02f, "../../assets/textures/lensFlareTextures/tex1.png", glm::vec3(0.5, 0.5, 0.0)));
   flare_textures.push_back(new FlareTexture(0.2f, "../../assets/textures/lensFlareTextures/tex2.png", glm::vec3(-0.5, -0.5, 0.0)));
   flare_textures.push_back(new FlareTexture(0.02f, "../../assets/textures/lensFlareTextures/tex3.png", glm::vec3(0.5, -0.5, 0.0)));
   flare_textures.push_back(new FlareTexture(0.2f, "../../assets/textures/lensFlareTextures/tex4.png", glm::vec3(-0.5, 0.5, 0.0)));
   flare_textures.push_back(new FlareTexture(0.02f, "../../assets/textures/lensFlareTextures/tex5.png", glm::vec3(0.2, 0.2, 0.0)));
   flare_textures.push_back(new FlareTexture(0.02f, "../../assets/textures/lensFlareTextures/tex6.png", glm::vec3(-0.2, -0.2, 0.0)));
   flare_textures.push_back(new FlareTexture(0.2f, "../../assets/textures/lensFlareTextures/tex7.png", glm::vec3(-0.4, 0.0, 0.0)));
   flare_textures.push_back(new FlareTexture(0.2f, "../../assets/textures/lensFlareTextures/tex8.png", glm::vec3(0.0, 0.0, 0.0)));
   flare_textures.push_back(new FlareTexture(0.02f, "../../assets/textures/lensFlareTextures/tex9.png", glm::vec3(-0.2, 0.2, 0.0)));
   
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
    render_data.initSaveMat();

        render_data.lockViewMat(glm::vec3(0.0f, 0.0f, 1.71f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
        calculateFlarePos();

        for(std::vector<FlareTexture*>::iterator it = flare_textures.begin(); it != flare_textures.end(); it++)
        {
            if(*it != nullptr)
            {
                it[0]->display(render_data);
            }
            
        }

    render_data.saveViewMat();
}

/***********************************************************************************************************************************************************************/
/**************************************************************************** calculateFlarePos **************************************************************************/
/***********************************************************************************************************************************************************************/
void FlareManager::calculateFlarePos()
{
    for(std::vector<FlareTexture*>::iterator it = flare_textures.begin(); it != flare_textures.end(); it++)
    {
        if(*it != nullptr)
        {
            // it[0]->setPositionFlareText(glm::vec3(0.0, 0.0, 0.0));
            it[0]->transformMat();
        }
        
    }
    
}