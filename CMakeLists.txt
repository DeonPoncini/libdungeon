cmake_minimum_required(VERSION 2.6)     
project(libdungeon)                           
                                        
################################        
# Compiler setup                        
################################        
                                        
add_definitions(-Wall)                  
                                        
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 
                                        
################################        
# Locate source                         
################################        
file(GLOB_RECURSE INCLUDES include/*.h) 
file(GLOB_RECURSE SRC src/*.cpp)        
                                        
include_directories(include)            
                                        
################################        
# Build targets                         
################################        
                                        
add_executable(libdungeon
    ${SRC}                              
    ${INCLUDES})                        
