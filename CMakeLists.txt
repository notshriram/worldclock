cmake_minimum_required (VERSION 3.11)
 
# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)
 
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  # Important: Specify a GIT_TAG XXXXX here.
  GIT_TAG v5.0.0
)
 
FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
 
# ------------------------------------------------------------------------------
 
project(worldclock
  LANGUAGES CXX
  VERSION 0.0.0
)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include)
 
target_link_libraries(${PROJECT_NAME}
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)