#pragma once

#include <ECS.h>

using namespace ECS;

// ����������洢ȫ�ֵ���Ⱦ���ڵ���Ϣ
struct WindowInfoSingletonComponent {

	GLFWwindow* Window;
	bool showGUI;
	int score;

	WindowInfoSingletonComponent(GLFWwindow *_window) {

		Window = _window;
		showGUI = false;
		score = 0;
	}
};
