# Nightwave Studios - C++ Core

# Minimum version required for CMake
cmake_minimum_required(VERSION 3.1)

if(UNIX AND NOT APPLE)
	set(LINUX TRUE)
endif()

# Project properties
project(NightwaveCore)
set(TARGET_VERSION_MAJOR 0)
set(TARGET_VERSION_MINOR 1)
set(TARGET_VERSION_PATCH 0)
set(TARGET_COPYRIGHT "©2017 Nightwave Studios: Vinyl Darkscratch, Light Apacha.")

set(CMAKE_BINARY_DIR ${PROJECT_BINARY_DIR}/bin)
set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
aux_source_directory(src source_file_list)

set(ROOT  ${CMAKE_SOURCE_DIR})
set(SRC   ${PROJECT_SOURCE_DIR})
set(BIN   ${CMAKE_BINARY_DIR})
set(INCL  ${ROOT}/include)
set(LIB   ${ROOT}/lib)
set(BUILD ${PROJECT_BINARY_DIR})

include_directories(${ROOT})
include_directories(${INCL})

add_library(NightwaveCore SHARED
	${SRC}/Colors.cpp ${INCL}/Colors.h
	${SRC}/DCHelpers.cpp ${INCL}/DCHelpers.h
	${SRC}/Helpers.cpp ${INCL}/Helpers.h
	${SRC}/SplashScreen.cpp ${INCL}/SplashScreen.h
)

set(CMAKE_CXX_COMPILER g++)
find_package(wxWidgets COMPONENTS html qa adv core xml net base REQUIRED)
execute_process(COMMAND "wx-config --cxxflags" OUTPUT_VARIABLE wxConfig_CXX_FLAGS)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ${wxConfig_CXX_FLAGS}")

IF(APPLE)
	IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmacosx-version-min=10.12")
	ENDIF()
	IF(${CMAKE_GENERATOR} MATCHES "Xcode")
		add_definitions(-DXCODE_BUNDLE)
		target_link_libraries(NightwaveCore "-framework CoreFoundation")
		set_target_properties(NightwaveCore PROPERTIES MACOSX_FRAMEWORK_IDENTIFIER co.nightwave.core)
	ENDIF()
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	add_definitions(-D__NO_INLINE__)
ENDIF()

include(${wxWidgets_USE_FILE})
target_link_libraries(NightwaveCore ${wxWidgets_LIBRARIES})

install(TARGETS NightwaveCore DESTINATION lib)

file(GLOB HEADERS include/*.h)
install(FILES ${HEADERS} DESTINATION include/NightwaveCore)

find_package(Doxygen)
IF(DOXYGEN_FOUND)
	configure_file(${ROOT}/doxygen.conf.in ${BUILD}/doxygen.conf @ONLY)
	add_custom_target(docs ALL DEPENDS ${BUILD}/doxygen/)
	add_custom_command(OUTPUT ${BUILD}/doxygen/ COMMAND ${DOXYGEN_EXECUTABLE} ${BUILD}/doxygen.conf DEPENDS ${SRC}/* ${ROOT}/../readme.md ${ROOT}/doxygen.conf.in VERBATIM) # COMMENT "Generating API documentation with Doxygen"
ENDIF(DOXYGEN_FOUND)
