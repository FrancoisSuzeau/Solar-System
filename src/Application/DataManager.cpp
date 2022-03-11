/*
AUTHOR : SUZEAU François

DATE : 23/11/2021

MODULE : DataManager

NAMEFILE : DataManager.hpp

PURPOSE :   - Manage data transfert between all module of the application program
            - Store datas references (for texture, render, settings)
*/

#include "DataManager.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
DataManager::DataManager(int width, int height, double angle) : m_width(width), m_height(height), hdr(true), exposure(0.8f),
bloom(true), bloom_strenght(10), render_normal(true), render_parallax(true), asteroid_count(10000), m_fps(60),
render_overlay(true), render_name(true), render_info(false)
{
    proj_mat = glm::perspective(glm::radians(angle), (double)width / height, 1.0, 900000.0);
    view_mat = glm::mat4(1.0f);
}

DataManager::~DataManager()
{
    for(std::map<std::string, Shader*>::iterator it = map_shader.begin(); it != map_shader.end(); ++it)
    {
        if(it->second != nullptr)
        {
            delete it->second;
        }
    }
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* getters/setters *********************************************************************/
/***********************************************************************************************************************************************************************/
void DataManager::setTerminate(bool const terminate)
{
    m_terminate = terminate;
}

bool DataManager::getTerminate() const
{
    return m_terminate;
}

int DataManager::getWidth() const
{
    return m_width;
}

int DataManager::getHeight() const
{
    return m_height;
}

void DataManager::setFps(unsigned int const fps)
{
    m_fps = fps;
}

unsigned int DataManager::getFps() const
{
    return m_fps;
}

void DataManager::setVolume(int const volume)
{
    m_volume = volume;
}

int DataManager::getVolume() const
{
    return m_volume;
}

void DataManager::setPause(bool const pause)
{
    m_pause_music = pause;
} 

bool DataManager::getPause() const
{
    return m_pause_music;
}

void DataManager::setTrack(int const track)
{
    m_track = track;
}

int DataManager::getTrack() const
{
    return m_track;
}

void DataManager::setShader(bool main_loop)
{
    std::vector<shader_datas> shader_init;
    shader_init.push_back({"../../src/Shader/Shaders/couleur3D.vert", "../../src/Shader/Shaders/couleur3D.frag", "square"});
    // shader_init.push_back({"../../src/Shader/Shaders/sphereShader.vert", "../../src/Shader/Shaders/sphereShader.frag", "atmosphere"});            

    for(std::vector<shader_datas>::iterator it = shader_init.begin(); it != shader_init.end(); ++it)
    {
        map_shader[it[0].key] = new Shader(it[0].v_shader_path, it[0].f_shader_path);
        assert(map_shader[it[0].key]);
        assert(map_shader[it[0].key]->loadShader());
    }              
}

Shader* DataManager::getShader(std::string key)
{
    return map_shader[key];
}

glm::mat4 DataManager::getViewMat() const
{
    return view_mat;
}

glm::mat4 DataManager::getProjMat() const
{
    return proj_mat;
}

void DataManager::lockView(glm::vec3 position, glm::vec3 target, glm::vec3 up)
{
    view_mat = glm::lookAt(position, target, up);
}

void DataManager::resetViewMat(glm::mat4 const new_val)
{
    view_mat = new_val;
}

void DataManager::setHDR(bool const new_val)
{
    hdr = new_val;
}

bool DataManager::getHDR() const
{
    return hdr;
}

void DataManager::setExposure(float const new_val)
{
    exposure = new_val;
}

float DataManager::getExposure() const
{
    return exposure;
}


void DataManager::setBloom(bool const new_val)
{
    bloom = new_val;
}

bool DataManager::getBloom() const
{
    return bloom;
}

void DataManager::setBloomStrength(int const new_val)
{
    bloom_strenght = new_val;
}

int DataManager::getBloomStrength() const
{
    return bloom_strenght;
}

void DataManager::setRenderNormal(bool const new_val)
{
    render_normal = new_val;
}

bool DataManager::getRenderNormal() const
{
    return render_normal;
}

void DataManager::setRenderParallax(bool const new_val)
{
    render_parallax = new_val;
}

bool DataManager::getRenderParallax() const
{
    return render_parallax;
}

void DataManager::setAsteroidCount(int const new_val)
{
    asteroid_count = new_val;
}

int DataManager::getAsteroidCount() const
{
    return asteroid_count;
}

void DataManager::setRenderOverlay(bool const new_val)
{
    render_overlay = new_val;
}

bool DataManager::getRenderOverlay() const
{
    return render_overlay;
}

void DataManager::setRenderName(bool const new_val)
{
    render_name = new_val;
}

bool DataManager::getRenderName() const
{
    return render_name;
}

void DataManager::setRenderInfo(bool const new_val)
{
    render_info = new_val;
}

bool DataManager::getRenderInfo() const
{
    return render_info;
}