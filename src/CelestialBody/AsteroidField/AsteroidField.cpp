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
    m_amount = 2500;
    asteroid = new Model("../assets/model/rock/rock.obj");
    if(asteroid == nullptr)
    {
        exit(EXIT_FAILURE);
    }
    this->initModel();

    if(model_shader != nullptr)
    {
        m_model_shader = model_shader;
    }
}

AsteroidField::~AsteroidField()
{
    if(asteroid != nullptr)
    {
        delete asteroid;
    }
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** drawAsteroidField **********************************************************************/
/***********************************************************************************************************************************************************************/
void AsteroidField::drawAsteroidField(std::vector<glm::mat4> projection_view_mat, bool hdr)
{
    glm::mat4 save = projection_view_mat[1];

        if((asteroid != nullptr) && (m_model_shader != nullptr))
        {
            for (unsigned int i = 0; i < m_amount; i++)
            {
                std::vector<glm::mat4> model_ligh_mat;
                model_ligh_mat.push_back(modelMatrices[i]);
                model_ligh_mat.push_back(modelLights[i]);
                asteroid->draw(projection_view_mat, model_ligh_mat , hdr, m_model_shader);
            }
        }
        
    projection_view_mat[1] = save;
}

/***********************************************************************************************************************************************************************/
/********************************************************************************** initModel **************************************************************************/
/***********************************************************************************************************************************************************************/
void AsteroidField::initModel()
{           
    glm::vec3 sun_pos = glm::vec3(0.01f, 0.0f, 0.0f); //cannot postioning to {0.0, 0.0, 0.0} so this the closest
    glm::mat4 light_src = glm::lookAt(sun_pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 save_light_src = light_src;

    modelMatrices = new glm::mat4[m_amount];
    modelLights = new glm::mat4[m_amount];

    float radius = 9000.0f;
    float offset = 100.0f;

    for (unsigned int i = 0; i < m_amount; i++)
    {
        glm::mat4 model(1.0f);

        float angle = (float) i / (float) m_amount * 360.0f;
        float displacement = (rand() % (int)(2*offset * 100)) / 100.0f - offset;
        float x = cos(glm::radians(angle)) * radius + displacement;

        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y = sin(glm::radians(angle)) * radius + displacement;

        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z = displacement * 0.4f;

        model = glm::translate(model, glm::vec3(x, y, z));
        light_src = glm::translate(light_src, glm::vec3(x, y, z));

        float rotAngle = (rand() % 360);
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
        light_src = glm::rotate(light_src, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

        float scaleM = (rand() % 20) / 100.0f + 5.0f;
        model = glm::scale(model, glm::vec3(scaleM));
        light_src = glm::scale(light_src, glm::vec3(scaleM));

        modelMatrices[i] = model;
        modelLights[i] = light_src;

        light_src = save_light_src;

    }
}