#include "Application.h"
#include "Chronometer.h"
#include <windows.h>
#include <d3d9.h>

void draw(char* data, int w, int h, int pitch, bool tictac) {
	for (int y = 0; y < h; ++y) {
		DWORD* row = (DWORD*)data;
		for (int x = 0; x < w; ++x) {
			int r = 0 + std::rand() / ((RAND_MAX + 1u) / 255);
			*row++ = D3DCOLOR_XRGB(255 - r * y / h, 255 * x / w, 255 * y / h);
		}
		data += pitch;
	}
}



int WINAPI WinMain(HINSTANCE _In_ hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Chronometer::toFile = 2;
	Application a;
	a.waitRR(false);
	a.createWindow(hInstance, "Minimal DX window", 640, 480);
	a.messagesLoop(draw);
	Chronometer::meanLap("Mean");
	return 0;
}