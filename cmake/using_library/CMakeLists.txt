cmake_minimum_required(VERSION 3.21) #cmake 최소버전
project(hello_world VERSION 1.0.0) #프로젝트 이름, 버전

add_library(
    say-hello  #라이브러리 이름
    hello.hpp  #라이브러리로 만들 소스파일
    hello.cpp
) #라이브러리 생성

add_executable(hello_world main.cpp) #실행파일 이름, 빌드할 파일명

target_link_libraries(hello_world PUBLIC say-hello) #실행파일에 라이브러리 연결