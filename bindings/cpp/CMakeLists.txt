cmake_minimum_required(VERSION 3.12)
cmake_policy(VERSION 3.12)

project(PortAudio LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Todo (multi-generator): Add support for multiple generators like:
# - {Debug, Release} x {Static, Dynamic} x {MT, MD (Windows only)}
set(portaudio-cpp-sources)
add_subdirectory(source/portaudiocpp) # define source-files

add_library(portaudiocpp ${portaudio-cpp-sources})
add_library(PortAudio::portaudiocpp ALIAS portaudiocpp) # For subdirectory build

# Remove, when PortAudio::portaudio-cpp has it's own CMakeLists.txt
if(TARGET portaudio)
    add_library(PortAudio::portaudio ALIAS portaudio) # Todo (responsibility): move to PortAudio's own CMakeLists.txt
elseif(NOT TARGET PortAudio::portaudio)
    find_package(portaudio CONFIG REQUIRED) # Import, if not already existing (e.g. in a sub-project)

    if(TARGET portaudio)
        add_library(PortAudio::portaudio ALIAS portaudio) # Todo (responsibility): move to PortAudio's own CMakeLists.txt
    endif()
endif()

target_link_libraries(portaudiocpp PUBLIC PortAudio::portaudio)
target_include_directories(portaudiocpp PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_compile_features(portaudiocpp PUBLIC cxx_std_14) # There is no benefit of using c++11

# ## Export ###

# make cache variables for install destinations
include(GNUInstallDirs)

install(TARGETS portaudiocpp
    EXPORT PortAudioTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Todo(export) copy header files:
install(FILES MathFunctions.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT PortAudioTargets
    FILE MathFunctionsTargets.cmake
    NAMESPACE PortAudio::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MathFunctions
)

# Create theactual package
include(CMakePackageConfigHelpers)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MathFunctions
)

install(FILES
          "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfig.cmake"
          "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MathFunctions
)