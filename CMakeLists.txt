cmake_minimum_required(VERSION 3.16)
project(HTTPInterceptor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === Headers ===
include_directories(include)

# === Sources principales ===
set(SOURCES
    src/main.cpp
    src/ProxyServer.cpp
    src/Router.cpp
    src/HttpClient.cpp
    src/Interceptor.cpp
    src/Logger.cpp
    src/Utils.cpp
)

# --- Exécutable principal ---
add_executable(http-interceptor ${SOURCES})

# === Tests ===
enable_testing()

# Intégration Catch2 (FetchContent pour portabilité)
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

# === Fichiers de tests unitaires ===
set(TEST_SOURCES
    tests/test_main.cpp  # Contient CATCH_CONFIG_MAIN
    tests/utils/test_isValidUrl.cpp
    tests/utils/test_extractHostFromUrl.cpp
    tests/HttpClient/test_sendRequest.cpp
)

add_executable(unit_tests
    ${TEST_SOURCES}
    src/ProxyServer.cpp
    src/Router.cpp
    src/HttpClient.cpp
    src/Interceptor.cpp
    src/Logger.cpp
    src/Utils.cpp
)

target_include_directories(unit_tests PRIVATE include)
target_link_libraries(unit_tests
    PRIVATE
        Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(unit_tests)
