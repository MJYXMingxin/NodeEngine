# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Logic_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Logic_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\NodeEngine_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\NodeEngine_autogen.dir\\ParseCache.txt"
  "Logic_autogen"
  "NodeEngine_autogen"
  )
endif()
