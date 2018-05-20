#pragma once
#include <GLFW/glfw3.h>

#include <ECS.h>
#include <Components/CameraInfoSingletonComponent.h>
#include <Components/WindowInfoSingletonComponent.h>
#include <Events/MouseMovementEvent.h>
#include <Events/KeyEvents.h>

using namespace ECS;


// ������ϵͳ������ camera ���ǣ�������ƶ�Ч��һ������׼�Ĵ�С
class RecoilSystem : public EntitySystem,
	public EventSubscriber<KeyPressEvent>,
	public EventSubscriber<MousePressEvent> {
public:

	virtual void configure(class World* world) override
	{
		world->subscribe<KeyPressEvent>(this);
		world->subscribe<MousePressEvent>(this);
	}

	virtual void unconfigure(class World* world) override
	{
		world->unsubscribeAll(this);
	}

	// ���յ� WASD ���µ��¼��󣬸��� Camera ��λ��
	virtual void receive(class World* world, const KeyPressEvent& event) override
	{	
		// �����ı�׼�ġ�ǹ�����ӵ�Ū��֮��׼�������ǹʵ�����Ū���
	}

	virtual void receive(class World* world, const MousePressEvent& event) override
	{
		// ��ôʵ�ֺ�����������ȥ֮���ܻ��������ҹ�����Ȼ��
		/*if (event.key == MOUSE_LEFT)
			world->emit<MouseMovementEvent>({ 0.5f , 1.5f });*/
	}

	RecoilSystem() {
		init();
	}

	void init() {

	}

	virtual void tick(class World* world, float deltaTime) override {
		
	}
};