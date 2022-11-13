cmake_minimum_required(VERSION 3.21)
set(PROJECT_NAME ImgtoC)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)
find_package(OpenGL)

# Default to release builds
if(NOT CMAKE_BUILD_TYPE)
endif()
set(CMAKE_BUILD_TYPE Release)

file(GLOB source_files
	"src/*.cpp"
)

set(SOURCES ${source_files})
set(CMAKE_CXX_STANDARD 11)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED COMPONENTS audio graphics window system)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE "include" "lib" "res")
target_link_libraries(${PROJECT_NAME} sfml-graphics)
if (UNIX)
   target_link_libraries(${PROJECT_NAME} pthread)
endif (UNIX)

# Copy data dir to the binary directory
if (IS_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/res")
   message("-- deleting res\n")
   file(REMOVE_RECURSE "${CMAKE_CURRENT_BINARY_DIR}/res")
endif()
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/res" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

if(MSVC)
   foreach(lib ${SFML_LIBS})
      get_target_property(lib_path ${lib} LOCATION)
      file(COPY ${lib_path} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
   endforeach()
endif(MSVC)