cmake_minimum_required(VERSION 3.20)
project(miniBankApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(minibank
    main.cpp
    src/user.cpp
    src/account.cpp
    src/transaction.cpp
    src/bankdb.cpp
    src/session_manager.cpp
    src/user_auth.cpp
)

target_include_directories(minibank PRIVATE include)
