#ifndef LINEV_H
#define LINEV_H
#include "idraw.hpp"
namespace topit {
  struct LineV:IDraw
  {
    LineV(p_t pos,int width);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t pos_;
    int width_;
  };
}


#endif
