cmake_minimum_required(VERSION 3.1)

project(SonicForcesStageTimer)
set(CMAKE_CXX_STANDARD 14)
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}")

set(SFML_DIR "C:/Users/Kamil/Desktop/GIT/SFML/install64/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()

file(GLOB SOURCE_FILES
	"src/*.cpp"
    "src/*.c")

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

include_directories("src")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}_${CMAKE_SYSTEM_NAME}_${CMAKE_BUILD_TYPE}")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_link_libraries(${PROJECT_NAME} sfml-graphics "${PROJECT_SOURCE_DIR}/assets/sfst.res")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	target_link_libraries(${PROJECT_NAME} -s -O4 -static -static-libgcc -static-libstdc++ -m64 sfml-graphics "${PROJECT_SOURCE_DIR}/assets/sfst.res")
endif()
