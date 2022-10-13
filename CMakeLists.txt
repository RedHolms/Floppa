cmake_minimum_required(VERSION 3.8)

option(FLOPPA_SHARED "Build static(OFF) or shared(ON) library (DEFAULT=OFF)" OFF)
option(FLOPPA_EXAMPLE "Build example game (DEFAULT=ON)" ON)
option(FLOPPA_USE_SMART_POINTERS "Use smart pointers for DynamicAllocated<...> type (DEFAULT=OFF)" OFF)

if(NOT DEFINED(FLOPPA_SOURCES_DIR))
	set(FLOPPA_SOURCES_DIR "${CMAKE_SOURCE_DIR}/src")
endif()

if(NOT DEFINED(FLOPPA_INCLUDES_DIR))
	set(FLOPPA_INCLUDES_DIR "${CMAKE_SOURCE_DIR}/include")
endif()

project(Floppa)

find_package(GLEW CONFIG REQUIRED HINTS "C:/")

if(FLOPPA_SHARED)
	set(_FLOPPA_LIB_TYPE SHARED)
else()
	set(_FLOPPA_LIB_TYPE STATIC)
endif()

if(WIN32)
	add_definitions(-D_FLOPPA_WIN32)
	set(_FLOPPA_OS_IMPL_NAME Win32)
endif()

if(FLOPPA_USE_SMART_POINTERS)
	add_definitions(-D_FLOPPA_USE_SMART_POINTERS)
endif()

add_definitions(-D_FLOPPA_${_FLOPPA_LIB_TYPE})
add_definitions(-D_FLOPPA_OS_IMPL_NAME=${_FLOPPA_OS_IMPL_NAME})

set(_FLOPPA_SOURCES_DIR "${FLOPPA_SOURCES_DIR}/Floppa")

add_library(FloppaEngine ${_FLOPPA_LIB_TYPE}
	"${_FLOPPA_SOURCES_DIR}/Engine.cpp"
	"${_FLOPPA_SOURCES_DIR}/Window.cpp"
	"${_FLOPPA_SOURCES_DIR}/Renderer.cpp"
	"${_FLOPPA_SOURCES_DIR}/Encoding.cpp"
	"${_FLOPPA_SOURCES_DIR}/Drawer.cpp"
	"${_FLOPPA_SOURCES_DIR}/VertexBuffer.cpp"
	"${_FLOPPA_SOURCES_DIR}/IndexBuffer.cpp"

	"${_FLOPPA_SOURCES_DIR}/${_FLOPPA_OS_IMPL_NAME}/Window.cpp"
	"${_FLOPPA_SOURCES_DIR}/${_FLOPPA_OS_IMPL_NAME}/OpenGL3/Renderer.cpp"
	"${_FLOPPA_SOURCES_DIR}/${_FLOPPA_OS_IMPL_NAME}/OpenGL3/GLBuffer.cpp"
	"${_FLOPPA_SOURCES_DIR}/${_FLOPPA_OS_IMPL_NAME}/OpenGL3/VertexBuffer.cpp"
	"${_FLOPPA_SOURCES_DIR}/${_FLOPPA_OS_IMPL_NAME}/OpenGL3/IndexBuffer.cpp"
)

target_link_libraries(FloppaEngine PUBLIC GLEW::GLEW)
target_include_directories(FloppaEngine PUBLIC ${FLOPPA_INCLUDES_DIR})

if(FLOPPA_EXAMPLE)
	add_subdirectory(example)
endif()
