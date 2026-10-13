#include "Device.h"
#include "Core/Application.h"
std::vector<const char*> Instance::GLFWGetRequiredExtension()
{
    uint32_t glfwExtensionCount = 0;
    const char** glfwextensions;

    glfwextensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwextensions, glfwextensions + glfwExtensionCount);


    if (enableDebug)
    {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        std::cout << "Extensions to be requested:\n";

        for (const char* extensionName : extensions)
        {
            std::cout << "\t\"" << extensionName << "\"\n";
        }
    }
    return extensions;
}

bool Instance::supported(std::vector<const char*>& extensions, std::vector<const char*>& layers)
{
    std::vector<vk::ExtensionProperties> supportedExtensions = vk::enumerateInstanceExtensionProperties();

    if (enableDebug)
    {
        std::cout << "Device can support the following extensions:\n";
        for (vk::ExtensionProperties supportedExtension : supportedExtensions)
        {
            std::cout << '\t' << supportedExtension.extensionName << std::endl;
        }
    }

    bool found;
    for (const char* extension : extensions)
    {
        found = false;
        for (vk::ExtensionProperties supportedExtension : supportedExtensions)
        {
            if (strcmp(extension, supportedExtension.extensionName) == 0)
            {
                found = { true };
                if (enableDebug)
                {
                    std::cout << "Extension \"" << extension << "\"is supported!\n";
                }
            }
        }
        if (!found)
        {
            if (enableDebug)
            {
                std::cout << "Extension \"" << extension << "\" is not supported!\n";
            }
            return false;
        }
    }

    std::vector<vk::LayerProperties> supportedLayers = vk::enumerateInstanceLayerProperties();

    if (enableDebug)
    {
        std::cout << "Device can support the following Layers:\n";
        for (vk::LayerProperties supportedLayer : supportedLayers)
        {
            std::cout << '\t' << supportedLayer.layerName << std::endl;
        }
    }

    for (const char* layer : layers)
    {
        found = false;
        for (vk::LayerProperties supportedLayer : supportedLayers)
        {
            if (strcmp(layer, supportedLayer.layerName) == 0)
            {
                found = true;
                if (enableDebug)
                {
                    std::cout << "Layer \"" << layer << "\" is supported!\n";
                }
            }
        }
        if (!found)
        {
            if (!enableDebug)
            {

                std::cout << "Layer \"" << layer << "\" is no supported!\n";
            }
            return false;
        }
    }
    return true;
}

bool Instance::checkforlayerSupport(std::vector<const char*>& extensions)
{
    if (enableDebug) layers.push_back("VK_LAYER_KHRONOS_validation");
    if (!supported(extensions, layers))
    {
        return false;
    }

    return true;
}
vk::Instance Instance::CreateInstance()
{

    uint32_t version{ 0 };
    vkEnumerateInstanceVersion(&version);

    /*
    * We  can then either use this version
    * (We Should just be sure to set the patch to 0 for best compatibility/stability)
    */
    // Removes Lower 12 bytes, Where Patch Number is Stored
    version &= ~(0xFFU);

    // Requesting The 0.1.0.0 version
    // Change VK_MAKE_API_VERSION to VK_MAKE_API_VERSION(0,1,0,0) if some problem occurs
    version = VK_MAKE_API_VERSION(0, 1, 1, 0);

    vk::ApplicationInfo appInfo = vk::ApplicationInfo(Core::Application().Get().GetSpecification()->Name.c_str(), version, "Mothra", version, version);

    auto extensions = GLFWGetRequiredExtension();

    checkforlayerSupport(extensions);

    vk::ValidationFeaturesEXT validationFeatures = {};
    {
        validationFeatures.sType = vk::StructureType::eValidationFeaturesEXT;
        validationFeatures.enabledValidationFeatureCount = 3;
        vk::ValidationFeatureEnableEXT enables[] = {
            vk::ValidationFeatureEnableEXT::eGpuAssisted,
            vk::ValidationFeatureEnableEXT::eGpuAssistedReserveBindingSlot,
            vk::ValidationFeatureEnableEXT::eSynchronizationValidation
        };
        validationFeatures.pEnabledValidationFeatures = enables;
    }

    vk::InstanceCreateInfo createInfo{};

    createInfo.flags = vk::InstanceCreateFlags{};
    createInfo.pApplicationInfo = &appInfo;

    createInfo.enabledLayerCount =
        static_cast<uint32_t>(layers.size());
    createInfo.ppEnabledLayerNames = layers.data();

    createInfo.enabledExtensionCount =
        static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    createInfo.pNext = &validationFeatures;

    try {
        return vk::createInstance(createInfo);
    }
    catch (vk::SystemError err)
    {

        std::cout << "Failed to create instance\n";

    }
    return nullptr;


}

void Instance::SetLayers(const char* layer)
{
    layers.push_back(layer);
}