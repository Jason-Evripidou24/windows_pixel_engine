// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#ifndef MODEL_HPP
#define MODEL_HPP
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
//-------------------------------------------------------------------------------------------------------------------------//
// Standard library.
//-------------------------------------------------------------------------------------------------------------------------//
#include <memory>
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Third party.
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------------------------------------//
// Internal.
//-------------------------------------------------------------------------------------------------------------------------//
#include "mesh/mesh.hpp"

#include "../math/core/math_core.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
struct Model
{
    //---------------------------------------------------------------------------------------------------------------------//
    int m_model_id;
    std::string m_model_name;

    std::shared_ptr<Mesh> m_mesh;

    Math::Core::Vec3_f m_position;
    Math::Core::Vec3_f m_scale;
    Math::Core::Quaternion m_rotation;
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    Model()
    {
        m_mesh     = nullptr;
        m_rotation = Math::Core::Quaternion();
        m_position = Math::Core::Vec3_f();
        m_scale    = Math::Core::Vec3_f(1.0f, 1.0f, 1.0f);
    }

    Model
    (
        int                    model_id,
        const std::string&     model_name,
        std::shared_ptr<Mesh>  mesh
    )
    {
        m_model_id   = model_id;
        m_model_name = model_name;
        m_mesh       = mesh;
        m_position   = Math::Core::Vec3_f();
        m_rotation   = Math::Core::Quaternion();
        m_scale      = Math::Core::Vec3_f(1.0f, 1.0f, 1.0f);
    }

    Model
    (
        int                    model_id,
        const std::string&     model_name,
        std::shared_ptr<Mesh>  mesh,
        Math::Core::Vec3_f     position,
        Math::Core::Quaternion rotation,
        Math::Core::Vec3_f     scale
    )
    {
        m_model_id   = model_id;
        m_model_name = model_name;
        m_mesh       = mesh;
        m_position   = position;
        m_rotation   = rotation;
        m_scale      = scale;
    }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    //---------------------------------------------------------------------------------------------------------------------//
    inline void moveX(const float offset)
    {
        m_position = m_position + (Math::Core::Vec3_f(1.0f, 0.0f, 0.0f) * offset);
    }
    inline void moveY(const float offset)
    {
        m_position = m_position + (Math::Core::Vec3_f(0.0f, 1.0f, 0.0f) * offset);
    }
    inline void moveZ(const float offset)
    {
        m_position = m_position + (Math::Core::Vec3_f(0.0f, 0.0f, 1.0f) * offset);
    }

    inline void rotateX(const float offset_rads)
    {
        Math::Core::Quaternion delta = Math::Core::Quaternion::fromAxisAngle(1.0f, 0.0f, 0.0f, offset_rads);
        m_rotation = m_rotation * delta;
    }
    inline void rotateY(const float offset_rads)
    {
        Math::Core::Quaternion delta = Math::Core::Quaternion::fromAxisAngle(0.0f, 1.0f, 0.0f, offset_rads);
        m_rotation = m_rotation * delta;
    }
    inline void rotateZ(const float offset_rads)
    {
        Math::Core::Quaternion delta = Math::Core::Quaternion::fromAxisAngle(0.0f, 0.0f, 1.0f, offset_rads);
        m_rotation = m_rotation * delta;
    }

    inline void scaleX(const float offset)
    {
        m_scale = m_scale + (Math::Core::Vec3_f(1.0f, 0.0f, 0.0f) * offset);
        if(m_scale.m_data[0] < 0.1f) { m_scale.m_data[0] = 0.1f; }
    }
    inline void scaleY(const float offset)
    {
        m_scale = m_scale + (Math::Core::Vec3_f(0.0f, 1.0f, 0.0f) * offset);
        if(m_scale.m_data[1] < 0.1f) { m_scale.m_data[1] = 0.1f; }
    }
    inline void scaleZ(const float offset)
    {
        m_scale = m_scale + (Math::Core::Vec3_f(0.0f, 0.0f, 1.0f) * offset);
        if(m_scale.m_data[2] < 0.1f) { m_scale.m_data[2] = 0.1f; }
    }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    Math::Core::Mat4_f calcModelMatrix() const
    {
        Math::Core::Mat4_f translate;
        translate.translation
        (
            m_position.m_data[0],
            m_position.m_data[1],
            m_position.m_data[2]
        );

        Math::Core::Mat4_f rotate = m_rotation.toRotationMatrix();

        Math::Core::Mat4_f scale;
        scale.scale
        (
            m_scale.m_data[0],
            m_scale.m_data[1],
            m_scale.m_data[2]
        );
        
        return translate * rotate * scale;
    }
    //---------------------------------------------------------------------------------------------------------------------//

    //---------------------------------------------------------------------------------------------------------------------//
    inline std::string toString() const
    {
        std::string output = std::string("");
        output += std::string("MODEL ID  : ") + std::to_string(m_model_id) + std::string("\n");
        output += std::string("MODEL NAME: ") + m_model_name + std::string("\n");
        
        if(m_mesh == nullptr)
        {
            output += std::string("MODEL HAS NO MESH!");
        }
        else
        {
            output += std::string("MODEL MESH DETAILS:") + std::string("\n") + m_mesh->toString();
        }

        return output;
    }
    //---------------------------------------------------------------------------------------------------------------------//
};
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
#endif
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //