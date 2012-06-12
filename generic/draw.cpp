#ifndef TH_GENERIC_FILE
#define TH_GENERIC_FILE "generic/draw.cpp"
#else

//======================================================================
// File: draw
//
// Description: Drawing primitives
//
// Created: June 11th, 2012
//
// Author: Michael Mathieu // michael.f.mathieu@gmail.com
//======================================================================
extern "C" {
#include <luaT.h>
#include <TH.h>
}

//============================================================
// Register functions in LUA
//
static const luaL_reg libdraw_(Main__) [] = 
{
  {"drawLine", DrawLine<real>},
  {NULL, NULL}  /* sentinel */
};

LUA_EXTERNC DLL_EXPORT int libdraw_(Main_init) (lua_State *L) {
  luaT_pushmetaclass(L, torch_(Tensor_id));
  luaT_registeratname(L, libdraw_(Main__), "libdraw");
  return 1;
}

#endif
