#pragma once
#include "SystemRenderer.h"
#include <string>
#include <iostream>
#include "Game.h"
#include "ecm.h"
#include "cmp_sprite.h"

class CursorComponent : public Component {

protected:
	sf::Sprite cursorSprite;
	bool is_visible = true;
public:
	explicit CursorComponent(Entity *p);
	CursorComponent() = delete;
	void setVisible() { is_visible = true; }
	void setInvisible() { is_visible = false; }
	void setSprite();
	void update();
	void render();
};
