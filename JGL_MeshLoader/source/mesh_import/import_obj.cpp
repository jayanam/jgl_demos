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

    std::string s_line;
    while (std::getline(in, s_line))
    {
      std::istringstream ss_line(s_line);
      std::string id;
      ss_line >> id;


      if (id == "v")
      {
        // read vertices
        glm::vec3 v;

        ss_line >> v.x >> v.y >> v.z;

        // Add to temporary vertices before indexing
        t_vert.push_back(v);
      }

      // Faces
      else if (id == "f")
      {
        // TODO: Add quads, now we just have tris, create a class to hold
        // vertex, normal and UV
        std::string v1, v2, v3;

        uint32_t vertexIndex[3];
        uint32_t normIdx[3];
        uint32_t uvIdx[3];

        int count_found = sscanf_s(s_line.substr(2).c_str(), 
          "%d/%d/%d %d/%d/%d %d/%d/%d\n", 
          &vertexIndex[0], &uvIdx[0], &normIdx[0],
          &vertexIndex[1], &uvIdx[1], &normIdx[1],
          &vertexIndex[2], &uvIdx[2], &normIdx[2]);

        if (count_found % 3 == 0) {
          pMesh->add_vertex_index(vertexIndex[0] - 1);
          pMesh->add_vertex_index(vertexIndex[1] - 1);
          pMesh->add_vertex_index(vertexIndex[2] - 1);
        }
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