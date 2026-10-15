#include"MothraCore.h"
#include<Device.h>
#include "Core/Application.h"
#include "Logging.h"

MothraLayer::MothraLayer()
{

	Instance instance;
	vk::Instance Instance = instance.CreateInstance();
	dldi = vk::detail::DispatchLoaderDynamic(Instance, vkGetInstanceProcAddr);
	debug.Setup(Instance, dldi);

	auto window = Core::Application::Get().GetWindow()->GetHandle();
	VkSurfaceKHR c_style_surface;
	if (glfwCreateWindowSurface(Instance, window, nullptr, &c_style_surface) != VK_SUCCESS)
	{
		if (enableDebug) {
			VK_LOG_ERROR("Failed to abstrtact the glfw surface for vulkan");
		}
	}
	else if (enableDebug)
	{
		VK_LOG_INFO("Succesfully abstracted the glfw surface for VUlKAN");
	}
}


void MothraLayer::OnEvent(Core::Event& event)
{

}

void MothraLayer::OnUpdate(float ts)
{
}

void MothraLayer::OnRender()
{
}

MothraLayer::~MothraLayer()
{
}