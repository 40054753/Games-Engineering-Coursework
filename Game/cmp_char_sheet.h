#pragma once
#include "ecm.h"

class CharacterSheetComponent : public Component {

protected:

	std::vector <std::shared_ptr<Entity>> _backpack;
	std::shared_ptr<Entity> helmet;
	std::shared_ptr<Entity> armour;
	std::shared_ptr<Entity> boots;
	std::shared_ptr<Entity> weapon;
	std::shared_ptr<Entity> shield;
public:
	std::vector<std::shared_ptr<Entity>> &getBP() { return _backpack; };
	void pickUp(std::shared_ptr<Entity>& item);
	explicit CharacterSheetComponent(Entity *p);
	CharacterSheetComponent() = delete;
	void render() override;
	void update(double dt) override;
	
};

