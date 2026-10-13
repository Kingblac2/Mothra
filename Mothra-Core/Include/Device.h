
#include <algorithm>
#include <set>
#include <string>
#include <string_view>
#include <vector>



 const static bool  enableDebug = ((std::getenv("DEBUG") != nullptr) || true);

struct GLFWContext
{
    GLFWwindow* w_handle;     //Window Handle
    int width, height;
    std::string name;
};

class Instance
{
public:
  

    vk::Instance CreateInstance();
    void SetLayers(const char* layer);

private:
    std::vector<const char*> GLFWGetRequiredExtension();

    bool supported(std::vector<const char*>& extensions, std::vector<const char*>& layers);



    bool checkforlayerSupport(std::vector<const char*>& extensions);

    private:
        std::vector<const char*> layers;

};
struct VulkanDeviceExtensions
{
    using List = std::vector<const char*>;

    vk::PhysicalDevice device;
    std::set<std::string, std::less<>> supported;

    explicit VulkanDeviceExtensions(vk::PhysicalDevice device)
        : device(device)
    {
        for (const auto& ext : device.enumerateDeviceExtensionProperties())
            supported.emplace(ext.extensionName.data());
    }

    [[nodiscard]]
    bool supports(std::string_view extension) const
    {
        return supported.contains(extension);
    }

    [[nodiscard]]
    bool supports(const List& required) const
    {
        return std::ranges::all_of(required, [this](const char* ext) {
            return ext && supports(ext);
            });
    }

    [[nodiscard]]
    std::vector<std::string> missing(const List& required) const
    {
        std::vector<std::string> result;

        for (const char* ext : required)
            if (!ext || !supports(ext))
                result.emplace_back(ext ? ext : "<null>");

        return result;
    }

    void print(std::ostream& out = std::cout) const
    {
        for (const auto& ext : supported)
            out << '\t' << ext << '\n';
    }
};