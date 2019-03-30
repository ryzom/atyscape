CMAKE_POLICY(SET CMP0003 NEW) # or cmake_policy(VERSION 2.6)

LINK_DIRECTORIES(${RYTURN_SOURCE_DIR}/src/mods)
LINK_DIRECTORIES(${RYTURN_SOURCE_DIR}/src/views)
LINK_DIRECTORIES(${RYTURN_SOURCE_DIR}/src/game_modes)

FILE(GLOB SRC *.cpp *.h)

ADD_EXECUTABLE(ryturn ${SRC})

IF(WIN32)
	# Needs tests !
	TARGET_LINK_LIBRARIES(ryturn CEGUIOpenGLRenderer CEGUIFalagardWRBase CEGUIBase nelceguirenderer nel_drv_opengl nel3d nelpacs nelmisc nelsnd_lowlevel nelsound rt mod_nel gm_make_avatar mod_avatar mod_cam view_scene_make_avatar view_avatar_show_case mod_audio mod_time view_fps)
ELSE(WIN32)
	TARGET_LINK_LIBRARIES(ryturn CEGUIOpenGLRenderer CEGUIFalagardWRBase CEGUIBase nelceguirenderer nel_drv_opengl nel3d nelpacs nelmisc nelsnd_lowlevel nelsound rt mod_nel gm_make_avatar mod_avatar mod_cam view_scene_make_avatar view_avatar_show_case mod_audio mod_time view_fps)
ENDIF (WIN32)
