// main.cpp
/*
	목표.
	 1. 제어권이 없는 큰 네모가 좌로 이동 (속도 : 10)
	 2. 위의 큰 네모가 좌측 벽에 부딪히면 방향이 바뀜 (좌 -> 우)
	 3. 우측 벽에 부딪히면 방향이 바뀜 (우 -> 좌)
	 4. 스페이스 바 입력 시 작은 네모가 미사일처럼 발사된다. (위쪽 방향으로)
	 5. 작은 네모와 자동으로 움직이는 큰 네모가 부딪히면 둘 다 사라진다.
	 6. 작은 네모는 화면을 벗어나면 다시 발사 가능하다.
	 7. 위에서 움직이는 큰 네모는 일정시간마다 미사일을 발사한다.
	 8. 밑에서 움직이는 큰 네모(플레이어)도 적의 미사일을 맞으면 화면에서 사라진다.
	 9. 각자 HP 3씩이 주어진다.
	 10. 코드 리팩토링 

	 Q1. 가만히 있을 때 화면이 갱신되게 하는 방법 ( Timer객체를 만들어서 해결 )
	 Q2. 좌우측 벽에 부딪혔는지 확인하는 방법 ( 체크해야 하는 변수를 알고 있으므로 할 수 있다 )

*/

/*
	실습1. 210906 파일을 다운로드 받는다.
	실습2. config.h / GameEntity 클래스 / MainGame 클래스를 만들고
	상속 구조를 구현한다.
	실습3. main.cpp 에 있는 코드를 g_mainGame 객체를 만들어서 옮긴다.
	기존과 같이 동작하는지 확인한다.
*/

#include <Windows.h>
#include "CommonFunction.h"
#include "MainGame.h"

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

// 전역변수
POINT		g_ptMouse;
HINSTANCE	g_hInstance;
HWND		g_hWnd;
LPSTR		g_lpszClass = (LPSTR)TEXT("윈메인의 시작");
MainGame	g_mainGame;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance,
	LPSTR _lpszCmdParam, int nCmdShow)
{
	// 윈도우를 생성하기 위한 기본 셋팅
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 핸들형변환
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = _hInstance;
	wndClass.lpfnWndProc = WndProc;				// 함수포인터(콜백함수)
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = g_lpszClass;
	wndClass.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;	// bit연산

	// 윈도우 클래스 등록
	RegisterClass(&wndClass);

	// 윈도우 생성
	g_hWnd = CreateWindow(g_lpszClass, g_lpszClass, WS_OVERLAPPEDWINDOW, 
		WIN_START_POS_X, WIN_START_POS_Y, WIN_SIZE_X, WIN_SIZE_Y,
		NULL, NULL, _hInstance, NULL);

	SetWindowSize(WIN_START_POS_X, WIN_START_POS_Y,
		WIN_SIZE_X, WIN_SIZE_Y);

	// 메인게임 초기화
	g_mainGame.Init();


	// 윈도우 출력
	ShowWindow(g_hWnd, nCmdShow);


	// 메시지 큐에 있는 메시지 처리
	MSG message;
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	// 메인게임 해제
	g_mainGame.Release();

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	static bool isUpdate = true;

	switch (iMessage)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			//isUpdate = !isUpdate;
			break;
		}
		break;
	case WM_TIMER:
		if (isUpdate)
		{
			g_mainGame.Update();		
		}

		break;
	case WM_PAINT:		// 윈도우 화면이 다시 그려지는 경우 발생하는 메시지
		hdc = BeginPaint(g_hWnd, &ps);

		g_mainGame.Render(hdc);

		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:	// 닫기 버튼 메시지처리 (프로그램 종료)
		PostQuitMessage(0);
		break;
	}

	return g_mainGame.MainProc(hWnd, iMessage, wParam, lParam);
}
