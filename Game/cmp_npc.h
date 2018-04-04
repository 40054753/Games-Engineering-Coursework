#pragma once
#include "ecm.h"
#include <string>

class NPCComponent : public Component {
protected:
	/// string dialogue???
	std::shared_ptr<Entity> _player;
	sf::RectangleShape dialogueBox;
	std::string dialogue;
	sf::Text text;
	bool trigger = false;
	float interactionDelay = 0.4f;
	bool dialogueFinished = false;
public:
	NPCComponent() = delete;
	explicit NPCComponent(Entity *p);
	void setEntities(std::shared_ptr<Entity>& e);
	void update(double dt) override;
	void setDialogue(std::string x);
	void render() override;
	void interact();	
	
};