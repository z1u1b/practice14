#include "lineh.hpp"
topit::LineH::LineH(p_t pos, int width):
  pos_(pos),
  width_(width)
{}
topit::p_t topit::LineH::begin() const
{
  return pos_;
}
topit::p_t topit::LineH::next(p_t prev) const
{
  if (prev.x==pos_.x+width_-1 && prev.y==pos_.y) {
    return pos_;
  }
  return {prev.x+1,prev.y};
}
