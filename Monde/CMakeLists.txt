# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

# Activez Rechargement à chaud pour les compilateurs MSVC si cela est pris en charge.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(PROJECT_NAME monde)

project(${PROJECT_NAME})

find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glew CONFIG REQUIRED)


include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_executable(
	${PROJECT_NAME}
	source/main.cpp
	source/Window.cpp
	source/ShaderReader.cpp
	source/Primitives/Triangle.cpp
	source/Vector3.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm glfw opengl32.lib imgui::imgui GLEW::glew)