//#pragma once
//
//#include <vector>
//#include "DxLib.h"
//#include "Meteorite.h"
//
//
//class Player;
//class Meteorite;
//class Explosion;
//class Evaluation;
//class EarnScore;
//
//class MeteoriteManager final
//{
//public:
//
//	//MeteoriteManager���̂ւ̃|�C���^��`
//	std::vector<MeteoriteManager*> instance;
//
//	 MeteoriteManager();
//	~MeteoriteManager();
//
//	//static void Initialize();							//������
//	static void Finalize();
//	static void Entry(Meteorite* newObj);				//�o�^
//	static void Release(Meteorite* releaseObj);			//�폜
//	static void ReleaseAllObj();						//�S��覐΂̍폜
//
//	static void Update(float deltaTime, Player* player);	//�X�V
//	void PlayerAndMeteorite(Player* player, /*Meteorite* meteorite[]*/Meteorite* meteorite,  Explosion* explosion, Evaluation* evaluation, EarnScore* earnscore);		//������`�F�b�N;
//	static void Draw();										//�`��
//	
//
//private:
//	
//
//	static MeteoriteManager* instance;
//	std::vector<Meteorite*> pendingObjects;
//	std::vector<Meteorite*> objects;
//
//	double direction;						//�v���C���[��覐΂̋���
//
//	bool hit;								//覐΂ƏՓ˂�����
//
//
//	//�ÓI�萔
//	static const float RADIUS_GOOD;			//good�͈̔�
//	static const float RADIUS_GREAT;		//great�͈̔�
//	static const float RADIUS_EXCELLENT;	//excellent�͈̔�
//	static const float RADIUS_MISS;			//miss�͈̔�
//};