#pragma once
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include <ECS.h>
#include <Components/WindowInfoSingletonComponent.h>
#include <Events/KeyEvents.h>

using namespace ECS;

// ���� ImGUI ����ʾ
class GUISystem : public EntitySystem,
	public EventSubscriber<KeyPressEvent> {
public:

	bool initialized;

	GUISystem() {
		init();
	}

	void init() {
		initialized = false;
	}

	virtual void configure(class World* world) override
	{
		world->subscribe<KeyPressEvent>(this);
	}

	virtual void unconfigure(class World* world) override
	{
		world->unsubscribeAll(this);
	}

	// ���յ� ESC ���µ��¼�����ʾ GUI
	virtual void receive(class World* world, const KeyPressEvent& event) override
	{
		if (event.key == ESC) {
			auto windowCHandle = world->getSingletonComponent<WindowInfoSingletonComponent>();
			windowCHandle->showGUI = true;
			glfwSetInputMode(windowCHandle->Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}


	// ��� ImGui ��û�г�ʼ���Ͱ󶨵� window���ȳ�ʼ���Ͱ�
	virtual void tick(class World* world, float deltaTime) override {
		auto windowCHandle = world->getSingletonComponent<WindowInfoSingletonComponent>();

		if (!initialized) {
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGui_ImplGlfwGL3_Init(windowCHandle->Window, true);

			initialized = true;
		}


		auto lightCHandle = world->getSingletonComponent<LightingInfoSingletonComponent>();

		if (windowCHandle->showGUI) {
			ImGui_ImplGlfwGL3_NewFrame();
			{
				ImGui::Begin("Game Menu", &(windowCHandle->showGUI));  // �����ϽǵĽ���ر� GUI

				ImGui::Text("Shadow type:");
				ImGui::RadioButton("Linear", &(lightCHandle->shadow_type), 0);
				ImGui::RadioButton("PCSS (fixed BS region)", &(lightCHandle->shadow_type), 1);
				ImGui::RadioButton("PCSS", &(lightCHandle->shadow_type), 2);

				ImGui::Text("\nLighting parameters:");
				ImGui::SliderFloat("Ambient strength", &(lightCHandle->AmbientStrength), 0.0f, 1.0f);
				ImGui::SliderFloat("Specular strength", &(lightCHandle->SpecularStrength), 0.0f, 1.0f);
				ImGui::SliderFloat("Diffuse strength", &(lightCHandle->DiffuseStrength), 0.0f, 1.0f);
				ImGui::SliderFloat("Shininess", &(lightCHandle->Shininess), 0.1f, 64.0f);

				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
		} else {
			glfwSetInputMode(windowCHandle->Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}
};