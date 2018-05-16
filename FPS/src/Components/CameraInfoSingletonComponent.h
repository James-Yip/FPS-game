#pragma once

#include <ECS.h>
#include <glm/gtc/type_ptr.hpp>

using namespace ECS;

// ����������洢ȫ�ֵ� Camera ��λ�ú��ӽ���Ϣ
struct CameraInfoSingletonComponent {
	ECS_DECLARE_TYPE;

	glm::mat4 CameraViewMatrix;
	glm::vec3 CameraPos;

	CameraInfoSingletonComponent(glm::vec3 _cameraPos) {
		CameraPos = _cameraPos;
	}
};

ECS_DEFINE_TYPE(CameraInfoSingletonComponent);