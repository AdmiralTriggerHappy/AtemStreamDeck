cmake_minimum_required(VERSION 3.15)

# CMAKE_MSVC_RUNTIME_POLICY support
cmake_policy(SET CMP0091 NEW)
# Statically link the MSVC runtime
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
SET(SWITCHERS_SDK_INCLUDE "include/BMDSwitcherAPI_i.cpp")
SET(ATEMCONTROL_INCLUDE "include/AtemControl.cpp")
add_library(ATEMControl ${SWITCHERS_SDK_INCLUDE})
add_library(BMDSwitcherAPI ${ATEMCONTROL_INCLUDE})

set(windows_common_link_options
      comsuppw.lib
    )

project(
  com.admiraltriggerhappy.atemcontrol
  VERSION 0.0.1
  LANGUAGES CXX
)

include("StreamDeckSDK.cmake")

if (MSVC)
  add_definitions("/Zc:__cplusplus -DUNICODE=1")
endif()

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(
    CMAKE_INSTALL_PREFIX
    "${STREAMDECK_PLUGIN_DIR}/${CMAKE_PROJECT_NAME}"
    CACHE PATH "..." FORCE
  )
endif()
message(STATUS "Install dir: ${CMAKE_INSTALL_PREFIX}")

add_executable(atemplugin AtemCut.cpp main.cpp)
set_target_properties(
  atemplugin
  PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)

#add_dependencies(atemplugin AtemControl)

#TARGET_INCLUDE_DIRECTORIES(atemplugin  PRIVATE ${SWITCHERS_SDK_INCLUDE_DIR})
target_link_libraries(atemplugin  ${windows_common_link_options} ATEMControl BMDSwitcherAPI StreamDeckSDK)
install(TARGETS atemplugin DESTINATION ${CMAKE_INSTALL_PREFIX})

# If doing a Debug or RelWithDebInfo build, install the debug symbols too
# On MacOS, these are part of the executable
if(WIN32)
  install(FILES "$<TARGET_PDB_FILE:atemplugin>" DESTINATION ${CMAKE_INSTALL_PREFIX} OPTIONAL)
endif()

install(FILES manifest.json DESTINATION ${CMAKE_INSTALL_PREFIX})
