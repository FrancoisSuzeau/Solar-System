/*
AUTHOR : SUZEAU François

DATE : 23/11/2021

MODULE : DataManager

NAMEFILE : DataManager.hpp

PURPOSE : header of the DataManager class
*/

#ifndef DATA_H
#define DATA_H


/********************************************************************* includes *********************************************************************/

        #include <iostream>
        #include <map>
        #include <vector>

        #include "../Shader/Shader.hpp"
        #include "../Loader/Loader.hpp"
        
        #include <SDL2/SDL_ttf.h>

        #define COLOR_FBO 0
        #define DEPTH_FBO 1
        

/********************************************************************* class definition *********************************************************************/

        typedef struct shader_datas {

            std::string v_shader_path;
            std::string f_shader_path;
            std::string g_shader_path;
            std::string key;

        }shader_datas;

        typedef struct body_data {

                float                           size;
                std::string                     type;
                int                             shininess;
                float                           oppacity;
                glm::vec3                       initial_pos;
                std::string                     name;
                float                           inclinaison_angle;
                float                           light_strength;
                // std::vector<std::string> nom_disp_path;
                // std::string name;
                // float   speed_rotation;

        } body_data;

        class DataManager
        {
            
            private:
                
                static int             m_width;
                static int             m_height;
                bool            m_terminate;
                unsigned int    m_fps;
                int             m_volume;
                bool            m_pause_music;
                int             m_track;
                bool            bloom;
                int             bloom_strenght;
                bool            render_normal;
                int             asteroid_count;
                bool            render_overlay;
                bool            render_name;
                bool            render_info;
                float           distance_from_ship;
                int             index_ship;
                bool            change_skin;
                float           near_plane;
                float           far_plane;
                unsigned int    depth_map;
                int             pass;
                bool            render_shadow;

                glm::mat4       proj_mat;
                glm::mat4       view_mat;
                std::map<std::string, Shader*> map_shader;
                glm::vec3       ship_position;
                glm::vec3       cam_pos;

                bool            hilight_sun;
                
                

            public:

                DataManager(int width, int height, double angle);
                ~DataManager();

                void clean();

                static std::vector<body_data>          m_bodys_data;
                
                void            setTerminate(bool const terminate);
                static int             getWidth();
                static int             getHeight(); 
                bool            getTerminate() const;
                void            setFps(unsigned int const fps);
                unsigned int    getFps() const;
                void            setVolume(int const volume);
                int             getVolume() const;
                void            setPause(bool const pause);
                bool            getPause() const;
                void            setTrack(int const track);
                int             getTrack() const;
                void            setShader();
                Shader          *getShader(std::string key);
                glm::mat4       getViewMat();
                void            setViewMat(glm::mat4 const new_val);
                void            resetViewMat(glm::mat4 const new_mat);
                glm::mat4       getProjMat() const;
                void            lockView(glm::vec3 position, glm::vec3 target, glm::vec3 up);
                void            setBloom(bool const new_val);
                bool            getBloom() const;
                void            setBloomStrength(int const new_val);
                int             getBloomStrength() const;
                void            setRenderNormal(bool const new_val);
                bool            getRenderNormal() const;
                void            setAsteroidCount(int const new_val);
                int             getAsteroidCount() const;
                void            setRenderOverlay(bool const new_val);
                bool            getRenderOverlay() const;
                void            setRenderName(bool const new_val);
                bool            getRenderName() const;
                void            setRenderInfo(bool const new_val);
                bool            getRenderInfo() const;
                void            setDistanceFromShip(float const new_val);
                float           getDistancteFromShip() const;
                void            setIndexShip(int const new_val);
                int             getIndexShip() const;
                void            setChangeSkin(bool const new_val);
                bool            getChangeSkin() const;
                void            setShipPos(glm::vec3 const new_val);
                glm::vec3       getShipPos() const;
                void            setCamPos(glm::vec3 const new_val);
                glm::vec3       getCamPos() const;
                glm::vec3       getSunPos() const;
                float           getFar() const;
                float           getNear() const;
                std::vector<glm::mat4>       getLightSpaceMatrix();
                void            setDepthMapTexture(unsigned int const new_val);
                unsigned int    getDepthMapTexture() const;
                void            setPass(int const new_val);
                int             getPass() const;
                void            setHilightSun(bool const new_val);
                bool            getHilightSun() const;
                void            setRenderShadow(bool const new_val);
                bool            getRenderShadow() const;
                static void            initDatas();
                static body_data       getBodyData(int index);


                glm::vec2 convertToScreenSpace(glm::vec3 const body_pos);


        };


#endif