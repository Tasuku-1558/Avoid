#pragma once

#include "DxLib.h"
#include "GameScene.h"
#include <string>

using namespace std;

/// <summary>
/// UIÇNX
/// </summary>
class UiManager final
{
public:
	UiManager();
	virtual ~UiManager();

	void Draw(GameScene::GameState gameState, int font, int countDown, int score, int wave);	//`æ

private:

	UiManager(const UiManager&);		//Rs[RXgN^

	//æÌíÞ
	enum Graphic
	{
		FRAME,			//gæ
		FEVER_IMAGE,
		GRAPHIC_AMOUNT,	//æÌ
	};
	
	void Initialize();
	void Finalize();
	void StartGameDraw();
	void GameUIDraw(int font, int countDown, int score, int wave);		//Q[àUI`æ
	void FrameDraw();					//g`æ
	void FeverImageDraw();				//tB[o[[hUIÌ`æ
	

	int uiHandle[GRAPHIC_AMOUNT];		//ænhi[p
	bool fever;


	//è
	const string FOLDER_PATH;			//æi[tH_
	const string UI_GRAPHIC_PATH;		//UIæ
	const string FILENAME_EXTENSION;	//æg£q
	
};