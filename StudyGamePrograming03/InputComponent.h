#pragma once
#include "Component.h"
class InputComponent : public Component
{
public:
	//コンストラクタ。Update Orderは早め。
	InputComponent(class Actor* owner, int updateOrder = 10);
	~InputComponent();


protected:



private:
	
};

