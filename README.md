# DirectFrameBuffer
Draw directly in DirectX9 frame buffer.\
DirectX9 plumbing is encapsulated in a ```Application``` class.

```C++
#include "Application.h"
#include "Chronometer.h"
#include <windows.h>
#include <d3d9.h>

void drawMoire(char* data, int w, int h, int pitch, bool tictac) {
	for (int y = 0; y < h; ++y) {
		DWORD* row = (DWORD*)data;
		for (int x = 0; x < w; ++x) {
			if (y % 3)
				*row++ = tictac ? D3DCOLOR_XRGB(95, 74, 124) : D3DCOLOR_XRGB(0, 255, 0);
			else{
				*row++ = tictac ? D3DCOLOR_XRGB(0, 255, 0) : D3DCOLOR_XRGB(95, 74, 124);
			}
			if (x % 3)
				*row++ = tictac ? D3DCOLOR_XRGB(95, 74, 124) : D3DCOLOR_XRGB(0, 255, 0);
			else {
				*row++ = tictac ? D3DCOLOR_XRGB(0, 255, 0) : D3DCOLOR_XRGB(95, 74, 124);
			}
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
	a.messagesLoop(drawInterferences);
	Chronometer::meanLap("Mean");
	return 0;
}
```
