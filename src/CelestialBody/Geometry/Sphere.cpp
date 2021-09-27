/*
AUTHOR : SUZEAU François

DATE : 06/06/2021

MODULE : Forme.Sphere

NAMEFILE : Sphere.cpp

PURPOSE : class Sphere
*/

//usefull macro for VBO
#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)0 + (offset))
#endif
#define VERT_NUM_FLOATS 8


#include "Sphere.hpp"

using namespace glm;

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
Sphere::Sphere() : m_vbo(0), m_ibo(0), m_radius(0)
{

}

Sphere::Sphere(const float radius, const unsigned int longSegs, const unsigned int latSegs) : 
m_vbo(0), m_ibo(0), m_element_count(0), m_radius(radius)
{
    /************************************************* calculate vertex position ********************************************************/
    const unsigned int longVerts = longSegs + 1;
    const unsigned int latVerts = latSegs + 1;
    m_vertCount = longVerts * latVerts;
    GLfloat verts[longVerts][latVerts][VERT_NUM_FLOATS];
    

    for (unsigned int i(0); i < longVerts; i++)
    {
        const float iDivLong  = i / (float)longSegs;
        const float theta     = i == 0 || i == longSegs ? 0.0 : iDivLong * 2.0 * M_PI;

        for (unsigned int j = 0; j < latVerts; j++)
        {
            const float jDivLat = j / (float)latSegs;
            const float phi     = jDivLat * M_PI;

            // Normal
            verts[i][j][3]  = cos(theta) * sin(phi);
            verts[i][j][4]  = cos(phi);
            verts[i][j][5]  = sin(theta) * sin(phi);

            // Position
            verts[i][j][0]  = verts[i][j][3] * radius;
            verts[i][j][1]  = verts[i][j][4] * radius;
            verts[i][j][2]  = verts[i][j][5] * radius;

            // Texture coordinates
            verts[i][j][6]  = iDivLong;
            verts[i][j][7]  = jDivLat;
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
    
    //===================================================================================================================================

    /************************************************* VBO management ********************************************************/
    //destroy a possible ancient VBO
    if(glIsBuffer(m_vbo) == GL_TRUE)
    {
        glDeleteBuffers(1, &m_vbo);
    }

    //generate Vertex Buffer Object ID
    glGenBuffers(1, &m_vbo);

    //lock VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

        //memory allocation
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * VERT_NUM_FLOATS * m_vertCount, 0, GL_DYNAMIC_DRAW);

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
    }

    //generate Index Buffer Object ID
    glGenBuffers(1, &m_ibo);

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


Sphere::~Sphere()
{
    glDeleteBuffers(1, &m_ibo);
    glDeleteBuffers(1, &m_vbo);
}


/***********************************************************************************************************************************************************************/
/******************************************************************************** display ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Sphere::display(glm::mat4 &projection, glm::mat4 &modelview, glm::mat4 &light_src, glm::vec3 &camPos, bool hdr, Shader *sphere_shader, Shader *ring_shader)
{
    if(sphere_shader != nullptr)
    {
        glUseProgram(sphere_shader->getProgramID());
        /************************************************* bind VBO and IBO ********************************************************/
        glBindBuffer(GL_ARRAY_BUFFER,         m_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glTexCoordPointer(2,  GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(sizeof(GLfloat) * 3 * 2));
        glNormalPointer(      GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(sizeof(GLfloat) * 3));
        glVertexPointer(  3,  GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(0));
        //===================================================================================================================================

        // Render
        // glUniformMatrix4fv(glGetUniformLocation(sphere_shader->getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
        // glUniformMatrix4fv(glGetUniformLocation(sphere_shader->getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
        sphere_shader->setMat4("modelview", modelview);
        sphere_shader->setMat4("projection", projection);
        sphere_shader->setMat4("light_src", light_src);

        sphere_shader->setVec3("viewPos", camPos);

        sphere_shader->setInt("hdr", hdr);
        
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

void Sphere::displaySunAtmo(glm::mat4 &projection, glm::mat4 &modelview, bool hdr, Shader *atm_shader)
{
    if(atm_shader != nullptr)
    {
        glUseProgram(atm_shader->getProgramID());
        /************************************************* bind VBO and IBO ********************************************************/
        glBindBuffer(GL_ARRAY_BUFFER,         m_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glTexCoordPointer(2,  GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(sizeof(GLfloat) * 3 * 2));
        glNormalPointer(      GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(sizeof(GLfloat) * 3));
        glVertexPointer(  3,  GL_FLOAT, sizeof(GLfloat) * VERT_NUM_FLOATS, BUFFER_OFFSET(0));
        //===================================================================================================================================

        // Render
        // glUniformMatrix4fv(glGetUniformLocation(atm_shader->getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
        // glUniformMatrix4fv(glGetUniformLocation(atm_shader->getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
        atm_shader->setMat4("modelview", modelview);
        atm_shader->setMat4("projection", projection);

        atm_shader->setInt("hdr", hdr);
        
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