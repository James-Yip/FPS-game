#pragma once

#include <ECS.h>
#include <glm/gtc/type_ptr.hpp>

using namespace ECS;

// ����� component �� entity ���ǵ�ǰ���Ƶ���ң�����������Ҫ�����ݣ���ʱ��û�У�
struct PlayerComponent {

    bool isJumping;

	PlayerComponent() {
        isJumping = false;
	}
};