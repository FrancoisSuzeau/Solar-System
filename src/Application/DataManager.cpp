/*
AUTHOR : SUZEAU François

DATE : 23/11/2021

MODULE : DataManager

NAMEFILE : DataManager.hpp

PURPOSE :   - Manage data transfert between all module of the application program
            - Store datas references (for texture, render, settings)
*/

#include "DataManager.hpp"
std::vector<body_data> DataManager::m_bodys_data;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
DataManager::DataManager(int width, int height, double angle) : m_width(width), m_height(height), hdr(true), exposure(0.8f),
bloom(true), bloom_strenght(10), render_normal(true), render_parallax(true), asteroid_count(100), m_fps(60),
render_overlay(true), render_name(true), render_info(false), distance_from_ship(3.f), index_ship(0), change_skin(true), //for loading the skin at program launch
far_plane(500.f), near_plane(0.1f)
{
    proj_mat = glm::perspective(glm::radians(angle), (double)width / height, (double)near_plane, (double)far_plane);
    view_mat = glm::mat4(1.0f);
}

DataManager::~DataManager()
{
    
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* clean *******************************************************************************/
/***********************************************************************************************************************************************************************/
void DataManager::clean()
{
    for(std::map<std::string, Shader*>::iterator it = map_shader.begin(); it != map_shader.end(); ++it)
    {
        if(it->second != nullptr)
        {
            it->second->clean();
            delete it->second;
            it->second = nullptr;
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
    shader_init.push_back({"../../src/Shader/Shaders/screenShader.vert", "../../src/Shader/Shaders/screenShader.frag", "NONE", "screen"});
    shader_init.push_back({"../../src/Shader/Shaders/depthShader.vert", "../../src/Shader/Shaders/depthShader.frag", "../../src/Shader/Shaders/depthShader.geom", "depth_map"});
    shader_init.push_back({"../../src/Shader/Shaders/squareShader.vert", "../../src/Shader/Shaders/squareShader.frag", "NONE", "square"});
    shader_init.push_back({"../../src/Shader/Shaders/skybox.vert", "../../src/Shader/Shaders/skybox.frag", "NONE", "skybox"});
    shader_init.push_back({"../../src/Shader/Shaders/model.vert", "../../src/Shader/Shaders/model.frag", "NONE", "model"});
    shader_init.push_back({"../../src/Shader/Shaders/sunShader.vert", "../../src/Shader/Shaders/sunShader.frag", "NONE", "sun"});
    shader_init.push_back({"../../src/Shader/Shaders/planeteShader.vert", "../../src/Shader/Shaders/uniqueTexturePlaneteShader.frag", "NONE", "simple_textured_planete"});
    shader_init.push_back({"../../src/Shader/Shaders/planeteShader.vert", "../../src/Shader/Shaders/doubleTexturePlaneteShader.frag", "NONE", "double_textured_planete"});
    shader_init.push_back({"../../src/Shader/Shaders/planeteShader.vert", "../../src/Shader/Shaders/earthShader.frag", "NONE", "earth"});
    shader_init.push_back({"../../src/Shader/Shaders/ringShader.vert", "../../src/Shader/Shaders/ringShader.frag", "NONE", "ring"});
    shader_init.push_back({"../../src/Shader/Shaders/modelInstanced.vert", "../../src/Shader/Shaders/modelInstanced.frag", "NONE", "INSTmodel"});
    
    // shader_init.push_back({"../../src/Shader/Shaders/sphereShader.vert", "../../src/Shader/Shaders/sphereShader.frag", "atmosphere"});            

    for(std::vector<shader_datas>::iterator it = shader_init.begin(); it != shader_init.end(); ++it)
    {
        map_shader[it[0].key] = new Shader(it[0].v_shader_path, it[0].f_shader_path, it[0].g_shader_path);
        assert(map_shader[it[0].key]);
        assert(map_shader[it[0].key]->loadShader());
    }              
}

Shader* DataManager::getShader(std::string key)
{
    return map_shader[key];
}

void DataManager::setViewMat(glm::mat4 const new_val)
{
    view_mat = new_val;
}
glm::mat4 DataManager::getViewMat()
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

std::vector<glm::mat4> DataManager::getLightSpaceMatrix()
{
    glm::vec3 lightPos = this->getSunPos();
    
    glm::mat4 shadowProj = glm::perspective(glm::radians(90.f), (float) this->getWidth()/(float)this->getWidth(), (float)this->near_plane, (float)this->far_plane);
    // glm::mat4 shadowProj = glm::ortho(-100.f, 100.f, -100.f, 100.f, (float)this->near_plane, (float)this->far_plane);
    std::vector<glm::mat4> shadowTransforms;
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    shadowTransforms.push_back(shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));

    return shadowTransforms;

}

void DataManager::setDepthMapTexture(unsigned int const new_val)
{
    depth_map = new_val;
}

unsigned int DataManager::getDepthMapTexture() const
{
    return depth_map;
}

void DataManager::setPass(int const new_val)
{
    pass = new_val;
}

int DataManager::getPass() const
{
    return pass;
}

void DataManager::initDatas()
{
    Loader::initializeMap();
   
    m_bodys_data.push_back({1.f, "simple_textured_planete", 32, 0.f, glm::vec3(20.f, -30.f, 0.f), "Mercury", 0.035f});

    m_bodys_data.push_back({3.f, "double_textured_planete", 128, 0.1f, glm::vec3(100.f, 0.f, 0.f), "Venus", 177.36f});

    m_bodys_data.push_back({1.f, "simple_textured_planete", 32, 0.f, glm::vec3(-70.f, 0.f, 0.f), "Moon", 6.687f});
    m_bodys_data.push_back({3.f, "earth", 128, 0.5f, glm::vec3(-80.f, 0.f, 0.f), "Earth", 23.436f});

    m_bodys_data.push_back({3.f, "double_textured_planete", 128, 0.3f, glm::vec3(0.f, 80.f, 0.f), "Mars", 25.19f});

    m_bodys_data.push_back({5.f, "simple_textured_planete", 16, 0.f, glm::vec3(80.f, 50.f, 0.f), "Jupiter", 3.12f});

    m_bodys_data.push_back({5.f, "simple_textured_planete", 16, 0.f, glm::vec3(-60.f, -50.f, 0.f), "Saturn", 26.73f});
    
    m_bodys_data.push_back({5.f, "simple_textured_planete", 16, 0.f, glm::vec3(-60.f, 50.f, 0.f), "Uranus", 97.8f});

    m_bodys_data.push_back({5.f, "simple_textured_planete", 16, 0.f, glm::vec3(0.f, -80.f, 0.f), "Neptune", 28.32f});
}

body_data DataManager::getBodyData(int index)
{
    return m_bodys_data[index];
}