#pragma once

#include "EffectBase.h"
#include <string>


using namespace std;

/// <summary>
/// エフェクト管理クラス
/// </summary>
class EffectManager final
{
public:
	EffectManager();
	virtual ~EffectManager();

	//エフェクトの種類
	enum Effect
	{
		EXPLOSION,			//爆発エフェクト
		EFFECT_AMOUNT,		//エフェクトの種類
	};

	void Initialize();		//初期化処理
	void Draw();			//描画処理

	void CreateExplosionEffect(VECTOR position);	//爆発エフェクトの生成

private:
	EffectManager(const EffectManager&);		//コピーコンストラクタ

	string InputPath(string folderPath,
					 string effectPath);		//エフェクトパスの入力


	EffectBase* effect[EFFECT_AMOUNT];			//エフェクト格納用


	//エフェクト
	const string EFFECT_FOLDER_PATH;		//effectフォルダまでのパス
	const string EXPLOSION_EFFECT_PATH;		//爆発エフェクトのパス

	//エフェクトのサイズ
	const float  EXPLOSION_SIZE;			//爆発エフェクトのサイズ

};