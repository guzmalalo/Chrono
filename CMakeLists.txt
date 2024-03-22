cmake_minimum_required(VERSION 3.27)
project(Chrono C)

set(CMAKE_C_STANDARD 11)

add_executable(Chrono main.c
        button.c
        button.h)

IF(WIN32)
    target_link_libraries(Chrono -lmingw32 -lallegro-5.0.10-monolith-md-debug)
ELSE()
    INCLUDE_DIRECTORIES(/usr/local/Cellar/allegro/5.2.9.1/include)
    LINK_DIRECTORIES(/usr/local/Cellar/allegro/5.2.9.1/lib)
    file(GLOB LIBRARIES "/usr/local/Cellar/allegro/5.2.9.1/lib/*.dylib")
    message("LIBRARIES = ${LIBRARIES}")
    TARGET_LINK_LIBRARIES(Chrono ${LIBRARIES})
ENDIF(WIN32)