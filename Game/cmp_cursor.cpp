#include "cmp_cursor.h"
#include "cmp_actor_movement.h"
#include "ecm.h"
#include "cmp_sprite.h"

CursorComponent::CursorComponent(Entity * p)  : Component(p)
{
	_parent->setPosition(sf::Vector2f(WX / 2, WY / 2));
	_parent->addComponent<CursorMovementComponent>();
}

void CursorComponent::setSprite()
{
	if (!cursorTexture.loadFromFile("res/img/items.png")) {
		std::cout << "Cannot load img!" << std::endl;
	}
	auto cs = _parent->addComponent<StaticSpriteComponent>();
	cs->getSprite().setTexture(cursorTexture);
	cs->getSprite().setTextureRect({ 0,112,16,16 });
	cs->getSprite().setScale({ 2, 2 });
	cursorSprite = cs->getSprite();
}

void CursorComponent::update()
{
	_parent->setPosition(_parent->getPosition());
}

void CursorComponent::render()
{
	Renderer::queue(-1, &cursorSprite);
}
