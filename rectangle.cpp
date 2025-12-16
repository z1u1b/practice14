#include "rectangle.hpp"
topit::Rectangle::Rectangle(p_t pos,int width,int height):
  pos_(pos),
  width_(width),
  height_(height)
{}
topit::p_t topit::Rectangle::begin() const {
  return pos_;
}
topit::p_t topit::Rectangle::next(p_t prev) const {

  if (prev.x==pos_.x && prev.y>pos_.y) {
    return {prev.x,prev.y-1};
  } else if (prev.x==pos_.x+width_-1 && prev.y<pos_.y+height_-1) {
    return {prev.x,prev.y+1};
  } else if (prev.y==pos_.y+height_-1 && prev.x>pos_.x) {
    return {prev.x-1,prev.y};
  } else if (prev.y==pos_.y && prev.x<pos_.x+width_-1) {
    return {prev.x+1,prev.y};
  }
  return pos_;
}
