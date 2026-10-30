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
#include "../mtl_file_parser.hpp"
//-------------------------------------------------------------------------------------------------------------------------//
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
std::string MtlFileParser::parseName(std::stringstream& line_string_stream)
{
    std::string name;

    if( !(line_string_stream >> name) ) { return std::string(""); }

    return name;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
Math::Core::Vec3_f MtlFileParser::parseColor(std::stringstream& line_string_stream)
{
    float r;
    float g;
    float b;

    // Invalid normal direction.
    if( !(line_string_stream >> r >> g >> b) ) { return Math::Core::Vec3_f(0.0f, 0.0f, 0.0f); }

    return Math::Core::Vec3_f(r, g, b);
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //


// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //
MaterialLibrary MtlFileParser::loadMaterialLibrary(const std::string& file_folder, const std::string& filename)
{
    MaterialLibrary material_library;

    //---------------------------------------------------------------------------------------------------------------------//
    std::ifstream file(file_folder + filename);
    if(!file.is_open()) { return material_library; }
    //---------------------------------------------------------------------------------------------------------------------//

    std::shared_ptr<Material> curr_material = nullptr;
    size_t curr_material_name_hash = 0;

    std::string line;
    while(std::getline(file, line))
    {
        std::stringstream ss(line);

        std::string prefix;
        ss >> prefix;

        //-----------------------------------------------------------------------------------------------------------------//
        // Comment.
        //-----------------------------------------------------------------------------------------------------------------//
        if(prefix == "#") { continue; }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // New material.
        //-----------------------------------------------------------------------------------------------------------------//
        if(prefix == "newmtl")
        {
            if(curr_material != nullptr)
            {
                if( material_library.m_materials.find(curr_material_name_hash) == material_library.m_materials.end() )
                {
                    material_library.m_materials[curr_material_name_hash] = curr_material;
                }
            }

            curr_material = std::make_shared<Material>();
            std::string curr_material_name = parseName(ss);

            curr_material_name_hash = Math::Core::hashString(curr_material_name);
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Diffuse colour.
        //-----------------------------------------------------------------------------------------------------------------//
        else if(prefix == "Kd")
        {
            if(curr_material == nullptr) { continue; }
            
            curr_material->m_diffuse = parseColor(ss);
        }
        //-----------------------------------------------------------------------------------------------------------------//

        //-----------------------------------------------------------------------------------------------------------------//
        // Diffuse texture.
        //-----------------------------------------------------------------------------------------------------------------//
        else if( (prefix == "map_Kd") || (prefix == "map_kd") )
        {
            if(curr_material == nullptr) { continue; }

            const std::string diffuse_texture_name = parseName(ss);

            if( material_library.m_diffuse_textures.find(diffuse_texture_name) == material_library.m_diffuse_textures.end() )
            {
                std::shared_ptr<Texture> new_texture = std::make_shared<Texture>();
                new_texture->loadTextureJpgPngFile(file_folder, diffuse_texture_name);

                material_library.m_diffuse_textures[diffuse_texture_name] = new_texture;
            }

            if
            (
                (curr_material != nullptr) &&
                (material_library.m_diffuse_textures.find(diffuse_texture_name) != material_library.m_diffuse_textures.end())
            )
            {
                curr_material->m_diffuse_texture = material_library.m_diffuse_textures[diffuse_texture_name];
            }
        }
        //-----------------------------------------------------------------------------------------------------------------//
    }

    if(curr_material != nullptr)
    {
        if( material_library.m_materials.find(curr_material_name_hash) == material_library.m_materials.end() )
        {
            material_library.m_materials[curr_material_name_hash] = curr_material;
        }
    }

    return material_library;
}
// ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### //