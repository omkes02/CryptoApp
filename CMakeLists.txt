cmake_minimum_required(VERSION 3.14)
project(CryptoSW-App2 LANGUAGES CXX)

# 1. Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Finds and links Qt6 Widgets
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Automatically handle MOC, UIC, and RCC for Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 8. Automatically include all source files in the project
file(GLOB_RECURSE APP_SOURCES 
    "src/*.cpp" 
    "src/*.h" 
    "src/*.ui"
)
file(GLOB_RECURSE CRYPTOPP_SOURCES 
    "cryptopp/include/*.cpp"
)
list(REMOVE_ITEM CRYPTOPP_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/test.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/validat0.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/validat1.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/validat2.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/validat3.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/validat4.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/validat5.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/validat6.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/validat7.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/validat8.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/validat9.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/validat10.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/regtest1.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/regtest2.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/regtest3.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/regtest4.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/bench1.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/bench2.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/bench3.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/datatest.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/dlltest.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/fipstest.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include/adhoc.cpp"
)

# Define the executable target and its source files
qt6_add_executable(CryptoSW-App2
    main.cpp
    ${APP_SOURCES}
    ${CRYPTOPP_SOURCES}
)

# 3. Include the Crypto++ headers from cryptopp/include
target_include_directories(CryptoSW-App2 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/cryptopp/include
)

# 5. Disable Crypto++ assembly optimizations
target_compile_definitions(CryptoSW-App2 
    PRIVATE 
        CRYPTOPP_DISABLE_ASM=ON
)

# 4. Link against Qt6 and your prebuilt libcryptopp.a
target_link_libraries(CryptoSW-App2
    PRIVATE
        Qt6::Widgets
)

# 6. Set the output executable to the build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Optional: Add install rule for deployment
install(TARGETS CryptoSW-App2 DESTINATION bin)
