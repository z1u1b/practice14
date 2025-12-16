#include "diagonal.hpp"
topit::Diagonal::Diagonal(p_t pos, int width):
  pos_(pos),
  width_(width)
{}
topit::p_t topit::Diagonal::begin() const
{
  return pos_;
}
topit::p_t topit::Diagonal::next(p_t prev) const
{
  if (prev.x==pos_.x+width_-1 && prev.y==pos_.y+width_-1) {
    return pos_;
  }
  return {prev.x+1,prev.y+1};
}

