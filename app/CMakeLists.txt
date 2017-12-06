cmake_minimum_required(VERSION 3.4.1)
project( LateralView )

include_directories( libs )

add_library( native-lib SHARED src/main/cpp/native-lib.cpp )

add_library( renderer STATIC src/main/cpp/renderer.cpp )

add_library( utilities STATIC
src/main/cpp/asset.cpp
src/main/cpp/chapa/utilities.cpp
src/main/cpp/chapa/shader.cpp
src/main/cpp/utils/lodepng.cpp )

add_library( graphics STATIC
src/main/cpp/chapa/graphics.cpp
src/main/cpp/chapa/transform.cpp
src/main/cpp/chapa/mat4.cpp
src/main/cpp/chapa/mat3.cpp
src/main/cpp/chapa/vec4.cpp
src/main/cpp/chapa/vec3.cpp )

target_link_libraries( native-lib android renderer utilities )
target_link_libraries( renderer log GLESv2 utilities graphics )
target_link_libraries( utilities log GLESv2 )



