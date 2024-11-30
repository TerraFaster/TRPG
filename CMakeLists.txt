# Minimum CMake version and project setup
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(TRPG VERSION 0.1.3)

# Output executable name
set(EXECUTABLE_NAME ${PROJECT_NAME})

# Set policies and options
cmake_policy(SET CMP0074 NEW)
# 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
# Set the C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# LTO for Release builds
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
# Set the runtime library to MultiThreaded for all configurations
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")


# Source files
file(GLOB_RECURSE TRPG_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE TRPG_HEADERS CONFIGURE_DEPENDS "src/*.h")

# Include directories
set(TRPG_INCLUDE_DIRS "")
foreach(_headerFile ${TRPG_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list(APPEND TRPG_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES TRPG_INCLUDE_DIRS)

# Add executable target
add_executable(${EXECUTABLE_NAME} ${TRPG_SOURCES})
target_include_directories(${EXECUTABLE_NAME} PRIVATE ${TRPG_INCLUDE_DIRS})


# Enable Unity build for faster compilation and set batch size
set_target_properties(${EXECUTABLE_NAME} PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 8)

# Some other properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%"
    LINK_FLAGS "/MANIFESTUAC:\"level='asInvoker' uiAccess='false'\""
)


# Compiler warnings and options (ignore specific warnings)
target_compile_options(${EXECUTABLE_NAME} PRIVATE /wd4244 /wd4838)
# Enable multi-processor compilation
target_compile_options(${EXECUTABLE_NAME} PRIVATE /MP)


# Include vendor libraries
# SDL3
add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/SDL)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE SDL3::SDL3)

# SDL3_image
set(SDLIMAGE_AVIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_BMP OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_GIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_JPG OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_JXL OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_LBM OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_PCX OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_PNG ON CACHE BOOL "" FORCE) # We only need PNG
set(SDLIMAGE_PNM OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_QOI OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_SVG OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_TGA OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_TIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_WEBP OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_XCF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_XPM OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_XV OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/SDL_image)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE SDL3_image::SDL3_image)

# nlohmann_json
add_subdirectory(${CMAKE_SOURCE_DIR}/vendor/json)
target_link_libraries(${EXECUTABLE_NAME} PRIVATE nlohmann_json::nlohmann_json)

# Copy resources folder to the build directory
add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/resources
)

# Start the executable after building
add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND $<TARGET_FILE:${EXECUTABLE_NAME}>
)
