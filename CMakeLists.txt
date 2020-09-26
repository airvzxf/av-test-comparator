cmake_minimum_required(VERSION 3.17)
project(av_test_comparator)

set(CMAKE_CXX_STANDARD 20)

find_package(CURL REQUIRED)

add_executable(av_test_comparator main.cpp)

if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIR})
    target_link_libraries(av_test_comparator ${CURL_LIBRARIES})
else (CURL_FOUND)
    message(FATAL_ERROR "Could not find the CURL library and development files.")
endif (CURL_FOUND)