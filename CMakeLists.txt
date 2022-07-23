cmake_minimum_required(VERSION 3.20.0)
project(algo-analysis)

set(SOURCE
        tree/AVLTree.cpp
        tree/BinarySearchTree.cpp
        )

find_package(GTest CONFIG REQUIRED)

set(IDX 0)
foreach (FILE ${SOURCE})
    math(EXPR IDX "${IDX}+1")
    set(EXECUTABLE_NAME al-${IDX})
    add_executable(${EXECUTABLE_NAME} ${FILE})
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
endforeach ()