#include "square.hpp"
topit::Square::Square(p_t pos,int width):
  pos_(pos),
  width_(width)
{}
topit::p_t topit::Square::begin() const {
  return pos_;
}
topit::p_t topit::Square::next(p_t prev) const {

  if (prev.x==pos_.x && prev.y>pos_.y) {
    return {prev.x,prev.y-1};
  } else if (prev.x==pos_.x+width_-1 && prev.y<pos_.y+width_-1) {
    return {prev.x,prev.y+1};
  } else if (prev.y==pos_.y+width_-1 && prev.x>pos_.x) {
    return {prev.x-1,prev.y};
  } else if (prev.y==pos_.y && prev.x<pos_.x+width_-1) {
    return {prev.x+1,prev.y};
  }
  return pos_;
}
