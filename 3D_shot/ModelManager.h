#pragma once

#include <string>

using namespace std;


/// <summary>
/// モデル管理クラス
/// </summary>
class ModelManager final
{
public:

	/// <summary>
	/// モデルの種類
	/// </summary>
	enum ModelType
	{
		PLAYER,
		PLAYER_LING,
		METEORITE,
		FIELD,
		MODEL_AMOUNT	//モデルの個数
	};

	static ModelManager& GetInstance();					  // アドレスを返す

	const int& GetModelHandle(ModelType modelType) const; // モデルハンドルの参照を返す

private:
	 ModelManager();							//コンストラクタ
	~ModelManager();							//デストラクタ

	 ModelManager(const ModelManager&);			//コピーコンストラクタ

	void LoadAllModel();						//全てのモデルの読み込み
	void DeleteAllModel();						//全てのモデルの削除


	int modelHandle[MODEL_AMOUNT];				//モデルハンドル格納用

	//静的定数
	static const string MODEL_FOLDER_PATH;		//modelフォルダまでのパス
	static const string PLAYER_PATH;			//playerモデルファイルのパス
	static const string LING_PATH;				//lingモデルファイルのパス
	static const string METEORITE_PATH;			//meteoriteモデルファイルのパス
	static const string FIELD_PATH;				//fieldモデルファイルのパス

};