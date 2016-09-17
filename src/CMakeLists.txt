IF(WIN32)
	SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
ENDIF(WIN32)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0.0 FATAL_ERROR)

SET(CMAKE_CONFIGURATION_TYPES "Debug;Release")

SET(MY_PROJECT_NAME DanceGame)

PROJECT( ${MY_PROJECT_NAME} VERSION 1 LANGUAGES C CXX )

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

# set cmake policy
IF(COMMAND CMAKE_POLICY)
	CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

IF(WIN32)
	IF(MSVC)
		ADD_DEFINITIONS(-D_SCL_SECURE_NO_WARNINGS)
		ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE)
	ENDIF(MSVC)
ENDIF(WIN32)


SET( CMAKE_INCLUDE_CURRENT_DIR ON )
SET( CMAKE_VERBOSE_MAKEFILE ON )


INCLUDE_DIRECTORIES($ENV{ddThirdParty}/../../../../Ref/OpenGl/Sdk/GLFW/Src/install/include 
					$ENV{ddThirdParty}/../../../../Ref/OpenGl/Sdk/Glew/sdk/glew_install/include 
					)
					
LINK_DIRECTORIES($ENV{ddThirdParty}/../../../../Ref/OpenGl/Sdk/GLFW/Src/install/lib 
				 $ENV{ddThirdParty}/../../../../Ref/OpenGl/Sdk/Glew/sdk/glew_install/lib/Release/Win32 
				  )

				  
				  
#add define
ADD_DEFINITIONS( )


IF(WIN32)
# this macro is for vs folder
macro(GroupSources curdir)
	MESSAGE("curdir = ${curdir} ")
	FILE(GLOB_RECURSE children RELATIVE ${curdir} "*.cpp" "*.h" "*.c" "*.tpp")
	FOREACH(child ${children})
		STRING(REPLACE "/" "\\" groupname ${child})
		STRING(FIND ${groupname} "\\" endpos REVERSE)
		IF( ${endpos} GREATER -1 )
			STRING(SUBSTRING ${groupname} 0 ${endpos} groupname)
			SOURCE_GROUP(${groupname} FILES ${curdir}/${child})
		ENDIF(${endpos} GREATER -1 )
   ENDFOREACH( child ${children})
endmacro()
GroupSources(${CMAKE_SOURCE_DIR})
ENDIF(WIN32)

FILE(GLOB_RECURSE incSrcFileList "*.cpp" "*.h" "*.c" "*.tpp")

ADD_EXECUTABLE( ${MY_PROJECT_NAME} WIN32 ${incSrcFileList})

TARGET_LINK_LIBRARIES(${MY_PROJECT_NAME} 
					glfw3 
					glew32s 
					opengl32 )

set_target_properties(${MY_PROJECT_NAME} PROPERTIES FOLDER ${MY_PROJECT_NAME}) 
