add_library(Mothra-Core STATIC)

set(SOURCES
    Source/MothraCore.cpp
    Include/MothraCore.h
)

target_sources(Mothra-Core
    PRIVATE
        ${SOURCES}
)

target_include_directories(Mothra-Core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
)


find_package(Vulkan REQUIRED)

target_link_libraries(Mothra-Core
    PUBLIC
        Vulkan::Vulkan
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

if (TARGET Mothra-Volk)

    target_link_libraries(Mothra-Core
        PRIVATE
            Mothra-Volk
    )

elseif (TARGET volk)

    target_link_libraries(Mothra-Core
        PRIVATE
            volk
    )

elseif (TARGET volk::volk)

    target_link_libraries(Mothra-Core
        PRIVATE
            volk::volk
    )

else()

    message(FATAL_ERROR
        "Mothra-Core: Volk target was not found."
    )

endif()


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

source_group(
    TREE "${CMAKE_CURRENT_SOURCE_DIR}"
    FILES ${SOURCES}
)