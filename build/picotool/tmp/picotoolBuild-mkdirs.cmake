# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/shreejal/Documents/Projects/enigma/build/_deps/picotool-src"
  "/home/shreejal/Documents/Projects/enigma/build/_deps/picotool-build"
  "/home/shreejal/Documents/Projects/enigma/build/_deps"
  "/home/shreejal/Documents/Projects/enigma/build/picotool/tmp"
  "/home/shreejal/Documents/Projects/enigma/build/picotool/src/picotoolBuild-stamp"
  "/home/shreejal/Documents/Projects/enigma/build/picotool/src"
  "/home/shreejal/Documents/Projects/enigma/build/picotool/src/picotoolBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/shreejal/Documents/Projects/enigma/build/picotool/src/picotoolBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/shreejal/Documents/Projects/enigma/build/picotool/src/picotoolBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
