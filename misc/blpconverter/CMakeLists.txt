cmake_minimum_required (VERSION 3.22)

# Set CMake policies to handle compatibility issues
if(POLICY CMP0144)
  cmake_policy(SET CMP0144 OLD)
endif()
if(POLICY CMP0167)
  cmake_policy(SET CMP0167 OLD)
endif()
if(POLICY CMP0169)
  cmake_policy(SET CMP0169 OLD)
endif()

project (BLPConverter)
file(GLOB_RECURSE sources *.cpp *.hpp *.c *.h)
add_executable (blpconverter main.cpp ${sources})
set_target_properties(blpconverter PROPERTIES CXX_STANDARD 17)
target_include_directories(blpconverter PUBLIC
	blp2png
	png2blp
	include/libimagequant
	include/libpng
	include/libtxc_dxtn
	include/pngpp
	include/zlib
	include/thread_pool
)

# Add macOS-specific configurations
if(APPLE)
  # Ensure compatibility with macOS
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
  set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum macOS deployment version")
endif()

if(UNIX)
	set(THREADS_PREFER_PTHREAD_FLAG ON)
	find_package(Threads REQUIRED)
	target_link_libraries(blpconverter PRIVATE Threads::Threads)
endif()
