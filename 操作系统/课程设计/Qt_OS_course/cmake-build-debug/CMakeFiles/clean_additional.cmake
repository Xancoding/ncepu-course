# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Qt_OS_course_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Qt_OS_course_autogen.dir\\ParseCache.txt"
  "Qt_OS_course_autogen"
  )
endif()
