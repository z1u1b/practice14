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
    virtual ~IDraw() = default;
  };
  bool operator==(p_t a, p_t b)
  {
    return a.x == b.x && a.y == b.y;
  }
  bool operator!=(p_t a, p_t b)
  {
    return !(a == b);
  }

  struct Dot:IDraw
  {
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t o;
    Dot(int x,int y);
  };
  struct frame_f {
    p_t left_dot;
    p_t right_dot;
  };
  void make_f(IDraw ** b,s_t k);
  void get_points(IDraw * b,p_t **ps,s_t &s);
  frame_f build_frame(const p_t * ps, s_t s);
  char * build_canvas(frame_f f);
  void paint_canvas(char * cnv,frame_f fr,const p_t * ps,s_t k,char f);
  void print_canvas(const char * cnv,frame_f fr);
} // namespace top

int main()
{
  using namespace top;
  int err=0;
  IDraw * f[3]={};
  p_t *p = nullptr;
  s_t s=0;
  char * cnv=nullptr;
  try {
    make_f(f,3);
    for (s_t i=0;i<3;++i) {
      get_points(f[i],&p,s);
    }
    frame_f fr = build_frame(p,s);

    cnv=build_canvas(fr);
    paint_canvas(cnv,fr,p,s,'#');
    print_canvas(cnv,fr);
  } catch (...) {
    err=1;
  }
  // for (s_t i=0;i<3;++i){
  //   delete f[i];
  // }
  delete f[0];
  delete f[1];
  delete f[2];
  delete [] p;
  delete [] cnv;
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
