﻿# CMakeList.txt: libCPPTable에 대한 CMake 프로젝트, 여기에 소스를 포함하고
# 프로젝트 특정 논리를 정의합니다.
#

# 이 프로젝트의 실행 파일에 소스를 추가합니다.
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src CPPTABLE_SRC_FILES)

add_library (libCPPTable ${CPPTABLE_SRC_FILES} "./inc/CPPTable.h")
target_include_directories(libCPPTable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET libCPPTable PROPERTY CXX_STANDARD 20)
endif()

# TODO: 필요한 경우 테스트를 추가하고 대상을 설치합니다.
