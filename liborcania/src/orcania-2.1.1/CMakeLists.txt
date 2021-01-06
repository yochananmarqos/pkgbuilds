#
# Orcania library
#
# CMake file used to build all programs
#
# Copyright 2018 Silvio Clecio <silvioprog@gmail.com>
# Copyright 2018-2020 Nicolas Mora <mail@babelouest.org>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the MIT License
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#

cmake_minimum_required(VERSION 3.5)

project(orcania C)

set(CMAKE_C_STANDARD 99)
if (NOT MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")
endif()

# library info

set(PROJECT_DESCRIPTION "Potluck with different functions for different purposes that can be shared among programs")
set(PROJECT_HOMEPAGE_URL "https://github.com/babelouest/orcania/")
set(PROJECT_BUGREPORT_PATH "https://github.com/babelouest/orcania/issues")
set(LIBRARY_VERSION_MAJOR "2")
set(LIBRARY_VERSION_MINOR "1")
set(LIBRARY_VERSION_PATCH "1")
set(LIBS "-lm")

set(PROJECT_VERSION "${LIBRARY_VERSION_MAJOR}.${LIBRARY_VERSION_MINOR}.${LIBRARY_VERSION_PATCH}")
set(PROJECT_VERSION_MAJOR ${LIBRARY_VERSION_MAJOR})
set(PROJECT_VERSION_MINOR ${LIBRARY_VERSION_MINOR})
set(PROJECT_VERSION_PATCH ${LIBRARY_VERSION_PATCH})

if (${LIBRARY_VERSION_MAJOR} VERSION_LESS 10)
    set (LIBRARY_VERSION_MAJOR_PAD "0${LIBRARY_VERSION_MAJOR}")
else ()
    set (LIBRARY_VERSION_MAJOR_PAD "${LIBRARY_VERSION_MAJOR}")
endif ()
if (${LIBRARY_VERSION_MINOR} VERSION_LESS 10)
    set (LIBRARY_VERSION_MINOR_PAD "0${LIBRARY_VERSION_MINOR}")
else ()
    set (LIBRARY_VERSION_MINOR_PAD "${LIBRARY_VERSION_MINOR}")
endif ()
if (${LIBRARY_VERSION_PATCH} VERSION_LESS 10)
    set (LIBRARY_VERSION_PATCH_PAD "0${LIBRARY_VERSION_PATCH}")
else ()
    set (LIBRARY_VERSION_PATCH_PAD "${LIBRARY_VERSION_PATCH}")
endif ()
set(PROJECT_VERSION_NUMBER "${LIBRARY_VERSION_MAJOR_PAD}${LIBRARY_VERSION_MINOR_PAD}${LIBRARY_VERSION_PATCH_PAD}")

set(LIBRARY_VERSION "${LIBRARY_VERSION_MAJOR}.${LIBRARY_VERSION_MINOR}.${LIBRARY_VERSION_PATCH}")
set(LIBRARY_SOVERSION "${LIBRARY_VERSION_MAJOR}.${LIBRARY_VERSION_MINOR}")

# cmake modules

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

include(GNUInstallDirs)
include(CheckSymbolExists)

# check if _GNU_SOURCE is available

if (NOT _GNU_SOURCE)
    check_symbol_exists(__GNU_LIBRARY__ "features.h" _GNU_SOURCE)

    if (NOT _GNU_SOURCE)
        unset(_GNU_SOURCE CACHE)
        check_symbol_exists(_GNU_SOURCE "features.h" _GNU_SOURCE)
    endif ()
endif ()

if (_GNU_SOURCE)
    add_definitions(-D_GNU_SOURCE)
endif ()

# directories and source

set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${INC_DIR})

set(LIB_SRC
        ${INC_DIR}/orcania.h # allow many IDEs to find and edit it
        ${SRC_DIR}/base64.c
        ${SRC_DIR}/memory.c
        ${SRC_DIR}/orcania.c)

option(WITH_STRSTR "Use inline implementation of strstr" OFF)
if (WITH_STRSTR)
    set(O_STRSTR ON)
else ()
    set(O_STRSTR OFF)
endif ()

set(PKGCONF_REQ "")
set(PKGCONF_REQ_PRIVATE "")

# build orcania-cfg.h file
configure_file(${INC_DIR}/orcania-cfg.h.in ${PROJECT_BINARY_DIR}/orcania-cfg.h)
set (CMAKE_EXTRA_INCLUDE_FILES ${PROJECT_BINARY_DIR})
include_directories(${PROJECT_BINARY_DIR})

# static library

option(BUILD_STATIC "Build static library." OFF)

if (BUILD_STATIC)
    add_library(orcania_static STATIC ${LIB_SRC})
    target_compile_definitions(orcania_static PUBLIC -DO_STATIC_LIBRARY)
    set_target_properties(orcania_static PROPERTIES
            OUTPUT_NAME orcania)
endif ()

# shared library

add_library(orcania SHARED ${LIB_SRC})
if (NOT MSVC)
    set_target_properties(orcania PROPERTIES
            COMPILE_OPTIONS -Wextra
            PUBLIC_HEADER "${INC_DIR}/orcania.h;${PROJECT_BINARY_DIR}/orcania-cfg.h"
            VERSION "${LIBRARY_VERSION}"
            SOVERSION "${LIBRARY_SOVERSION}")
endif()
if (WIN32)
    set_target_properties(orcania PROPERTIES SUFFIX "-${LIBRARY_VERSION_MAJOR}.dll")
endif ()
target_link_libraries(orcania ${LIBS})

# documentation

option(BUILD_ORCANIA_DOCUMENTATION "Build the documentation." OFF)
if (BUILD_ORCANIA_DOCUMENTATION)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/doc/doxygen.cfg)
        set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/doxyfile)
        
        configure_file(${doxyfile_in} ${doxyfile} @ONLY)
        
        add_custom_target(doc
                          COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile_in}
                          WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                          COMMENT "Generating documentation with Doxygen"
                          VERBATIM)

    else ()
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif ()
endif ()

# tests

option(BUILD_ORCANIA_TESTING "Build the testing tree." OFF) # because we do not use include(CTest)

if (BUILD_ORCANIA_TESTING)
    include(FindCheck)
    find_package(Check)
    if (CHECK_FOUND)
        if (NOT WIN32 AND NOT APPLE)
            include(FindSubunit)
            find_package(Subunit REQUIRED)
        endif ()

        enable_testing()

        set(CMAKE_CTEST_COMMAND ctest -V)

        set(TST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
        set(LIBS orcania ${LIBS} ${CHECK_LIBRARIES})
        if (NOT WIN32)
            find_package(Threads REQUIRED)
            set(LIBS ${LIBS} ${CMAKE_THREAD_LIBS_INIT} m)
        endif ()
        if (NOT APPLE)
            set(LIBS ${LIBS} rt)
        endif ()
        if (NOT WIN32 AND NOT APPLE)
            set(LIBS ${LIBS} ${SUBUNIT_LIBRARIES} rt)
        endif ()

        set(TESTS
                str_test
                split_test
                memory_test
                pointer_list_test)

        configure_file(
                "${CMAKE_MODULE_PATH}/CTestCustom.cmake.in"
                "${CMAKE_CURRENT_BINARY_DIR}/CTestCustom.cmake"
                @ONLY)

        foreach (t ${TESTS})
            add_executable(${t} EXCLUDE_FROM_ALL ${TST_DIR}/${t}.c)
            target_include_directories(${t} PUBLIC ${TST_DIR})
            target_link_libraries(${t} PUBLIC ${LIBS})
            add_test(NAME ${t}
                    WORKING_DIRECTORY ${TST_DIR}
                    COMMAND ${t})
        endforeach ()
    endif ()
endif ()

# install target

option(INSTALL_HEADER "Install the header files" ON) # Install orcania.h or not

configure_file(liborcania.pc.in liborcania.pc @ONLY)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/liborcania.pc
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

set(TARGETS orcania)
if (BUILD_STATIC)
    set(TARGETS ${TARGETS} orcania_static)
endif ()

if (INSTALL_HEADER)
    install(TARGETS ${TARGETS}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
else ()
    install(TARGETS ${TARGETS}
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif ()

# uninstall target

if (NOT TARGET uninstall)
    configure_file(
            "${CMAKE_MODULE_PATH}/CMakeUninstall.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
            IMMEDIATE @ONLY)
    add_custom_target(uninstall
            COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif ()

# packaging

set(CPACK_PACKAGE_VERSION_MAJOR ${LIBRARY_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${LIBRARY_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${LIBRARY_VERSION_PATCH})

if (INSTALL_HEADER)
    set(PACKAGE_FILE_NAME
            "lib${CMAKE_PROJECT_NAME}-dev_${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
else ()
    set(PACKAGE_FILE_NAME
            "lib${CMAKE_PROJECT_NAME}_${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
endif ()
set(PACKAGE_IGNORED_FILES
        "${CMAKE_CURRENT_BINARY_DIR}/;/.git/;.gitignore;~$;${CPACK_SOURCE_IGNORE_FILES}")

set(CPACK_PACKAGE_NAME "liborcania")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Potluck for C programs")
set(CPACK_GENERATOR "TGZ;DEB")
set(CPACK_PACKAGE_VERSION_MAJOR ${LIBRARY_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${LIBRARY_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${LIBRARY_VERSION_PATCH})

option(BUILD_RPM "Build a RPM for your system" OFF)
if (BUILD_RPM)
  set(CPACK_GENERATOR "TGZ;DEB;RPM")
  set(CPACK_RPM_PACKAGE_LICENSE "LGPL")
  set(CPACK_RPM_PACKAGE_URL "http://babelouest.github.io/orcania/")
endif ()

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "mail@babelouest.org")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION ${PROJECT_DESCRIPTION})
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/babelouest/orcania")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.4)")
set(CPACK_PACKAGE_FILE_NAME ${PACKAGE_FILE_NAME})
set(CPACK_PACKAGE_FILE_NAME ${PACKAGE_FILE_NAME})

set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_PACKAGE_FILE_NAME ${PACKAGE_FILE_NAME})
set(CPACK_SOURCE_IGNORE_FILES ${PACKAGE_IGNORED_FILES})

include(CPack)

add_custom_target(dist_o
        COMMAND ${CMAKE_MAKE_PROGRAM} package_source)

message(STATUS "Force inline implementation of strstr: ${WITH_STRSTR}")
message(STATUS "Build static library: ${BUILD_STATIC}")
message(STATUS "Build testing tree: ${BUILD_ULFIUS_TESTING}")
message(STATUS "Install the header files: ${INSTALL_HEADER}")
message(STATUS "Build RPM package: ${BUILD_RPM}")
message(STATUS "Build documentation: ${BUILD_ORCANIA_DOCUMENTATION}")
