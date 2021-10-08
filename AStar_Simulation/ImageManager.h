#pragma once
#include "Config.h"
#include "Singleton.h"

class Image;
class ImageManager : public Singleton<ImageManager>
{
private:
	map<string, Image*>	mapImages;
	//map<string, map<int, int>>	mapTest;

	//"enemy_3_bullet"
	/*
	* 이미지를 600000개를 등록했다.
	* 6개 중에 bullet.bmp를 찾는다.
	* 찾았으면 리턴한다.
	* 
	// 자료구조 : vector 장점 크기를 가변적으로 바꿀 수 있다.
	//					단점 삽입, 삭제가 필요하면 메모리할당과
							복사가 일어나서 속도가 느리다

				 map	장점 찾는 속도가 빠른 자료구조
						단점 자료구조 구현이 복잡하다
	*/

public:
	void Init();
	void Release();

	/*
	HRESULT Init(const char* fileName, int width, int height,
		bool isTrans = false, COLORREF transColor = NULL); // File 프레임이 없는 이미지
	HRESULT Init(const char* fileName, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = NULL);
		
	*/

	Image* AddImage(const char* fileName, int width, int height,
		bool isTrans = false, COLORREF transColor = NULL);	// 사용할 이미지를 등록하는 기능
	
	Image* AddImage(const char* fileName, int width, int height,
		int maxFrameX, int maxFrameY,
		bool isTrans = false, COLORREF transColor = NULL);
	
	Image* FindImage(const char* fileName);	// 등록된 이미지 중에 필요한 이미지를 찾는 기능
	void DeleteImage(const char* fileName);	// 사용이 종료된 이미지를 등록 해제하는 기능
};

