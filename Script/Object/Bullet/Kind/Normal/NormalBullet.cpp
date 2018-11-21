#include "NormalBullet.h"
#include "../../../../Define/Define.h"
#include "DxLib.h"
#include "../../../../System/Image/Image.h"

static int count = 0;

NormalBullet::NormalBullet(float x,float y):BaseBullet(x,y){

	moveSpeed = 2.0f;
	moveAngle = Define::Math::Math_Pai / 2 - Define::Math::Math_Pai / 5;
	movePatternID = 0;

	if(count > 360){
		count = 0;
	}
	moveAngle = (float)count;
	count++;

}


void NormalBullet::Draw() const{

	DrawCircle(vec2.GetDx(), vec2.GetDy(), 5, Define::Color::Color_Red, true);

}

void NormalBullet::SetSize(){

	width = 5;
	height = 5;

}