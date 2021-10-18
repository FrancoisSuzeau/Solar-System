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
using namespace ButtonChoice;

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
    float quadVertices[] = {-1.0f, -1.0f, -1.0f,   1.0f, -1.0f, -1.0f,   1.0f, 1.0f, -1.0f,   
                        -1.0f, -1.0f, -1.0f,   -1.0f, 1.0f, -1.0f,   1.0f, 1.0f, -1.0f   

    };

    float temp_coord[] = {0.0f, 0.0f,   1.0f, 0.0f,   1.0f, 1.0f,
                          0.0f, 0.0f,   0.0f, 1.0f,   1.0f, 1.0f
                          
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
    if(screenShader == nullptr)
    {
        exit(EXIT_FAILURE);
    }

    screenShader->loadShader();
}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** startLoop *********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::startLoop()
{
    /************************************************* Variables ********************************************************/
    /************************************************* load police ********************************************************/
    m_police.push_back(TTF_OpenFont("../assets/font/venus rising rg.ttf", 300));
    if(m_police[0] == nullptr)
    {
        std::cout << ">> Loading font file : ERROR : " << TTF_GetError() << std::endl;
    }
    std::cout << ">> Loading font file  " << "../assets/font/venus rising rg.ttf" << " : SUCCESS" << std::endl;

    m_police.push_back(TTF_OpenFont("../assets/font/aAtmospheric.ttf", 300));
    if(m_police[1] == nullptr)
    {
        std::cout << ">> Loading font file : ERROR : " << TTF_GetError() << std::endl;
    }
    std::cout << ">> Loading font file  " << "../assets/font/aAtmospheric.ttf" << " : SUCCESS" << std::endl;

    StartScreen *startScreen = new StartScreen(m_police[0]);
    if(startScreen == nullptr)
    {
        exit(EXIT_FAILURE);
    }

    Camera      *startScreen_cam = new Camera(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), 0.5f, 0.9f);
    if(startScreen_cam == nullptr)
    {
        exit(EXIT_FAILURE);
    }

    text_shader = new Shader("../src/Shader/Shaders/textShader.vert", "../src/Shader/Shaders/textShader.frag");
    if(text_shader == nullptr)
    {
        exit(EXIT_FAILURE);
    }
    text_shader->loadShader();

    m_overlay = new Overlay(m_police[1]);
    if(m_overlay == nullptr)
    {
        exit(EXIT_FAILURE);
    }

    m_settings = new Settings(m_police[1]);
    if(m_settings == nullptr)
    {
        exit(EXIT_FAILURE);
    }

    aud = new Audio();
    if(aud == nullptr)
    {
        exit(EXIT_FAILURE);
    }

    solar_system = new SolarSystemCreator();
    if(solar_system == nullptr)
    {
        exit(EXIT_FAILURE);
    }

    square_shader = new Shader("../src/Shader/Shaders/couleur3D.vert", "../src/Shader/Shaders/couleur3D.frag");
    if(square_shader == nullptr)
    {
        exit(EXIT_FAILURE);
    }
    square_shader->loadShader();

    Square      *square = new Square(0.05f, 0.500f);
    vec3 color = vec3(0.5f);
    if(square == nullptr)
    {
        exit(EXIT_FAILURE);
    }

    m_particuleGenerator = new Particule();
    std::cout << m_particuleGenerator << std::endl;
    if(m_particuleGenerator == nullptr)
    {
        exit(EXIT_FAILURE);
    }

    int nb_loaded(0);

    mat4 projection;
    mat4 model_view;
    mat4 save_model_view;     
    //===================================================================================================================

    m_input.capturePointer(true);
    m_input.displayPointer(false);

    //initialize modelview and projection matrix
    projection = perspective(glm::radians(70.0), (double)m_window_width / m_window_height, 1.0, 120.0);
    model_view = mat4(1.0f);

    //loading system and making start screen
    while(nb_loaded < 9)
    {

        //cleaning the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(startScreen_cam != nullptr)
        {
            startScreen_cam->lookAt(model_view);
        }
        

        //save the modelview matrix
        save_model_view = model_view;

            model_view = translate(model_view, vec3(0.0f, 0.5f, 0.0f));
            if(startScreen != nullptr)
            {
                if(text_shader != nullptr)
                {
                    startScreen->drawStartScreen(projection, model_view, text_shader);
                }
            }
            

        //restaure the modelview matrix
        model_view = save_model_view;
        
            if(square != nullptr)
            {
                square->drawLoad(nb_loaded, projection, model_view, color, square_shader);
            }
            
        //restaure the modelview matrix
        model_view = save_model_view;

        //actualising the window
        SDL_GL_SwapWindow(m_window);

        if(nb_loaded == 0)
        {
            if(solar_system != nullptr)
            {
                solar_system->MakingSystem("Solar System", 8, m_police[0]);
                nb_loaded++;
            }
            
        }
        if(nb_loaded < 9)
        {
            if(solar_system != nullptr)
            {
                nb_loaded += solar_system->loadSystem(nb_loaded, m_police[0]);
            }
            
        }
        
    }

    SDL_Delay(1000);

    if(startScreen != nullptr)
    {
        delete startScreen;
    }
    
    if(startScreen_cam != nullptr)
    {
        delete startScreen_cam;
    }
    
    if(square != nullptr)
    {
        delete square;
    }
    

}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** mainLoop **********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::mainLoop()
{
    Spaceship ship("../assets/model/spaceship/number1/OBJ/untitled.obj");
    Shader *m_model_shader = new Shader("../src/Shader/Shaders/model.vert", "../src/Shader/Shaders/model.frag");
    if(m_model_shader == nullptr)
    {
        exit(EXIT_FAILURE);
    }
    m_model_shader->loadShader();
    /************************************************* Variables ********************************************************/
    pause_music = false;
    speed_key_pressed = false;
    volume = 0;

    m_terminate = false;

    frame_rate = 1000 / 50;
    start_loop = 0;
    end_loop = 0;
    time_past = 0;

    camera = new Camera(vec3(1.0f, 9000.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), 0.5f, 200.0f);
    
    if(camera == nullptr)
    {
        exit(EXIT_FAILURE);
    }

    //hdr variables
    exposure = 5.0f;
    hdr = true;
    hdr_key_pressed = false;

    menu = false;
    menu_app_key_pressed = false;

    info_render = false;
    info_render_key_pressed = false;

    m_overlay_display = true;
    m_name_display = true;

    is_moving = false;

    //==================================================================================================================
    
    m_input.capturePointer(true);
    m_input.displayPointer(false);
    
    //initialize modelview and projection matrix
    projection = perspective(glm::radians(70.0), (double)m_window_width / m_window_height, 1.0, 9000000.0);
    model_view = mat4(1.0f);

    //load and play the music
    if(aud != nullptr)
    {
        aud->loadMusic();
        // aud->playMusic();
    }

    
    

    while(!m_terminate)
    {   
        start_loop = SDL_GetTicks();
    
    /********************************************************** MANAGING EVENTS *************************************************************/
        m_input.updateEvents();

        windowProcess();

    //======================================================================================================================================

    /******************************************************** MANAGING MUSIC *******************************************************************/
        if(aud != nullptr)
        {
            aud->volume(volume);
            aud->pause(pause_music);
            volume = 0;
            // aud->updateTrack();
        }
        
    //===========================================================================================================================================
        if(camera != nullptr)
        {
            camera->move(m_input, !menu);

            camera->lookAt(model_view);
        }

    /********************************************************************** Framebuffer activation ******************************************************************/
            glBindFramebuffer(GL_FRAMEBUFFER, fb);

            glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

            ///make sure we clear the framebuffer's content
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

            //cleaning the screen
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /************************************************************** RENDER OF ALL THE SCENE *****************************************************************/
            renderScene();
    //=======================================================================================================================================================

    /******************************************************************* RENDER OVERLAY ********************************************************************/
            renderOverlay();
    //=======================================================================================================================================================

    /******************************************************************* RENDER OVERLAY ********************************************************************/
            renderInfo();
    //=======================================================================================================================================================

    /******************************************************************* RENDER OVERLAY ********************************************************************/
            renderSettings();
    //=======================================================================================================================================================

    /******************************************************************* RENDER PARTICLES ********************************************************************/
        if(is_moving)
        {
            renderParticles();
        }
    //=======================================================================================================================================================

        save_model_view = model_view;

            std::vector<glm::mat4> projection_view;
            projection_view.push_back(projection);
            projection_view.push_back(model_view);

            ship.drawSpaceship(projection_view, hdr, m_model_shader, camera, m_input);
        
        model_view = save_model_view;


    /**************************************************************** SWAPPING FRAMEBUFFER *****************************************************************/
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
        // clear all relevant buffers
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(screenShader != nullptr)
        {
            glUseProgram(screenShader->getProgramID());

                glBindVertexArray(quadVAO);

                    screenShader->setTexture("screenTexture", 0);
                    screenShader->setFloat("exposure", exposure);
                    screenShader->setInt("hdr", hdr);

                    glBindTexture(GL_TEXTURE_2D, fb_texture);	// use the color attachment texture as the texture of the quad plane
                    glDrawArrays(GL_TRIANGLES, 0, 6);

                    glBindTexture(GL_TEXTURE_2D, 0);

                glBindVertexArray(0);
            glUseProgram(0);
        }

        

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

    if(solar_system != nullptr)
    {
        delete solar_system;
    }
    
    if(camera != nullptr)
    {
        delete camera;
    }
    
    if(aud != nullptr)
    {
        delete aud;
    }
    
    if(screenShader != nullptr)
    {
        delete screenShader;
    }

    if(m_overlay != nullptr)
    {
        delete m_overlay;
    }
    
    if(m_settings != nullptr)
    {
        delete m_settings;
    }
    
    if(text_shader != nullptr)
    {
        delete text_shader;
    }

    if(square_shader != nullptr)
    {
        delete square_shader;
    }

    if(m_particuleGenerator != nullptr)
    {
        delete m_particuleGenerator;
    }

    for (int i(0); i < 2; i++)
    {
        if(m_police[i] != nullptr)
        {
            TTF_CloseFont(m_police[i]);
        }
    }

    if(m_model_shader != nullptr)
    {
        delete m_model_shader;
    }
    
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
    glDeleteFramebuffers(1, &fb);
    glDeleteRenderbuffers(1, &depth_rb);
    
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** renderScene ***********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::renderOverlay()
{
    if((m_overlay_display) && (square_shader != nullptr))
    {
        if((aud != nullptr) && (camera != nullptr) && (m_overlay != nullptr))
        {
            std::string track = aud->getTrack();
            glm::vec3 position = camera->getPosition();
            float speed = camera->getSpeed();

                model_view = lookAt(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

                    m_overlay->displayGeneralOverlay(projection, model_view, hdr, square_shader);

                //restaure the modelview matrix
                model_view = save_model_view;

                model_view = lookAt(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

                    m_overlay->displayMusicOverlay(projection, model_view, hdr, track, text_shader, square_shader);

                //restaure the modelview matrix
                model_view = save_model_view;

                model_view = lookAt(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

                    m_overlay->displayMoveInfoOverlay(projection, model_view, hdr, position, speed, text_shader, square_shader);

                //restaure the modelview matrix
                model_view = save_model_view;

                model_view = lookAt(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

                    m_overlay->displayTimeInfoOverlay(projection, model_view, hdr, text_shader, square_shader);

                //restaure the modelview matrix
                model_view = save_model_view;
        }
        
    }
    
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** renderScene ***********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::renderScene()
{
    if( (camera != nullptr) && (solar_system != nullptr))
    {
        glm::vec3 camPos = camera->getPosition();

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

                if((text_shader != nullptr) && (m_name_display == true))
                {
                    solar_system->drawName(projection, model_view, camPos, text_shader);
                }
                

            //restaure the modelview matrix
            model_view = save_model_view;

            /******************************************* asteroid field render *****************************************************/

                std::vector<glm::mat4> projection_view;
                projection_view.push_back(projection);
                projection_view.push_back(model_view);

                solar_system->drawAsteroidField(projection_view, hdr);
                
            //restaure the modelview matrix
            model_view = save_model_view;
    }
    
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** renderInfo ***********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::renderInfo()
{
    if((camera != nullptr) && (solar_system != nullptr) && (square_shader != nullptr))
    {
        if(info_render)
        {
            //save the modelview matrix
            save_model_view = model_view;

            glm::vec3 camPos = camera->getPosition();

                if(text_shader != nullptr)
                {
                    solar_system->drawInfo(projection, model_view, camPos, hdr, nullptr, text_shader, square_shader);
                }
                

            //restaure the modelview matrix
            model_view = save_model_view;
        }
    }
    
    

}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** windowProcess *********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::windowProcess()
{
        if(m_input.getKey(SDL_SCANCODE_ESCAPE))
        {
            m_terminate = true;
        }

        int scroll = m_input.getScroll();

        if(camera != nullptr)
        {
            if(scroll != 0)
            {
                if((camera->getSpeed() < 200.0f) && (scroll > 0))
                {
                    camera->setSpeed(1.0f);
                }

                if((camera->getSpeed() >= 0.0f) && (scroll < 0))
                {
                    camera->setSpeed(-1.0f);
                }
            }
        }
        
        
        if((m_input.getKey(SDL_SCANCODE_Q)) && (!speed_key_pressed))
        {
            if(camera->getSpeed() > 0.6f)
            {
                camera->setMinimumSpeed();
            }
            speed_key_pressed = true;
        }
        if ((m_input.getKey(SDL_SCANCODE_Q)) == false)
        {
            speed_key_pressed = false;
        }

        if((m_input.getKey(SDL_SCANCODE_E)) && (!speed_key_pressed))
        {
            if(camera->getSpeed() > 0.6f)
            {
                camera->setMaximumSpeed();
            }
            speed_key_pressed = true;
        }
        if ((m_input.getKey(SDL_SCANCODE_E)) == false)
        {
            speed_key_pressed = false;
        }

        if((m_input.getKey(SDL_SCANCODE_P)) && (!menu_app_key_pressed))
        {
            menu = !menu;
            menu_app_key_pressed = true;
        }
        if ((m_input.getKey(SDL_SCANCODE_P)) == false)
        {
            menu_app_key_pressed = false;
        }

        if((m_input.getKey(SDL_SCANCODE_I)) && (!info_render_key_pressed))
        {
            info_render = !info_render;
            info_render_key_pressed = true;
        }
        if ((m_input.getKey(SDL_SCANCODE_I)) == false)
        {
            info_render_key_pressed = false;
        }

        if((m_input.getKey(SDL_SCANCODE_W)) || (m_input.getKey(SDL_SCANCODE_S)) || (m_input.getKey(SDL_SCANCODE_A)) || (m_input.getKey(SDL_SCANCODE_D)))
        {
            is_moving = true;
        }
        else if((!m_input.getKey(SDL_SCANCODE_W)) && (!m_input.getKey(SDL_SCANCODE_S)) && (!m_input.getKey(SDL_SCANCODE_A)) && (!m_input.getKey(SDL_SCANCODE_D)))
        {
            is_moving = false;
        }
}

/***********************************************************************************************************************************************************************/
/*********************************************************************************** renderSetting *********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::renderSettings()
{
    if((camera != nullptr) && (m_settings != nullptr) && (square_shader != nullptr))
    {
        if(menu)
        {
            m_input.capturePointer(false);
            m_input.displayPointer(true);

            model_view = lookAt(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

                m_settings->displayFrameSettings(projection, model_view, hdr, text_shader, square_shader);

            model_view = save_model_view;

            int button_type = m_settings->manageButton(m_input);

            switch (button_type)
            {
                case QUIT:
                    m_terminate = true;
                    break;

                case HDR_ON:
                    hdr = true;
                    if(exposure == 0.0f)
                    {
                        exposure = 5.0f;
                    }
                    break;

                case HDR_OFF:
                    hdr = false;
                    break;

                case EXPOSURE_DEC:
                    if( (exposure >= 0.0f) && (exposure <= 5.0f))
                    {
                        exposure = exposure - 1.0f;
                    }
                    if(exposure == 0.0f)
                    {
                        hdr = false;
                    }
                    break;

                case EXPOSURE_INC:
                    if( (exposure >= 0.0f) && (exposure <= 5.0f))
                    {
                        exposure = exposure + 1.0f;
                    }
                    if(exposure > 5.0f)
                    {
                        exposure = 5.0f;
                    }
                    if(exposure == 1.0f)
                    {
                        hdr = true;
                    }
                    break;

                case SPEED_DEC:
                    if((camera->getSpeed() >= 0.0f))
                    {
                        camera->setSpeed(-0.1f);
                    }
                    break;

                case SPEED_INC:
                    if(camera->getSpeed() <= 1.0f)
                    {
                        camera->setSpeed(0.1f);
                    }
                    break;

                case MUSIC_ON:
                    pause_music = false;
                    break;
        
                case MUSIC_OFF:
                    pause_music = true;
                    break;

                case MUSIC_DEC:
                    volume = -2;
                    break;

                case MUSIC_INC:
                    volume = 2;
                    break;

                case OVERLAY_ON:
                    m_overlay_display = true;
                    break;

                case OVERLAY_OFF:
                    m_overlay_display = false;
                    break;

                case PLANETE_INFO_ON:
                    info_render = true;
                    break;
                
                case PLANETE_INFO_OFF:
                    info_render = false;
                    break;

                case SHOW_NAME_ON:
                    m_name_display = true;
                    break;

                case SHOW_NAME_OFF:
                    m_name_display = false;
                    break;

                default:
                    break;
            }
        }
        else
        {
            m_input.capturePointer(true);
            m_input.displayPointer(false);
        }
    }
    
    
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* renderParticles *********************************************************************/
/***********************************************************************************************************************************************************************/
void OpenGlSketch::renderParticles()
{
    glm::mat4 save = model_view;

        model_view = lookAt(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
        
        if(m_particuleGenerator != nullptr)
        {
            if((m_input.getKey(SDL_SCANCODE_W)) && (m_input.getKey(SDL_SCANCODE_S)))
            {
                //do nothing
            }
            else
            {
                m_particuleGenerator->drawParticles(projection, model_view, m_input, camera->getSpeed());
            }
        }

    model_view = save;
}