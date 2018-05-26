#pragma once

#include <ECS.h>

using namespace ECS;

enum Key {
	W,
	S,
	A,
	D,
	ESC,
	LEFT_SHIFT,
	SPACE,

	MOUSE_LEFT
};

struct MousePressEvent {
	MousePressEvent(Key _key, float _deltaTime)
		: key(_key), deltaTime(_deltaTime) {};

	Key key;
	float deltaTime;
};

struct KeyPressEvent {

	KeyPressEvent(Key _key, float _deltaTime)
		: key(_key), deltaTime(_deltaTime) {};
	
	Key key;
	float deltaTime;
};

struct KeyReleaseEvent {

	KeyReleaseEvent(Key _key, float _deltaTime)
		: key(_key), deltaTime(_deltaTime) {};

	Key key;
	float deltaTime;
};