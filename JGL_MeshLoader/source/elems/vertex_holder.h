#pragma once
namespace nelems
{
  class VertexHolder
  {

  public:
    VertexHolder() : mV(), mN(), mUV() {}
    VertexHolder(const std::vector<std::string> tokens)
    {

    }

    ~VertexHolder() = default;
  private:

    glm::vec3 mV;

    glm::vec3 mN;

    glm::vec3 mUV;


  };
}

