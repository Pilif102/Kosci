cmake_minimum_required(VERSION 3.5)

project(ServerKosci LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ServerKosci main.cpp

    poczekalnia.h poczekalnia.cpp
    struktury.h
    playermanager.h playermanager.cpp
    gamemanager.h gamemanager.cpp
    pointscount.h pointscount.cpp)

include(GNUInstallDirs)
install(TARGETS ServerKosci
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
