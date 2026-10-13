#include"MothraCore.h"
#include<Device.h>
#include "Core/Application.h"

MothraLayer::MothraLayer()
{

}


void MothraLayer::OnEvent(Core::Event& event)
{

}

void MothraLayer::OnUpdate(float ts)
{
}

void MothraLayer::OnRender()
{
	Instance instance;
	vk::Instance Instance = instance.CreateInstance();
}

MothraLayer::~MothraLayer()
{
}