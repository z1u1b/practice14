
#ifndef CANVAS_H
#define CANVAS_H
#include <iosfwd>
#include "geom.hpp"

namespace topit {
  // построить полотно (из фрейма получить количество столбцов и колонок)
  char* canvas(f_t fr, char fill);

  // координаты точки перевести в координаты в двумерном массиве
  void paint(char* cnv, f_t fr, p_t p, char fill);

  // вывод двумперного массива на основе размеров, определяемых фреймом
  void flush(std::ostream& os, const char* cnv, f_t fr);
}
#endif
