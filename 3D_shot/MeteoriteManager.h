#pragma once

#include <vector>
#include "DxLib.h"
#include "Meteorite.h"


class Player;

class MeteoriteManager final
{
public:
	static void Initialize();							//‰Šú‰»
	static void Finalize();
	static void Entry(Meteorite* newObj);				//“o˜^
	static void Release(Meteorite* releaseObj);			//íœ
	static void ReleaseAllObj();						//‘S‚Äè¦Î‚Ìíœ

	static void Update(float deltaTime, Player* player);	//XV
	static void Draw();										//•`‰æ
	int GetSize();
private:
	 MeteoriteManager();
	~MeteoriteManager();

	static MeteoriteManager* instance;
	std::vector<Meteorite*> pendingObjects;
	std::vector<Meteorite*> objects;
};