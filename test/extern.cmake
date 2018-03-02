cmake_minimum_required(VERSION 2.8.2)

project(ryml-extern-download NONE)

include(ExternalProject)

ExternalProject_Add(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG master
    SOURCE_DIR "${RYML_EXT_DIR}/googletest-src"
    BINARY_DIR "${RYML_EXT_DIR}/googletest-build"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)

ExternalProject_Add(libyaml
    GIT_REPOSITORY https://github.com/yaml/libyaml
    GIT_TAG master
    SOURCE_DIR "${RYML_EXT_DIR}/libyaml-src"
    BINARY_DIR "${RYML_EXT_DIR}/libyaml-build"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)

ExternalProject_Add(yaml-cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp
    GIT_TAG master
    SOURCE_DIR "${RYML_EXT_DIR}/yaml-cpp-src"
    BINARY_DIR "${RYML_EXT_DIR}/yaml-cpp-build"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)
