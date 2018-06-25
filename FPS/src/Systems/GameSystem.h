#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include <ECS.h>
#include <Components/TextComponent.h>
#include <Events/KeyEvents.h>
#include <Events/TextChangeEvent.h>

using namespace ECS;
using namespace std;

const float GAME_TIME = 15.0f;

class GameSystem : public EntitySystem,
	public EventSubscriber<KeyPressEvent> {
public:

	float time_left;

	virtual void configure(class World* world) override
	{
		world->subscribe<KeyPressEvent>(this);
	}

	virtual void unconfigure(class World* world) override
	{
		world->unsubscribeAll(this);
	}

	virtual void receive(class World* world, const KeyPressEvent& event) override {
		auto windowCHandle = world->getSingletonComponent<WindowInfoSingletonComponent>();
		if (!windowCHandle->game_start) {
			windowCHandle->game_start = true;
			time_left = GAME_TIME;

			world->each<ObjectComponent>([&](Entity* ent, ComponentHandle<ObjectComponent> objectCHandle) -> void {
				if (objectCHandle->id == "monster") {
					ent->removeAll();
				}
			});

			world->each<TextComponent>([&](Entity* ent, ComponentHandle<TextComponent> textCHandle) -> void {
				if (textCHandle->info == "end") {
					ent->removeAll();
				}
			});
		}
	}


	GameSystem() {
		time_left = GAME_TIME;
	}

	virtual void tick(class World* world, float deltaTime) override {
		auto windowCHandle = world->getSingletonComponent<WindowInfoSingletonComponent>();
		int window_width, window_height;
		glfwGetWindowSize(windowCHandle->Window, &window_width, &window_height);

		if (windowCHandle->game_start) {
			time_left -= deltaTime;
			if (time_left < 0) {
				windowCHandle->game_start = false;
				Entity* win_text = world->create();
				win_text->assign<TextComponent>("end", "You Win", 0.3f, 0.45f, 1.5f, window_width, window_height, glm::vec3(0.5, 0.8f, 0.2f), windowCHandle->gameRootPath + "/resources/fonts/");
				
				world->each<ObjectComponent>([&](Entity* ent, ComponentHandle<ObjectComponent> objectCHandle) -> void {
					if (objectCHandle->id == "monster") {
						auto positionCHandle = ent->get<PositionComponent>();

						ParticleSystem::simulateDisappearing(world, glm::vec3(positionCHandle->Position.x, 4.0f, positionCHandle->Position.z));

						ent->removeAll();
					}
				});
			}

			world->each<ObjectComponent>([&](Entity* ent, ComponentHandle<ObjectComponent> objectCHandle) -> void {

				if (objectCHandle->id == "monster") {
					auto positionCHandle = ent->get<PositionComponent>();
					glm::vec3 position = positionCHandle->Position;

					// �������ӻ��ƻ����ӣ������м�ľ���
					if (position.x < 30.0f && position.x > -30.0f && position.z < 30.0f && position.z > -30.0f) {
						windowCHandle->game_start = false;
						Entity* win_text = world->create();
						win_text->assign<TextComponent>("end", "You Lose", 0.28f, 0.45f, 1.5f, window_width, window_height, glm::vec3(0.5, 0.8f, 0.2f), windowCHandle->gameRootPath + "/resources/fonts/");
						
						world->each<ObjectComponent>([&](Entity* ent, ComponentHandle<ObjectComponent> objectCHandle) -> void {
							if (objectCHandle->id == "monster") {
								ent->remove<MovementComponent>();
							}
						});
					}
				}
			});
		}

		updateTime(world);
	}

	void updateTime(class World* world) {
		world->each<TextComponent>([&](Entity* ent, ComponentHandle<TextComponent> textCHandle) -> void {
			if (textCHandle->info == "time") {
				string tmp;
				ostringstream osstream;
				osstream << int(time_left) << "s";

				world->emit<TextChangeEvent>({ "time", osstream.str() });
			}
		});
	}
};