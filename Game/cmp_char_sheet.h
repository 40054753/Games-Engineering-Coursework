#pragma once
#include "ecm.h"

class CharacterSheetComponent : public Component {

protected:
	std::shared_ptr<Entity> helmet;
	std::shared_ptr<Entity> armour;
	std::shared_ptr<Entity> boots;
	std::shared_ptr<Entity> weapon;
	std::shared_ptr<Entity> shield;
	std::vector <std::shared_ptr<Entity>> _backpack;
public:
	std::shared_ptr<Entity> getHelmet() { return helmet; }
	std::shared_ptr<Entity> getArmour() { return armour; }
	std::shared_ptr<Entity> getBoots() { return boots; }
	std::shared_ptr<Entity> getWeapon() { return weapon; }
	std::shared_ptr<Entity> getShield() { return shield; }
	void equip( std::shared_ptr<Entity>& item);
	std::vector<std::shared_ptr<Entity>> &getBP() { return _backpack; };
	void pickUp(std::shared_ptr<Entity>& item);
	explicit CharacterSheetComponent(Entity *p);
	CharacterSheetComponent() = delete;
	void render() override;
	void update(double dt) override;
	
};

