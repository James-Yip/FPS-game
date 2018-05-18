#pragma once

#include <ECS.h>
#include <glm/gtc/type_ptr.hpp>

using namespace ECS;

// ����������洢ȫ�ֵ� Camera ��λ�ú��ӽ���Ϣ
struct CameraInfoSingletonComponent {

	glm::mat4 CameraViewMatrix;
	glm::vec3 CameraPos;

	CameraInfoSingletonComponent(glm::vec3 _cameraPos) {
		CameraPos = _cameraPos;
	}
};
