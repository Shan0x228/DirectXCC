#include "DirectXCCApplication.h"

int CALLBACK wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
	DirectXCCApplication app{};
	return app.Run();
}