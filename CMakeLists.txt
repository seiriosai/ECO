cmake_minimum_required(VERSION 3.10.0)

project(eco)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fsee -fomit-frame-pointer -fno-signed-zeros -fno-math-errno -funroll-loops")

find_package(Eigen3 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(fftw3 REQUIRED)

include_directories(
    include
    include/feat_extra
    include/implements
    ${EIGEN3_INCLUDE_DIR}
    ${OpenCV_INCLUDE_DIRS}
    ${FFTW3_INCLUDE_DIRS}
)

link_directories(
    ${FFTW3_LIBRARY_DIRS}
    ${OpenCV_LIBRARY_DIRS}
)

list(APPEND ECO_SOURCE_FILES
    src/config.cpp
    src/matlab_func.cpp
    src/feat_extra/fhog.cpp
    src/feat_extra/cnf.cpp

    src/implements/tracker.cpp
    src/implements/train.cpp
    src/implements/scale_filter.cpp
    src/implements/sample_space.cpp
)

add_library(eco ${ECO_SOURCE_FILES})

option(BUILD_WITH_TEST "build with test program" ON)

if(BUILD_WITH_TEST)
    list(APPEND ECO_DEP_LIBS 
        eco
        ${OpenCV_LIBRARIES}
        ${FFTW3_LIBRARIES}
    )

    add_executable(func_test func_test.cpp)       
    target_link_libraries(func_test ${ECO_DEP_LIBS})

    add_executable(eco_main main.cpp)       
    target_link_libraries(eco_main ${ECO_DEP_LIBS})

    add_executable(vot100_test vot100_test.cpp)       
    target_link_libraries(vot100_test ${ECO_DEP_LIBS})

    add_executable(video_test test_720p.cpp)       
    target_link_libraries(video_test ${ECO_DEP_LIBS})
endif()
