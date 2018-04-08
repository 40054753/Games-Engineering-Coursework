#pragma once
#include <ecm.h>

class PathfindingComponent : public Component {
protected:
	std::vector<sf::Vector2i> _path;
	size_t _index = 0;
	double _elapsed = 0.0;
	float speed = 80;
	bool _pathset = false;
public:
	void update(double) override;
	void render() override {}
	void setPath(std::vector<sf::Vector2i>& path);
	int getNextIndexX();
	int getNextIndexY();
	bool isPathSet() { return _pathset; };
	explicit PathfindingComponent(Entity* p);
	PathfindingComponent() = delete;
};