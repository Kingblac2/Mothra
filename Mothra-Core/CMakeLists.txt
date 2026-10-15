add_library(Mothra-Core STATIC)

set(SOURCES
    Include/MothraCore.h
    Include/Device.h
    Include/DebugCallback.h

    Source/MothraCore.cpp
    Source/Device.cpp
    Source/DebugCallback.cpp
)


set(VULKAN_SDK_PATH "$ENV{VULKAN_SDK}")
set(Vulkan_INCLUDE_DIRS "$ENV{VULKAN_SDK}/Include")

target_sources(Mothra-Core
    PRIVATE
        ${SOURCES}
)

target_link_libraries(Mothra-Core
    PUBLIC
    Core
)

target_include_directories(Mothra-Core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_precompile_headers(Mothra-Core
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Include/pch.h
)

find_package(Vulkan REQUIRED)

set(VULKAN_SDK_PATH "$ENV{VULKAN_SDK}")

# Find Vulkan-Hpp bundled with the installed SDK
find_path(VULKAN_HPP_INCLUDE_DIR
    NAMES vulkan/vulkan.hpp
    PATHS
        "${VULKAN_SDK_PATH}/Include"
    NO_DEFAULT_PATH
)

if (NOT VULKAN_HPP_INCLUDE_DIR)
    message(FATAL_ERROR
        "Mothra-Core: vulkan.hpp was not found in the Vulkan SDK. "
        "Check your VULKAN_SDK environment variable."
    )
endif()

message(STATUS "Mothra-Core: Using Vulkan-Hpp from Vulkan SDK")
message(STATUS "  Include directory: ${VULKAN_HPP_INCLUDE_DIR}")

target_include_directories(Mothra-Core
    PUBLIC
        "${VULKAN_HPP_INCLUDE_DIR}"
)


target_link_libraries(Mothra-Core
    PUBLIC
        Vulkan::Vulkan
)


target_link_directories(Mothra-Core PUBLIC
    "${VULKAN_SDK_PATH}/Lib"
)

target_link_libraries(Mothra-Core PUBLIC
    vulkan-1.lib
)
#
# GLM
#

if (TARGET glm::glm)

    target_link_libraries(Mothra-Core
        PUBLIC
            glm::glm
    )

elseif (TARGET glm)

    target_link_libraries(Mothra-Core
        PUBLIC
            glm
    )

endif()





#
# Volk
#
#
# Volk
#


#find_path(VOLK_INCLUDE_DIR
#    NAMES volk.h
#    PATHS
#        "${VULKAN_SDK_PATH}/Include"
#    NO_DEFAULT_PATH
#)
#find_path(VOLK_INCLUDE_DIR volk.c volk.h HINTS ${Vulkan_INCLUDE_DIRS} ${Vulkan_INCLUDE_DIRS}/volk)
#
#find_library(VOLK_LIBRARY
#    NAMES volk
#    PATHS
#        "${VULKAN_SDK_PATH}/Lib"
#    NO_DEFAULT_PATH
#)
#
#if (VOLK_INCLUDE_DIR AND VOLK_LIBRARY)
#
#    message(STATUS "Mothra-Core: Using Volk from Vulkan SDK")
#    message(STATUS "  Include: ${VOLK_INCLUDE_DIR}")
#    message(STATUS "  Library: ${VOLK_LIBRARY}")
#
#    target_include_directories(Mothra-Core
#        PRIVATE
#            "${VOLK_INCLUDE_DIR}"
#    )
#
#    target_link_libraries(Mothra-Core
#        PRIVATE
#            "${VOLK_LIBRARY}"
#    )
#
#elseif (TARGET Mothra-Volk)
#
#    message(STATUS "Mothra-Core: Using downloaded Mothra-Volk")
#
#    target_link_libraries(Mothra-Core
#        PRIVATE
#            Mothra-Volk
#    )
#
#elseif (TARGET volk)
#
#    message(STATUS "Mothra-Core: Using downloaded volk")
#
#    target_link_libraries(Mothra-Core
#        PRIVATE
#            volk
#    )
#
#elseif (TARGET volk::volk)
#
#    message(STATUS "Mothra-Core: Using downloaded volk::volk")
#
#    target_link_libraries(Mothra-Core
#        PRIVATE
#            volk::volk
#    )
#
#else()
#
#    message(FATAL_ERROR
#        "Mothra-Core: Volk was not found in the Vulkan SDK or dependencies."
#    )
#
#endif()


#
# tinyobjloader
#

if (TARGET tinyobjloader)

    target_link_libraries(Mothra-Core
        PRIVATE
            tinyobjloader
    )

elseif (TARGET tinyobjloader::tinyobjloader)

    target_link_libraries(Mothra-Core
        PRIVATE
            tinyobjloader::tinyobjloader
    )

endif()


#
# KTX
#
#if (TARGET ktx)
#
#    target_link_libraries(Mothra-Core
#        PRIVATE
#            ktx
#    )
#
#    target_include_directories(Mothra-Core
#        PRIVATE
#            ${ktx_SOURCE_DIR}/include
#    )
#
#elseif (TARGET KTX::ktx)
#
#    target_link_libraries(Mothra-Core
#        PRIVATE
#            KTX::ktx
#    )
#
#endif()


#
# Visual Studio filters
#

target_compile_definitions(Mothra-Core
    PUBLIC
        GLFW_INCLUDE_NONE
)


if (TARGET glfw)

    target_link_libraries(Mothra-Core
        PUBLIC
            glfw
    )

elseif (TARGET glfw3)

    target_link_libraries(Mothra-Core
        PUBLIC
            glfw3
    )

elseif (TARGET glfw3::glfw)

    target_link_libraries(Mothra-Core
        PUBLIC
            glfw3::glfw
    )

else()

    message(FATAL_ERROR
        "Mothra-Core: GLFW target was not found."
    )

endif()

source_group(
    TREE "${CMAKE_CURRENT_SOURCE_DIR}"
    FILES ${SOURCES}
)