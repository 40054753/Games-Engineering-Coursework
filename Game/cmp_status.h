#pragma once
#include "ecm.h"

class StatusComponent : public Component {

protected:
	bool burning = false;
	bool blinded = false;
	bool slowed = false;
	float blindTimer = 5.0f;
public:
	explicit StatusComponent(Entity *p);
	StatusComponent() = delete;
	bool getBurning() { return &burning; }
	bool getBlinded() { return blinded; }
	bool getSlowed() { return &slowed; }
	void setBurning() { burning = true; }
	void reset();
	void setBlinded(bool a) { blinded = a; }
	void setSlowed() { slowed = true; }
	void render() override;
	void update(double dt) override;


};

