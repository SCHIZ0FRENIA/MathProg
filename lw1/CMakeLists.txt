cmake_minimum_required(VERSION 3.10)

project(Auxil)

set(SOURCES
    Auxil.cpp
)

set(HEADERS
    Auxil.h
)

add_executable(Auxil ${SOURCES} ${HEADERS})