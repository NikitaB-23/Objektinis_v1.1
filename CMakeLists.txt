cmake_minimum_required(VERSION 3.10)
project(StudentuPrograma CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(programa
    main.cpp
    Studentas.cpp
    Failai.cpp
    Rikiavimas.cpp
    Tyrimai.cpp
    Meniu.cpp
    StrategijosVector.cpp
    StrategijosList.cpp
)