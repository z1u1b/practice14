#include <iostream>
namespace topit
{
  struct p_t
  {
    int x, y;
  };
  bool operator==(p_t, p_t);
  bool operator!=(p_t, p_t);
  struct f_t
  {
    p_t aa, bb;
  };

  struct IDraw
  {
    virtual ~IDraw() = default;
    virtual p_t begin() const = 0;
    virtual p_t next(p_t) const = 0;
  };

  struct Dot:IDraw
  {
    Dot(int x, int y);
    explicit Dot(p_t dd);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t d;
  };
  struct LineH:IDraw
  {
    LineH(p_t pos,int width);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t pos_;
    int width_;
  };
  struct LineV:IDraw
  {
    LineV(p_t pos,int width);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t pos_;
    int width_;
  };
  struct Diagonale:IDraw
  {
    Diagonale(p_t pos,int width);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t pos_;
    int width_;
  };
  struct Square:IDraw
  {
    Square(p_t pos,int width);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t pos_;
    int width_;
  };
  struct Rectangle:IDraw
  {
    Rectangle(p_t pos,int width,int height);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t pos_;
    int width_;
    int height_;
  };
  // Домашнее задание:
  // - Добавить ещё 2-3 фигуры:
  //   - Вертикальный отрезок
  //   - Горизонтальный отрезок
  //   - Диагональ под 45 заданной длины
  //   - Придумать свою фигуру

  // расширять заданный массив точками из очередной фигуры
  // - extend...
  size_t points(const IDraw& d, p_t** pts, size_t s);

  // найти минимум и максимум по каждой координате среди точек и сформировать фрейм
  f_t frame(const p_t* pts, size_t s);

  // построить полотно (из фрейма получить количество столбцов и колонок)
  char* canvas(f_t fr, char fill);

  // координаты точки перевести в координаты в двумерном массиве
  void paint(char* cnv, f_t fr, p_t p, char fill);

  // вывод двумперного массива на основе размеров, определяемых фреймом
  void flush(std::ostream& os, const char* cnv, f_t fr);

  void extend(topit::p_t** pts, size_t s, p_t p);
  size_t rows(f_t fr);
  size_t cols(f_t fr);
} // namespace topit
int main()
{
  using topit::Dot;
  using topit::LineH;
  using topit::LineV;
  using topit::Diagonale;
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
    shps[4] = new Diagonale({2,2},3);
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


size_t topit::points(const IDraw& d, p_t** pts, size_t s)
{
  p_t p = d.begin();
  extend(pts, s, p);
  size_t delta = 1;
  while (d.next(p) != d.begin()) {
    p = d.next(p);
    extend(pts, s + delta, p);
    ++delta;
  }
  return delta;
}

topit::f_t topit::frame(const p_t* pts, size_t s)
{
  if (!s) {
    throw std::logic_error("bad size");
  }
  int minx = pts[0].x, maxx = minx;
  int miny = pts[0].y, maxy = miny;
  for (size_t i = 1; i < s; ++i) {
    minx = std::min(minx, pts[i].x);
    maxx = std::max(maxx, pts[i].x);
    miny = std::min(miny, pts[i].y);
    maxy = std::max(maxy, pts[i].y);
  }
  p_t aa{minx, miny};
  p_t bb{maxx, maxy};
  return {aa, bb};
}
size_t topit::rows(topit::f_t fr)
{
  return (fr.bb.y - fr.aa.y + 1);
}
size_t topit::cols(topit::f_t fr)
{
  return (fr.bb.x - fr.aa.x + 1);
}
char* topit::canvas(topit::f_t fr, char fill)
{
  char* cnv = new char[rows(fr) * cols(fr)];
  for (size_t i = 0; i < rows(fr) * cols(fr); ++i) {
    cnv[i] = fill;
  }
  return cnv;
}

void topit::paint(char* cnv, topit::f_t fr, topit::p_t p, char fill)
{
  int dx = p.x - fr.aa.x;
  int dy = fr.bb.y - p.y;
  cnv[dy * cols(fr) + dx] = fill;
}

void topit::flush(std::ostream& os, const char* cnv, topit::f_t fr)
{
  for (size_t i = 0; i < rows(fr); ++i) {
    for (size_t j = 0; j < cols(fr); ++j) {
      os << cnv[i * cols(fr) + j];
    }
    os << '\n';
  }
}
void topit::extend(topit::p_t** pts, size_t s, p_t p)
{
    size_t upd_s = s + 1;
    p_t* res = new p_t[upd_s];
    for (size_t i = 0; i < s; ++i) {
      res[i] = (*pts)[i];
    }

    res[s] = p;
    delete[] *pts;
    *pts = res;
  }

topit::Dot::Dot(p_t dd) : IDraw(), d{dd}
{}

topit::Dot::Dot(int x, int y) : IDraw(), d{x, y}
{}

topit::p_t topit::Dot::begin() const
{
  return d;
}

topit::p_t topit::Dot::next(p_t prev) const
{
  if (prev != begin()) {
    throw std::logic_error("bad impl");
  }
  return d;
}
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
topit::Diagonale::Diagonale(p_t pos, int width):
  pos_(pos),
  width_(width)
{}
topit::p_t topit::Diagonale::begin() const
{
  return pos_;
}
topit::p_t topit::Diagonale::next(p_t prev) const
{
  if (prev.x==pos_.x+width_-1 && prev.y==pos_.y+width_-1) {
    return pos_;
  }
  return {prev.x+1,prev.y+1};
}
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
bool topit::operator==(p_t a, p_t b)
{
  return a.x == b.x && a.y == b.y;
}
bool topit::operator!=(p_t a, p_t b)
{
  return !(a == b);
}
