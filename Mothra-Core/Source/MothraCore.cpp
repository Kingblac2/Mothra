#include"MothraCore.h"
#include<Device.h>
#include "Core/Application.h"

MothraLayer::MothraLayer()
{

	Instance instance;
	vk::Instance Instance = instance.CreateInstance();
	dldi = vk::detail::DispatchLoaderDynamic(Instance, vkGetInstanceProcAddr);
	debug.Setup(Instance, dldi);
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