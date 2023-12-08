set (TARGET_NAME LearnOpenGL)
project( ${TARGET_NAME} )
# load files
FILE( GLOB Core_files "Core/*.cpp" "Core/*.h")
FILE( GLOB Test_files "Tools/*.cpp" "Tools/*.h")
FILE( GLOB Glad_files "Glad/*.c")
# group files
source_group( "Core" FILES ${Core_files} ) 
source_group( "Tools" FILES ${Test_files} ) 
source_group( "Glad" FILES ${Glad_files} ) 
# create exe
ADD_EXECUTABLE(${TARGET_NAME} ${Core_files} ${Test_files} ${Glad_files})
# set output dir
set_target_properties( ${TARGET_NAME} PROPERTIES 
						RUNTIME_OUTPUT_DIRECTORY_DEBUG  ${CMAKE_CURRENT_BINARY_DIR}/bin
						RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/bin)

# set include
target_include_directories(${TARGET_NAME} PUBLIC 
						${CMAKE_SOURCE_DIR}/Source 
						${CMAKE_SOURCE_DIR}/Source/ThirdParty/glfw3/include 
						${CMAKE_SOURCE_DIR}/Source/ThirdParty/glad/include)
# set link
target_link_libraries( ${TARGET_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Source/ThirdParty/glfw3/lib/glfw3.lib opengl32.lib)
# copy resource
add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/bin $<TARGET_FILE_DIR:${TARGET_NAME}>)