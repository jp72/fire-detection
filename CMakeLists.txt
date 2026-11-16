cmake_minimum_required(VERSION 3.16)
project(fire LANGUAGES CXX)

find_package(OpenCV 4 REQUIRED COMPONENTS core imgproc imgcodecs)

add_library(fire_detectors detectors.cpp)
target_compile_features(fire_detectors PUBLIC cxx_std_11)
target_include_directories(fire_detectors PUBLIC ${OpenCV_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(fire_detectors PUBLIC ${OpenCV_LIBS})

add_executable(fire main.cpp)
target_link_libraries(fire PRIVATE fire_detectors)

include(CTest)
if(BUILD_TESTING)
    add_executable(detector_tests detector_tests.cpp)
    target_link_libraries(detector_tests PRIVATE fire_detectors)
    add_test(NAME detectors COMMAND detector_tests)
    add_test(NAME cli_help COMMAND fire --help)
    add_test(NAME cli_missing_arguments COMMAND fire)
    set_tests_properties(cli_missing_arguments PROPERTIES WILL_FAIL TRUE)
    add_test(NAME cli_invalid_method COMMAND fire unused.png --method unknown)
    set_tests_properties(cli_invalid_method PROPERTIES WILL_FAIL TRUE)
endif()
