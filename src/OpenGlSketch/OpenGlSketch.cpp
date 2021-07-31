/*
AUTHOR : SUZEAU François

DATE : 26/05/2021

MODULE : OpenGlSketch

NAMEFILE : OpenGlSketch.h

PURPOSE :   - creating OpenGL Context
            - Intialise all object of the scene
            - manage event and interaction
*/

//usefull macro for VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

#include "OpenGlSketch.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/

OpenGlSketch::OpenGlSketch(): m_window_title("No name"), m_window_width(800), m_window_height(600), m_input()
//m_openGL_context(0), m_window(0), m_initiGLEW(0), m_input()
{
    
}

OpenGlSketch::OpenGlSketch(std::string window_title, int width, int height): m_window_title(window_title), m_window_width(width), m_window_height(height), m_input()
//m_openGL_context(0), m_window(0), m_initiGLEW(0), m_input()
{

}

OpenGlSketch::~OpenGlSketch()
{
    SDL_GL_DeleteContext(m_openGL_context);
    SDL_DestroyWindow(m_window);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
    puts("");
    puts("");
    puts("");
    std::cout << ">> Leaving program SDL : SUCCESS" << std::endl;
}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** initWindow ********************************************************************/
/***********************************************************************************************************************************************************************/

bool OpenGlSketch::initWindow()
{
    /************************************************* initialize SDL ********************************************************/
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << ">> Initialise SDL : ERROR : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    std::cout << ">> Initialise SDL : SUCCESS" << std::endl;
    //===================================================================================================================

    /************************************************* initialize SDL mixer ********************************************************/
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
    {
        std::cout << ">> Initialise SDL mixer : ERROR : " << Mix_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    std::cout << ">> Initialise SDL mixer : SUCCESS" << std::endl;
    //===================================================================================================================

    /************************************************* initialize SDL ttf ********************************************************/
    if(TTF_Init() < 0)
    {
        std::cout << ">> Initialise TTF : ERROR : " << TTF_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return false;
    }
    std::cout << ">> Initialise TTF : SUCCESS" << std::endl;
    //===================================================================================================================

    /************************************************* setting attribute for openGL context ********************************************************/
    //openGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    /*
        - SDL_GL_CONTEXT_PROFILE_CORE : erradicate all ancient implementation OpenGL fonctionnality
        - SDL_GL_CONTEXT_PROFILE_COMPATIBILITY : compatible with OpenGL 2.1
    */

    //double buffering deprecated in OpenGL 3.3
    // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    //===================================================================================================================

    m_window = SDL_CreateWindow(m_window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_window_width, m_window_height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if(m_window == NULL)
    {
        std::cout << ">> Creating window : ERROR : " << SDL_GetError() << std::endl;
        Mix_CloseAudio();
        TTF_Quit();
        SDL_Quit();
        return false;
    }
    std::cout << ">> Creating window : SUCCESS" << std::endl;
    //===================================================================================================================

    /************************************************* creating an openGL context ********************************************************/
    m_openGL_context = SDL_GL_CreateContext(m_window);
    if(m_openGL_context == 0)
    {
        std::cout << ">> Creating context OpenGL : ERROR : " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        Mix_CloseAudio();
        TTF_Quit();
        SDL_Quit();
        return false;
    }
    std::cout << ">> Creating context OpenGL : SUCCESS" << std::endl;
    //===================================================================================================================

    return true;
}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** initGL ************************************************************************/
/***********************************************************************************************************************************************************************/
bool OpenGlSketch::initGL()
{
    /************************************************* initialize Glew ********************************************************/
    m_initiGLEW = glewInit();
    if (m_initiGLEW != GLEW_OK)
    {
        std::cout << ">> Initialize Glew : ERROR : " << glewGetErrorString(m_initiGLEW) << std::endl;
        SDL_GL_DeleteContext(m_openGL_context);
        SDL_DestroyWindow(m_window);
        Mix_CloseAudio();
        TTF_Quit();
        SDL_Quit();
        return false;
    }
    std::cout << ">> Initialize Glew : SUCCESS" << std::endl;
    glEnable(GL_DEPTH_TEST);
    //===================================================================================================================

    return true; 
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* initFrameBuffer *********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::initFrameBuffer()
{
    float quadVertices[] = {-1.0, -1.0, -1.0,   1.0, -1.0, -1.0,   1.0, 1.0, -1.0,   
                        -1.0, -1.0, -1.0,   -1.0, 1.0, -1.0,   1.0, 1.0, -1.0   

    };

    float temp_coord[] = {0, 0,   1, 0,   1, 1,
                          0, 0,   0, 1,   1, 1
                          
                          };

    int m_bytes_vertices_size = 18 * sizeof(float);
    int m_bytes_coord_size = 12 * sizeof(float);

    /************************************************* VBO management ********************************************************/
    //destroy a possible ancient VBO
    if(glIsBuffer(quadVBO) == GL_TRUE)
    {
        glDeleteBuffers(1, &quadVBO);
    }

    //generate Vertex Buffer Object ID
    glGenBuffers(1, &quadVBO);

    //lock VBO
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

        //memory allocation
        glBufferData(GL_ARRAY_BUFFER, m_bytes_vertices_size + m_bytes_coord_size, 0, GL_DYNAMIC_DRAW);
        /*
            - GL_STATIC_DRAW : data with few updating
            - GL_DYNAMIC_DRAW : data with frequently updating (many times per second but not each frame
            - GL_STREAM_DRAW : data with each frame updating
        there is 6 other possible values
        */

       //vertices transfert$
       glBufferSubData(GL_ARRAY_BUFFER, 0, m_bytes_vertices_size, quadVertices);
       glBufferSubData(GL_ARRAY_BUFFER, m_bytes_vertices_size, m_bytes_coord_size, temp_coord);


    //unlock VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //===================================================================================================================

    /************************************************* VAO management ********************************************************/
    //destroy a possible ancient VAO
    if(glIsVertexArray(quadVAO) == GL_TRUE)
    {
        glDeleteVertexArrays(1, &quadVAO);
    }
    //generate Vertex Array Object ID
    glGenVertexArrays(1, &quadVAO);

    //lock VAO
    glBindVertexArray(quadVAO);

        //lock VBO
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

        //acces to the vertices in video memory
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
        glEnableVertexAttribArray(0);

        //acces to the colors in video memory
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_bytes_vertices_size));
        glEnableVertexAttribArray(2);

        //unlock VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);

    //unlock VAO
    glBindVertexArray(0);
    //===================================================================================================================

    /************************************************* Framebuffer management ********************************************************/
    
    glGenFramebuffers(1, &fb);
    glBindFramebuffer(GL_FRAMEBUFFER, fb);

    //FOR BLOOM EFFECT !
    // glGenTextures(2, colorBuffers);
    // for (unsigned int i = 0; i < 2; i++)
    // {
    //     glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
    //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_window_width, m_window_height, 0, GL_RGBA, GL_FLOAT, NULL);
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //     // attach texture to framebuffer
    //     glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
    // }

    // glGenRenderbuffers(1, &rboDepth);
    // glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    // glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_window_width, m_window_height);
    // glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    // // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
    // unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    // glDrawBuffers(2, attachments);
    // // finally check if framebuffer is complete
    // if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    //     std::cout << "Framebuffer not complete!" << std::endl;
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // glGenTextures(2, pingpongColorbuffers);
    // for (unsigned int i = 0; i < 2; i++)
    // {
    //     glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
    //     glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
    //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_window_width, m_window_height, 0, GL_RGBA, GL_FLOAT, NULL);
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
    //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //     glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);
    //     // also check if framebuffers are complete (no need for depth buffer)
    //     if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    //         std::cout << "Framebuffer not complete!" << std::endl;
    //     glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
    // }

    //ONLY HDR THAT WORKS !
    // Create a texture to render to
    glGenTextures(1, &fb_texture);

    glBindTexture(GL_TEXTURE_2D, fb_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // NULL means reserve texture memory
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_window_width, m_window_height, 0, GL_RGBA, GL_FLOAT, NULL);
    // Attach the texture to the framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fb_texture, 0);

    glGenRenderbuffers(1, &depth_rb);
    glBindRenderbuffer(GL_RENDERBUFFER, depth_rb);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_window_width, m_window_height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depth_rb);
    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //===================================================================================================================


    screenShader = new Shader("../src/Shader/Shaders/screenShader.vert", "../src/Shader/Shaders/screenShader.frag");
    // shaderBlur = new Shader("../src/Shader/Shaders/blur.vert", "../src/Shader/Shaders/blur.frag");

    screenShader->loadShader();
    // shaderBlur->loadShader();
}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** startLoop *********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::startLoop()
{
    /************************************************* Variables ********************************************************/
    StartScreen *startScreen = new StartScreen();
    Camera      *startScreen_cam = new Camera(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0), 0.5, 0.9);

    aud = new Audio();

    solar_system = new SolarSystemCreator();

    Square      *square = new Square(0.05, "../src/Shader/Shaders/couleur3D.vert", "../src/Shader/Shaders/couleur3D.frag", 0.500);

    int nb_loaded(0);

    mat4 projection;
    mat4 model_view;
    mat4 save_model_view;     
    //===================================================================================================================

    m_input.displayPointer(false);
    m_input.capturePointer(true);

    //initialize modelview and projection matrix
    projection = perspective(70.0, (double)m_window_width / m_window_height, 1.0, 100.0);
    model_view = mat4(1.0);

    //loading system and making start screen
    while(nb_loaded < 9)
    {

        //cleaning the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        startScreen_cam->lookAt(model_view);

        //save the modelview matrix
        save_model_view = model_view;

            model_view = translate(model_view, vec3(0.0, 0.5, 2.6));
            startScreen->drawStartScreen(projection, model_view);

        //restaure the modelview matrix
        model_view = save_model_view;
        
            square->drawLoad(nb_loaded, projection, model_view);

        //restaure the modelview matrix
        model_view = save_model_view;

        //actualising the window
        SDL_GL_SwapWindow(m_window);

        if(nb_loaded == 0)
        {
            solar_system->MakingSystem("Solar System", 8);
            nb_loaded++;
        }
        if(nb_loaded < 9)
        {
            nb_loaded += solar_system->loadSystem(nb_loaded);
        }
        
    }

    SDL_Delay(1000);

    delete startScreen;
    delete startScreen_cam;
    delete square;

}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** mainLoop **********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::mainLoop()
{
    /************************************************* Variables ********************************************************/
    bool pause(false);
    bool pause_key_pressed(false);
    int change(0);

    unsigned int frame_rate(1000 / 50);
    Uint32 start_loop(0), end_loop(0), time_past(0);

    Camera	*camera = new Camera(vec3(100, 100, 100), vec3(0, 0, 0), vec3(0, 0, 1), 0.5, 0.9);

    mat4 projection;
    mat4 model_view;
    mat4 save_model_view;

    MusicOverlay overlay;

    //hdr variables
    float exposure(5.0f);
    bool hdr(true);
    bool hdr_key_pressed(false);

    //bloom effect variables
    // bool horizontal = true, first_iteration = true;
    // unsigned int amount = 10;
    
    //==================================================================================================================
    
    m_input.displayPointer(false);
    m_input.capturePointer(true);
    
    //initialize modelview and projection matrix
    projection = perspective(70.0, (double)m_window_width / m_window_height, 1.0, 1000.0);
    model_view = mat4(1.0);

    //load and play the music
    aud->loadMusic();
    aud->playMusic();

    while(!m_input.getTerminate())
    {   
        start_loop = SDL_GetTicks();
        
    /********************************************************** MANAGING EVENTS *************************************************************/
        m_input.updateEvents();

        if(m_input.getKey(SDL_SCANCODE_ESCAPE))
        {
            break;
        }

        if(m_input.getKey(SDL_SCANCODE_DOWN))
        {
            change = -1;
        }
        if(m_input.getKey(SDL_SCANCODE_UP))
        {
            change = 1;
        }

        if ((m_input.getKey(SDL_SCANCODE_H)) && (!hdr_key_pressed))
        {
            hdr = !hdr;
            hdr_key_pressed = true;
        }
        if ((m_input.getKey(SDL_SCANCODE_H)) == false)
        {
            hdr_key_pressed = false;
        }
        
        if((m_input.getKey(SDL_SCANCODE_SPACE)) && (!pause_key_pressed))
        {
            pause = !pause;
            pause_key_pressed = true;
        }
        if ((m_input.getKey(SDL_SCANCODE_SPACE)) == false)
        {
            pause_key_pressed = false;
        }
        //======================================================================================================================================

    /******************************************************** MANAGING MUSIC *******************************************************************/
        aud->volume(change);
        aud->pause(pause);
        pause = false;
        change = 0;
        aud->updateTrack();
    //===========================================================================================================================================

        camera->move(m_input);

        camera->lookAt(model_view);
        
        glm::vec3 camPos = camera->getPosition();

        // ///make sure we clear the framebuffer's content
        // glClearColor(0.0, 0.0, 0.0, 1.0f);

        // //cleaning the screen
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /********************************************************************** Framebuffer activation ******************************************************************/
            glBindFramebuffer(GL_FRAMEBUFFER, fb);

            glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

            ///make sure we clear the framebuffer's content
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

            //cleaning the screen
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /**************************************** RENDER OF ALL THE SCENE **************************************************/

            //save the modelview matrix
            save_model_view = model_view;

            /****************************************** skybox render **************************************************/

                solar_system->drawSkybox(projection, model_view, hdr);

            //restaure the modelview matrix
            model_view = save_model_view;

            /****************************************** bodys render ****************************************************/
            
                solar_system->drawSystem(projection, model_view, camPos, hdr);

            //restaure the modelview matrix
            model_view = save_model_view;

            /****************************************** atmosphere render *************************************************/

                solar_system->drawAtmo(projection, model_view, camPos, hdr);

            //restaure the modelview matrix
            model_view = save_model_view;

            /******************************************* name render *****************************************************/

                solar_system->drawName(projection, model_view, camPos);

            //restaure the modelview matrix
            model_view = save_model_view;

        //=======================================================================================================================================================

        /************************************************* OVERLAY RENDER ********************************************************/
            model_view = lookAt(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0));

                overlay.display(projection, model_view);

            //restaure the modelview matrix
            model_view = save_model_view;
        //=======================================================================================================================================================


        /************************************************* SWAPPING FRAMEBUFFER ********************************************************/
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // 2. blur bright fragments with two-pass Gaussian Blur 
        // --------------------------------------------------
        // glUseProgram(shaderBlur->getProgramID());

        //         shaderBlur->setTexture("image", 0);
        //         for (unsigned int i = 0; i < amount; i++)
        //         {
        //             glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
        //             shaderBlur->setInt("horizontal", horizontal);

        //             glBindVertexArray(quadVAO);
        //                 glBindTexture(GL_TEXTURE_2D, first_iteration ? colorBuffers[1] : pingpongColorbuffers[!horizontal]);  // bind texture of other framebuffer (or scene if first iteration)
        //                 glDrawArrays(GL_TRIANGLES, 0, 6);
        //             glBindVertexArray(0);

        //             horizontal = !horizontal;
        //             if (first_iteration)
        //             {
        //                 first_iteration = false;
        //             } 
        //         }

        //         glBindTexture(GL_TEXTURE_2D, 0);

        // glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // glUseProgram(0);


        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        // clear all relevant buffers
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(screenShader->getProgramID());

            glBindVertexArray(quadVAO);

                screenShader->setTexture("screenTexture", 0);
                // screenShader->setTexture("bloomBlur", 1);
                screenShader->setFloat("exposure", exposure);
                screenShader->setInt("hdr", hdr);

                // glActiveTexture(GL_TEXTURE0);
                // glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
                // glActiveTexture(GL_TEXTURE1);
                // glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!horizontal]);

                glBindTexture(GL_TEXTURE_2D, fb_texture);	// use the color attachment texture as the texture of the quad plane
                glDrawArrays(GL_TRIANGLES, 0, 6);

                glBindTexture(GL_TEXTURE_2D, 0);

            glBindVertexArray(0);
        glUseProgram(0);

    /************************************************* SWAPPING WINDOWS ********************************************************/

        //actualising the window
        SDL_GL_SwapWindow(m_window);

        //managing the frame rate
        end_loop = SDL_GetTicks();
        time_past = end_loop - start_loop;
        if(time_past < frame_rate)
        {
            SDL_Delay(frame_rate - time_past);
        }
    //===================================================================================================================
    }

    delete solar_system;
    delete camera;
    delete aud;
    delete screenShader;
    // delete shaderBlur;
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
    glDeleteFramebuffers(1, &fb);
    glDeleteRenderbuffers(1, &depth_rb);
}
