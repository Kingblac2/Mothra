#pragma once
class VulkanDebug
{
public:
    VulkanDebug() = default;
    ~VulkanDebug() = default;

    VulkanDebug(const VulkanDebug&) = delete;
    VulkanDebug& operator=(const VulkanDebug&) = delete;

    bool Setup(
        vk::Instance instance,
        const vk::detail::DispatchLoaderDynamic& dldi);

    void Shutdown();

    vk::DebugUtilsMessengerEXT GetMessenger() const
    {
        return m_DebugMessenger;
    }

    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData);

private:
    vk::Instance m_Instance = VK_NULL_HANDLE;
    vk::DebugUtilsMessengerEXT m_DebugMessenger = VK_NULL_HANDLE;

    // Copy the dispatcher so it remains available to this class.
    vk::detail::DispatchLoaderDynamic m_Dldi{};
};