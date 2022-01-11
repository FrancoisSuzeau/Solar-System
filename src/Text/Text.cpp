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

Text::Text(float x, float y, float z, std::string file_path) : 
m_file_path(file_path)
{
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

	m_police = nullptr;

	model_mat = glm::mat4(1.0f);

}

Text::Text(float x, float y, float z, std::string file_path, TTF_Font *police) : 
m_file_path(file_path)
{
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

	m_police = police;
	assert(m_police);

}

Text::~Text()
{
	//no need to close font because it is made in the mainLoop method
	
	glDeleteTextures(1, &m_id);
	if(glIsTexture(m_id) == GL_FALSE)
    {
        std::cout << "TEXT :: delete >>> SUCESS" << std::endl;
    }
}

/***********************************************************************************************************************************************************************/
/************************************************************************************ loadTTF **************************************************************************/
/***********************************************************************************************************************************************************************/
bool Text::loadTTF(std::string const text)
{
	
    /************************************************* load police ********************************************************/
	if(m_police == nullptr)
	{
		m_police = TTF_OpenFont(m_file_path.c_str(), 300);
		if(m_police == nullptr)
		{
			std::cout << ">> Loading font file : ERROR : " << TTF_GetError() << std::endl;
			return false;
		}
		std::cout << ">> Loading font file  " << m_file_path << " : SUCCESS" << std::endl;
	}
    
    //===================================================================================================================

	assert(this->setText(text));

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
/********************************************************************************** updatePosition *********************************************************************/
/***********************************************************************************************************************************************************************/
void Text::updatePosition(glm::vec3 position)
{
	model_mat = glm::mat4(1.0f);
	model_mat = glm::translate(model_mat, position);
}

/***********************************************************************************************************************************************************************/
/********************************************************************************** updateScale *********************************************************************/
/***********************************************************************************************************************************************************************/
void Text::updateScale(glm::vec3 position)
{
	model_mat = glm::scale(model_mat, position);
}

/***********************************************************************************************************************************************************************/
/************************************************************************************** rotateText *********************************************************************/
/***********************************************************************************************************************************************************************/
void Text::rotateText(double ratio, float phi, float theta, float y)
{
	phi = (float) (phi * 180 / M_PI);
	theta = (float) (theta * 180 / M_PI);

	if((phi < 0.0f) && (y > 0.0f))
	{
		model_mat = rotate(model_mat, glm::radians(-90.0f + phi), vec3(0.0f, 0.0f, 1.0f));
	}
	else if( (phi > 0.0f) && (y < 0.0f) )
	{
		model_mat = rotate(model_mat, glm::radians(-90.0f + phi), vec3(0.0f, 0.0f, 1.0f));
	}
	else if( (phi > 0.0f) && (y > 0.0f) )
	{
		model_mat = rotate(model_mat, glm::radians(90.0f + phi), vec3(0.0f, 0.0f, 1.0f));
	}
	else if( (phi < 0.0f) && (y < 0.0f) )
	{
		model_mat = rotate(model_mat, glm::radians(90.0f + phi), vec3(0.0f, 0.0f, 1.0f));
	}

	model_mat = rotate(model_mat, glm::radians(theta), vec3(1.0f, 0.0f, 0.0f));
		
	
}

/***********************************************************************************************************************************************************************/
/************************************************************************************ renderText ***********************************************************************/
/***********************************************************************************************************************************************************************/
void Text::renderMovingText(RenderData &render_data, double ratio, float phi, float theta, float y)
{

	if(render_data.getShader("text") != nullptr)
	{
		
		render_data.initSaveMat();

		this->rotateText(ratio, phi, theta, y);

		this->updateScale(glm::vec3(4.0f * (ratio/270), (4.0f+10)*(ratio/270), 0));

		this->renderText(render_data);

		render_data.saveViewMat();
	}
	

}

/***********************************************************************************************************************************************************************/
/******************************************************************************* renderTextoverlay *********************************************************************/
/***********************************************************************************************************************************************************************/
void Text::renderText(RenderData &render_data)
{
	if(render_data.getShader("text") != nullptr)
	{
		//activate shader program
		glUseProgram(render_data.getShader("text")->getProgramID());

		//send vertices coordinates
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
		glEnableVertexAttribArray(0);

		//send texture coordinates
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, m_texture_coord);
		glEnableVertexAttribArray(2);

		//send matrices
		render_data.getShader("text")->setMat4("projection", render_data.getProjectionMat());
		render_data.getShader("text")->setMat4("view", render_data.getViewMat());
		render_data.getShader("text")->setMat4("model", model_mat);
		render_data.getShader("text")->setTexture("texture0", 0);

		//lock texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_id);

		//render
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//unlock texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);

		//deactivate array
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(0);

		//deactivate shader program
		glUseProgram(0);
	}
	
}

/***********************************************************************************************************************************************************************/
/*************************************************************************************** setText ***********************************************************************/
/***********************************************************************************************************************************************************************/
bool Text::setText(std::string const text)
{
	/************************************************* create surface and invert pixel ********************************************************/
    m_colorText.r = 192;
    m_colorText.g = 192;
    m_colorText.b = 192;
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
	if(glIsTexture(m_id) == GL_TRUE)
	{
		glDeleteTextures(1, &m_id);
	}
	glGenTextures(1, &m_id);

	//lock OpenGL Texture
    glActiveTexture(GL_TEXTURE0);
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
    glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	SDL_FreeSurface(surface);

	return true;
}