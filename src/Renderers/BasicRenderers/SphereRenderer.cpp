/*
AUTHOR : SUZEAU François

DATE : 06/06/2021

MODULE : Renderer::BasicRenderers

NAMEFILE : SphereRenderer.cpp

PURPOSE : class SphereRenderer
*/

//usefull macro for VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)0 + (offset))
#endif
#define VERT_NUM_FLOATS 8


#include "SphereRenderer.hpp"


/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
SphereRenderer::SphereRenderer(const float radius, const unsigned int longSegs, const unsigned int latSegs) : 
m_ibo(0), m_element_count(0), m_radius(radius)
{
    m_vboID = 0;
    /************************************************* calculate vertex position ********************************************************/
    longVerts = longSegs + 1;
    latVerts = latSegs + 1;
    m_vertCount = longVerts * latVerts;
    
    tmp = new GLfloat**[longVerts];
    
    for (unsigned int i(0); i < longVerts; i++)
    {
        const float iDivLong  = i / (float)longSegs;
        const float theta     = i == 0 || i == longSegs ? 0.0 : iDivLong * 2.0 * M_PI;

        tmp[i] = new GLfloat*[latVerts];

        for (unsigned int j = 0; j < latVerts; j++)
        {
            tmp[i][j] = new GLfloat[VERT_NUM_FLOATS];
            const float jDivLat = j / (float)latSegs;
            const float phi     = jDivLat * M_PI;

            // Normal
            tmp[i][j][3]  = cos(theta) * sin(phi);
            tmp[i][j][4]  = cos(phi);
            tmp[i][j][5]  = sin(theta) * sin(phi);

            // Position
            tmp[i][j][0]  = tmp[i][j][3] * radius;
            tmp[i][j][1]  = tmp[i][j][4] * radius;
            tmp[i][j][2]  = tmp[i][j][5] * radius;

            // Texture coordinates
            tmp[i][j][6]  = iDivLong;
            tmp[i][j][7]  = jDivLat;
        }
    }
    
    //===================================================================================================================================

    /************************************************* build triangle ********************************************************/
    const unsigned int triCount = longSegs * latSegs * 2;
    m_element_count = triCount * 3;
    GLushort tris[m_element_count];
    unsigned int index = 0;
    for (unsigned int i = 0; i < longSegs; i++)
    {
        for (unsigned int j = 0; j < latSegs; j++)
        {
            // Vertex indices
            const unsigned int v0 = j + latVerts * i;
            const unsigned int v1 = j + latVerts * (i + 1);
            const unsigned int v2 = v1 + 1;
            const unsigned int v3 = v0 + 1;

            // First triangle
            tris[index++]         = v0;
            tris[index++]         = v1;
            tris[index++]         = v2;

            // Second triangle
            tris[index++]         = v0;
            tris[index++]         = v2;
            tris[index++]         = v3;
        }
    }

    m_tris = tris;

    this->load();    
    // ===================================================================================================================================

}


SphereRenderer::~SphereRenderer()
{
    
}

/***********************************************************************************************************************************************************************/
/******************************************************************************** clean ******************************************************************************/
/***********************************************************************************************************************************************************************/
void SphereRenderer::clean()
{
    if(glIsBuffer(m_vboID) == GL_TRUE)
    {
        glDeleteBuffers(1, &m_vboID);
        m_vboID = 0;
    }
    if(glIsBuffer(m_ibo) == GL_TRUE)
    {
        glDeleteBuffers(1, &m_ibo);
        m_ibo = 0;
    }

    for(unsigned int i(0); i < longVerts; i++)
    {
        for(unsigned int j(0); j < latVerts; j++)
        {
            delete [] tmp[i][j];
        }
    }

    for(unsigned int i(0); i < longVerts; i++)
    {
        delete [] tmp[i];
    }

    delete [] tmp;

    std::cout << ">> SPHERE RENDERER : DESTROY COMPLETE" << std::endl;
}

/***********************************************************************************************************************************************************************/
/************************************************************************************** load ***************************************************************************/
/***********************************************************************************************************************************************************************/
void SphereRenderer::load()
{
    GLfloat verts[longVerts][latVerts][VERT_NUM_FLOATS];
    for(unsigned int i(0); i < longVerts; i++)
    {
        for(unsigned int j(0); j < latVerts; j++)
        {
            verts[i][j][0] = tmp[i][j][0];
            verts[i][j][1] = tmp[i][j][1];
            verts[i][j][2] = tmp[i][j][2];
            verts[i][j][3] = tmp[i][j][3];
            verts[i][j][4] = tmp[i][j][4];
            verts[i][j][5] = tmp[i][j][5];
            verts[i][j][6] = tmp[i][j][6];
            verts[i][j][7] = tmp[i][j][7];
        }
    }
    /************************************************* VBO management ********************************************************/
    //destroy a possible ancient VBO
    if(glIsBuffer(m_vboID) == GL_TRUE)
    {
        glDeleteBuffers(1, &m_vboID);
        m_vboID = 0;
    }

    //generate Vertex Buffer Object ID
    glGenBuffers(1, &m_vboID);
    assert(m_vboID != 0);

    //lock VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

        //memory allocation
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * VERT_NUM_FLOATS * m_vertCount, 0, GL_STATIC_DRAW);

        /*
            - GL_STATIC_DRAW : data with few updating
            - GL_DYNAMIC_DRAW : data with frequently updating (many times per second but not each frame
            - GL_STREAM_DRAW : data with each frame updating
        there is 6 other possible values
        */

       //vertices transfert$
       glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * VERT_NUM_FLOATS * m_vertCount, verts);


    //unlock VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //===================================================================================================================

    /************************************************* IBO management ********************************************************/
    //destroy a possible ancient IBO
    if(glIsBuffer(m_ibo) == GL_TRUE)
    {
        glDeleteBuffers(1, &m_ibo);
        m_ibo = 0;
    }

    //generate Index Buffer Object ID
    glGenBuffers(1, &m_ibo);
    assert(m_ibo != 0);

    //lock IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    

        //memory allocation
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * m_element_count, 0, GL_DYNAMIC_DRAW);


        /*
            - GL_STATIC_DRAW : data with few updating
            - GL_DYNAMIC_DRAW : data with frequently updating (many times per second but not each frame
            - GL_STREAM_DRAW : data with each frame updating
        there is 6 other possible values
        */

       //Indices transfert
       glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLushort) * m_element_count, m_tris);

    //unlock IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //===================================================================================================================
}


/***********************************************************************************************************************************************************************/
/******************************************************************************** render ******************************************************************************/
/***********************************************************************************************************************************************************************/
void SphereRenderer::render(DataManager &data_manager, Object *sphere)
{
    if(data_manager.getShader(sphere->getType()) != nullptr)
    {
        glUseProgram(data_manager.getShader(sphere->getType())->getProgramID());
        /************************************************* bind VBO and IBO ********************************************************/
        glBindBuffer(GL_ARRAY_BUFFER,         m_vboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glTexCoordPointer(2,  GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(sizeof(GLfloat) * 3 * 2));
        glNormalPointer(      GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(sizeof(GLfloat) * 3));
        glVertexPointer(  3,  GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(0));
        //===================================================================================================================================
        
        glDrawElements(GL_TRIANGLES, m_element_count, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));

        /************************************************* unbind VBO and IBO ********************************************************/
        glBindBuffer(GL_ARRAY_BUFFER,         0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
        //===================================================================================================================================

        glUseProgram(0);
    }
    
}