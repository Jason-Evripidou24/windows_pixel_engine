// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "object.hpp"
#include "../math/mat4/mat4_f.hpp"
#include "../math/math.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Mat4_f Object::calcModelMatrix() const
{
    Mat4_f translate = Math::translationMat4_f(m_position.m_data[0], m_position.m_data[1], m_position.m_data[2]);
    Mat4_f scale = Math::scaleMat4_f(m_scale.m_data[0], m_scale.m_data[1], m_scale.m_data[2]);
    Mat4_f rotate = Math::rotationMat4_f(m_rotation.m_data[0], m_rotation.m_data[1], m_rotation.m_data[2], m_rotation_theta_radians);
    Mat4_f model = Math::multiply(Math::multiply(translate, scale), rotate);
    return model;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Object Object::createCube()
{
    Object cube_object;
    
    cube_object.m_vertex_count = 8;
    cube_object.m_index_count = 36;

    cube_object.m_vertices = std::vector<Vec4_f>(cube_object.m_vertex_count);
    cube_object.m_clip     = std::vector<Vec4_f>(cube_object.m_vertex_count);
    cube_object.m_ndc      = std::vector<Vec3_f>(cube_object.m_vertex_count);
    cube_object.m_screen   = std::vector<Vec3_f>(cube_object.m_vertex_count);

    cube_object.m_indices = std::vector<int>(cube_object.m_index_count);

    cube_object.m_vertices[0] = {-0.5f,-0.5f,-0.5f,1.0f};
    cube_object.m_vertices[1] = { 0.5f,-0.5f,-0.5f,1.0f};
    cube_object.m_vertices[2] = { 0.5f, 0.5f,-0.5f,1.0f};
    cube_object.m_vertices[3] = {-0.5f, 0.5f,-0.5f,1.0f};

    cube_object.m_vertices[4] = {-0.5f,-0.5f, 0.5f,1.0f};
    cube_object.m_vertices[5] = { 0.5f,-0.5f, 0.5f,1.0f};
    cube_object.m_vertices[6] = { 0.5f, 0.5f, 0.5f,1.0f};
    cube_object.m_vertices[7] = {-0.5f, 0.5f, 0.5f,1.0f};

    int idx[] =
    {
        0,1,2, 2,3,0,
        4,5,6, 6,7,4,
        0,3,7, 7,4,0,
        1,5,6, 6,2,1,
        0,1,5, 5,4,0,
        3,2,6, 6,7,3
    };
    for(int i = 0; i < cube_object.m_index_count; i++)
    {
        cube_object.m_indices[i] = idx[i];
    }

    cube_object.m_position = {0.0f, 0.0f, -2.0f};
    cube_object.m_rotation = {0.0f, 0.0f, 1.0f};
    cube_object.m_rotation_theta_radians = 0.0f;
    cube_object.m_scale = {1.0f, 1.0f, 1.0f};

    return cube_object;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //