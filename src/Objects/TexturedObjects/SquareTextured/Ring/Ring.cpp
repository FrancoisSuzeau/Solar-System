/*
AUTHOR : SUZEAU François

DATE : 10/06/2021

MODULE : Objects::TexturedObjects::SquareTextured::Ring

NAMEFILE : Ring.cpp

PURPOSE : class Ring

*/

#include "Ring.hpp"

/***********************************************************************************************************************************************************************/
/*********************************************************************** Constructor and Destructor ********************************************************************/
/***********************************************************************************************************************************************************************/
// Ring::Ring(float size, std::string const texture, init_data data): Disk(size),
// m_texture(texture), m_bytes_coord_size(12 * sizeof(float))
// {
    
//     assert(m_texture.loadTexture());

//     m_rotation_angle = 0.0f;
//     m_speed_rotation = 0.1f;

//     heighhtScale = 0.000001f;

//     if(data.name == "Saturn")
//     {
//         m_inclinaison_angle = 26.73f;
//         m_real_size = 300.0f;

//         m_normal_surf = new Texture("../../assets/textures/normalMap/ring_sat_normalMap.jpg");
//         assert(m_normal_surf);
//         assert(m_normal_surf->loadTexture());

//         m_disp_surf = new Texture("../../assets/textures/displacementMap/sat_ring_dispMap.jpg");
//         assert(m_disp_surf);
//         assert(m_disp_surf->loadTexture());
//     }
//     else if(data.name == "Uranus")
//     {
//         m_inclinaison_angle = 97.77f;
//         m_real_size = 100.0f;

//         m_normal_surf = new Texture("../../assets/textures/normalMap/ring_ur_normalMap.jpg");
//         assert(m_normal_surf);
//         assert(m_normal_surf->loadTexture());

//         m_disp_surf = new Texture("../../assets/textures/displacementMap/ur_ring_dispMap.jpg");
//         assert(m_disp_surf);
//         assert(m_disp_surf->loadTexture());
//     }
//     else if(data.name == "Neptune")
//     {
//         m_inclinaison_angle = 26.32f;
//         m_real_size = 100.0f;

//         m_normal_surf = new Texture("../../assets/textures/normalMap/ring_nep_normalMap.jpg");
//         assert(m_normal_surf);
//         assert(m_normal_surf->loadTexture());

//         m_disp_surf = new Texture("../../assets/textures/displacementMap/nep_ring_dispMap.jpg");
//         assert(m_disp_surf);
//         assert(m_disp_surf->loadTexture());
//     }

//     float temp_coord[] = {0, 0,   1, 0,   1, 1,
//                           0, 0,   0, 1,   1, 1,
                          
//                           };

//     for (int i(0); i < 12; i++)
//     {
//         m_coord[i] = temp_coord[i];
//     }

//     this->load();
    
// }

Ring::Ring(float size, std::vector<std::string> textures_path, std::string const type, int shininess) : super(size, type)
{
    m_shininess = shininess;
    int i = 0;
    for(std::vector<std::string>::iterator it = textures_path.begin(); it != textures_path.end(); ++it)
    {
        super::surface_tex_ids.push_back(Loader::loadTextureWithSDL(it[0]));
        assert(super::surface_tex_ids[i] != 0);
        i++;
    }
}

Ring::~Ring()
{
    // if(m_normal_surf != nullptr)
    // {
    //     delete m_normal_surf;
    // }

    // if(m_disp_surf != nullptr)
    // {
    //     delete m_disp_surf;
    // }
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** transform ******************************************************************************/
/***********************************************************************************************************************************************************************/
void Ring::transform(glm::vec3 ship_pos, Input *input)
{
    super::m_model_mat = glm::mat4(1.0);

    super::translateObject(super::m_model_mat, (super::m_position + ship_pos));
    super::scaleObject(super::m_model_mat, super::m_size);
}

/***********************************************************************************************************************************************************************/
/****************************************************************************** sendToShader ***************************************************************************/
/***********************************************************************************************************************************************************************/
void Ring::sendToShader(DataManager &data_manager)
{
    if(data_manager.getPass() == COLOR_FBO)
    {
        if(data_manager.getShader(super::m_type) != nullptr)
        {
            glUseProgram(data_manager.getShader(super::m_type)->getProgramID());
                data_manager.getShader(super::m_type)->setTexture("diffuseTexture", 0);
                data_manager.getShader(super::m_type)->setVec3("sunPos", data_manager.getSunPos());
                data_manager.getShader(super::m_type)->setVec3("viewPos", data_manager.getCamPos());
                data_manager.getShader(super::m_type)->setMat4("light_space_matrix", data_manager.getLightSpaceMatrix());
                data_manager.getShader(super::m_type)->setTexture("shadowMap", 1);
                // data_manager.getShader(super::m_type)->setInt("material.shininess", m_shininess);
            glUseProgram(0);
        }
    }
    
    super::sendToShader(data_manager);
}

// /***********************************************************************************************************************************************************************/
// /************************************************************************************ load *****************************************************************************/
// /***********************************************************************************************************************************************************************/
// void Ring::load()
// {
//     /************************************************* VBO management ********************************************************/
//     //destroy an possible ancient VBO
//     if(glIsBuffer(m_vboID) == GL_TRUE)
//     {
//         glDeleteBuffers(1, &m_vboID);
//     }

//     //generate Vertex Buffer Object ID
//     glGenBuffers(1, &m_vboID);

//     //lock VBO
//     glBindBuffer(GL_ARRAY_BUFFER, m_vboID);


//         //memory allocation
//         glBufferData(GL_ARRAY_BUFFER, m_bytes_vertices_size + m_bytes_coord_size, 0, GL_DYNAMIC_DRAW);
//         /*
//             - GL_STATIC_DRAW : data with few updating
//             - GL_DYNAMIC_DRAW : data with frequently updating (many times per second but not each frame
//             - GL_STREAM_DRAW : data with each frame updating
//         there is 6 other possible values
//         */

//        //vertices transfert$
//        glBufferSubData(GL_ARRAY_BUFFER, 0, m_bytes_vertices_size, m_vertices);
//        glBufferSubData(GL_ARRAY_BUFFER, m_bytes_vertices_size, m_bytes_coord_size, m_coord);


//     //unlock VBO
//     glBindBuffer(GL_ARRAY_BUFFER, 0);
//     //===================================================================================================================

//     /************************************************* VAO management ********************************************************/
//     if(glIsVertexArray(m_vaoID) == GL_TRUE)
//     {
//         glDeleteVertexArrays(1, &m_vaoID);
//     }
//     //generate Vertex Array Object ID
//     glGenVertexArrays(1, &m_vaoID);

//     //lock VAO
//     glBindVertexArray(m_vaoID);

//         //lock VBO
//         glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

//         //access to vertices in video memory
//         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
//         glEnableVertexAttribArray(0);

//         //acces to coordonates texture in video memory
//         glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_bytes_vertices_size));
//         glEnableVertexAttribArray(2);

//         //unlock VBO
//         glBindBuffer(GL_ARRAY_BUFFER, 0);

//     //unlock VAO
//     glBindVertexArray(0);
//     //===================================================================================================================

// }

// /***********************************************************************************************************************************************************************/
// /****************************************************************************** updatePosRing **************************************************************************/
// /***********************************************************************************************************************************************************************/
// void Ring::updatePosRing(glm::vec3 planPos)
// {
//     m_current_position = planPos;
// }

// /***********************************************************************************************************************************************************************/
// /************************************************************************************ display **************************************************************************/
// /***********************************************************************************************************************************************************************/
// void Ring::display(RenderData &render_data)
// {
//     if(render_data.getShader("ring") != nullptr)
//     {
//         //Activate the shader
//         glUseProgram(render_data.getShader("ring")->getProgramID());

//         //lock VAO
//         glBindVertexArray(m_vaoID);

//             render_data.getShader("ring")->setMat4("view", render_data.getViewMat());
//             render_data.getShader("ring")->setMat4("projection", render_data.getProjectionMat());
//             render_data.getShader("ring")->setMat4("model", m_model_mat);

//             render_data.getShader("ring")->setVec3("viewPos", render_data.getCamPos());
//             render_data.getShader("ring")->setVec3("sunPos", render_data.getSunPos());
//             render_data.getShader("ring")->setInt("hdr", render_data.getHDR());

//             render_data.getShader("ring")->setTexture("texture0", 0);

//             if(m_normal_surf != nullptr)
//             {
//                 heighhtScale += 0.000001f;
//                 if(heighhtScale >= 0.01f)
//                 {
//                     heighhtScale = 0.000001f;
//                 }

//                 render_data.getShader("ring")->setTexture("normalMap", 1);
//                 render_data.getShader("ring")->setInt("has_normal", render_data.getShadowGround());

//                 render_data.getShader("ring")->setTexture("depthMap", 2);
//                 render_data.getShader("ring")->setFloat("heightScale", heighhtScale);

//                 glActiveTexture(GL_TEXTURE2);
//                 glBindTexture(GL_TEXTURE_2D, m_disp_surf->getID());
//                 render_data.getShader("ring")->setInt("has_disp", render_data.getDispMapRender());

//                 glActiveTexture(GL_TEXTURE1);
//                 glBindTexture(GL_TEXTURE_2D, m_normal_surf->getID());
//             }
//             else
//             {
//                 render_data.getShader("ring")->setInt("has_normal", false);
//                 render_data.getShader("ring")->setInt("has_disp", false);
//             }

//             glActiveTexture(GL_TEXTURE0);
//             glBindTexture(GL_TEXTURE_2D, m_texture.getID());

//             //display the form
//             glDrawArrays(GL_TRIANGLES, 0, 6);

//             glActiveTexture(GL_TEXTURE2);
//             glBindTexture(GL_TEXTURE_2D, 0);

//             //unlock texture
//             glActiveTexture(GL_TEXTURE1);
//             glBindTexture(GL_TEXTURE_2D, 0);

//             glActiveTexture(GL_TEXTURE0);
//             glBindTexture(GL_TEXTURE_2D, 0);

//         //unlock VAO
//         glBindVertexArray(0);

//         glUseProgram(0);
//     }
    
// }

// //NOT CONCERN 
// // void Ring::displayInfo(glm::mat4 &projection, glm::mat4 &view, bool hdr)
// // {
    
// // }