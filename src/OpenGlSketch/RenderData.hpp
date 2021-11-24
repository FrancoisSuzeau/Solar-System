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
        

/********************************************************************* class definition *********************************************************************/

        class RenderData
        {
            
            private:

                glm::mat4 projection;
                glm::mat4 view;
                glm::mat4 save_view;

                bool hdr;
                float exposure;

                // bool pause_music;
                // int volume;

                bool m_terminate;
                

                unsigned int frame_rate;
                Uint32 start_loop, end_loop, time_past;

                // bool is_moving;
                bool bloom;
                

            public:

                RenderData(int width, int height)
                {
                    // pause_music = false;
                    // volume = 0;

                    frame_rate = 1000 / 50;
                    start_loop = 0;
                    end_loop = 0;
                    time_past = 0;

                    exposure = 0.8;
                    hdr = true;

                    // is_moving = false;

                    projection = glm::perspective(glm::radians(45.0), (double)width / height, 1.0, 900000.0);
                    view = glm::mat4(1.0f);

                    bloom = true;

                    m_terminate = false;

                }
                ~RenderData() {}

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
 
        };


#endif