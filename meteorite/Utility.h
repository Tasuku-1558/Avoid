#pragma once


//���S�̃C���X�^���X���J��
#define SAFE_DELETE(p){ if(p) { delete p; p = nullptr; } }