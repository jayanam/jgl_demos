#pragma once

namespace nelems
{
  class VertexHolder
  {

  public:
    VertexHolder() : mPos(), mNormal() {}
    
    // Initialize by string to be tokenized
    // TODO: Better handle outside of this class
    VertexHolder(const std::vector<std::string> tokens)
    {
    }

    VertexHolder(const glm::vec3& pos, const glm::vec3& normal)
      : mPos(pos), mNormal(normal)
    {
    }

    ~VertexHolder() = default;


    glm::vec3 mPos;

    glm::vec3 mNormal;

    // TODO
    // glm::vec2 mUV;


  };
}

