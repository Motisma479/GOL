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
#include <scrnsave.h>
#include <algorithm>

#define COLOR_ALIVE 159, 223, 76
#define COLOR_DEAD 37, 27, 44
#include "GOL.hpp"

#include "Gen_Shape.hpp"

constexpr int bitmapRes[2] = { 180, 100 };
GOL<bitmapRes[0], bitmapRes[1]> gol;

Gdiplus::Bitmap* bp = nullptr;


BOOL WINAPI RegisterDialogClasses(HANDLE hInstance)
{
    return TRUE;
}
BOOL WINAPI ScreenSaverConfigureDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	return FALSE;
}

void WriteData()
{
    Gdiplus::BitmapData bmdata;
    Gdiplus::Rect rect(0, 0, bitmapRes[0], bitmapRes[1]);
    bp->LockBits(&rect, Gdiplus::ImageLockModeWrite, PixelFormat32bppRGB, &bmdata);

	unsigned int* data = (unsigned int*)((char*)bmdata.Scan0);
	auto source = gol.GetImageData();
	std::copy(source, source + bitmapRes[0] * bitmapRes[1], data);

    bp->UnlockBits(&bmdata);
}

void DrawScreen(HDC hdc, HWND hwnd)
{
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
		
		if (gol.update(100))
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

		bp = new Gdiplus::Bitmap(bitmapRes[0], bitmapRes[1], PixelFormat32bppRGB);

		SetTimer(hwnd, 1, 0, NULL); // 2000ms

		//set the initial cell in the GOL.
		for (const auto& i : genShape_5(20, 50))
		{
			gol.SetCell(i[0], i[1], true);
		}
		for (const auto& i : genShape_5(150, 50))
		{
			gol.SetCell(i[0], i[1], true);
		}
		for (const auto& i : genShape_5(50, 50))
		{
			gol.SetCell(i[0], i[1], true);
		}
		for (const auto& i : genShape_5(110, 50))
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