#include "classes.h"

void Window::Init() {
	ray::InitWindow(size.x, size.y, title.c_str());
	ray::SetTargetFPS(fps);
}

void Window::ProcessPerFrame() {

}

void Window::ProcessPerTick() {

}