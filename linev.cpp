#include "linev.hpp"
topit::LineV::LineV(p_t pos, int width):
  pos_(pos),
  width_(width)
{}
topit::p_t topit::LineV::begin() const
{
  return pos_;
}
topit::p_t topit::LineV::next(p_t prev) const
{
  if (prev.x==pos_.x && prev.y==pos_.y+width_-1) {
    return pos_;
  }
  return {prev.x,prev.y+1};
}
