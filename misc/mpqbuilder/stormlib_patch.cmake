# This file is used to patch StormLib's CMakeLists.txt to use our libtomcrypt_alloc library
# It will be included by StormLib's CMakeLists.txt

# Add our libtomcrypt_alloc library to StormLib's target_link_libraries
target_link_libraries(storm libtomcrypt_alloc)