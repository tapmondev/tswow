cmake_minimum_required(VERSION 3.22)

# Set CMake policies to handle Boost properly
if(POLICY CMP0144)
  cmake_policy(SET CMP0144 OLD)
endif()
if(POLICY CMP0167)
  cmake_policy(SET CMP0167 OLD)
endif()
if(POLICY CMP0169)
  cmake_policy(SET CMP0169 OLD)
endif()

# Set minimum policy version for StormLib
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

project(mpqbuilder)

# Boost configuration
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_NO_SYSTEM_PATHS OFF)
set(Boost_NO_BOOST_CMAKE ON)  # Force using FindBoost.cmake instead of BoostConfig.cmake

# MacPorts Boost path
if(APPLE)
  # Use MacPorts Boost installation
  set(BOOST_ROOT "/opt/local/libexec/boost/1.81")
  set(Boost_INCLUDE_DIR "/opt/local/libexec/boost/1.81/include")
  set(Boost_LIBRARY_DIR "/opt/local/libexec/boost/1.81/lib")
  message(STATUS "Using MacPorts Boost at ${BOOST_ROOT}")
  
  # Add MacPorts include and library paths
  include_directories("/opt/local/libexec/boost/1.81/include")
  link_directories("/opt/local/libexec/boost/1.81/lib")
endif()

find_package(Boost 1.60 COMPONENTS filesystem REQUIRED)
add_executable(mpqbuilder mpqbuilder.cpp)
add_executable(luaxmlreader luaxmlreader.cpp)

include (FetchContent)
FetchContent_Declare(
  storm
  GIT_REPOSITORY https://github.com/ladislav-zezula/StormLib.git
  GIT_TAG 60c2dd0fa16d3506722e25fee9b6fa4082b0c1e5
)
FetchContent_GetProperties (storm)
if (NOT storm_POPULATED)
  message (STATUS "Installing StormLib...")
  FetchContent_Populate (storm)
endif()

# Configure StormLib to not use TomCrypt
set(STORMLIB_USE_LIBTOMCRYPT OFF CACHE BOOL "Use LibTomCrypt" FORCE)
# Use our custom memory allocation functions instead
set(STORMLIB_MALLOC "LibTomMalloc" CACHE STRING "Memory allocation function" FORCE)
set(STORMLIB_FREE "LibTomFree" CACHE STRING "Memory deallocation function" FORCE)
set(STORMLIB_USE_LIBTOMCRYPT OFF CACHE BOOL "Use LibTomCrypt" FORCE)
set(STORMLIB_USE_LIBTOMCRYPT OFF CACHE BOOL "Use LibTomCrypt" FORCE)
set(STORMLIB_USE_LZMA OFF CACHE BOOL "Use LZMA" FORCE)
set(STORMLIB_USE_ZLIB OFF CACHE BOOL "Use ZLIB" FORCE)
set(STORMLIB_USE_LIBTOMCRYPT OFF CACHE BOOL "Use LibTomCrypt" FORCE)

# Configure StormLib to include our patch
file(WRITE ${storm_SOURCE_DIR}/stormlib_patch.cmake "include(\"${CMAKE_CURRENT_SOURCE_DIR}/stormlib_patch.cmake\")")

# Copy our patch files to the StormLib source directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libtomcrypt_alloc.h ${storm_SOURCE_DIR}/src/libtomcrypt/src/headers/libtomcrypt_alloc.h COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tomcrypt_custom_patch.h ${storm_SOURCE_DIR}/src/libtomcrypt/src/headers/tomcrypt_custom_patch.h COPYONLY)

# Add include directory for StormLib
include_directories(${storm_SOURCE_DIR}/src/libtomcrypt/src/headers)

# Patch StormLib's tomcrypt_custom.h to include our patch
file(READ ${storm_SOURCE_DIR}/src/libtomcrypt/src/headers/tomcrypt_custom.h TOMCRYPT_CUSTOM_H)
if(NOT TOMCRYPT_CUSTOM_H MATCHES "tomcrypt_custom_patch.h")
  file(WRITE ${storm_SOURCE_DIR}/src/libtomcrypt/src/headers/tomcrypt_custom.h.new "#include \"tomcrypt_custom_patch.h\"\n${TOMCRYPT_CUSTOM_H}")
  file(RENAME ${storm_SOURCE_DIR}/src/libtomcrypt/src/headers/tomcrypt_custom.h.new ${storm_SOURCE_DIR}/src/libtomcrypt/src/headers/tomcrypt_custom.h)
endif()

# Create the libtomcrypt_alloc library
add_library(libtomcrypt_alloc STATIC libtomcrypt_alloc.c)

# Add macOS-specific configurations
if(APPLE)
  # Ensure compatibility with macOS
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
  set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum macOS deployment version")
endif()

# Make LibTomMalloc and LibTomFree available to StormLib
add_definitions(-DLIBTOMCRYPT_EXPORTS)



# Create a custom target to modify StormLib's CMakeLists.txt to include our libtomcrypt_alloc
add_custom_target(patch_stormlib ALL
  COMMAND ${CMAKE_COMMAND} -E echo "Patching StormLib to use our libtomcrypt_alloc"
)

add_subdirectory (${storm_SOURCE_DIR} ${storm_BINARY_DIR} EXCLUDE_FROM_ALL)
set (storm_warning_disable_flags "")

TARGET_LINK_LIBRARIES(mpqbuilder
  Boost::filesystem
  storm
  libtomcrypt_alloc
)
TARGET_LINK_LIBRARIES(luaxmlreader
  Boost::filesystem
  storm
  libtomcrypt_alloc
)
