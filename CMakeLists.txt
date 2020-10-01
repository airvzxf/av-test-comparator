cmake_minimum_required(VERSION 3.17)
project(av_test_comparator)

set(CMAKE_CXX_STANDARD 20)

find_package(CURL REQUIRED)

add_executable(
        av_test_comparator
        main.cpp
        library/library.h
        library/html/extract/inner.cpp library/html/extract/inner.h
        library/html/extract/outer.cpp library/html/extract/outer.h
        library/utility/text.cpp library/utility/text.h
        library/utility/replace.cpp library/utility/replace.h
)

if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIR})
    target_link_libraries(av_test_comparator ${CURL_LIBRARY})
else (CURL_FOUND)
    message(FATAL_ERROR "Could not find the CURL library and development files.")
endif (CURL_FOUND)
