#include "cmp_items.h"
#include "cmp_char_sheet.h"
ItemComponent::ItemComponent(Entity *p) : Component(p) ,_sprite(std::make_shared<sf::Sprite>()) {
	
}

sf::Sprite& ItemComponent::getSprite() const {
	return *_sprite;
}
void ItemComponent::setPlayer(std::shared_ptr<Entity>& e) {
	_player = e;
}
void ItemComponent::render()
{
	Renderer::queue(0,_sprite.get());
}
void ItemComponent::update(double dt)
{
	_sprite->setPosition(_parent->getPosition());

	if(length(_parent->getPosition() - _player->getPosition()) < 20.0f)
	{
		auto x= _player->GetComponent<CharacterSheetComponent>();
		x->pickUp(_this);
	}

}
