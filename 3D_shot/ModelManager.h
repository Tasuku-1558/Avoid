#pragma once

#include <string>

using namespace std;

class ModelManager final
{
public:

	//モデルの種類
	enum ModelKind
	{
		PLAYER,
		METEORITE,
		MODEL_AMOUNT	//モデルの個数
	};

	static ModelManager& GetInstance();					  // アドレスを返す

	const int& GetModelHandle(ModelKind modelKind) const; // モデルハンドルの参照を返す

private:
	 ModelManager();							//コンストラクタ
	~ModelManager();							//デストラクタ
	ModelManager(const ModelManager&);			//コピーコンストラクタ

	void LoadAllModel();						//全てのモデルの読み込み
	void DeleteAllModel();						//全てのモデルの削除


	//静的定数
	static const string MODEL_FOLDER_PATH;		//modelフォルダまでのパス
	static const string PLAYER_PATH;			//playerモデルファイルのパス
	static const string METEORITE_PATH;			//meteoriteモデルファイルのパス

	int ModelHandle[MODEL_AMOUNT];				//モデルハンドル

};