#pragma once

#include <ECS.h>

using namespace ECS;

// ����������洢ȫ�ֵ���Ⱦ���ڵ���Ϣ
struct WindowInfoSingletonComponent {

	GLFWwindow* Window;
	bool showGUI;
	int score;
	bool game_start;
	string gameRootPath;

	WindowInfoSingletonComponent(GLFWwindow *_window, string _gameRootPath) {

		Window = _window;
		showGUI = false;
		score = 0;
		game_start = false;
		gameRootPath = _gameRootPath;
	}
};
