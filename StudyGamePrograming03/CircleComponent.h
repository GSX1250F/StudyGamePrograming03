#pragma once
#include "Component.h"
#include "Math.h"

class CircleComponent : public Component
{
public:
	CircleComponent(class Actor* owner);

	void SetRadius(float radius) { mRadius = radius; }
	float GetRadius() const { return mOwner->GetScale() * mRadius; }
	Vector2 GetCenter() const { return mCenter; }
	void SetCenter(Vector2 pos) { mCenter = pos };

protected:


private:
	float mRadius;
	Vector2 mCenter;

};

bool Intersect(const CircleComponent& a, const CircleComponent& b);