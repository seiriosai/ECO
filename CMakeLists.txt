cmake_minimum_required(VERSION 3.10.0)

project(eco)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fsee -fomit-frame-pointer -fno-signed-zeros -fno-math-errno -funroll-loops -lm")
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/CMakeModules/")
FIND_PACKAGE(Eigen3 REQUIRED PATHS "../../build/install/share/eigen3/cmake")
FIND_PACKAGE(OpenCV REQUIRED)
FIND_PACKAGE(fftw3 REQUIRED PATHS "../../build/install/lib/cmake/fftw3/" NO_DEFAULT_PATH)

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

add_library(IMP_SRC
        src/config.cpp
        src/matlab_func.cpp
        src/feat_extra/fhog.cpp
        src/feat_extra/cnf.cpp

        src/implements/tracker.cpp
        src/implements/train.cpp
        src/implements/scale_filter.cpp
        src/implements/sample_space.cpp
		)

list(APPEND THIRD_PARTY_LIBS 
    IMP_SRC
    ${OpenCV_LIBRARIES}
    ${FFTW3_LIBRARIES}
    m
)
add_executable(func_test func_test.cpp)       
target_link_libraries(func_test IMP_SRC
                    ${THIRD_PARTY_LIBS}
                    )

add_executable(eco main.cpp)       
target_link_libraries(eco 
                    IMP_SRC
                    ${OpenCV_LIBRARIES}
                    ${FFTW3_LIBRARIES}
                    m
                    )

add_executable(vot100_test vot100_test.cpp)       
target_link_libraries(vot100_test 
                    IMP_SRC
                    
                    m
                    )

add_executable(video_test test_720p.cpp)       
target_link_libraries(video_test 
                    IMP_SRC
                    ${OpenCV_LIBRARIES}
                    ${FFTW3_LIBRARIES}
                    m
                    )
