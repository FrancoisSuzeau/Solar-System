/*
AUTHOR : SUZEAU François

DATE : 13/03/2021

MODULE : Loader

NAMEFILE : Loader.hpp

PURPOSE :   - Load assets for stbi APi
            - Load assets for SDL image API
            - Load assets for SDL mixer API
            - Load assets for SDL TTF API

*/

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Loader.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Loader::Loader()
{
    
}

Loader::~Loader()
{
    
}

/***********************************************************************************************************************************************************************/
/********************************************************************************** loadWithStbi ***********************************************************************/
/***********************************************************************************************************************************************************************/
bool Loader::loadWithStbi(std::string file_path, GLuint &id, int &w, int &h)
{
    unsigned char* image_data = stbi_load(file_path.c_str(), &w, &h, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create a OpenGL texture identifier
    if(glIsTexture(id) == GL_TRUE)
    {
        glDeleteTextures(1, &id);
        id = 0;
    }

    glGenTextures(1, &id);
    assert(id != 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

unsigned int Loader::loadWithStbi(const char *path, const std::string &directory)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    int width, height, nrComponents;
    unsigned int textureID = 0;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glGenTextures(1, &textureID);
        assert(textureID != 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);

            std::cout << ">> Texture loading by path: " << path << " SUCCESS" << std::endl;

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);

    }
    else
    {
        std::string err_msg = "Texture failed to load for path : ";
        err_msg.append(path);
        showError(nullptr, ErrorHandler(err_msg.c_str()), __FILENAME__, __FUNCTION__, __LINE__);
        stbi_image_free(data);
    }

    return textureID;
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** loadWithSDLMixer ***********************************************************************/
/***********************************************************************************************************************************************************************/
 Mix_Music* Loader::loadWithSDLMixer(std::string file_path, Mix_Music *m_music)
{
    if(m_music != NULL)
    {
        Mix_FreeMusic(m_music);
    }
    /************************************************* load the file ********************************************************/
    m_music = Mix_LoadMUS(file_path.c_str());
    if(m_music == NULL)
    {
        std::string err_msg = "Loading file music : ";
        err_msg.append(Mix_GetError());
        showError(nullptr, ErrorHandler(err_msg.c_str()), __FILENAME__, __FUNCTION__, __LINE__);
        return m_music;
    }
    std::cout << ">> Loading file music : SUCCESS : " << file_path << std::endl; 
    return m_music;
}