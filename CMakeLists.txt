cmake_minimum_required( VERSION 2.6 )
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package ( Qt4 REQUIRED )
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/)

IF(UNIX)
	set(CMAKE_CXX_FLAGS "-Wall")
	set(CMAKE_C_FLAGS "-Wall")
ENDIF(UNIX)

#############################################
################### MACROS ##################
#############################################

MACRO(USE_QT_LIB lib)
	SET(QT_USE_QT${lib} true)
	SET(LIBRARIES ${LIBRARIES} ${QT_QT${lib}_LIBRARIES})
	SET(INCLUDES ${INCLUDES} ${QT_QT${lib}_INCLUDE_DIR})
ENDMACRO(USE_QT_LIB)

MACRO(CALL_PROJECT_HACK name)
#	PROJECT(${name})
ENDMACRO(CALL_PROJECT_HACK)

MACRO(PROJECT_BEGIN name apptype)
	SET(PROJECT_NAME ${name})
	SET(PROJECT_APP_TYPE ${apptype})
	IF("${PROJECT_APP_TYPE}" MATCHES "LIBRARY")
		IF("${PROJECT_APP_TYPE}" MATCHES "STATIC_LIBRARY")
			SET(BUILD_${PROJECT_NAME}_STATIC ON)
			OPTION(BUILD_${PROJECT_NAME}_STATIC "Build ${PROJECT_NAME} statically." ON)
		ELSE("${PROJECT_APP_TYPE}" MATCHES "STATIC_LIBRARY")
			OPTION(BUILD_${PROJECT_NAME}_STATIC "Build ${PROJECT_NAME} statically." OFF)
		ENDIF("${PROJECT_APP_TYPE}" MATCHES "STATIC_LIBRARY")
	ENDIF("${PROJECT_APP_TYPE}" MATCHES "LIBRARY")
	CALL_PROJECT_HACK(${PROJECT_NAME})
ENDMACRO(PROJECT_BEGIN)

MACRO(PROJECT_END)
	SET(INCLUDES ${INCLUDES}
		./
	)
	include ( ${QT_USE_FILE} )

	QT4_WRAP_CPP(MOC_SOURCES ${HEADERS})
	QT4_WRAP_UI(FORMS_UI ${FORMS})
	QT4_ADD_RESOURCES(RESOURCES_SRCS ${RESOURCES})
	SET(SOURCES ${SOURCES} ${RESOURCES_SRCS})

	INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_BINARY_DIR})

	IF("${PROJECT_APP_TYPE}" MATCHES "LIBRARY")
		IF(BUILD_${PROJECT_NAME}_STATIC)
			SET(${PROJECT_NAME}_LIBRARY_TYPE STATIC)
		ELSE(BUILD_${PROJECT_NAME}_STATIC)
			SET(${PROJECT_NAME}_LIBRARY_TYPE SHARED)
		ENDIF(BUILD_${PROJECT_NAME}_STATIC)

		IF("${${PROJECT_NAME}_LIBRARY_TYPE}" MATCHES "STATIC")
			MESSAGE(STATUS "Building ${PROJECT_NAME} as a static library.")
		ELSE("${${PROJECT_NAME}_LIBRARY_TYPE}" MATCHES "STATIC")
			IF("${${PROJECT_NAME}_LIBRARY_TYPE}" MATCHES "SHARED")
				MESSAGE(STATUS "Building ${PROJECT_NAME} as a shared library.")
				IF(UNIX)
					ADD_CUSTOM_TARGET(
							lib${PROJECT_NAME}.so.1 ALL
							ln -fs lib${PROJECT_NAME}.so.1.0.0 lib${PROJECT_NAME}.so.1
							DEPENDS ${PROJECT_NAME}
					)
					INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/lib${PROJECT_NAME}.so.1
						DESTINATION lib
					)
				ENDIF(UNIX)
			ELSE("${${PROJECT_NAME}_LIBRARY_TYPE}" MATCHES "SHARED")
				MESSAGE(FATAL_ERROR "Library type must be either SHARED or STATIC, found ${${PROJECT_NAME}_LIBRARY_TYPE}. Please fix the PROJECT_BEGIN macro in CMakeLists.txt")
			ENDIF("${${PROJECT_NAME}_LIBRARY_TYPE}" MATCHES "SHARED")
		ENDIF("${${PROJECT_NAME}_LIBRARY_TYPE}" MATCHES "STATIC")

		ADD_LIBRARY(${PROJECT_NAME} ${${PROJECT_NAME}_LIBRARY_TYPE} ${SOURCES} ${MOC_SOURCES} ${FORMS_UI})
		SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
					VERSION 1.0.0
					SOVERSION 1)
	ELSE("${PROJECT_APP_TYPE}" MATCHES "LIBRARY")
		IF("${PROJECT_APP_TYPE}" MATCHES "EXECUTABLE")
			MESSAGE(STATUS "Building ${PROJECT_NAME} as an executable.")
		ELSE("${PROJECT_APP_TYPE}" MATCHES "EXECUTABLE")
			MESSAGE(FATAL_ERROR "Project type must be either LIBRARY or EXECUTABLE, found ${PROJECT_APP_TYPE}. Please fix the PROJECT_BEGIN macro in CMakeLists.txt")
		ENDIF("${PROJECT_APP_TYPE}" MATCHES "EXECUTABLE")
		IF(WIN32)
			USE_QT_LIB(MAIN)
		ENDIF(WIN32)
		ADD_EXECUTABLE(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCES} ${MOC_SOURCES} ${FORMS_UI})
	ENDIF("${PROJECT_APP_TYPE}" MATCHES "LIBRARY")

	SET(LIBRARIES ${LIBRARIES} ${QT_LIBRARIES})
	TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})
	INCLUDE_DIRECTORIES(
		${INCLUDES}
		${QT_INCLUDE_DIR}
	)

	TARGET_LINK_LIBRARIES(${PROJECT_NAME}
		${QT_LIBRARIES}
	)
	SET(SOURCES)
	SET(HEADERS)
	SET(LIBRARIES)
	SET(INCLUDES)
	SET(RESOURCES)
	SET(FORMS)
	SET(PROJECT_NAME)
	SET(PROJECT_APP_TYPE)
ENDMACRO(PROJECT_END)


MACRO(INSTALL_HEADERS path)
FILE(GLOB CONVHEADERS ./include/[A-Z]*)
FOREACH(CH ${CONVHEADERS})
	STRING(REGEX REPLACE ".*/" "" HEADERNAME ${CH})
	SET(HEADERNAME ${HEADERNAME}.h)
	STRING(TOLOWER ${HEADERNAME} HEADERNAME)
	INSTALL(FILES ${CH} ${HEADERNAME}
		DESTINATION include/${path})
ENDFOREACH()
ENDMACRO(INSTALL_HEADERS)

FOREACH(SUBDIR ${SUBDIRECTORIES})
	add_subdirectory(${SUBDIR})
ENDFOREACH()

IF(UNIX AND NOT APPLE)
FOREACH(SUBDIR ${SUBDIRECTORIES_UNIX})
	add_subdirectory(${SUBDIR})
ENDFOREACH()
ENDIF(UNIX AND NOT APPLE)


#############################################
################### PROJECT##################
#############################################


add_subdirectory("lib")
add_subdirectory("examples/basic_client")
add_subdirectory("examples/basic_server")
add_subdirectory("examples/event_client")
add_subdirectory("examples/event_server")
add_subdirectory("examples/async_client")
add_subdirectory("examples/async_server")
add_subdirectory("examples/auth_client")
add_subdirectory("examples/auth_server")
add_subdirectory("examples/md5auth_client")
add_subdirectory("examples/md5auth_server")
add_subdirectory("examples/ssl_client")
add_subdirectory("examples/ssl_server")
add_subdirectory("examples/thread_client")
add_subdirectory("examples/thread_server")
add_subdirectory("examples/data_client")
add_subdirectory("examples/data_server")
add_subdirectory("examples/discovery_client")
add_subdirectory("examples/discovery_server")
