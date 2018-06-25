#pragma once
#include <GLFW/glfw3.h>

#include <ECS.h>
#include <Events/MouseMovementEvent.h>
#include <Components/WindowInfoSingletonComponent.h>

using namespace ECS;

// ��������ƶ��ı䵱ǰ camera ������ entity �� PositionComponent ��Ϣ
class MouseMovingSystem : public EntitySystem, 
	public EventSubscriber<MouseMovementEvent> {
public:

	bool firstMouse;
	float lastX, lastY;

	virtual void configure(class World* world) override
	{
		world->subscribe<MouseMovementEvent>(this);
	}

	virtual void unconfigure(class World* world) override
	{
		world->unsubscribeAll(this);
	}

	

	MouseMovingSystem() {
		init();
	}

	void init() {
		firstMouse = true;
	}

	virtual void receive(class World* world, const MouseMovementEvent& event) override
	{
		updateCamera(world, event.xoffset, event.yoffset);
	}

	// ÿ����ѯ��ʱ����� GUI û������ʾ���ͻ�õ�ǰ����λ�ã������ offset
	virtual void tick(class World* world, float deltaTime) override {
		auto windowCHandle = world->getSingletonComponent<WindowInfoSingletonComponent>();
		
		if (windowCHandle->showGUI) {
			firstMouse = true;
			return;
		}

		double xpos, ypos;
		int window_width, window_height;
		glfwGetWindowSize(windowCHandle->Window, &window_width, &window_height);
		glfwGetCursorPos(windowCHandle->Window, &xpos, &ypos);

		if (firstMouse) {
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;

		lastX = xpos;
		lastY = ypos;

		updateCamera(world, xoffset, yoffset);
		world->each<TransformComponent>([&](Entity* ent, ComponentHandle<TransformComponent> transformCHandle) -> void {
			transformCHandle->relative_translate = glm::vec3(0.0f, 0.0f, 0.0f);
		});
	}

private:
	void updateTransform(World* world, float pitch) {
		world->each<PlayerComponent>([&](Entity* ent, ComponentHandle<PlayerComponent> playerCHandle) -> void {
			auto positionCHandle = ent->get<PositionComponent>();
			auto transformCHandle = ent->get<TransformComponent>();

			float rotate_x = 0.0f, rotate_y = 0.0f;

			// ���� Front ������ player ��ģ���� y ����ת
			glm::vec3 XZ_front = glm::normalize(glm::vec3(positionCHandle->Front.x, 0.0f, positionCHandle->Front.z));
			float x = XZ_front.x, z = XZ_front.z;
				
			if (x > 0 && z > 0) {
				rotate_y = glm::acos(z);
			}
			else if (x > 0 && z < 0) {
				rotate_y = float(glm::acos(z));
			}
			else if (x < 0 && z > 0) {
				rotate_y = float(-glm::acos(z));
			}
			else if (x < 0 && z < 0) {
				rotate_y = float(6.28 - glm::acos(z));
			}
			transformCHandle->rotate_y = rotate_y;

			// ���� Front ������ player ��ģ���� x ����ת
			glm::vec3 n_front = glm::normalize(positionCHandle->Front);
			x = n_front.x; z = n_front.z; float y = n_front.y;

			if (y < 0.001f && y > -0.001f) transformCHandle->rotate_x = 0.0f;
			else transformCHandle->rotate_x = -float(glm::asin(y));

			if (pitch > 0) {
				transformCHandle->relative_translate.z = pitch / 300.0f;
				transformCHandle->relative_translate.y = pitch / 50.0f;
			}
			else {
				transformCHandle->relative_translate.z = -abs(pitch) / 80.0f;
				transformCHandle->relative_translate.y = -abs(pitch) / 70.0f;
			}
			
			
		});
	}

	// ���� player entity �� camera �� position �����ݣ�֮ǰ camera �� updateVectors ������ processMouseMovement ������
	// ��Ҫ�Ǹ��� Front �� Right ����
	// ����Ӱ�첻���� player entity ������ entity �� PositionComponent
	void updateCamera(World* world, float xoffset, float yoffset) {
		world->each<PlayerComponent>([&](Entity* ent, ComponentHandle<PlayerComponent> playerCHandle) -> void {
			auto cameraCHandle = ent->get<CameraComponent>();
			auto positionCHandle = ent->get<PositionComponent>();
            auto collisionCHandle = ent->get<CollisionComponent>();

			xoffset *= cameraCHandle->MouseSensitivity;
			yoffset *= cameraCHandle->MouseSensitivity;

			cameraCHandle->Yaw += xoffset;
			cameraCHandle->Pitch += yoffset;

			// Make sure that when pitch is out of bounds, screen doesn't get flipped
			if (cameraCHandle->Pitch > 45.0f)
				cameraCHandle->Pitch = 45.0f;
			if (cameraCHandle->Pitch < -40.0f)
				cameraCHandle->Pitch = -40.0f;

			glm::vec3 front;
			front.x = cos(glm::radians(cameraCHandle->Yaw)) * cos(glm::radians(cameraCHandle->Pitch));
			front.y = sin(glm::radians(cameraCHandle->Pitch));
			front.z = sin(glm::radians(cameraCHandle->Yaw)) * cos(glm::radians(cameraCHandle->Pitch));
            
			positionCHandle->Front = glm::normalize(front);

            // unfinished
            //float z = sin(glm::radians(cameraCHandle->Yaw));
            ////printf("(%f, %f)\n", x, z);
            ////printf("acos(z): %f\n", float(glm::acos(abs(z))));
            //float angle = float(glm::acos(abs(z)));
            ////printf("angle: %f\n", angle);
            //float original_width = collisionCHandle->original_width;
            //float original_depth = collisionCHandle->original_depth;
            //float new_width = original_width * cos(angle) + original_depth * sin(angle);
            //float new_depth = original_width * sin(angle) + original_depth * cos(angle);
            //collisionCHandle->updateBody(new_width, new_depth);
            ////collisionCHandle->Print();

			positionCHandle->Right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
			positionCHandle->Up = glm::normalize(glm::cross(positionCHandle->Right, front));

			updateTransform(world, cameraCHandle->Pitch);
		});
	}
};