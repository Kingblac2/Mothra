#pragma once
#define VK_USE_PLATFORM_WIN32_KHR
#define VK_NO_PROTOTYPES
#include"Volk/volk.h"
#include<vulkan/vulkan.hpp>

namespace Mothra
{

class MothraCore
{
public:
    MothraCore();
    ~MothraCore() = default;
};

}