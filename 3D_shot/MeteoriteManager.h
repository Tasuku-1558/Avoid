#pragma once

#include <vector>
#include "DxLib.h"
#include "Meteorite.h"


class Player;
class Meteorite;
class Explosion;
class Evaluation;
class EarnScore;

class MeteoriteManager final
{
public:

	//MeteoriteManager実体へのポインタ定義
	std::vector<MeteoriteManager*> instance;

	 MeteoriteManager();
	~MeteoriteManager();

	//static void Initialize();							//初期化
	static void Finalize();
	static void Entry(Meteorite* newObj);				//登録
	static void Release(Meteorite* releaseObj);			//削除
	static void ReleaseAllObj();						//全て隕石の削除

	static void Update(float deltaTime, Player* player);	//更新
	bool PlayerAndMeteorite(Player* player, /*Meteorite* meteorite[]*/Meteorite* meteorite,  Explosion* explosion, Evaluation* evaluation, EarnScore* earnscore);		//当たりチェック;
	static void Draw();										//描画

	/*int GetSize() { return pendingObjects.size(); }*/

	

private:
	

	static MeteoriteManager* instance;
	std::vector<Meteorite*> pendingObjects;
	std::vector<Meteorite*> objects;

	double direction;						//プレイヤーと隕石の距離

	bool hit;								//隕石と衝突したか


	//静的定数
	static const float RADIUS_GOOD;			//goodの範囲
	static const float RADIUS_GREAT;		//greatの範囲
	static const float RADIUS_EXCELLENT;	//excellentの範囲
	static const float RADIUS_MISS;			//missの範囲
};