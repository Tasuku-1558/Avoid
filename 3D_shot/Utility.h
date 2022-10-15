#pragma once


//安全のインスタンスを開放
#define SAFE_DELETE(p){ if(p) { delete p; p = nullptr; } }