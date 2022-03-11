/*
AUTHOR : SUZEAU François

DATE : 13/06/2021

MODULE : Skybox

NAMEFILE : Skybox.cpp

PURPOSE : class Skybox

*/

#include "Skybox.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Skybox::Skybox()
{   
    GLfloat skyboxVertices[108] = 
    {
        // positions          
        -2.0f,  2.0f, -2.0f,
        -2.0f, -2.0f, -2.0f,
        2.0f, -2.0f, -2.0f,
        2.0f, -2.0f, -2.0f,
        2.0f,  2.0f, -2.0f,
        -2.0f,  2.0f, -2.0f,

        -2.0f, -2.0f,  2.0f,
        -2.0f, -2.0f, -2.0f,
        -2.0f,  2.0f, -2.0f,
        -2.0f,  2.0f, -2.0f,
        -2.0f,  2.0f,  2.0f,
        -2.0f, -2.0f,  2.0f,

        2.0f, -2.0f, -2.0f,
        2.0f, -2.0f,  2.0f,
        2.0f,  2.0f,  2.0f,
        2.0f,  2.0f,  2.0f,
        2.0f,  2.0f, -2.0f,
        2.0f, -2.0f, -2.0f,

        -2.0f, -2.0f,  2.0f,
        -2.0f,  2.0f,  2.0f,
        2.0f,  2.0f,  2.0f,
        2.0f,  2.0f,  2.0f,
        2.0f, -2.0f,  2.0f,
        -2.0f, -2.0f,  2.0f,

        -2.0f,  2.0f, -2.0f,
        2.0f,  2.0f, -2.0f,
        2.0f,  2.0f,  2.0f,
        2.0f,  2.0f,  2.0f,
        -2.0f,  2.0f,  2.0f,
        -2.0f,  2.0f, -2.0f,

        -2.0f, -2.0f, -2.0f,
        -2.0f, -2.0f,  2.0f,
        2.0f, -2.0f, -2.0f,
        2.0f, -2.0f, -2.0f,
        -2.0f, -2.0f,  2.0f,
        2.0f, -2.0f,  2.0f
    };

    glGenVertexArrays(1, &m_vaoID);
    glGenBuffers(1, &m_vboID);
    glBindVertexArray(m_vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    m_faces = {

            "../../assets/textures/SkyboxMap/right.png",
            "../../assets/textures/SkyboxMap/left.png",
            "../../assets/textures/SkyboxMap/up.png",
            "../../assets/textures/SkyboxMap/bottom.png",
            "../../assets/textures/SkyboxMap/front.png",
            "../../assets/textures/SkyboxMap/back.png"

                };
    m_texture_id = 0;
    m_texture_id = this->load();
    assert(m_texture_id != 0);
}

Skybox::~Skybox()
{
    glDeleteTextures(1, &m_texture_id);
    //destroy VBO
    glDeleteBuffers(1, &m_vboID);
    
    //destroy VAO
    glDeleteVertexArrays(1, &m_vaoID);

    if((glIsTexture(m_texture_id) == GL_FALSE) && 
    (glIsBuffer(m_vboID) == GL_FALSE) && 
    (glIsVertexArray(m_vaoID) == GL_FALSE))
    {
        std::cout << ">> SKYBOX :: delete >>> SUCESS" << std::endl;
    }

}

/***********************************************************************************************************************************************************************/
/************************************************************************************ load *****************************************************************************/
/***********************************************************************************************************************************************************************/
unsigned int Skybox::load()
{
    /************************************************* destroying ancien ID *********************************************/
    if(glIsTexture(m_texture_id) == GL_TRUE)
    {
        glDeleteTextures(1, &m_texture_id);
    }
    //===================================================================================================================

    /************************************************* generate ID ********************************************************/
    unsigned int textID;
    glGenTextures(1, &textID);
    //===================================================================================================================

    /************************************************* lock object ********************************************************/
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textID);
    //=====================================================================================================================
    
    /************************************************* load the file ********************************************************/
    for (unsigned int i(0); i < m_faces.size(); i++)
    {
        SDL_Surface *picture_SDL = nullptr;
        picture_SDL = IMG_Load(m_faces[i].c_str());
        if(picture_SDL == nullptr)
        {
            std::string msg_err = ">> Loading file img : ERROR : ";
            msg_err.append(SDL_GetError());
            showError(nullptr, ErrorHandler(msg_err.c_str()), __FILENAME__, __FUNCTION__, __LINE__);
            return 0;
        }
        std::cout << ">> Loading file " << m_faces[i] << " : SUCCESS" << std::endl;
        //===================================================================================================================

        /************************************************* copying pixels **************************************************************/
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, picture_SDL->w, picture_SDL->h, 0, GL_RGB, GL_UNSIGNED_BYTE, picture_SDL->pixels);
        SDL_FreeSurface(picture_SDL);
        //==============================================================================================================================
    }
    
    /************************************************* applying layer ********************************************************/
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    //=====================================================================================================================

    /************************************************* unlock object ********************************************************/
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    //=====================================================================================================================

    return textID;

}

/***********************************************************************************************************************************************************************/
/********************************************************************************* render *****************************************************************************/
/***********************************************************************************************************************************************************************/
void Skybox::render(DataManager &data_manager)
{   
    
    glDepthFunc(GL_LEQUAL);

    glUseProgram(data_manager.getShader("skybox")->getProgramID());

    //lock vao
        glBindVertexArray(m_vaoID);

        glm::mat4 save = data_manager.getViewMat();

        data_manager.getShader("skybox")->setMat4("view", data_manager.getViewMat());
        data_manager.getShader("skybox")->setMat4("projection", data_manager.getProjMat());

        data_manager.getShader("skybox")->setTexture("skybox", 0);
        // data_manager.getShader("skybox")->setInt("hdr", data_manager.getHDR());

        //lock texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_id);

        //display the form
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //unlock texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    //unlock VAO
    glBindVertexArray(0);

    glUseProgram(0);

    glDepthFunc(GL_LESS);
    
    data_manager.resetViewMat(save);
}

