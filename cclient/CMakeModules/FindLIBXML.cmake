# - Locate libxml2 
# This module defines
#  LIBXML_LIBRARY_DIR, the library to link against
#  LIBXML_FOUND, if false, do not try to link to libxml2
#  LIBXML_INCLUDE_DIR, where to find headers.

IF(LIBXML_LIBRARY AND LIBXML_INCLUDE_DIRS)
  # in cache already
  SET(LIBXML_FIND_QUIETLY TRUE)
ENDIF(LIBXML_LIBRARY AND LIBXML_INCLUDE_DIRS)

FIND_PATH(LIBXML_INCLUDE_DIR
  libxml
  PATHS
  $ENV{LIBXML_DIR}/include
  /usr/local/include
  /usr/include
  /sw/include
  /opt/local/include
  /opt/csw/include
  /opt/include
  PATH_SUFFIXES libxml2
)

FIND_LIBRARY(LIBXML_LIBRARY_DIR
  NAMES xml2 libxml2
  PATHS
  $ENV{LIBXML_DIR}/lib
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

IF(LIBXML_LIBRARY_DIR AND LIBXML_INCLUDE_DIR)
  SET(LIBXML_FOUND "YES")
  IF(NOT LIBXML_FIND_QUIETLY)
    MESSAGE(STATUS "Found libxml2: ${LIBXML_INCLUDE_DIR}, ${LIBXML_LIBRARY_DIR}")
  ENDIF(NOT LIBXML_FIND_QUIETLY)
ELSE(LIBXML_LIBRARY_DIR AND LIBXML_INCLUDE_DIR)
  IF(NOT LIBXML_FIND_QUIETLY)
    MESSAGE(STATUS "Warning: Unable to find libxml2!")
  ENDIF(NOT LIBXML_FIND_QUIETLY)
ENDIF(LIBXML_LIBRARY_DIR AND LIBXML_INCLUDE_DIR)

