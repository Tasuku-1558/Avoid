#pragma once

#include <vector>
#include "DxLib.h"
#include "Meteorite.h"
//#include "Math3D.h"

class Player;

class MeteoriteManager final
{
public:
	static void Initialize();							//������
	static void Finalize();
	static void Entry(Meteorite* newObj);				//�o�^
	static void Release(Meteorite* releaseObj);			//�폜
	static void ReleaseAllObj();						//�S��覐΂̍폜

	static void Update(float deltaTime, Player* player);	//�X�V
	static void Draw();										//�`��
	int GetSize();
private:
	 MeteoriteManager();
	~MeteoriteManager();

	static MeteoriteManager* instance;
	std::vector<Meteorite*> pendingObjects;
	std::vector<Meteorite*> objects;
};