add_executable(tests tests.cpp)
target_link_libraries(tests
    PUBLIC
        numcmc::numcmc
)
add_executable(example-0 example-0/example.cpp)
target_link_libraries(example-0
    PUBLIC
        numcmc::numcmc
)
add_executable(example-1 example-1/example.cpp)
target_link_libraries(example-1
    PUBLIC
        numcmc::numcmc
)
add_executable(example-2 example-2/example.cpp)
target_link_libraries(example-2
    PUBLIC
        numcmc::numcmc
)
add_executable(example-3 example-3/example.cpp)
target_link_libraries(example-3
    PUBLIC
        numcmc::numcmc
)
add_executable(example-4 example-4/example.cpp)
target_link_libraries(example-4
    PUBLIC
        numcmc::numcmc
)
add_executable(example-5 example-5/example.cpp)
target_link_libraries(example-5
    PUBLIC
        numcmc::numcmc
)

