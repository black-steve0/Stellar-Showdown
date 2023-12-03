#pragma once

#include <raylib.h>
#include <stvlib.h>
#include <string>

struct Window {
	ray::Vector2 size;
	std::string title;
	int fps;

	Window(ray::Vector2 p_size, std::string p_title, int p_fps = 60) {
		size = p_size;
		title = p_title;
		fps = p_fps;
	}

	void Init() {
		ray::InitWindow(size.x, size.y, title.c_str());
		ray::SetTargetFPS(fps);
	}

	void ProcessPerFrame(void);

	void ProcessPerTick(void);

} window(ray::Vector2(700, 900), "Stellar Showdown", 60);