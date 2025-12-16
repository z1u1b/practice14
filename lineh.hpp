#ifndef LINEH_H
#define LINEH_H
#include "idraw.hpp"
namespace topit {
  struct LineH:IDraw
  {
    LineH(p_t pos,int width);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t pos_;
    int width_;
  };
}
#endif 
