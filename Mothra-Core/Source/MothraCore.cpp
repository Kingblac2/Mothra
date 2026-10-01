#include"MothraCore.h"


Mothra::MothraCore::MothraCore()
{
    VkResult r;
    uint32_t version;
    void* ptr;

    /* This won't compile if the appropriate Vulkan platform define isn't set. */
    ptr = &vkCreateWin32SurfaceKHR;


    /* Try to initialize volk. This might not work on CI builds, but the
     * above should have compiled at least. */
    r = volkInitialize();
    if (r != VK_SUCCESS) {
        printf("volkInitialize failed!\n");
        exit(-1);
    }

    version = volkGetInstanceVersion();
    printf("Vulkan version %d.%d.%d initialized.\n",
        VK_VERSION_MAJOR(version),
        VK_VERSION_MINOR(version),
        VK_VERSION_PATCH(version));
}
