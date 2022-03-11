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
        

/********************************************************************* class definition *********************************************************************/

        typedef struct shader_datas {

            std::string v_shader_path;
            std::string f_shader_path;
            std::string key;

        }shader_datas;

        class DataManager
        {
            
            private:
                
                int             m_width;
                int             m_height;
                bool            m_terminate;
                unsigned int    m_fps;
                int             m_volume;
                bool            m_pause_music;
                int             m_track;
                bool            hdr;
                float           exposure;
                bool            bloom;
                int             bloom_strenght;
                bool            render_normal;
                bool            render_parallax;
                int             asteroid_count;
                bool            render_overlay;
                bool            render_name;
                bool            render_info;

                glm::mat4       proj_mat;
                glm::mat4       view_mat;
                std::map<std::string, Shader*> map_shader;
                

            public:

                DataManager(int width, int height, double angle);
                ~DataManager();
                
                void            setTerminate(bool const terminate);
                int             getWidth() const;
                int             getHeight() const; 
                bool            getTerminate() const;
                void            setFps(unsigned int const fps);
                unsigned int    getFps() const;
                void            setVolume(int const volume);
                int             getVolume() const;
                void            setPause(bool const pause);
                bool            getPause() const;
                void            setTrack(int const track);
                int             getTrack() const;
                void            setShader(bool main_loop);
                Shader          *getShader(std::string key);
                glm::mat4       getViewMat() const;
                void            resetViewMat(glm::mat4 const new_mat);
                glm::mat4       getProjMat() const;
                void            lockView(glm::vec3 position, glm::vec3 target, glm::vec3 up);
                void            setHDR(bool const new_val);
                bool            getHDR() const;
                void            setExposure(float const new_value);
                float           getExposure() const;
                void            setBloom(bool const new_val);
                bool            getBloom() const;
                void            setBloomStrength(int const new_val);
                int             getBloomStrength() const;
                void            setRenderNormal(bool const new_val);
                bool            getRenderNormal() const;
                void            setRenderParallax(bool const new_val);
                bool            getRenderParallax() const;
                void            setAsteroidCount(int const new_val);
                int             getAsteroidCount() const;
                void            setRenderOverlay(bool const new_val);
                bool            getRenderOverlay() const;
                void            setRenderName(bool const new_val);
                bool            getRenderName() const;
                void            setRenderInfo(bool const new_val);
                bool            getRenderInfo() const;


        };


#endif