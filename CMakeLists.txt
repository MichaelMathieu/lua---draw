CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)
CMAKE_POLICY(VERSION 2.6)
FIND_PACKAGE(Torch REQUIRED)

SET(src THpp.cpp draw.cpp)
SET(luasrc init.lua)

ADD_TORCH_PACKAGE(draw "${src}" "${luasrc}" "Drawing primitives")
TARGET_LINK_LIBRARIES(draw luaT TH)
