cmake_minimum_required(VERSION 3.17)
project(av_test_comparator)

set(CMAKE_CXX_STANDARD 11)

find_package(CURL REQUIRED)

add_executable(
        av_test_comparator
        main.cpp
        core/core.h
        core/structure/antivirus.h
        core/structure/catalog.h
        core/structure/settings.h core/structure/settings.cpp
        core/windows/pc/detail.cpp core/windows/pc/detail.h
        core/windows/pc/helper/assign.cpp core/windows/pc/helper/assign.h
        core/windows/pc/helper/display.cpp core/windows/pc/helper/display.h
        core/windows/pc/helper/values.cpp core/windows/pc/helper/values.h
        core/windows/pc/main.cpp core/windows/pc/main.h
        library/html/extract/outer.cpp library/html/extract/outer.h
        library/html/extract/tag.cpp library/html/extract/tag.h
        library/html/find/inner.cpp library/html/find/inner.h
        library/html/find/outer.cpp library/html/find/outer.h
        library/html/find/tag.cpp library/html/find/tag.h
        library/html/request.cpp library/html/request.h
        library/library.h
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
