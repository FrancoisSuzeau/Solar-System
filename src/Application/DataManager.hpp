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
                glm::mat4       getProjMat() const;
                void            lockView(glm::vec3 position, glm::vec3 target, glm::vec3 up);


        };


#endif