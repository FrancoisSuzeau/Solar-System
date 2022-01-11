/*
AUTHOR : SUZEAU François

DATE : 23/11/2021

MODULE : RenderData

NAMEFILE : RenderData.h

PURPOSE : header of the RenderData class
*/

#ifndef RENDERDATA_H
#define RENDERDATA_H


/********************************************************************* includes *********************************************************************/

        #include <glm/glm.hpp>
        #include <glm/gtx/transform.hpp>
        #include <glm/gtc/type_ptr.hpp>

        #include <SDL2/SDL.h>
        #include <iostream>
        #include <string>
        #include <math.h>
        #include <cassert>
        #include <map>
        #include <vector>

        #include "../../lib/imgui/imgui.h"
        #include "../../lib/imgui/imgui_impl_sdl.h"
        #include "../../lib/imgui/imgui_impl_opengl3.h"

        #include "../Shader/Shader.hpp"

        typedef struct shader_datas {

            std::string v_shader_path;
            std::string f_shader_path;
            std::string key;

        }shader_datas;
        

/********************************************************************* class definition *********************************************************************/

        class RenderData
        {
            
            private:

                glm::mat4 projection;
                glm::mat4 view;
                glm::mat4 save_view;

                glm::vec3 camPos;
                glm::vec3 shiPos;
                glm::vec3 sunPos;

                bool hdr;
                float exposure;

                int track_music;

                bool pause_music;
                int volume;

                bool m_terminate;

                int m_width;
                int m_height;
                
                bool menu;

                unsigned int frame_rate;
                Uint32 start_loop, end_loop, time_past;

                bool bloom;
                unsigned int bloom_str;

                bool normal_map_render;

                std::map<std::string, Shader*> map_shader;

                float ship_speed;
                

            public:

                RenderData(int width, int height, double angle, bool main_loop)
                {
                    // pause_music = false;
                    volume = 64;

                    frame_rate = 1000 / 50;
                    start_loop = 0;
                    end_loop = 0;
                    time_past = 0;

                    exposure = 0.8;
                    hdr = true;

                    // is_moving = false;

                    projection = glm::perspective(glm::radians(angle), (double)width / height, 1.0, 900000.0);
                    view = glm::mat4(1.0f);

                    bloom = true;
                    bloom_str = 10;

                    normal_map_render = true;

                    m_terminate = false;

                    m_width = width;
                    m_height = height;

                    setShader(main_loop);

                }
                ~RenderData()
                {
                    for(std::map<std::string, Shader*>::iterator it = map_shader.begin(); it != map_shader.end(); ++it)
                    {
                        if(it->second != nullptr)
                        {
                            delete it->second;
                        }
                    }
                }

                glm::mat4& getViewMat() { return view;}

                glm::mat4& getProjectionMat() {return projection;}

                void saveViewMat() { view = save_view;}
                void initSaveMat() { save_view = view;}

                void initFrameRate() { start_loop = SDL_GetTicks();}
                void manageFrameRate()
                {
                    end_loop = SDL_GetTicks();
                    time_past = end_loop - start_loop;
                    if(time_past < frame_rate)
                    {
                        SDL_Delay(frame_rate - time_past);
                    }
                }

                void lockViewMat(glm::vec3 position, glm::vec3 target, glm::vec3 up)
                {
                    view = glm::lookAt(position, target, up);
                }

                void updateExposure(float new_value) {exposure = new_value;}
                void changeExposure(float value_to_add) {exposure += value_to_add;}
                float getExposure() const {return exposure;}
                void updateBloom(bool update) {bloom = update;}
                void updateHDR(bool update) {hdr = update;}

                bool getHDR() const {return hdr;}
                bool getBloom() const {return bloom;}
                void updateView(glm::mat4 &new_mat) {view = new_mat;}

                void setShader(bool main_loop)
                {
                    std::vector<shader_datas> shader_init;
                    shader_init.push_back({"../src/Shader/Shaders/textShader.vert", "../src/Shader/Shaders/textShader.frag", "text"});
                    shader_init.push_back({"../src/Shader/Shaders/couleur3D.vert", "../src/Shader/Shaders/couleur3D.frag", "square"});

                    if(main_loop)
                    {
                        shader_init.push_back({"../src/Shader/Shaders/model.vert", "../src/Shader/Shaders/model.frag", "model"});
                        shader_init.push_back({"../src/Shader/Shaders/planeteTexture.vert", "../src/Shader/Shaders/oneTexturePlanete.frag", "one_texture_p"});
                        shader_init.push_back({"../src/Shader/Shaders/planeteTexture.vert", "../src/Shader/Shaders/MultiPlaneteTexture.frag", "multi_texture_p"});
                        shader_init.push_back({"../src/Shader/Shaders/sunShader.vert", "../src/Shader/Shaders/sunShader.frag", "sun"});
                        shader_init.push_back({"../src/Shader/Shaders/texture.vert", "../src/Shader/Shaders/texture.frag", "ring"});
                        shader_init.push_back({"../src/Shader/Shaders/sphereShader.vert", "../src/Shader/Shaders/sphereShader.frag", "atmosphere"});
                        shader_init.push_back({"../src/Shader/Shaders/screenShader.vert", "../src/Shader/Shaders/screenShader.frag", "screen"});
                        shader_init.push_back({"../src/Shader/Shaders/blur.vert", "../src/Shader/Shaders/blur.frag", "blur"});
                        shader_init.push_back({"../src/Shader/Shaders/modelInstanced.vert", "../src/Shader/Shaders/modelInstanced.frag", "INSTmodel"});
                    }
                    

                    for(std::vector<shader_datas>::iterator it = shader_init.begin(); it != shader_init.end(); ++it)
                    {
                        map_shader[it[0].key] = new Shader(it[0].v_shader_path, it[0].f_shader_path);
                        assert(map_shader[it[0].key]);
                        assert(map_shader[it[0].key]->loadShader());
                    }
                    
                }

                Shader *getShader(std::string key) {return map_shader[key];}

                void setCamPos(glm::vec3 new_cam_pos) {camPos = new_cam_pos;}
                void setShipPos(glm::vec3 new_ship_pos) {shiPos = new_ship_pos;}
                glm::vec3 getCamPos() const {return camPos;}
                glm::vec3 getShipPos() const {return shiPos;}

                void setSunPos(glm::vec3 new_sun_pos) {sunPos = new_sun_pos;}
                glm::vec3 getSunPos() const {return sunPos;}

                int getWidth() const {return m_width;}
                int getHeight() const {return m_height;}

                void setTrackMusic(int const track) {track_music = track;}
                int getTrack() const {return track_music;}

                int getVolume() const {return volume;}
                void setVolume(int const new_volume) {volume = new_volume;}

                void setPauseMusic(bool const pause) {pause_music = pause;}
                bool getPauseMusic() const {return pause_music;}

                void setShipSpeed(float const speed) {ship_speed = speed;}
                float getShipSpeed() const {return ship_speed;}

                static void HelpMarker(std::string sentence)
                {
                    ImGui::TextDisabled("(?)");
                    if (ImGui::IsItemHovered())
                    {
                        ImGui::BeginTooltip();
                        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                        ImGui::TextUnformatted(sentence.c_str());
                        ImGui::PopTextWrapPos();
                        ImGui::EndTooltip();
                    }
                }

                void setMenu(bool const new_val) {menu = new_val;}
                bool getMenu() const {return menu;}

                void setTerminate(bool const new_val) {m_terminate = new_val;}
                bool getTerminate() const {return m_terminate;}

                void setBloomStr(unsigned int new_val) {bloom_str = new_val;}
                unsigned int getBloomStr() const {return bloom_str;}

                void setRenderShadowGround(bool const new_val) {normal_map_render = new_val;}
                bool getShadowGround() const {return normal_map_render;}
 
        };


#endif