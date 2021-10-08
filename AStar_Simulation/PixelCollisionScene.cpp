#include "PixelCollisionScene.h"
#include "Image.h"
#include "CommonFunction.h"

HRESULT PixelCollisionScene::Init()
{
    SetWindowSize(50, 50, PIXELMAP_SIZE_X, PIXELMAP_SIZE_Y);

    ball = ImageManager::GetSingleton()->AddImage("Image/ball.BMP",
        60, 60, true, RGB(255, 0, 255));

    mountain = ImageManager::GetSingleton()->AddImage("Image/mountain.BMP",
        PIXELMAP_SIZE_X, PIXELMAP_SIZE_Y, true, RGB(255, 0, 255));

    posBall.x = PIXELMAP_SIZE_X / 2.0f;
    posBall.y = 100.0f;

    moveSpeed = 0.0f;
    maxMoveSpeed = 1200.0f;
    accel = 98.1f;

    return S_OK;
}

void PixelCollisionScene::Update()
{
    /*
        1. 방향키 좌우를 써서 볼을 이동시킨다.
        2. 화면 좌측에 탱크를 만들고 스페이스 바를 눌러서 볼을 발사
        3. 지형과 볼(미사일)이 충돌하면 지형이 파인다.
    */

    moveSpeed += (accel * TimerManager::GetSingleton()->GetDeltaTime());
    moveSpeed = min(moveSpeed, maxMoveSpeed);

    float tempPosY = posBall.y + moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
    //posBall.y += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();

    float x = posBall.x;
    float y = tempPosY + ball->GetHeight() / 2.0f;

    COLORREF color;
    WORD r, g, b;
    for (int i = 0; i < 10; i++)
    {
        color = GetPixel(mountain->GetMemDC(),
            posBall.x, tempPosY + ball->GetHeight() / 2.0f + i);

        r = GetRValue(color);
        g = GetGValue(color);
        b = GetBValue(color);

        if (!(r == 255 && g == 0 && b == 255))
        {
            break;
        }
        else
        {
            posBall.y = tempPosY;
            break;
        }
    }

    //if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
    //{
    //    cout << r << ", " << g << ", " << b << endl;
    //}
}

void PixelCollisionScene::Render(HDC hdc)
{
    PatBlt(hdc, 0, 0, PIXELMAP_SIZE_X, PIXELMAP_SIZE_Y, WHITENESS);

    mountain->Render(hdc, PIXELMAP_SIZE_X / 2, PIXELMAP_SIZE_Y / 2);

    ball->Render(hdc, posBall.x, posBall.y);
}

void PixelCollisionScene::Release()
{
}
