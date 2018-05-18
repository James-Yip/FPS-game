#pragma once

#include <ECS.h>

using namespace ECS;

// ����������洢ȫ�ֵ���Ⱦ���ڵ���Ϣ
struct WindowInfoSingletonComponent {

	//int Width;
	//int Height;
	GLFWwindow* Window;
	bool showGUI;


	WindowInfoSingletonComponent(GLFWwindow *_window) {
		//Width = _width;
		//Height = _height;
		Window = _window;
		showGUI = false;
	}
};
