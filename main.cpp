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
    virtual p_t begin() const = 0;
    virtual p_t next(p_t) const = 0;
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

  struct Dot:IDraw
  {
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t o;
    Dot(int x,int y);
  };

} // namespace top

int main()
{
  using namespace top;
  size_t result = 0;
  std::cout << result << '\n';
  return 0;
}
top::Dot::Dot(int x,int y):
  IDraw(),
  o{x,y}
{}
top::p_t top::Dot::begin() const {
  return o;
}
top::p_t top::Dot::next(p_t) const {
  return begin();
}
