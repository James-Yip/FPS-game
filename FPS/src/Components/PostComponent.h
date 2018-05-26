#pragma once

#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <ECS.h>

using namespace ECS;


// ֮�� assign ��ÿ��ǹ�� entity���Ӷ���ͬ��ǹ��ӵ�в�ͬ��׼������
struct PostComponent {
	float length;  // ׼�������ߵĳ���
	float size;  // ׼�Ĵ�С��ԽСԽ׼
	glm::vec3 Color;
	GLuint line_VAO, line_VBO, point_VAO, point_VBO;

	float vertices[24] = {
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f, 

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
	};

	PostComponent(glm::vec3 _color, float _size, float _length = 0.03f) {
		init(_color, _size, _length);
	}

	void init(glm::vec3 _color, float _size, float _length = 0.03f) {
		Color = _color;
		glGenVertexArrays(1, &line_VAO);
		glGenBuffers(1, &line_VBO);
		glBindVertexArray(line_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, line_VBO);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		float point[3] = { 0.0f, 0.0f, 0.0f };
		glGenVertexArrays(1, &point_VAO);
		glGenBuffers(1, &point_VBO);
		glBindVertexArray(point_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, point_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(point), &point[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		length = _length;
		setSize(_size);
	}

	// ת�����豸���������λ�ø��ݴ��ڴ�С���������ܱ�ɹ̶���С�������Ρ�Ҫ�Ҹı䴰�ڴ�С��׼�Ĵ�СҲ���䡣
	void setSize(float _size) {
		size = _size;

		vertices[0] = -size;
		vertices[3] = -size - length;

		vertices[6] = size;
		vertices[9] = size + length;

		vertices[13] = size;
		vertices[16] = size + length;

		vertices[19] = -size;
		vertices[22] = -size - length;

		glBindVertexArray(line_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, line_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
};