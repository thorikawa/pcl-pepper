cmake_minimum_required(VERSION 2.6.4 FATAL_ERROR)
# Give a name to the project.
project(pclsample)
# This include enable you to use qibuild framework

find_package(qibuild)

set(_srcs
  Viewer.cpp
  Viewer.h
  openni_test.cpp  
)

# Create an executable named sayhelloworld,
# with the source file : main.cpp
qi_create_bin(pclsample ${_srcs})

# Tell CMake that sayhelloworld depends on ALCOMMON and ALPROXIES
# This will set the libraries to link sayhelloworld with,
# the include paths, and so on
qi_use_lib(pclsample openni2 ALCOMMON ALPROXIES)
