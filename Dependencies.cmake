#function(mothra_set_dependency_folder root_dir folder_name)
#
#    get_property(all_targets DIRECTORY PROPERTY BUILDSYSTEM_TARGETS)
#
#    foreach(target IN LISTS all_targets)
#
#        if (NOT TARGET ${target})
#            continue()
#        endif()
#
#        get_target_property(target_source_dir
#            ${target}
#            SOURCE_DIR
#        )
#
#        if (target_source_dir)
#
#            file(REAL_PATH
#                "${target_source_dir}"
#                target_source_dir_real
#            )
#
#            file(REAL_PATH
#                "${root_dir}"
#                root_dir_real
#            )
#
#            if (target_source_dir_real MATCHES
#                "^${root_dir_real}(/|\\\\)"
#            )
#                set_target_properties(${target}
#                    PROPERTIES
#                        FOLDER "${folder_name}"
#                )
#            endif()
#
#        endif()
#
#    endforeach()
#
#endfunction()


#
# Dependencies
#
include(FetchContent)

# GLFW
find_package(glfw3 3.4 QUIET)
if (NOT glfw3_FOUND)
    FetchContent_Declare(
            glfw3
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip
    )
    FetchContent_GetProperties(glfw3)
    if (NOT glfw3_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(glfw3)
        add_subdirectory(${glfw3_SOURCE_DIR} ${glfw3_BINARY_DIR})
    endif()
endif()

# OpenGL
find_package(OpenGL REQUIRED)

# GLAD
FetchContent_Declare(
    glad
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/Dav1dde/glad/archive/refs/tags/v2.0.8.zip
)

FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(glad)

    add_subdirectory("${glad_SOURCE_DIR}/cmake" glad_cmake)
    glad_add_library(glad REPRODUCIBLE EXCLUDE_FROM_ALL LOADER API gl:core=4.6)
endif()
set_target_properties(glad PROPERTIES FOLDER "Dependencies")





#
# Vulkan
#

find_package(Vulkan REQUIRED)




#
# Volk
#

#find_package(Volk QUIET)
#
#if (NOT Volk_FOUND)
#
#    FetchContent_Declare(
#        volk
#        DOWNLOAD_EXTRACT_TIMESTAMP OFF
#        URL https://github.com/zeux/volk/archive/refs/tags/1.4.304.zip
#    )
#
#    FetchContent_GetProperties(volk)
#
#    if (NOT volk_POPULATED)
#
#        set(FETCHCONTENT_QUIET NO)
#
#        FetchContent_Populate(volk)
#
#        add_subdirectory(
#            ${volk_SOURCE_DIR}
#            ${volk_BINARY_DIR}
#            EXCLUDE_FROM_ALL
#        )
#
#    endif()
#
#endif()


#
# VMA - Vulkan Memory Allocator
#

find_package(VulkanMemoryAllocator QUIET)

if (NOT VulkanMemoryAllocator_FOUND)

    FetchContent_Declare(
        vma
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator/archive/refs/tags/v3.3.0.zip
    )

    FetchContent_GetProperties(vma)

    if (NOT vma_POPULATED)

        set(FETCHCONTENT_QUIET NO)

        FetchContent_Populate(vma)

        add_subdirectory(
            ${vma_SOURCE_DIR}
            ${vma_BINARY_DIR}
            EXCLUDE_FROM_ALL
        )

    endif()

endif()


#
# GLM
#

find_package(glm 1.0.1 QUIET)

if (NOT glm_FOUND)

    FetchContent_Declare(
        glm
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/g-truc/glm/archive/refs/tags/1.0.1.zip
    )

    FetchContent_GetProperties(glm)

    if (NOT glm_POPULATED)

        set(FETCHCONTENT_QUIET NO)

        FetchContent_Populate(glm)

        add_subdirectory(
            ${glm_SOURCE_DIR}
            ${glm_BINARY_DIR}
            EXCLUDE_FROM_ALL
        )

    endif()

endif()

set_target_properties(glm PROPERTIES
    FOLDER "Dependencies"
)


#
# tinyobjloader
#

find_package(tinyobjloader QUIET)

if (NOT tinyobjloader_FOUND)

    FetchContent_Declare(
        tinyobjloader
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/tinyobjloader/tinyobjloader/archive/refs/tags/v2.0.0rc13.zip
    )

    FetchContent_GetProperties(tinyobjloader)

    if (NOT tinyobjloader_POPULATED)

        set(FETCHCONTENT_QUIET NO)

        FetchContent_Populate(tinyobjloader)

        add_subdirectory(
            ${tinyobjloader_SOURCE_DIR}
            ${tinyobjloader_BINARY_DIR}
            EXCLUDE_FROM_ALL
        )

    endif()

endif()


#
# KTX-Software
#

#find_package(KTX QUIET)

#if (NOT KTX_FOUND)

#    FetchContent_Declare(
#        ktx
#        URL https://github.com/KhronosGroup/KTX-Software/archive/refs/tags/v4.4.0.zip
#        DOWNLOAD_EXTRACT_TIMESTAMP OFF
#    )

#     FetchContent_MakeAvailable(ktx) 
#     FetchContent_GetProperties(ktx)

	

#   if (NOT ktx_POPULATED)
#       FetchContent_Populate(ktx)	
#  endif()
#		mothra_set_dependency_folder(
#    	 "${ktx_SOURCE_DIR}"
#    	 "Dependencies/KTX"
#	)
	
	
#endif()




