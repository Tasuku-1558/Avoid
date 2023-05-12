#pragma once

#include "EffectBase.h"

/// <summary>
/// エフェクト管理クラス
/// </summary>
class EffectManager final
{
public:
	EffectManager();
	virtual ~EffectManager();

	//エフェクトの種類
	enum EffectType
	{
		EXPLOSION,			//爆発エフェクト
		FIRE,				//炎エフェクト
		EFFECT_AMOUNT,		//エフェクトの種類
	};

	void Draw();			//描画処理

	void CreateEffect(VECTOR position, EffectType effectType);	//エフェクトの生成

private:
	EffectManager(const EffectManager&);	//コピーコンストラクタ

	void Initialize();						//初期化処理
	void DeleteEffect();					//エフェクトの削除

	EffectBase* effect[EFFECT_AMOUNT];		//エフェクト格納用

	struct Effects
	{
		string effectPath;	//エフェクトのパス
		float  effectSize;	//エフェクトのサイズ
	};

	//エフェクト
	const string EFFECT_FOLDER_PATH;		//Effectフォルダまでのパス
	const string EXPLOSION_EFFECT_PATH;		//爆発エフェクトのパス
	const string FIRE_EFFECT_PATH;			//炎エフェクトのパス

	//エフェクトのサイズ
	const float  EXPLOSION_SIZE;			//爆発エフェクトのサイズ
	const float  FIRE_SIZE;					//炎エフェクトのサイズ

};