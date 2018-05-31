#pragma once
#include <GLFW/glfw3.h>

#include <ECS.h>
#include <Components/WindowInfoSingletonComponent.h>
#include <Events/MouseMovementEvent.h>
#include <Events/KeyEvents.h>
#include <iostream>
#include <ctime>

using namespace ECS;


// ������ϵͳ������ camera ���ǣ�������ƶ�Ч��һ������׼�Ĵ�С
class RecoilSystem : public EntitySystem,
	public EventSubscriber<KeyPressEvent>,
	public EventSubscriber<MousePressEvent> {
public:
	const float move_x = 7.0f, move_y = 12.0f, t = 0.15f;//move_x,move_y:��ǰ����ƫ��ֵ;
	float dx = 0, dy = 0, bx = 0, by = 0;//dx,dy:ÿһ��tickǰ����ƫ��ֵ;bx,by:ÿһ��tick���ص�ƫ��ֵ
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
	void   Delay(int   time)//time*1000Ϊ���� 
	{
		clock_t   now = clock();

		while (clock() - now   <   time);
	}

	
	virtual void receive(class World* world, const MousePressEvent& event) override
	{
		// ��ôʵ�ֺ�����������ȥ֮���ܻ��������ҹ�����Ȼ��
		if (event.key == MOUSE_LEFT) {
			dx = move_x;
			dy = move_y;
			bx = -move_x;
			by = -move_y;
		}	
	}

	RecoilSystem() {
		init();
	}

	void init() {

	}
	virtual void tick(class World* world, float deltaTime) override {
		if (dx != 0) {
			if ((dx > move_x * (deltaTime / t)) && (dy > move_y * (deltaTime / t))) {
				world->emit<MouseMovementEvent>({ move_x * (deltaTime / t) , move_y * (deltaTime / t) });
				dx = dx - (move_x * (deltaTime / t));
				dy = dy - (move_y * (deltaTime / t));
			}
			else {
				world->emit<MouseMovementEvent>({ dx , dy });
				dx = dy = 0;
			}
		}
		else {
			if ((bx < -move_x * (deltaTime / t)) && (by < -move_y * (deltaTime / t))) {
				world->emit<MouseMovementEvent>({ -move_x * (deltaTime / t) , -move_y * (deltaTime / t) });
				bx += (move_x * (deltaTime / t));
				by += (move_y * (deltaTime / t));
			}
			else {
				world->emit<MouseMovementEvent>({ bx , by });
				bx = by = 0;
			}
		}
	}
};