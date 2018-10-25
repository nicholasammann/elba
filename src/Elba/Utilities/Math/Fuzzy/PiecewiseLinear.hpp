#include <vector>

#include <glm/vec2.hpp>

namespace Elba
{
class PiecewiseLinear
{
public:
  PiecewiseLinear();

  float ValueAt(float x) const;

  void AddPoint(glm::vec2 point);
  void ClearPoints();

  unsigned int GetNumPoints() const;

private:
  std::vector<glm::vec2> mPoints;
};

} // End of Elba namespace
