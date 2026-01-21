# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "Blockchain_autogen"
  "CMakeFiles/Blockchain_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/Blockchain_autogen.dir/ParseCache.txt"
  )
endif()
