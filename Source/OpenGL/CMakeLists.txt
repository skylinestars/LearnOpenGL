
FILE( GLOB Core_files "Core/*.cpp" "Core/*.h")
FILE( GLOB Test_files "Test/*.cpp" "Test/*.h")
FILE( GLOB Glad_files "Glad/*.c")

source_group( "Core" FILES ${Core_files} ) 
source_group( "Test" FILES ${Test_files} ) 
source_group( "Glad" FILES ${Glad_files} ) 

ADD_EXECUTABLE(LearnOpenGL ${Core_files} ${Test_files} ${Glad_files})

target_include_directories(LearnOpenGL PUBLIC 
						${CMAKE_SOURCE_DIR}/Source 
						${CMAKE_SOURCE_DIR}/Source/ThirdParty/glfw3/include 
						${CMAKE_SOURCE_DIR}/Source/ThirdParty/glad/include)

target_link_libraries( LearnOpenGL PUBLIC ${CMAKE_SOURCE_DIR}/Source/ThirdParty/glfw3/lib/glfw3.lib opengl32.lib)