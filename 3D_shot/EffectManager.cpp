#include "EffectManager.h"
#include "Effect.h"
#include "InputManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
EffectManager::EffectManager()
	: EFFECT_FOLDER_PATH("Data/Effect/")
	, EXPLOSION_EFFECT_PATH("Explosion/Explosion.efkefc")
	, FIRE_EFFECT_PATH("Fire/Fire.efkefc")
	, EXPLOSION_SIZE(30.0f)
	, FIRE_SIZE(30.0f)
{
	Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
EffectManager::~EffectManager()
{
	DeleteEffect();
}

/// <summary>
/// 初期化処理
/// </summary>
void EffectManager::Initialize()
{
	Effects effects[] =
	{
		{EXPLOSION_EFFECT_PATH, EXPLOSION_SIZE},
		{FIRE_EFFECT_PATH,		FIRE_SIZE},
	};

	for (int i = 0; i < EFFECT_AMOUNT; i++)
	{
		//各エフェクトの読み込み
		effect[i] = new Effect(Input::InputPath(EFFECT_FOLDER_PATH, effects[i].effectPath), effects[i].effectSize);
	}
}

/// <summary>
/// エフェクトの削除
/// </summary>
void EffectManager::DeleteEffect()
{
	for (int i = 0; i < EFFECT_AMOUNT; i++)
	{
		if (effect[i] != NULL)
		{
			delete effect[i];
			effect[i] = NULL;
		}
	}
}

/// <summary>
/// 描画処理
/// </summary>
void EffectManager::Draw()
{
	for (int i = 0; i < EFFECT_AMOUNT; i++)
	{
		effect[i]->Draw();
	}
}

/// <summary>
/// エフェクトの生成
/// </summary>
/// <param name="position">エフェクトの位置</param>
/// <param name="effectType">エフェクトの種類</param>
void EffectManager::CreateEffect(VECTOR position, EffectType effectType)
{
	effect[effectType]->Update(position);
}