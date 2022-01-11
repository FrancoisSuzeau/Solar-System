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
AsteroidField::AsteroidField()
{
    m_amount = 10000;
    heightScale = 0.0f;
    asteroid = new Model("../assets/model/rock/rock.obj");
    if(asteroid == nullptr)
    {
        exit(EXIT_FAILURE);
    }
    this->initModel();
    this->initInstanced(modelMatrices);

    m_noramal_surface = new Texture("../assets/textures/normalMap/rock_normalMap.jpg");
    assert(m_noramal_surface);
    assert(m_noramal_surface->loadTexture());

    m_disp_surface = new Texture("../assets/textures/displacementMap/rock_dispMap.jpg");
    assert(m_disp_surface);
    assert(m_disp_surface->loadTexture());
}

AsteroidField::~AsteroidField()
{
    if(asteroid != nullptr)
    {
        delete asteroid;
    }

    if(modelMatrices != nullptr)
    {
        delete modelMatrices;
    }

    if(m_positions != nullptr)
    {
        delete m_positions;
    }

    if(rotAngle != nullptr)
    {
        delete rotAngle;
    }

    if(scaleM != nullptr)
    {
        delete scaleM;
    }

    if(m_rot_vector != nullptr)
    {
        delete m_rot_vector;
    }

    if(glIsBuffer(buffer1) == GL_TRUE)
    {
        glDeleteBuffers(1, &buffer1);
    }

    if(m_noramal_surface != nullptr)
    {
        delete m_noramal_surface;
    }

    if(m_disp_surface != nullptr)
    {
        delete m_disp_surface;
    }

}

/***********************************************************************************************************************************************************************/
/****************************************************************************** drawAsteroidField **********************************************************************/
/***********************************************************************************************************************************************************************/
void AsteroidField::drawAsteroidField(RenderData &render_data)
{
    glm::mat4 save = render_data.getViewMat();

        if((asteroid != nullptr) && (render_data.getShader("INSTmodel") != nullptr))
        {
            glUseProgram(render_data.getShader("INSTmodel")->getProgramID());

            render_data.getShader("INSTmodel")->setTexture("texture_diffuse1", 0);
            render_data.getShader("INSTmodel")->setInt("hdr", render_data.getHDR());
            render_data.getShader("INSTmodel")->setMat4("projection", render_data.getProjectionMat());
            render_data.getShader("INSTmodel")->setMat4("view", render_data.getViewMat());
            render_data.getShader("INSTmodel")->setVec3("viewPos", render_data.getCamPos());
            render_data.getShader("INSTmodel")->setVec3("sunPos", render_data.getSunPos());

            if(m_disp_surface != nullptr)
            {
                heightScale += 0.000001f;
                if(heightScale >= 360.0f)
                {
                    heightScale -= 360.0f;
                }
                render_data.getShader("INSTmodel")->setFloat("heightScale", heightScale);
                render_data.getShader("INSTmodel")->setInt("has_disp", render_data.getDispMapRender());
                
                glActiveTexture(GL_TEXTURE2);
                glBindTexture(GL_TEXTURE_2D, m_disp_surface->getID());
            }

            if(m_noramal_surface != nullptr)
            {

                render_data.getShader("INSTmodel")->setInt("has_normal", render_data.getShadowGround());
                render_data.getShader("INSTmodel")->setTexture("normalMap", 1);

                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, m_noramal_surface->getID());
            }
            else
            {
                render_data.getShader("INSTmodel")->setInt("has_normal", false);
                render_data.getShader("INSTmodel")->setInt("has_disp", false);

            }
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, asteroid->getTextureLoadedID(0));

            for (unsigned int i = 0; i < asteroid->getSizeMeshesVector(); i++)
            {
                glBindVertexArray(asteroid->getMeshVAO(i));
                glDrawElementsInstanced(GL_TRIANGLES, asteroid->getMeshVectorIndiceSize(i), GL_UNSIGNED_INT, 0, m_amount);
                glBindVertexArray(0);
            }

            if(m_disp_surface != nullptr)
            {
                glActiveTexture(GL_TEXTURE2);
                glBindTexture(GL_TEXTURE_2D, 0);
            }


            if(m_noramal_surface != nullptr)
            {
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
            
            
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
    m_positions = new glm::vec3[m_amount];
    rotAngle = new float[m_amount];
    scaleM = new float[m_amount];
    m_rot_vector = new glm::vec3[m_amount];

    float radius = 42000.0f;
    float offset = 5000.0f;

    for (unsigned int i = 0; i < m_amount; i++)
    {
        glm::mat4 model(1.0f);

        float min = -offset;
        float max = offset;

        float angle = (float) i / (float) m_amount * 360.0f;
        float displacement = min + ((float) rand() / RAND_MAX * (max - min + 1.0));
        // float x = cos(glm::radians(angle)) * radius + displacement;
        m_positions[i].x = cos(glm::radians(angle)) * radius + displacement;

        displacement = min + ((float) rand() / RAND_MAX * (max - min + 1.0));
        // float y = sin(glm::radians(angle)) * radius + displacement;
        m_positions[i].y = sin(glm::radians(angle)) * radius + displacement;

        min = -500.0f;
        max = 500.0f;
        displacement = min + ((float) rand() / RAND_MAX * (max - min + 1.0));
        // float z = displacement * 0.4f;
        m_positions[i].z = displacement * 0.4f;

        model = glm::translate(model, m_positions[i]);

        rotAngle[i] = (rand() % 360);
        min = -1.0f;
        max = 1.0f;
        m_rot_vector[i].x = min + ((float) rand() / RAND_MAX * (max - min));
        m_rot_vector[i].y = min + ((float) rand() / RAND_MAX * (max - min));
        m_rot_vector[i].z = min + ((float) rand() / RAND_MAX * (max - min));
        model = glm::rotate(model, rotAngle[i], m_rot_vector[i]);
        

        min = 1.0f;
        max = 20.0f;
        scaleM[i] = min + ((float) rand() / RAND_MAX * (max - min));
        model = glm::scale(model, glm::vec3(scaleM[i]));
        

        modelMatrices[i] = model;

    }
}

/***********************************************************************************************************************************************************************/
/********************************************************************************** initInstance ***********************************************************************/
/***********************************************************************************************************************************************************************/
void AsteroidField::initInstanced(glm::mat4 *matrice)
{
    // configure instanced array
    // -------------------------
    if(glIsBuffer(buffer1) == GL_TRUE)
    {
        glDeleteBuffers(1, &buffer1);
    }
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

/***********************************************************************************************************************************************************************/
/********************************************************************************** updatePostion **********************************************************************/
/***********************************************************************************************************************************************************************/
void AsteroidField::updatePostion(glm::vec3 shiPos)
{
    for (unsigned int i = 0; i < m_amount; i++)
    {
        glm::mat4 model(1.0f);

        model = glm::translate(model, (m_positions[i] - shiPos));

        rotAngle[i] += 0.005f;
        if(rotAngle[i] >= 360)
        {
            rotAngle[i] -= 360;
        }
        model = glm::rotate(model, rotAngle[i], m_rot_vector[i]);

        model = glm::scale(model, glm::vec3(scaleM[i]));

        modelMatrices[i] = model;
    }

    this->initInstanced(modelMatrices);
}

/***********************************************************************************************************************************************************************/
/************************************************************************************ updateCount **********************************************************************/
/***********************************************************************************************************************************************************************/
void AsteroidField::updateCount(RenderData &render_data)
{
    if(render_data.getAsteroidCount() != m_amount)
    {
        if(modelMatrices != nullptr)
        {
            delete modelMatrices;
        }

        if(m_positions != nullptr)
        {
            delete m_positions;
        }

        if(rotAngle != nullptr)
        {
            delete rotAngle;
        }

        if(scaleM != nullptr)
        {
            delete scaleM;
        }

        if(m_rot_vector != nullptr)
        {
            delete m_rot_vector;
        }

        m_amount = render_data.getAsteroidCount();

        this->initModel();
        this->initInstanced(modelMatrices);
    }
}