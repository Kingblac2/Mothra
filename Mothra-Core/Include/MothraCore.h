#pragma once

#include <Core/Layer.h>
#include <Core/InputEvents.h>
#include <Core/WindowEvents.h>


class MothraLayer : public Core::Layer
{
public:
    MothraLayer();
    virtual ~MothraLayer();

	virtual void OnEvent(Core::Event& event) override;

	virtual void OnUpdate(float ts) override;
	virtual void OnRender() override;
private:
	bool OnMouseButtonPressed(Core::MouseButtonPressedEvent& event);
	bool OnMouseMoved(Core::MouseMovedEvent& event);
	bool OnWindowClosed(Core::WindowClosedEvent& event);

};
