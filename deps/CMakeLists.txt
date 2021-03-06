cmake_minimum_required(VERSION 3.1)
project(NHEKO_DEPS)

# Point CMake at any custom modules we may ship
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(DEPS_INSTALL_DIR "${CMAKE_BINARY_DIR}/usr"
    CACHE PATH "Dependencies install directory.")
set(DEPS_BIN_DIR "${DEPS_INSTALL_DIR}/bin"
    CACHE PATH "Dependencies binary install directory.")
set(DEPS_LIB_DIR "${DEPS_INSTALL_DIR}/lib"
    CACHE PATH "Dependencies library install directory.")
set(DEPS_BUILD_DIR "${CMAKE_BINARY_DIR}/build"
    CACHE PATH "Dependencies build directory.")
set(DEPS_DOWNLOAD_DIR "${DEPS_BUILD_DIR}/downloads"
    CACHE PATH "Dependencies download directory.")

option(USE_BUNDLED "Use bundled dependencies." ON)

option(USE_BUNDLED_BOOST "Use the bundled version of Boost." ${USE_BUNDLED})
option(USE_BUNDLED_SPDLOG "Use the bundled version of spdlog." ${USE_BUNDLED})
option(USE_BUNDLED_OLM "Use the bundled version of libolm." ${USE_BUNDLED})
option(USE_BUNDLED_TWEENY "Use the bundled version of Tweeny." ${USE_BUNDLED})
option(USE_BUNDLED_LMDBXX "Use the bundled version of lmdbxx." ${USE_BUNDLED})
option(USE_BUNDLED_MATRIX_STRUCTS "Use the bundled version of matrix-structs."
       ${USE_BUNDLED})
option(USE_BUNDLED_MATRIX_CLIENT "Use the bundled version of mtxclient."
       ${USE_BUNDLED})

include(ExternalProject)

set(BOOST_URL
    https://dl.bintray.com/boostorg/release/1.66.0/source/boost_1_66_0.tar.bz2)
set(BOOST_SHA256
    5721818253e6a0989583192f96782c4a98eb6204965316df9f5ad75819225ca9)

set(MATRIX_STRUCTS_URL https://github.com/mujx/matrix-structs)
set(MATRIX_STRUCTS_TAG 8de04afea34e95c14d1dde82af390592dfde90dd)

set(MTXCLIENT_URL https://github.com/mujx/mtxclient)
set(MTXCLIENT_TAG 2f519d28b4521f7f234b2ed0f32360cbb1edd2f7)

set(TWEENY_URL https://github.com/mobius3/tweeny)
set(TWEENY_TAG b94ce07cfb02a0eb8ac8aaf66137dabdaea857cf)

set(
  LMDBXX_HEADER_URL
  https://raw.githubusercontent.com/bendiken/lmdbxx/0b43ca87d8cfabba392dfe884eb1edb83874de02/lmdb%2B%2B.h
  )
set(LMDBXX_SHA c57b501a4e8fa1187fa7fd348da415c7685a50a7cb25b17b3f257b9e9426f73d)

set(OLM_URL https://git.matrix.org/git/olm.git)
set(OLM_TAG 4065c8e11a33ba41133a086ed3de4da94dcb6bae)

set(SPDLOG_URL https://github.com/gabime/spdlog)
set(SPDLOG_TAG 560df2878ad308b27873b3cc5e810635d69cfad6)

if(USE_BUNDLED_BOOST)
  include(Boost)
endif()

if(USE_BUNDLED_SPDLOG)
  include(SpdLog)
endif()

if(USE_BUNDLED_OLM)
  include(Olm)
endif()

if(USE_BUNDLED_MATRIX_STRUCTS)
  include(MatrixStructs)
endif()

if(USE_BUNDLED_TWEENY)
  include(Tweeny)
endif()

if(USE_BUNDLED_LMDBXX)
  file(DOWNLOAD ${LMDBXX_HEADER_URL} ${DEPS_INSTALL_DIR}/include/lmdb++.h
       EXPECTED_HASH SHA256=${LMDBXX_SHA})
endif()

if(WIN32)
  if("${TARGET_ARCH}" STREQUAL "X86_64")
    set(TARGET_ARCH x64)
  elseif(TARGET_ARCH STREQUAL "X86")
    set(TARGET_ARCH ia32)
  endif()
endif()

add_custom_target(third-party ALL
                  COMMAND ${CMAKE_COMMAND} -E touch .third-party
                  DEPENDS ${THIRD_PARTY_DEPS})

if(USE_BUNDLED_MATRIX_CLIENT)
  include(MatrixClient)
  add_dependencies(MatrixClient third-party)
endif()
