cmake_minimum_required(VERSION 3.8)

project("HeadingIndicatorExample")

# Enable Hot Reload for MSVC
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT 
      "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CMAKE_CXX_STANDARD 20)

# Use vcpkg dependencies
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(HeadingIndicatorExample 
    main.cpp 
    HeadingIndicator.cpp 
    HeadingIndicator.h
 "Constants.h")

target_link_libraries(HeadingIndicatorExample PRIVATE
    OpenGL::GL
    glfw
    GLEW::GLEW
    glm::glm-header-only
    imgui::imgui
)
