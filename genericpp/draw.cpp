#include "THpp.hpp"

template<typename THreal>
static int DrawLine(lua_State *L) {
  setLuaState(L);
  THTensor<THreal> im = FromLuaStack<THTensor<THreal> >(L, 1);
  int x1   = FromLuaStack<int>(L, 2);
  int y1   = FromLuaStack<int>(L, 3);
  int x2   = FromLuaStack<int>(L, 4);
  int y2   = FromLuaStack<int>(L, 5);
  THreal r = FromLuaStack<THreal>(L, 6);
  THreal g = FromLuaStack<THreal>(L, 7);
  THreal b = FromLuaStack<THreal>(L, 8);
  
  THassert((im.nDimension() == 3) && (im.size(0) == 3));
  THassert((x1 >= 0) && (y1 >= 0) && (x2 >= 0) && (y2 >= 0));
  THassert((x1 < im.size(2)) && (y1 < im.size(1)));
  THassert((x2 < im.size(2)) && (y2 < im.size(1)));

  int dx = abs(x2-x1);
  int dy = abs(y2-y1);
  int x, y;
  float k;
  if (dy <= dx) {
    if (dx != 0) {
      if (x2 < x1) {
	int t = x1; x1 = x2; x2 = t;
	t = y1; y1 = y2; y2 = t;
      }
      k = ((float)(y2-y1))/dx;
      for (x = 0; x <= dx; ++x) {
	y = round(k*x);
	im(0, y1+y, x1+x) = r;
	im(1, y1+y, x1+x) = g;
	im(2, y1+y, x1+x) = b;
      }
    }
  } else {
    if (y2 < y1) {
      int t = x1; x1 = x2; x2 = t;
      t = y1; y1 = y2; y2 = t;
    }
    k = ((float)(x2-x1))/dy;
    for (y = 0; y <= dy; ++y) {
      x = round(k*y);
      im(0, y1+y, x1+x) = r;
      im(1, y1+y, x1+x) = g;
      im(2, y1+y, x1+x) = b;
    }
  }
  
  return 0;
}
