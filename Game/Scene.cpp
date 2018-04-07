#include "scene.h"
#include "SystemRenderer.h"

Scene::Scene()
{
}
void Scene::update(double dt)
{
}
void Scene::render()
{
	for (auto &e : _ents.list) {
		e->render();
	}
}

