#include <iostream>
#include "ascii_draw.hpp"

int main()
{
  using topit::Dot;
  using topit::LineH;
  using topit::LineV;
  using topit::Diagonal;
  using topit::Square;
  using topit::Rectangle;
  using topit::f_t;
  using topit::IDraw;
  using topit::p_t;
  int err = 0;
  const size_t size_arr=5;
  IDraw* shps[size_arr] = {};
  p_t* pts = nullptr;
  size_t s = 0;
  try {

    shps[0] = new Dot(0, 0);
    shps[1] = new Dot(5, 7);
    shps[2] = new Dot(-5, -2);
    // shps[3] = new Square({0,0},3);
    shps[3] = new Rectangle({-3,5},4,2);
    shps[4] = new Diagonal({2,2},3);
    for (size_t i = 0; i < size_arr; ++i) {
      s += topit::points(*(shps[i]), &pts, s);
    }
    f_t fr = frame(pts, s);
    char* cnv = topit::canvas(fr, '.');
    for (size_t i = 0; i < s; ++i) {
      topit::paint(cnv, fr, pts[i], '#');
    }
    topit::flush(std::cout, cnv, fr);
    delete[] cnv;
  } catch (...) {
    err = 2;
    std::cerr << "Bad drawing\n";
  }
  delete[] pts;
  delete shps[0];

  return err;
}







