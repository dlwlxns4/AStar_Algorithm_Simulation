#include "Button.h"
#include "Image.h"
#include "ButtonFunction.h"

HRESULT Button::Init()
{
	return E_NOTIMPL;
}

HRESULT Button::Init(int posX, int posY)
{
	//pF = AddNum;

	//int c = AddNum(10, 20);
	//int d = pF(10, 20);

	//pF = MinusNum;
	//d = pF(10, 20);


	img = ImageManager::GetSingleton()->FindImage("Image/button.bmp");
	pos.x = posX;
	pos.y = posY;

	shape.left = pos.x - img->GetFrameWidth() / 2;
	shape.right = pos.x + img->GetFrameWidth() / 2;
	shape.top = pos.y - img->GetFrameHeight() / 2;
	shape.bottom = pos.y + img->GetFrameHeight() / 2;

	state = Button_State::None;

	return S_OK;
}

void Button::Update()
{
	// 마우스 커서가 충돌영역에 들어갔는지
	if (PtInRect(&shape, g_ptMouse))
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{
			state = Button_State::Down;
		}
		else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON)
			&& state == Button_State::Down)
		{
			state = Button_State::Up;

			// 버튼 기능 수행 (함수포인터를 활용)
			funcPtr();

			if (bf && pFunc)
				(bf->*pFunc)(arg);

			//switch (type)
			//{
			//case Button_Type::GotoBattle:
			//	SceneManager::GetSingleton()->ChangeScene("전투씬", "로딩씬");
			//	break;
			//case Button_Type::GotoResult:
			//	SceneManager::GetSingleton()->ChangeScene("전투씬", "로딩씬");
			//	break;
			//case Button_Type::Close:
			//	Release();
			//	break;
			//}
			return;
		}
	}
	else
	{
		state = Button_State::None;
	}
}

void Button::Render(HDC hdc)
{

	switch (state)
	{
	case Button_State::None:
	case Button_State::Up:
		if (img)
			img->Render(hdc, pos.x, pos.y, 0, 0);
		break;
	case Button_State::Down:
		if (img)
			img->Render(hdc, pos.x, pos.y, 0, 1);
		break;
	}

	//Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);
}

void Button::Release()
{
}
