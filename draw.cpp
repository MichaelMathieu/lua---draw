extern "C" {
#include <TH.h>
#include <luaT.h>
}

#include "genericpp/draw.cpp"

#define torch_(NAME) TH_CONCAT_3(torch_, Real, NAME)
#define torch_string_(NAME) TH_CONCAT_STRING_3(torch., Real, NAME)
#define libdraw_(NAME) TH_CONCAT_3(libdraw_, Real, NAME)

static const void* torch_FloatTensor_id = NULL;
static const void* torch_DoubleTensor_id = NULL;

#include "generic/draw.cpp"
#include "THGenerateFloatTypes.h"

LUA_EXTERNC DLL_EXPORT int luaopen_libdraw(lua_State *L)
{
  torch_FloatTensor_id = luaT_checktypename2id(L, "torch.FloatTensor");
  torch_DoubleTensor_id = luaT_checktypename2id(L, "torch.DoubleTensor");

  libdraw_FloatMain_init(L);
  libdraw_DoubleMain_init(L);

  return 1;
}
