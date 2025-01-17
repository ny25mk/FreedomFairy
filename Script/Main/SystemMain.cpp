#include "SystemMain.h"
#include "DxLib.h"
#include "../Define/Define.h"
#include "GameMain.h"

bool SystemMain::Init() const{

	ChangeWindowMode(true);
	SetGraphMode(Define::Window::Window_Width, Define::Window::Window_Height, Color_Bit);
	SetMainWindowText(Window_Title);
	SetOutApplicationLogValidFlag(false);		//Log.txt�̏o�͂��~

	if(DxLib_Init()){
		return false;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	return true;
}

bool SystemMain::Update() const{

	GameMain gameMain;

	while(ProcessLoop()){

		if(!gameMain.GameLoop()){
			break;
		}

	}

	return false;
}

void SystemMain::Destroy() const{

	DxLib_End();

}

bool SystemMain::ProcessLoop() const{

	if(ScreenFlip() != 0){
		return false;
	}
	if(ProcessMessage() != 0){
		return false;
	}
	if(ClearDrawScreen() != 0){
		return false;
	}

	return true;
}