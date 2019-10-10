include_directories(../src)

include_directories(.)

add_executable(tests
    # test sources
    int_stack_test.cpp
    stack_machine_test.cpp
    # task sources
    ../src/int_stack.cpp
    ../src/int_stack.h
    ../src/stack_machine.cpp
    ../src/stack_machine.h
    # gtest sources
    gtest/gtest-all.cc
    gtest/gtest_main.cc
)

# add pthread for unix systems
if (UNIX)
    target_link_libraries(tests pthread)
endif ()