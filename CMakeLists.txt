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
        library/html/request.cpp library/html/request.h
        library/utility/text/clean.cpp library/utility/text/clean.h
        library/utility/text/escape.cpp library/utility/text/escape.h
        library/utility/text/replace.cpp library/utility/text/replace.h
        library/utility/text/trim.cpp library/utility/text/trim.h
)

if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIR})
    target_link_libraries(av_test_comparator ${CURL_LIBRARY})
else (CURL_FOUND)
    message(FATAL_ERROR "Could not find the CURL library and development files.")
endif (CURL_FOUND)
