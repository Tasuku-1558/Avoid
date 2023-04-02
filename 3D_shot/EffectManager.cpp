#include "EffectManager.h"
#include "Effect.h"


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
	for (int i = 0; i < EFFECT_AMOUNT; i++)
	{
		delete effect[i];
	}
}

/// <summary>
/// 初期化処理
/// </summary>
void EffectManager::Initialize()
{
	//各エフェクトの読み込み
	effect[EXPLOSION] = new Effect(InputPath(EFFECT_FOLDER_PATH, EXPLOSION_EFFECT_PATH), EXPLOSION_SIZE);
	effect[FIRE] = new Effect(InputPath(EFFECT_FOLDER_PATH, FIRE_EFFECT_PATH), FIRE_SIZE);
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

/// <summary>
/// エフェクトパスの入力
/// </summary>
/// <param name="folderPath">エフェクトフォルダーのパス</param>
/// <param name="effectPath">エフェクトのパス</param>
/// <returns>エフェクトのパス</returns>
string EffectManager::InputPath(string folderPath, string effectPath)
{
	return string(folderPath + effectPath);
}