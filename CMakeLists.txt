cmake_minimum_required (VERSION 2.8.11)
project (markov)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")

find_package(SFML 2 COMPONENTS system window graphics REQUIRED)
find_package(Boost)
find_package(JsonCpp)
include_directories(${SFML_INCLUDE_DIR} ${Boost_INCLUDE_DIRS} ${JSONCPP_INCLUDE_DIRS})

file(GLOB_RECURSE SRC_FILES   "src/*.cpp")

add_executable(markov ${SRC_FILES})
target_link_libraries(markov ${SFML_LIBRARIES} ${Boost_LIBRARIES} ${JSONCPP_LIBRARIES})

