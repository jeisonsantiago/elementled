project(app VERSION 0.0.1)

#get all cpp files
set(SRC_FILES
    src/App.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

# link libraries (engine library)
target_link_libraries(${PROJECT_NAME} core)
# include directories
include_directories(${CMAKE_SOURCE_DIR}/core/src)

# add include directories
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
