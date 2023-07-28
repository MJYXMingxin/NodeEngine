# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\NodeEngine_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\NodeEngine_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\nativelib_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\nativelib_autogen.dir\\ParseCache.txt"
  "NodeEngine_autogen"
  "nativelib_autogen"
  )
endif()
