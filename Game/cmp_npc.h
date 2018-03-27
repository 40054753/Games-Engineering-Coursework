#pragma once
#include "ecm.h"


class NPCComponent : public Component {
protected:
	/// string dialogue???
	std::vector <std::shared_ptr<Entity>> _entities;
public:
	NPCComponent() = delete;
	explicit NPCComponent(Entity *p);
	void setEntities(std::vector<std::shared_ptr<Entity>>& e);
	void update(double dt) override;
	void render() override;
	void interact();	
	
};