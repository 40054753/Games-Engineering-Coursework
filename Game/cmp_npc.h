#pragma once
#include "ecm.h"
#include <string>

class NPCComponent : public Component {
protected:
	bool twoDialogues = false;
	/// string dialogue???
	sf::RectangleShape dialogueBox;
	std::string dialogue;
	bool talked = false;
	std::string dialogue2;
	sf::Text text;
	bool trigger = false;
	float interactionDelay = 0.4f;
	bool dialogueFinished = false;
public:
	NPCComponent() = delete;
	explicit NPCComponent(Entity *p);
	void update(double dt) override;
	void setDialogue(std::string x);
	void setDialogue2(std::string x) { dialogue2 = x; twoDialogues = true; }
	void render() override;
	void interact();	
	
};