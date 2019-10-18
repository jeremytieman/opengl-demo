set(HEADER_FILES ../include/glad/glad.h ../include/init.h ../include/math.h)
set(SOURCE_FILES Main.cpp glad.c init.cpp math.cpp)

add_executable(Demo ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(Demo PUBLIC ${PROJECT_BINARY_DIR}/glfw-src/include/)
target_include_directories(Demo PUBLIC ../include/)
target_link_libraries(Demo PUBLIC glfw)
set_target_properties(Demo PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/)