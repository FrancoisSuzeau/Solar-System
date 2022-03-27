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
render_overlay(true), render_name(true), render_info(false), distance_from_ship(3.f), index_ship(0), change_skin(true), //for loading the skin at program launch
far_plane(1000.f), near_plane(0.1f), depth_render(false)
{
    proj_mat = glm::perspective(glm::radians(angle), (double)width / height, (double)near_plane, (double)far_plane);
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

void DataManager::setShader()
{
    std::vector<shader_datas> shader_init;
    shader_init.push_back({"../../src/Shader/Shaders/screenShader.vert", "../../src/Shader/Shaders/screenShader.frag", "screen"});
    shader_init.push_back({"../../src/Shader/Shaders/depthShader.vert", "../../src/Shader/Shaders/depthShader.frag", "depth_map"});
    shader_init.push_back({"../../src/Shader/Shaders/squareShader.vert", "../../src/Shader/Shaders/squareShader.frag", "square"});
    shader_init.push_back({"../../src/Shader/Shaders/skybox.vert", "../../src/Shader/Shaders/skybox.frag", "skybox"});
    shader_init.push_back({"../../src/Shader/Shaders/model.vert", "../../src/Shader/Shaders/model.frag", "model"});
    shader_init.push_back({"../../src/Shader/Shaders/sunShader.vert", "../../src/Shader/Shaders/sunShader.frag", "sun"});
    shader_init.push_back({"../../src/Shader/Shaders/planeteShader.vert", "../../src/Shader/Shaders/uniqueTexturePlaneteShader.frag", "simple_textured_planete"});
    shader_init.push_back({"../../src/Shader/Shaders/planeteShader.vert", "../../src/Shader/Shaders/doubleTexturePlaneteShader.frag", "double_textured_planete"});
    shader_init.push_back({"../../src/Shader/Shaders/ringShader.vert", "../../src/Shader/Shaders/ringShader.frag", "ring"});
    
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

glm::mat4& DataManager::getViewMat()
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

void DataManager::setDistanceFromShip(float const new_val)
{
    distance_from_ship = new_val;
}

float DataManager::getDistancteFromShip() const
{
    return distance_from_ship;
}

void DataManager::setIndexShip(int const new_val)
{
    index_ship = new_val;
}

int DataManager::getIndexShip() const
{
    return index_ship;
}

void DataManager::setChangeSkin(bool const new_val)
{
    change_skin = new_val;
}

bool DataManager::getChangeSkin() const
{
    return change_skin;
}

void DataManager::setShipPos(glm::vec3 const new_val)
{
    ship_position = new_val;
}

glm::vec3 DataManager::getShipPos() const
{
    return ship_position;
}

void DataManager::setCamPos(glm::vec3 const new_val)
{
    cam_pos = new_val;
}

glm::vec3 DataManager::getCamPos() const
{
    return cam_pos;
}

glm::vec3 DataManager::getSunPos() const
{
    return glm::vec3(0.f) - ship_position;
}

float DataManager::getFar() const
{
    return far_plane;
}

float DataManager::getNear() const
{
    return near_plane;
}

void DataManager::setDepthRender(bool const new_val)
{
    depth_render = new_val;
}

bool DataManager::getDepthRender() const
{
    return depth_render;
}

glm::mat4 DataManager::getLightSpaceMatrix()
{
    glm::mat4 lightProjection, lightView;
    lightProjection = glm::ortho(0.0f, (float)this->m_width, 0.0f, (float)this->m_height, this->near_plane, this->far_plane);
    lightView = glm::lookAt(this->getSunPos(), glm::vec3(0.0f), glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 lightSpaceMatrix = lightProjection * lightView;
    return lightSpaceMatrix;
}

void DataManager::setDepthMapTexture(unsigned int const new_val)
{
    depth_map = new_val;
}

unsigned int DataManager::getDepthMapTexture() const
{
    return depth_map;
}