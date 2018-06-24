#pragma once

#include <ECS.h>

using namespace ECS;

// ����������洢ȫ�ֵ���Ⱦ���ڵ���Ϣ
struct WindowInfoSingletonComponent {

	GLFWwindow* Window;
	bool showGUI;
	int score;
	string gameRootPath;

	WindowInfoSingletonComponent(GLFWwindow *_window, string _gameRootPath) {

		Window = _window;
		showGUI = false;
		score = 0;
		gameRootPath = _gameRootPath;
	}
};
