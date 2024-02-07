cmake_minimum_required(VERSION 3.10)

project(Combi)

set(SOURCES
    main.cpp
)

set(HEADERS
    subset.h
    combination.h
    permutation.h
    accomodation.h
    salesman.h
)

add_executable(Combi ${SOURCES} ${HEADERS})