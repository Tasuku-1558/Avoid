#pragma once

#include <string>

using namespace std;

/// <summary>
/// シングルトン
/// モデル管理クラス
/// </summary>
class ModelManager final
{
public:
	
	//モデルの種類
	enum ModelType
	{
		PLAYER,			//プレイヤーモデル
		PLAYER_LING,	//プレイヤーリングモデル
		METEORITE,		//隕石モデル
		FIELD,			//ステージモデル
		MODEL_AMOUNT,	//モデルの数
	};

	static ModelManager& GetInstance();					  //アドレスを返す

	const int& GetModelHandle(ModelType modelType) const; //モデルハンドルの参照を返す

private:
	ModelManager();
	ModelManager(const ModelManager&);			//コピーコンストラクタ
	virtual ~ModelManager();

	void LoadAllModel();						//全てのモデルの読み込み
	void DeleteAllModel();						//全てのモデルの削除

	string InputPath(string folderPath,
					 string modelPath);			//モデルのパスを入力

	int modelHandle[MODEL_AMOUNT];				//モデルハンドル格納用

	//定数
	const string MODEL_FOLDER_PATH;		//Modelフォルダまでのパス
	const string PLAYER_PATH;			//playerモデルファイルのパス
	const string LING_PATH;				//lingモデルファイルのパス
	const string METEORITE_PATH;		//meteoriteモデルファイルのパス
	const string FIELD_PATH;			//fieldモデルファイルのパス

};