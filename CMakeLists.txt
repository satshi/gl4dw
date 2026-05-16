cmake_minimum_required(VERSION 3.20)

project(gl4dw LANGUAGES CXX)

option(GL4DW_BUILD_VIEWER "Build the GLUT/OpenGL viewer" ON)
option(GL4DW_BUILD_SMOKE_TEST "Build a tiny compile/link smoke test" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
  add_compile_options(/utf-8)
endif()

include(CTest)

find_package(nlohmann_json CONFIG REQUIRED)

add_library(gl4dw_core STATIC
  src/cell.cpp
  src/cells.cpp
  src/dirutil.cpp
  src/inter.cpp
  src/p_cell.cpp
  src/pgen.cpp
  src/points.cpp
  src/polytope.cpp
  src/proj.cpp
  src/Vector.cpp
  src/vector3.cpp
)

target_include_directories(gl4dw_core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

if(MSVC)
  target_compile_definitions(gl4dw_core PRIVATE _CRT_SECURE_NO_WARNINGS)
  target_compile_options(gl4dw_core PRIVATE /permissive- /W3)
endif()

if(GL4DW_BUILD_SMOKE_TEST)
  add_executable(gl4dw_smoke tests/smoke_test.cpp)
  target_link_libraries(gl4dw_smoke PRIVATE gl4dw_core)
  if(BUILD_TESTING)
    add_test(NAME gl4dw_smoke COMMAND gl4dw_smoke)
  endif()

  add_executable(gl4dw_config_smoke
    tests/config_smoke.cpp
    src/readp.cpp
  )
  target_include_directories(gl4dw_config_smoke PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
  target_link_libraries(gl4dw_config_smoke PRIVATE nlohmann_json::nlohmann_json)
  if(BUILD_TESTING)
    add_test(NAME gl4dw_config_smoke COMMAND gl4dw_config_smoke)
  endif()
endif()

if(GL4DW_BUILD_VIEWER)
  find_package(OpenGL REQUIRED)
  find_package(GLUT QUIET)

  if(GLUT_FOUND)
    if(GL4DW_BUILD_SMOKE_TEST)
      add_executable(gl4dw_data_smoke
        tests/data_smoke.cpp
        src/gl4d.cpp
      )
      target_link_libraries(gl4dw_data_smoke PRIVATE gl4dw_core OpenGL::GL OpenGL::GLU GLUT::GLUT)
      if(BUILD_TESTING)
        add_test(NAME gl4dw_data_smoke COMMAND gl4dw_data_smoke)
        set_tests_properties(gl4dw_data_smoke PROPERTIES
          WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        )
      endif()
      add_executable(gl4dw_data_validation
        tests/data_validation.cpp
        src/gl4d.cpp
      )
      target_link_libraries(gl4dw_data_validation PRIVATE gl4dw_core OpenGL::GL OpenGL::GLU GLUT::GLUT)
      if(BUILD_TESTING)
        add_test(NAME gl4dw_data_validation COMMAND gl4dw_data_validation)
        set_tests_properties(gl4dw_data_validation PROPERTIES
          WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        )
      endif()
      add_executable(gl4dw_readpolytope_failure
        tests/readpolytope_failure.cpp
        src/gl4d.cpp
      )
      target_link_libraries(gl4dw_readpolytope_failure PRIVATE gl4dw_core OpenGL::GL OpenGL::GLU GLUT::GLUT)
      if(BUILD_TESTING)
        add_test(NAME gl4dw_readpolytope_failure COMMAND gl4dw_readpolytope_failure)
      endif()
      if(MSVC)
        target_compile_definitions(gl4dw_data_smoke PRIVATE _CRT_SECURE_NO_WARNINGS)
        target_compile_options(gl4dw_data_smoke PRIVATE /permissive- /W3)
        target_compile_definitions(gl4dw_data_validation PRIVATE _CRT_SECURE_NO_WARNINGS)
        target_compile_options(gl4dw_data_validation PRIVATE /permissive- /W3)
        target_compile_definitions(gl4dw_readpolytope_failure PRIVATE _CRT_SECURE_NO_WARNINGS)
        target_compile_options(gl4dw_readpolytope_failure PRIVATE /permissive- /W3)
      endif()
    endif()

    add_executable(gl4dw
      src/gl4d.cpp
      src/glevent.cpp
      src/glmain.cpp
      src/readp.cpp
    )
    target_link_libraries(gl4dw PRIVATE gl4dw_core OpenGL::GL OpenGL::GLU GLUT::GLUT nlohmann_json::nlohmann_json)
    if(MSVC)
      target_compile_definitions(gl4dw PRIVATE _CRT_SECURE_NO_WARNINGS)
      target_compile_options(gl4dw PRIVATE /permissive- /W3)
    endif()
  else()
    message(WARNING "GLUT/freeglut was not found. The gl4dw viewer target will be skipped; gl4dw_core still builds.")
  endif()
endif()
