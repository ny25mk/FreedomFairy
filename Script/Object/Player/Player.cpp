#include "Player.h"
#include "DxLib.h"
#include "../../MyLibrary/MyLibrary.h"
#include "../../Define/Define.h"
#include "../../Input/Controller.h"
#include "../../Collider/Inheritance/StationeryCollider.h"
#include "../Creater/ObjectCreater.h"
#include "../../System/HitPoint/HitPoint.h"

using Key = Input::eInputType;
using Win = Define::Window;

const int Hit_Range = 2;
const int Image_AllNum = 12;
const int Image_Size = 48;

Player::Player(){

	vec2.Set((float)Win::Center_Px, (float)Win::Out_Height * 0.8f);
	moveSpeed = 4.0f;
	isAlive = true;

	radius = 7;
	color = GetColor(255, 255, 255);		//画像に変更するので削除予定

	collider = new CircleCollider(vec2, Hit_Range, eTag_Player);
	hp = new HitPoint(1);

	ListRegistration(this);

}

Player::~Player(){

	SELF_DELETE(hp);
	collider->SetAliveFlag(false);

}

bool Player::Update(){

	if(collider->GetHitFlag()){
		HitAction();
	}

	Move();

	if(Controller::Instance().Get(Key::Shot)){
		Shot();
	}

	collider->SetVector(vec2);

	return isAlive;
}

void Player::Draw() const{

	DrawCircle(vec2.GetDx(), vec2.GetDy(), radius, color, true);	//画像に変更するので削除予定
	collider->Draw();

}

void Player::Move(){

	float moveX = 0, moveY = 0;

	if(Controller::Instance().Get(Key::Up)){
		moveY -= moveSpeed;
	}

	if(Controller::Instance().Get(Key::Down)){
		moveY += moveSpeed;
	}

	if(Controller::Instance().Get(Key::Left)){
		moveX -= moveSpeed;
	}

	if(Controller::Instance().Get(Key::Right)){
		moveX += moveSpeed;
	}

	//斜め移動時√2で割る
	if(moveX && moveY){
		moveX /= (float)std::sqrt(2.0);
		moveY /= (float)std::sqrt(2.0);
	}

	//減速
	if(Controller::Instance().Get(Key::Slow)){
		moveX /= 2;
		moveY /= 2;
	}

	//移動可能範囲の確認
	float px = vec2.GetX(), py = vec2.GetY();
	if(px + moveX - radius < Win::In_Px){
		moveX = 0;
	} else if(px + moveX + radius > Win::In_Px + Win::In_Width){
		moveX = 0;
	}

	if(py + moveY - radius < Win::In_Py){
		moveY = 0;
	} else if(py + moveY + radius > Win::In_Py + Win::In_Height){
		moveY = 0;
	} 

	vec2.Add(moveX , moveY);

}

void Player::Shot(){

	/*ObjectCreater objCreate;
	objCreate.BulletCreate(vec2, 5, -15.0f, eTag_Player);*/

}

void Player::HitAction(){

	hp->Sub(1);

	if(hp->Get() == 0){
		isAlive = false;
	}

}