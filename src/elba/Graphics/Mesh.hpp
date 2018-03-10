#include <glm/mat4x4.hpp>
#include "Utilities/StdTypedefs.hpp"

#include "Graphics/GraphicsForwardDeclarations.hpp"

namespace Elba
{
  class Mesh
  {
  public:
    Mesh();

    void Draw(const glm::mat4& proj, const glm::mat4& view, const glm::mat4& model);

    void SetShader(const char* shaderName);

  private:
    std::vector<UniquePtr<Submesh>> mSubmeshes;
  };
}