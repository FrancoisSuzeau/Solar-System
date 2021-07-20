/*
AUTHOR : SUZEAU François

DATE : 26/05/2021

MODULE : Texture

NAMEFILE : Texture.h

PURPOSE :   - load an image with SDL2_image
            - generate ID of this OpenGL object
            - lock ID
            - Configure object
            - unlock ID
*/

#include "Texture.hpp"


/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Texture::Texture(): m_id(0), m_file_picture(""), m_width(0), m_height(0), 
//m_internal_format(0), m_format(0), 
m_empty_texture(false)
{

}

Texture& Texture::operator=(Texture const &texture_to_copy)
{
    m_file_picture = texture_to_copy.m_file_picture;

    m_width = texture_to_copy.m_width;
    m_height = texture_to_copy.m_height;
    m_format = texture_to_copy.m_format;
    m_internal_format = texture_to_copy.m_internal_format;
    m_empty_texture = texture_to_copy.m_empty_texture;

    if(m_empty_texture && glIsTexture(texture_to_copy.m_id) == GL_TRUE)
    {
        loadEmptyTexture();
    }
    else //if (glIsTexture(texture_to_copy.m_id) == GL_TRUE)
    {
        loadTexture();
    }

    //loadTexture();
    

    return *this;
}

Texture::Texture(std::string file_image) : m_id(0), m_file_picture(file_image), m_width(0), m_height(0), 
//m_format(0), m_internal_format(0), 
m_empty_texture(false)
{

}

Texture::Texture(int width, int height, GLenum format, GLenum internal_format, bool empty_texture):
m_id(0), m_file_picture(""), m_width(width), m_height(height), m_format(format), m_internal_format(internal_format), m_empty_texture(empty_texture)
{

}

Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}

/***********************************************************************************************************************************************************************/
/***************************************************************************** loadEmptyTexture ************************************************************************/
/***********************************************************************************************************************************************************************/
void Texture::loadEmptyTexture()
{
    /************************************************* destroying potential ancient texture ********************************************************/
    if(glIsTexture(m_id) == GL_TRUE)
    {
        glDeleteTextures(1, &m_id);
    }
    //===================================================================================================================

    /************************************************* generate id ********************************************************/
    glGenTextures(1, &m_id);
    //===================================================================================================================

    // lock texture
    glBindTexture(GL_TEXTURE_2D, m_id);

        glTexImage2D(GL_TEXTURE_2D, 0, m_internal_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, 0);

        /************************************************* applying layer ********************************************************/
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        //=====================================================================================================================

    //unlock texture
    glBindTexture(GL_TEXTURE_2D, 0);

}

/***********************************************************************************************************************************************************************/
/********************************************************************************* loadTexture *************************************************************************/
/***********************************************************************************************************************************************************************/
bool Texture::loadTexture()
{
    /************************************************* load the file ********************************************************/
    SDL_Surface *picture_SDL = IMG_Load(m_file_picture.c_str());
    if(picture_SDL == 0)
    {
        std::cout << ">> Loading file img : ERROR : " << SDL_GetError() << std::endl;
        return false;
    }
    std::cout << ">> Loading file " << m_file_picture << " : SUCCESS" << std::endl;
    //===================================================================================================================

    /************************************************* invert img ********************************************************/
    SDL_Surface *img_invert = pixelsInverter(picture_SDL);
    SDL_FreeSurface(picture_SDL);
    //===================================================================================================================

    /************************************************* destroying ancien ID *********************************************/
    if(glIsTexture(m_id) == GL_TRUE)
    {
        glDeleteTextures(1, &m_id);
    }
    //===================================================================================================================

    /************************************************* generate ID ********************************************************/
    glGenTextures(1, &m_id);
    //===================================================================================================================

    /************************************************* lock object ********************************************************/
    glBindTexture(GL_TEXTURE_2D, m_id);
    //=====================================================================================================================

    /************************************************* determinate the alpha component *************************************/
    GLenum intern_format(0);
    GLenum format(0);

    if(img_invert->format->BytesPerPixel == 3) //there is no alpha component
    {
        intern_format = GL_RGB;

        if(img_invert->format->Rmask == 0xff)
        {
            format = GL_RGB;
        }
        else
        {
            format = GL_BGR;
        }
    }
    else if(img_invert->format->BytesPerPixel == 4) //there is one
    {
        intern_format = GL_RGBA;

        if(img_invert->format->Rmask == 0xff)
        {
            format = GL_RGBA;
        }
        else
        {
            format = GL_BGRA;
        }
    }
    else
    {
        std::cout << ">> Alpha component : ERROR : picture format unknown" << std::endl;
        SDL_FreeSurface(img_invert);
        return false;
    }
    //=====================================================================================================================

    /************************************************* copying pixels **************************************************************/
    glTexImage2D(GL_TEXTURE_2D, 0, intern_format, img_invert->w, img_invert->h, 0, format, GL_UNSIGNED_BYTE, img_invert->pixels);
    //==============================================================================================================================

    /************************************************* applying layer ********************************************************/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //=====================================================================================================================

    /************************************************* unlock object ********************************************************/
    glBindTexture(GL_TEXTURE_2D, 0);
    //=====================================================================================================================

    SDL_FreeSurface(img_invert);
    return true;
}

/***********************************************************************************************************************************************************************/
/************************************************************************************ getID ****************************************************************************/
/***********************************************************************************************************************************************************************/
GLuint Texture::getID() const
{
    return m_id;
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* setFilePicture **********************************************************************/
/***********************************************************************************************************************************************************************/
void Texture::setFilePicture(const std::string &file_image)
{
    m_file_picture = file_image;
}

/***********************************************************************************************************************************************************************/
/********************************************************************************* pixelInverter ***********************************************************************/
/***********************************************************************************************************************************************************************/
SDL_Surface* Texture::pixelsInverter(SDL_Surface *src_img) const
{
    /************************************************* copying img without pixels **************************************************************/
    SDL_Surface *img_inverted = SDL_CreateRGBSurface(0, src_img->w, src_img->h, src_img->format->BitsPerPixel, src_img->format->Rmask,
                                                        src_img->format->Gmask, src_img->format->Bmask, src_img->format->Amask);
    if(img_inverted == NULL)
    {
        std::cout << ">> RGB surface : ERROR : " << SDL_GetError() << std::endl;
        return src_img;
    }
    std::cout << ">> RGB surface : SUCCESS" << std::endl;
    //==============================================================================================================================

    /************************************************* intermediate array  **************************************************************/
    unsigned char* src_pixels = (unsigned char *)src_img->pixels;
    unsigned char* inverted_pixels = (unsigned char *)img_inverted->pixels;
    //==============================================================================================================================

    /************************************************* invert pixels  **************************************************************/
    for (int i(0); i < src_img->h; i++)
    {
        for (int j(0); j < src_img->w * src_img->format->BytesPerPixel; j++)
        {
            inverted_pixels[(src_img->w * src_img->format->BytesPerPixel * (src_img->h - 1 - i)) + j] = src_pixels[(src_img->w * src_img->format->BytesPerPixel * i) + j];
        }
        
    }
    //==============================================================================================================================

    return img_inverted;
}

/***********************************************************************************************************************************************************************/
/************************************************************************************ getFileName **********************************************************************/
/***********************************************************************************************************************************************************************/
std::string Texture::getFileName() const
{
    return m_file_picture;
}

