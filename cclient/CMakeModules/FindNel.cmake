# - Locate NeL library
# This module defines
#  NEL_LIBRARY_DIR, the library to link against
#  NEL_FOUND, if false, do not try to link to NeL
#  NEL_INCLUDE_DIR, where to find headers.

IF(NEL_LIBRARY AND NEL_INCLUDE_DIRS)
  # in cache already
  SET(NEL_FIND_QUIETLY TRUE)
ENDIF(NEL_LIBRARY AND NEL_INCLUDE_DIRS)


FIND_PATH(NEL_INCLUDE_DIR
  nel
  PATHS
  $ENV{NEL_DIR}/include
  /usr/local/include
  /usr/include
  /sw/include
  /opt/local/include
  /opt/csw/include
  /opt/include
  PATH_SUFFIXES nel
)

FIND_LIBRARY(NEL_LIBRARY_DIR
  NAMES nel3d nelmisc nelnet nelceguirenderer nelsound nelpacs
  PATHS
  $ENV{NEL_DIR}/lib
  /usr/local/lib
  /usr/lib
  /usr/local/X11R6/lib
  /usr/X11R6/lib
  /sw/lib
  /opt/local/lib
  /opt/csw/lib
  /opt/lib
  /usr/freeware/lib64
)

IF(NEL_LIBRARY_DIR AND NEL_INCLUDE_DIR)
  SET(NEL_FOUND "YES")
  IF(NOT NEL_FIND_QUIETLY)
    MESSAGE(STATUS "Found NEL: ${NEL_INCLUDE_DIR}, ${NEL_LIBRARY_DIR}")
  ENDIF(NOT NEL_FIND_QUIETLY)
ELSE(NEL_LIBRARY_DIR AND NEL_INCLUDE_DIR)
  IF(NOT NEL_FIND_QUIETLY)
    MESSAGE(STATUS "Warning: Unable to find NEL!")
  ENDIF(NOT NEL_FIND_QUIETLY)
ENDIF(NEL_LIBRARY_DIR AND NEL_INCLUDE_DIR)
