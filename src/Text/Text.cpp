/*
AUTHOR : SUZEAU François

DATE : 10/06/2021

MODULE : Text

NAMEFILE : Text.h

PURPOSE :   - Load and lock text surface
            - transform an SDL surface to a texture usable by OpenGL
*/

#include "Text.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Text::Text()
{

}

Text::Text(float x, float y, float z, std::string file_path, std::string const vertex_shader, std::string const fragment_shader) : 
m_file_path(file_path), m_shader(vertex_shader, fragment_shader)
{
	m_shader.loadShader();
    /************************************************* making triangle ********************************************************/
    float	verticeTmp[] = { -x, -y, -z,   x, -y, -z,   x, y, -z,  // Triangle 1
						-x, -y, -z,   -x, y, -z,   x, y, -z };  // Triangle 2

	float	coordTmp[] = { 0, 0,   1, 0,   1, 1,     // Triangle 1
							0, 0,   0, 1,   1, 1 };    // Triangle 2

	for (int i = 0; i < 18; i++)
	{
		m_vertices[i] = verticeTmp[i];

	}
	for (int i = 0; i < 12; i++)
	{
		m_texture_coord[i] = coordTmp[i];
	}
    //===================================================================================================================


}

Text::~Text()
{
    TTF_CloseFont(m_police);
	glDeleteTextures(1, &m_id);
}

/***********************************************************************************************************************************************************************/
/************************************************************************************ loadTTF **************************************************************************/
/***********************************************************************************************************************************************************************/
bool Text::loadTTF(std::string const text)
{
    /************************************************* load police ********************************************************/
    m_police = TTF_OpenFont(m_file_path.c_str(), 300);
    if(m_police == nullptr)
    {
        std::cout << ">> Loading font file : ERROR : " << TTF_GetError() << std::endl;
        return false;
    }
    std::cout << ">> Loading font file  " << m_file_path << " : SUCCESS" << std::endl;
    //===================================================================================================================

    /************************************************* create surface and invert pixel ********************************************************/
    m_colorText = {192, 192, 192};
    SDL_Surface *tmp = TTF_RenderText_Blended(m_police, text.c_str(), m_colorText);
    if(tmp == nullptr)
    {
        std::cout << ">> Creating blended surface : ERROR : " << TTF_GetError() << std::endl;
        return false;
    }
    std::cout << ">> Creating blended surface : SUCCESS" << std::endl;
    SDL_Surface *surface = this->reversePixels(tmp);
    SDL_FreeSurface(tmp);
    //===================================================================================================================

	//activate blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //creating ID for OpenGL Texture
	glGenTextures(1, &m_id);

	//lock OpenGL Texture
	glBindTexture(GL_TEXTURE_2D, m_id);

	//copying pixels
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
	//applying filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //texture proche -> GL_TEXTURE_MIN_FILTER
																		//lissage -> GL_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //texture lointaine -> GL_TEXTURE_MAG_FILTER
																		//pixlisation -> GL_NEAREST

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0); glVertex2d(150, 150);
	glTexCoord2d(1, 0); glVertex2d(surface->w, 150);
	glTexCoord2d(1, 1); glVertex2d(surface->w, surface->h);
	glTexCoord2d(0, 1); glVertex2d(150, surface->h);
	glEnd();

	//unlock OpenGL Texture
	glBindTexture(GL_TEXTURE_2D, 0);

	SDL_FreeSurface(surface);

	return true;
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** reversePixels ************************************************************************/
/***********************************************************************************************************************************************************************/
SDL_Surface *Text::reversePixels(SDL_Surface *src) const
{
    /************************************************* copying img without pixels **************************************************************/
    SDL_Surface *reverse_surface = SDL_CreateRGBSurface(0, src->w, src->h, src->format->BitsPerPixel, src->format->Rmask,
                                                        src->format->Gmask, src->format->Bmask, src->format->Amask);
    if(reverse_surface == NULL)
    {
        std::cout << ">> RGB surface : ERROR : " << SDL_GetError() << std::endl;
        return src;
    }
    std::cout << ">> RGB surface : SUCCESS" << std::endl;
    //==============================================================================================================================

    /************************************************* intermediate array  **************************************************************/
    unsigned char* src_pixels = (unsigned char *)src->pixels;
    unsigned char* inverted_pixels = (unsigned char *)reverse_surface->pixels;
    //==============================================================================================================================

    /************************************************* invert pixels  **************************************************************/
    for (int i(0); i < src->h; i++)
    {
        for (int j(0); j < src->w * src->format->BytesPerPixel; j++)
        {
            inverted_pixels[(src->w * src->format->BytesPerPixel * (src->h - 1 - i)) + j] = src_pixels[(src->w * src->format->BytesPerPixel * i) + j];
        }
        
    }
    //==============================================================================================================================


	return reverse_surface;
}

/***********************************************************************************************************************************************************************/
/************************************************************************************ renderText ***********************************************************************/
/***********************************************************************************************************************************************************************/
void Text::renderText(glm::mat4 &projection, glm::mat4 &modelview, float const z)
{
	// projection = perspective(70.0, (double)width / height, 1.0, 100.0);
	// modelview = mat4(1.0);

	/************************************************* positionning text **************************************************************/
	float size = 4.0;
	glm::mat4 save = modelview;
	modelview = translate(modelview, vec3(0.0, size - 4.0, z + 4.0));
	modelview = rotate(modelview, 180.0f, vec3(0.0, 1.0, 1.0));
	modelview = scale(modelview, vec3(size, size+10, 0));
    //==============================================================================================================================

	//activate shader program
	glUseProgram(m_shader.getProgramID());

	//send vertices coordinates
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
	glEnableVertexAttribArray(0);

	//send texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, m_texture_coord);
	glEnableVertexAttribArray(2);

	//send matrices
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));

	//lock texture
	glBindTexture(GL_TEXTURE_2D, m_id);

	//render
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//unlock texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//deactivate array
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(0);

	//deactivate shader program
	glUseProgram(0);

	modelview = save;

}

/***********************************************************************************************************************************************************************/
/************************************************************************************ renderTextStartScreen ************************************************************/
/***********************************************************************************************************************************************************************/
void Text::renderTextStartScreen(glm::mat4 &projection, glm::mat4 &modelview)
{
	//activate shader program
	glUseProgram(m_shader.getProgramID());

	//send vertices coordinates
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
	glEnableVertexAttribArray(0);

	//send texture coordinates
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, m_texture_coord);
	glEnableVertexAttribArray(2);

	//send matrices
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));

	//lock texture
	glBindTexture(GL_TEXTURE_2D, m_id);

	//render
	glDrawArrays(GL_TRIANGLES, 0, 6);

	//unlock texture
	glBindTexture(GL_TEXTURE_2D, 0);

	//deactivate array
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(0);

	//deactivate shader program
	glUseProgram(0);
}