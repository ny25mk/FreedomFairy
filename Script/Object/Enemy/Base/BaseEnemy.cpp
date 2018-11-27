#include "BaseEnemy.h"
#include "../../../Define/Define.h"
#include <math.h>

namespace Game = Define::GameSize;

BaseEnemy::BaseEnemy(float x, float y):BaseGameObject(x,y){

	moveAngle = 0;
	counter = 0;
	width = 0;
	height = 0;

}

void BaseEnemy::Init(){

	SetSize();

}

bool BaseEnemy::Update(){

	Move();
	counter++;

	return  IsInside();
}

bool BaseEnemy::IsInside() const{

	//�ŏ�1�b�͔��薳��
	if(counter < 60){
		return true;
	}

	float x = vec2.GetX();
	float y = vec2.GetY();

	//�͈͂̊m�F
	if(x < Game::In_Px - width * 2){
		return false;
	}
	if(x > Game::In_Width + width * 2){
		return false;
	}
	if(y < Game::In_Py - height * 2){
		return false;
	}
	if(y > Game::In_Height + height * 2){
		return false;
	}

	return true;
}

void BaseEnemy::Move(){

	float x, y;

	x = cos(moveAngle) * moveSpeed;
	y = sin(moveAngle) * moveSpeed;
	vec2.Add(x, y);

}

#pragma region Accessor
float BaseEnemy::GetSpeed() const{

	return moveSpeed;
}

void BaseEnemy::SetSpeed(const float spd){

	moveSpeed = spd;

}

float BaseEnemy::GetAngle() const{

	return moveAngle;
}

void BaseEnemy::SetAngle(const float ang){

	moveAngle = ang;

}

int BaseEnemy::GetCount() const{

	return counter;
}

int BaseEnemy::GetMovePatternID() const{

	return movePatternID;
}
#pragma endregion

