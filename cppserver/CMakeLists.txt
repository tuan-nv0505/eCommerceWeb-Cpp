cmake_minimum_required(VERSION 3.16)
project(cppserver CXX)

include(CheckIncludeFileCXX)

check_include_file_cxx(any HAS_ANY)
check_include_file_cxx(string_view HAS_STRING_VIEW)
check_include_file_cxx(coroutine HAS_COROUTINE)

add_compile_definitions(_LIBCPP_ENABLE_CXX20_REMOVED_FEATURES)
add_compile_options("-Wno-deprecated-declarations")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} main.cc)

find_package(Drogon CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)
find_package(OpenSSL CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)
target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::Crypto)


if (CMAKE_CXX_STANDARD LESS 17)
    message(FATAL_ERROR "c++17 or higher is required")
elseif (CMAKE_CXX_STANDARD LESS 20)
    message(STATUS "use c++17")
else ()
    message(STATUS "use c++20 Coroutine Enabled!")
endif ()

aux_source_directory(controllers CTL_SRC)
aux_source_directory(filters FILTER_SRC)
aux_source_directory(plugins PLUGIN_SRC)
aux_source_directory(models MODEL_SRC)
aux_source_directory(services SERVICES_SRC)
aux_source_directory(repositories REPOSITORIES_SRC)
aux_source_directory(app_configs APPLICATION_CONTEXT_SRC)
aux_source_directory(utils UTILS_SRC)
aux_source_directory(dto DTO_SRC)
aux_source_directory(validations VALIDATIONS_SRC)

drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
        ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(${PROJECT_NAME}
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/app_configs
        ${CMAKE_CURRENT_SOURCE_DIR}/models
        ${CMAKE_CURRENT_SOURCE_DIR}/services
        ${CMAKE_CURRENT_SOURCE_DIR}/repositories
        ${CMAKE_CURRENT_SOURCE_DIR}/paginators
        ${CMAKE_CURRENT_SOURCE_DIR}/dto
        ${CMAKE_CURRENT_SOURCE_DIR}/exception
        ${CMAKE_CURRENT_SOURCE_DIR}/utils
        ${CMAKE_CURRENT_SOURCE_DIR}/validations
)

target_sources(${PROJECT_NAME}
        PRIVATE
        ${SRC_DIR}
        ${CTL_SRC}
        ${FILTER_SRC}
        ${PLUGIN_SRC}
        ${MODEL_SRC}
        ${APPLICATION_CONTEXT_SRC}
        ${UTILS_SRC}
        ${DTO_SRC}
        ${VALIDATIONS_SRC}
        ${SERVICES_SRC}
        ${REPOSITORIES_SRC}
)

add_subdirectory(test)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/uploads)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/secret)