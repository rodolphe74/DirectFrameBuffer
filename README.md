# DirectFrameBuffer
Draw directly in DirectX9 frame buffer. DirectX9 plumbing is encapsulated in a ```Application``` class.

```C++
#include "Application.h"
#include "Chronometer.h"
#include <windows.h>

class MyApplication : public Application {
	void drawOnDxBackedBuffer() {
		drawOnDxBackedBufferSample();
	}
};

int WINAPI WinMain(HINSTANCE _In_ hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Chronometer::toFile = 2;
	MyApplication a;
	a.waitRR(false);
	a.createWindow(hInstance, "Minimal DX window", 640, 480);
	a.messagesLoop();
	Chronometer::meanLap("Mean");
	return 0;
}
```
