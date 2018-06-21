#pragma once

#include <ECS.h>
#include <glm/gtc/type_ptr.hpp>

using namespace ECS;

// ����� component �� entity ���ǵ�ǰ���Ƶ���ң�����������Ҫ�����ݣ���ʱ��û�У�
struct PlayerComponent {

    bool isJumping;
	bool can_shot;  // �����Ƿ������
	int bullet_capacity, cur_bullet;  // ��������

	PlayerComponent() {
		init();
        
	}

	void init() {
		bullet_capacity = 30;
		cur_bullet = bullet_capacity;
		isJumping = false;
	}
};