#include <iostream>
using s_t = size_t;

namespace top
{
  struct p_t
  {
    int x, y;
  };

  struct IDraw
  {
    virtual p_t begin() = 0;
    virtual p_t next(p_t) = 0;
  };
  bool operator==(p_t a, p_t b)
  {
    return a.x == b.x && a.y == b.y;
  }
  bool operator!=(p_t a, p_t b)
  {
    return !(a == b);
  }
  s_t count(IDraw& d)
  {}
} // namespace top

int main()
{
  using namespace top;
  size_t result = 0;
  std::cout << result << '\n';
  return 0;
}
