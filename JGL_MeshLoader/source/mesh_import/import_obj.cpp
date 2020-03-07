#include "pch.h"
#include "import_obj.h"

namespace nmesh_import
{
  bool ObjMeshImporter::from_file(const std::string& filepath, nelems::Mesh* pMesh)
  {
    std::ifstream in(filepath, std::ios::in);
    if (!in)
    {
      return false;
    }

    std::vector<glm::vec3> t_vert;

    std::string line;
    while (std::getline(in, line))
    {
      if (line.substr(0, 2) == "v ")
      {
        // read vertices
        std::istringstream s(line.substr(2));
        glm::vec3 v; s >> v.x; s >> v.y; s >> v.z;

        // Add to temporary vertices before indexing
        t_vert.push_back(v);
      }
      else if (line.substr(0, 2) == "f ")
      {
        // TODO: Store UVs and Normals
        unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
        int count_found = sscanf_s(line.substr(2).c_str(), 
          "%d/%d/%d %d/%d/%d %d/%d/%d\n", 
          &vertexIndex[0], &uvIndex[0], &normalIndex[0], 
          &vertexIndex[1], &uvIndex[1], &normalIndex[1], 
          &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

        if (count_found != 9) {
          return false;
        }

        pMesh->add_vertex_index(vertexIndex[0]-1);
        pMesh->add_vertex_index(vertexIndex[1]-1);
        pMesh->add_vertex_index(vertexIndex[2]-1);

      }
    }

    // Now use the indices to create the concrete vertices for the mesh
    for (auto v_idx : pMesh->GetVertexIndices())
    {
      glm::vec3 vertex = t_vert[v_idx];
      pMesh->add_vertex(vertex);
    }
    return true;
  }
}