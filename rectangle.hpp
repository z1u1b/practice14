#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "idraw.hpp"
namespace topit {
  struct Rectangle:IDraw
  {
    Rectangle(p_t pos,int width,int height);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t pos_;
    int width_;
    int height_;
  };
}
#endif
