#pragma once
#include "Component.h"
class InputComponent : public Component
{
public:
	//�R���X�g���N�^�BUpdate Order�͑��߁B
	InputComponent(class Actor* owner, int updateOrder = 10);
	~InputComponent();


protected:



private:
	
};

