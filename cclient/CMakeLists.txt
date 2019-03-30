#-----------------------------------------------------------------------------
#
# Ryturn
#  Authors: Nevrax and the OpenNeL Community, adapted for the Ryturn project
#  Notes:
#    * Changing install location: add -DCMAKE_INSTALL_PREFIX:PATH=/my/new/path
#  Version: 
#
PROJECT(RYTURN CXX C)
SET(RYTURN_VERSION_MAJOR 0)
SET(RYTURN_VERSION_MINOR 9)
SET(RYTURN_VERSION_PATCH 8)
SET(RYTURN_VERSION "${RYTURN_VERSION_MAJOR}.${RYTURN_VERSION_MINOR}.${RYTURN_VERSION_PATCH}")

#-----------------------------------------------------------------------------
# Loads some macros.
SET(CMAKE_MODULE_PATH "${RYTURN_SOURCE_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")
INCLUDE(InstallRequiredSystemLibraries)

###
# Checks build vs. source location. Prevents In-Source builds.
###
IF(${RYTURN_SOURCE_DIR} STREQUAL ${RYTURN_BINARY_DIR})
   MESSAGE(FATAL_ERROR "

CMake generation for this project is not allowed within the source directory!
Remove the CMakeCache.txt file and try again from another folder, e.g.:

   rm CMakeCache.txt
   mkdir cmake
   cd cmake
   cmake -G \"Unix Makefiles\" ..
    ")
ENDIF(${RYTURN_SOURCE_DIR} STREQUAL ${RYTURN_BINARY_DIR})

CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

#-----------------------------------------------------------------------------
# Redirect output files
SET(EXECUTABLE_OUTPUT_PATH "${RYTURN_SOURCE_DIR}/bin")
SET(RUNTIME_OUTPUT_DIRECTORY "${RYTURN_SOURCE_DIR}/bin")
SET(LIBRARY_OUTPUT_PATH  "${RYTURN_SOURCE_DIR}/lib")

#-----------------------------------------------------------------------------
# looking for some libraries
FIND_PACKAGE(CEGUI REQUIRED)
IF(CEGUI_FOUND)
	INCLUDE_DIRECTORIES(${CEGUI_INCLUDE_DIRS})
	LINK_DIRECTORIES(${CEGUI_LIBRARY})
ENDIF(CEGUI_FOUND)

FIND_PACKAGE(Nel REQUIRED)
IF(NEL_FOUND)
	INCLUDE_DIRECTORIES(${NEL_INCLUDE_DIR})
	LINK_DIRECTORIES(${NEL_LIBRARY_DIR})
ENDIF(NEL_FOUND)

FIND_PACKAGE(LIBXML REQUIRED)
IF(LIBXML_FOUND)
	INCLUDE_DIRECTORIES(${LIBXML_INCLUDE_DIR})
	LINK_DIRECTORIES(${LIBXML_LIBRARY_DIR})
ENDIF(LIBXML_FOUND)


IF(UNIX)
	SET(prefix ${CMAKE_INSTALL_PREFIX})
	SET(exec_prefix ${CMAKE_INSTALL_PREFIX}/bin)
	SET(libdir "${CMAKE_INSTALL_PREFIX}/lib ${PLATFORM_LINKFLAGS}")
	#SET(includedir "${CMAKE_INSTALL_PREFIX}/include ${PLATFORM_CFLAGS}")

	INSTALL(PROGRAMS ${RYTURN_SOURCE_DIR}/bin/ryturn DESTINATION bin)
	INSTALL(FILES ${RYTURN_SOURCE_DIR}/bin/atyscape.cfg_ DESTINATION bin)
	INSTALL(DIRECTORY ${RYTURN_SOURCE_DIR}/lib/ DESTINATION lib)
ENDIF(UNIX)

INCLUDE_DIRECTORIES(${RYTURN_SOURCE_DIR}/src/mods)
INCLUDE_DIRECTORIES(${RYTURN_SOURCE_DIR}/src/views)
INCLUDE_DIRECTORIES(${RYTURN_SOURCE_DIR}/src/game_modes)
INCLUDE_DIRECTORIES(${RYTURN_SOURCE_DIR}/src)

ADD_SUBDIRECTORY(src/mods)
ADD_SUBDIRECTORY(src/views)
ADD_SUBDIRECTORY(src/game_modes)
ADD_SUBDIRECTORY(src)

#-----------------------------------------------------------------------------
# Packaging
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Ryturn")
SET(CPACK_PACKAGE_VENDOR "Anyrow's team")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/Copyright.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR "${RYTURN_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${RYTURN_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${RYTURN_VERSION_PATCH}")
SET(CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR};ryturn;ALL;/")
SET(CPACK_PACKAGE_EXECUTABLES "ryturn" "Ryturn")
SET(CPACK_PACKAGE_FILE_NAME "ryturn-${RYTURN_VERSION}")

IF(WIN32 AND NOT UNIX)
	#FIXME: Needs test under windows, see http://www.cmake.org/Wiki/CMake:CPackWin32NewbiesChecklist
	# There is a bug in NSI that does not handle full unix paths properly. Make
	# sure there is at least one set of four (4) backlasshes.
	SET(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
	SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\ryturn.exe")
	SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} Ryturn")
	SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\atyscape.diwi.org/trac/wiki/WikiStart")
	SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\atyscape.diwi.org/trac/wiki/WikiStart")
	SET(CPACK_NSIS_CONTACT "anyrow@googlegroups.com")
	SET(CPACK_NSIS_MODIFY_PATH ON)
ELSE(WIN32 AND NOT UNIX)
	SET(CPACK_STRIP_FILES "bin/ryturn")
	SET(CPACK_SOURCE_STRIP_FILES "")
ENDIF(WIN32 AND NOT UNIX)

## Source Packages
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "ryturn-${RYTURN_VERSION}-src")
IF(WIN32)
  SET(CPACK_GENERATOR "ZIP")
  SET(CPACK_SOURCE_GENERATOR "ZIP")
ELSE(WIN32)
  SET(CPACK_GENERATOR "TGZ;STGZ")
  SET(CPACK_SOURCE_GENERATOR "TGZ")
ENDIF(WIN32)
SET(CPACK_SOURCE_IGNORE_FILES
	"~$"
	"\\\\.cvsignore$"
	"^${CMAKE_SOURCE_DIR}.*/CVS/"
	"^${CMAKE_SOURCE_DIR}.*/\\\\.svn/"
	"^${CMAKE_SOURCE_DIR}/debian/"
	"^${CMAKE_SOURCE_DIR}/old/")

INCLUDE(CPack)

