/*
AUTHOR : SUZEAU François

DATE : 30/10/2021

MODULE : AsteroidField

NAMEFILE : AsteroidField.cpp

PURPOSE : class AsteroidField
*/

#include "AsteroidField.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
AsteroidField::AsteroidField(Shader *model_shader)
{
    m_amount = 4200;
    asteroid = new Model("../assets/model/rock/rock.obj");
    if(asteroid == nullptr)
    {
        exit(EXIT_FAILURE);
    }
    this->initModel();
    this->initInstanced(modelMatrices);

    m_model_shader = new Shader("../src/Shader/Shaders/modelInstanced.vert", "../src/Shader/Shaders/modelInstanced.frag");
    if(m_model_shader == nullptr)
    {
        exit(EXIT_FAILURE);
    }
    m_model_shader->loadShader();

    m_noramal_surface = new Texture("../assets/textures/normalMap/rock_normalMap.jpg");
    assert(m_noramal_surface);
    assert(m_noramal_surface->loadTexture());
}

AsteroidField::~AsteroidField()
{
    if(asteroid != nullptr)
    {
        delete asteroid;
    }

    if(m_model_shader != nullptr)
    {
        delete m_model_shader;
    }

    if(modelMatrices != nullptr)
    {
        delete modelMatrices;
    }

    glDeleteBuffers(1, &buffer1);

    if(m_noramal_surface != nullptr)
    {
        delete m_noramal_surface;
    }

}

/***********************************************************************************************************************************************************************/
/****************************************************************************** drawAsteroidField **********************************************************************/
/***********************************************************************************************************************************************************************/
void AsteroidField::drawAsteroidField(RenderData &render_data, glm::vec3 camPos)
{
    glm::mat4 save = render_data.getViewMat();

        if((asteroid != nullptr) && (m_model_shader != nullptr))
        {
            glUseProgram(m_model_shader->getProgramID());

            m_model_shader->setTexture("texture_diffuse1", 0);
            m_model_shader->setInt("hdr", render_data.getHDR());
            m_model_shader->setMat4("projection", render_data.getProjectionMat());
            m_model_shader->setMat4("view", render_data.getViewMat());
            m_model_shader->setVec3("viewPos", camPos);

            if(m_noramal_surface != nullptr)
            {

                m_model_shader->setInt("has_normal", true);
                m_model_shader->setTexture("normalMap", 1);

                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, m_noramal_surface->getID());
            }
            else
            {
                m_model_shader->setInt("has_normal", false);

            }
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, asteroid->getTextureLoadedID(0));

            for (unsigned int i = 0; i < asteroid->getSizeMeshesVector(); i++)
            {
                glBindVertexArray(asteroid->getMeshVAO(i));
                glDrawElementsInstanced(GL_TRIANGLES, asteroid->getMeshVectorIndiceSize(i), GL_UNSIGNED_INT, 0, m_amount);
                glBindVertexArray(0);
            }

            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, 0);
            
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);

            glUseProgram(0);

        }
        
    render_data.updateView(save);
}

/***********************************************************************************************************************************************************************/
/********************************************************************************** initModel **************************************************************************/
/***********************************************************************************************************************************************************************/
void AsteroidField::initModel()
{           

    modelMatrices = new glm::mat4[m_amount];

    float radius = 42000.0f;
    float offset = 1000.0f;

    for (unsigned int i = 0; i < m_amount; i++)
    {
        glm::mat4 model(1.0f);

        float min = -offset;
        float max = offset;

        float angle = (float) i / (float) m_amount * 360.0f;
        float displacement = min + ((float) rand() / RAND_MAX * (max - min + 1.0));
        float x = cos(glm::radians(angle)) * radius + displacement;

        displacement = min + ((float) rand() / RAND_MAX * (max - min + 1.0));
        float y = sin(glm::radians(angle)) * radius + displacement;

        min = -500.0f;
        max = 500.0f;
        displacement = min + ((float) rand() / RAND_MAX * (max - min + 1.0));
        float z = displacement * 0.4f;

        model = glm::translate(model, glm::vec3(x, y, z));

        float rotAngle = (rand() % 360);
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
        

        min = 1.0f;
        max = 20.0f;
        float scaleM = min + ((float) rand() / RAND_MAX * (max - min));
        model = glm::scale(model, glm::vec3(scaleM));
        

        modelMatrices[i] = model;

    }
}

/***********************************************************************************************************************************************************************/
/********************************************************************************** initInstance **************************************************************************/
/***********************************************************************************************************************************************************************/
void AsteroidField::initInstanced(glm::mat4 *matrice)
{
    // configure instanced array
    // -------------------------
    glGenBuffers(1, &buffer1);
    glBindBuffer(GL_ARRAY_BUFFER, buffer1);
    glBufferData(GL_ARRAY_BUFFER, m_amount * sizeof(glm::mat4), &matrice[0], GL_STATIC_DRAW);

    // set transformation matrices as an instance vertex attribute (with divisor 1)
    // note: we're cheating a little by taking the, now publicly declared, VAO of the model's mesh(es) and adding new vertexAttribPointers
    // normally you'd want to do this in a more organized fashion, but for learning purposes this will do.
    // -----------------------------------------------------------------------------------------------------------------------------------
    for (unsigned int i = 0; i < asteroid->getSizeMeshesVector(); i++)
    {
        unsigned int VAO = asteroid->getMeshVAO(i);
        glBindVertexArray(VAO);
        // set attribute pointers for matrix (4 times vec4)
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        glBindVertexArray(0);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);


}