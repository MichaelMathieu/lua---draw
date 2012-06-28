#include "THpp.hpp"

inline bool epseq(float a, float b, float eps = 0.05f) {
  return ((a-eps < b) && (b < a+eps));
}

inline bool checkBordersLow(float & a1, float & b1, float a2, float b2) {
  if (a1 < 0.0f) {
    if (epseq(a1, a2))
      return false;
    float lambda = a1 / (a1-a2);
    a1 = 0.0f;
    b1 = b1 + lambda * (b2-b1);
  }
  return true;
}
inline bool checkBordersHigh(float & a1, float & b1, float a2, float b2, float c) {
  if (a1 > c) {
    if (epseq(a1, a2))
      return false;
    float lambda = (c-a1) / (a2-a1);
    a1 = c;
    b1 = b1 + lambda * (b2-b1);
  }
  return true;
}
template<typename THreal>
static int DrawLine(lua_State *L) {
  setLuaState(L);
  THTensor<THreal> im = FromLuaStack<THTensor<THreal> >(L, 1);
  float x1   = FromLuaStack<float>(L, 2);
  float y1   = FromLuaStack<float>(L, 3);
  float x2   = FromLuaStack<float>(L, 4);
  float y2   = FromLuaStack<float>(L, 5);
  THreal r = FromLuaStack<THreal>(L, 6);
  THreal g = FromLuaStack<THreal>(L, 7);
  THreal b = FromLuaStack<THreal>(L, 8);
  
  THassert((im.nDimension() == 3) && (im.size(0) == 3));
  
  float w = im.size(2), h = im.size(1);
  if ((!checkBordersLow(x1, y1, x2, y2)) || (!checkBordersLow(y1, x1, y2, x2)) ||
      (!checkBordersLow(x2, y2, x1, y1)) || (!checkBordersLow(y2, x2, y1, x1)))
    return 0;
  if ((!checkBordersHigh(x1, y1, x2, y2, w-1)) || (!checkBordersHigh(y1, x1, y2, x2, h-1)) ||
      (!checkBordersHigh(x2, y2, x1, y1, w-1)) || (!checkBordersHigh(y2, x2, y1, x1, h-1)))
    return 0;
  if (epseq(x1, x2) && epseq(y1, y2))
    return 0;
  
  THassert((x1 >= 0) && (y1 >= 0) && (x2 >= 0) && (y2 >= 0));
  THassert((x1 < w) && (y1 < h) && (x2 < w) && (y2 < h));

  float dx = abs(x2-x1);
  float dy = abs(y2-y1);
  float x, y, k, t;
  int xi, yi;
  if (dy <= dx) {
    if (dx != 0) {
      if (x2 < x1) {
	t = x1; x1 = x2; x2 = t;
	t = y1; y1 = y2; y2 = t;
      }
      k = (y2-y1)/dx;
      for (x = 0; x <= dx; ++x) {
	y = k*x;
	yi = round(y1+y);
	xi = round(x1+x);
	im(0, yi, xi) = r;
	im(1, yi, xi) = g;
	im(2, yi, xi) = b;
      }
    }
  } else {
    if (y2 < y1) {
      t = x1; x1 = x2; x2 = t;
      t = y1; y1 = y2; y2 = t;
    }
    k = (x2-x1)/dy;
    for (y = 0; y <= dy; ++y) {
      x = k*y;
      yi = round(y1+y);
      xi = round(x1+x);
      im(0, yi, xi) = r;
      im(1, yi, xi) = g;
      im(2, yi, xi) = b;
    }
  }
  
  return 0;
}
