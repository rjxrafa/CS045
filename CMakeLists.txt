cmake_minimum_required(VERSION 3.13)
project(CS045)

set(CMAKE_CXX_STANDARD 14)

# includes
include_directories(sieve_of_eratosthenes)
include_directories(video_poker)


# find libraries
find_package(Curses REQUIRED)

# set user variables
set(SOURCES     sieve_of_eratosthenes/sieve.cpp
                sets/sets.cpp
                prime_decomposition/prime_decomposition.cpp
                video_poker/poker.cpp)

set(INCLUDES    sieve_of_eratosthenes/sieve.h
                sets/sets.h
                prime_decomposition/prime_decomposition.h
                video_poker/poker.h)

if(MINGW)
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} -static-libstdc++)
endif()


add_executable(CS045    main.cpp
                        ${SOURCES}
                        ${INCLUDES})

# add libraries
target_link_libraries(CS045 ${CURSES_LIBRARIES})