#include "DebugCallback.h"
#include "Logging.h"

bool VulkanDebug::Setup(
    vk::Instance instance,
    const vk::detail::DispatchLoaderDynamic& dldi)
{
    if (instance == VK_NULL_HANDLE)
        return false;

    if (m_DebugMessenger != VK_NULL_HANDLE)
        return true;

    m_Instance = instance;
    m_Dldi = dldi;

    VkDebugUtilsMessengerCreateInfoEXT createInfo{};
    createInfo.sType =
        VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

    createInfo.messageSeverity =
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

    createInfo.messageType =
        VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

    createInfo.pfnUserCallback = DebugCallback;
    createInfo.pUserData = this;

    m_DebugMessenger = 
        instance.createDebugUtilsMessengerEXT(
            createInfo,
            nullptr,
            m_Dldi);

    if (m_DebugMessenger == VK_NULL_HANDLE)
    {
        std::cerr << "[Vulkan] Failed to create debug messenger: "
             << '\n';

        m_Instance = VK_NULL_HANDLE;
        m_DebugMessenger = VK_NULL_HANDLE;
        return false;
    }

    return true;
}

void VulkanDebug::Shutdown()
{
    if (m_Instance != VK_NULL_HANDLE &&
        m_DebugMessenger != VK_NULL_HANDLE)
    {
        m_Dldi.vkDestroyDebugUtilsMessengerEXT(
            m_Instance,
            m_DebugMessenger,
            nullptr);
    }

    m_DebugMessenger = VK_NULL_HANDLE;
    m_Instance = VK_NULL_HANDLE;
}

VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebug::DebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* /*pUserData*/)
{
    if (!pCallbackData || !pCallbackData->pMessage)
        return VK_FALSE;

    switch (messageSeverity)
    {
    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
        VK_LOG_TRACE("[Validation] {}", pCallbackData->pMessage);
        break;

    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
        VK_LOG_INFO("[Validation] {}", pCallbackData->pMessage);
        break;

    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
        VK_LOG_WARN("[Validation] {}", pCallbackData->pMessage);
        break;

    case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
        VK_LOG_ERROR("[Validation] {}", pCallbackData->pMessage);
        break;

    default:
        VK_LOG_INFO("[Validation] {}", pCallbackData->pMessage);
        break;
    }

    return VK_FALSE;

}