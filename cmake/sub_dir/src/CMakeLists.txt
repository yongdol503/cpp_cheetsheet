add_library(
    say-hello
    hello.hpp
    hello.cpp
) #라이브러리 생성

target_include_directories(say-hello PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}") #라이브러리 연결