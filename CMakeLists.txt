cmake_minimum_required(VERSION 3.10)
project(netsim)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
 source/main.cpp
 source/Router.cpp
 source/Simulation.cpp
 source/Host.cpp
 source/Packet.cpp
 source/Layers.cpp
)

add_executable(
	netsim.out ${SOURCE_FILES}
)
