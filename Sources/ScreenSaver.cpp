#ifndef UNICODE
#define UNICODE
#endif

// "#pragma comment" lines only work in visual studio; otherwise include these libraries with the linker
#pragma comment(lib, "Gdiplus.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "comctl32.lib")
#ifdef UNICODE
#pragma comment(lib, "ScrnSavw.lib")
#else
#pragma comment(lib, "ScrnSave.lib")
#endif

#include <Windows.h>
#include <gdiplus.h>
#include <Scrnsave.h>
#include <algorithm>

#include "GOL.hpp"
#include "Gen_Shape.hpp"
#include "ScreenSaver.hpp"
#include "ScreenRenderer.hpp"

Maths::IVec2 bitmapRes(100, 100);
Gdiplus::Bitmap* bp = nullptr;

GOL<100, 100> gol;

BOOL WINAPI RegisterDialogClasses(HANDLE hInstance)
{
    return TRUE;
}

BOOL WINAPI ScreenSaverConfigureDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hSpeed;
    static HWND hOK;
    HRESULT result;

    switch(message)
    {
    case WM_INITDIALOG:
        result = LoadString(hMainInstance, idsAppName, szAppName, APPNAMEBUFFERLEN);
        result = LoadString(hMainInstance, idsIniFile, szIniFile, MAXFILELEN);
        hOK = GetDlgItem(hDlg, ID_OK);
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_OK:

        case ID_CANCEL:
			EndDialog(hDlg, LOWORD(wParam) == ID_OK);

			return TRUE;
		default:
			return false;
        }

    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return true;
    }
    return FALSE;
}

void WriteData()
{
    unsigned int width = bp->GetWidth();
    unsigned int height = bp->GetHeight();
    {
        Gdiplus::BitmapData bmdata;
        Gdiplus::Rect rect(0, 0, width, height);
        bp->LockBits(&rect, Gdiplus::ImageLockModeWrite, PixelFormat32bppRGB, &bmdata);
        for (unsigned int y = 0; y < height; ++y)
        {
            unsigned int* line = (unsigned int*)((char*)bmdata.Scan0 + (size_t)bmdata.Stride * y);
            auto source = gol.GetLineData(y);
            std::copy(source, source + width, line);
        }
        bp->UnlockBits(&bmdata);
    }
}

void DrawScreen(HDC hdc, HWND hwnd)
{
	/*for (const auto& i : genShape_4(126, 126))
	{
		gol.SetCell(i[0], i[1], true);
	}
	for (const auto& i : genShape_4(124, 126))
	{
		gol.SetCell(i[0], i[1], true);
	}*/

	RECT rcClient;
	GetClientRect(hwnd, &rcClient);
	Gdiplus::Graphics graphics(hdc);

	
	gol.Print();
	WriteData();

	INT windowWidth = rcClient.right - rcClient.left;
	INT windowHeight = rcClient.bottom - rcClient.top;
	float percentWidth = windowWidth / (float)(bp->GetWidth() - 1);
	float percentHeight = windowHeight / (float)(bp->GetHeight() - 1);
	float percent = windowWidth > windowHeight ? percentHeight : percentWidth;
	Gdiplus::Rect gdiRect;
	gdiRect.Width = (INT)(bp->GetWidth() * percent);
	gdiRect.Height = (INT)(bp->GetHeight() * percent);
	gdiRect.X = (windowWidth - (INT)gdiRect.Width) / 2;
	gdiRect.Y = (windowHeight - (INT)gdiRect.Height) / 2;
	//FillRect(hdc, &rcClient, (HBRUSH)GetStockObject(BLACK_BRUSH));
	graphics.SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
	graphics.DrawImage(reinterpret_cast<Gdiplus::Image*>(bp), gdiRect);
}

Gdiplus::GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken;

// handle screen saver window messages; most are already handled by "DefScreenSaverProc"
LRESULT WINAPI ScreenSaverProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_TIMER:
	{
		RECT rect;
		GetClientRect(hwnd, &rect);
		InvalidateRect(hwnd, &rect, FALSE);
	}
	return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		if (gol.update(1))
			DrawScreen(hdc, hwnd);
		EndPaint(hwnd, &ps);
	}
	return 0;

	case WM_CREATE:
	{
		// Retrieve the application name from the .rc file. 
		LoadString(hMainInstance, idsAppName, szAppName, APPNAMEBUFFERLEN);

		// Retrieve the .ini (or registry) file name. 
		LoadString(hMainInstance, idsIniFile, szIniFile, MAXFILELEN);

		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

		bp = new Gdiplus::Bitmap(bitmapRes.x, bitmapRes.y, PixelFormat32bppRGB);

		SetTimer(hwnd, 1, 0, NULL); // 2000ms

		
		for (const auto& i : genShape_3(50, 50))
		{
			gol.SetCell(i[0], i[1], true);
		}
	}
	return 0;

	case WM_DESTROY:
		KillTimer(hwnd, 1);

		Gdiplus::GdiplusShutdown(gdiplusToken);

		return 0;
	}
	return DefScreenSaverProc(hwnd, msg, wParam, lParam);
}