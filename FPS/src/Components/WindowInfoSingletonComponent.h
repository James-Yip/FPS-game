#pragma once

#include <ECS.h>

// ����������洢ȫ�ֵ���Ⱦ���ڵ���Ϣ
struct WindowInfoSingletonComponent {
	ECS_DECLARE_TYPE;

	//int Width;
	//int Height;
	GLFWwindow* Window;


	WindowInfoSingletonComponent(GLFWwindow *_window) {
		//Width = _width;
		//Height = _height;
		Window = _window;
	}
};

ECS_DEFINE_TYPE(WindowInfoSingletonComponent);