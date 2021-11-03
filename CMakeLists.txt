cmake_minimum_required(VERSION 3.0)

project(PetitRenderer)

set(ZLIB_LIBRARIES zlibstatic)
set(ENABLE_BOOST_WORKAROUND ON)
#set(BUILD_STATIC_LIB ON)
set(ASSIMP_BUILD_SAMPLES OFF)
set(BUILD_ASSIMP_TOOLS  OFF)
set(ASSIMP_BUILD_DOCS OFF)
set(ASSIMP_BUILD_STATIC_LIB ON)
set(ASSIMP_NO_EXPORT ON)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)

add_subdirectory(third_party/glfw)
add_subdirectory(third_party/assimp)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /DGLFW_INCLUDE_NONE /std:c++17 /wd4100 /wd4505")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -std=c++17")
endif()

include_directories(include/
                    third_party/glad/include/
                    third_party/glfw/include/
                    third_party/glm/
                    third_party/stb/
					third_party/zlib/
                    third_party/imgui/
                    third_party/imgui/backends/
                    third_party/assimp/include/
					)

file(GLOB VENDORS_SOURCES third_party/glad/src/glad.c)
file(GLOB PROJECT_HEADERS include/*.hpp)
file(GLOB PROJECT_SOURCES src/*.cpp
                          src/model/*.cpp
                          third_party/imgui/*.cpp
                          third_party/imgui/backends/*opengl3.cpp
                          third_party/imgui/backends/*glfw.cpp
                        )

file(GLOB PROJECT_SHADERS shaders/*.frag
                          shaders/*.vert)

file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitignore
                         .gitmodules)                         

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
                               ${VENDORS_SOURCES}  "src/main.cpp")

target_link_libraries(${PROJECT_NAME} glfw assimp 
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

message("### Moving shaders next to binary dir ####")
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>
    DEPENDS ${PROJECT_SHADERS})
