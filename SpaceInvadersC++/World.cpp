#include "World.h"

void World::DrawArea()
{
	// Set console code page to UTF-8 so console known how to interpret string data
	SetConsoleOutputCP(CP_UTF8);

	// Enable buffering to prevent VS from chopping up UTF-8 byte sequences
	setvbuf(stdout, nullptr, _IOFBF, 1000);

	HRSRC hResource = FindResource(hInstance, MAKEINTRESOURCE(IDR_TEXT1), L"TEXT");

	if (hResource)
	{
		HGLOBAL hLoadedResource = LoadResource(hInstance, hResource);

		if (hLoadedResource)
		{
			LPCSTR area = (LPCSTR)LockResource(hLoadedResource);

			if (area)
			{
				DWORD dwResourceSize = SizeofResource(hInstance, hResource);

				if (0 != dwResourceSize)
				{
					for (int i = 0; i < strnlen(area, 8915); i++) {
						cout << area[i];
					}
				}
			}
		}
	}

	setvbuf(stdout, NULL, _IONBF, 0);
}

void World::Refresh()
{
	this_thread::sleep_for(chrono::milliseconds(10));	
	GameObject tool; // for tools

	tool.SetPos(0, 0);

	for (int y = 0; y < 45; y++)
	{
		for (int x = 0; x < 150; x++)
		{
			cout << vBuf[y][x];
		}
	}

	while (worldIsRun)
	{
		for (int i = 0; i < 45; i++)
		{
			for (int j = 0; j < 150; j++)
			{
				if (vBuf2[i][j] == vBuf[i][j])
				{
					continue;
				}
				cout << vBuf2[i][j];
			}
		}
		cout << flush;
		copy(vBuf2.begin(), vBuf2.end(), vBuf.begin());
	}
}

void World::CreateWorld() {
	term.Terminal();  // Set virtual terminal settings
	term.SetScreenSize();

	printf(CSI "?1049h"); // enable alt buffer
	printf(CSI "?25l"); // hide cursor blinking

	DrawArea();

	GameObject myGun(vBuf, 5, 3, 15, 15); // Player cannon size and position 
	/*thread myChar(&MyCharGun::RunGun, myGun);
	myChar.detach();*/

	thread Ticks(&World::Refresh, this);
	Ticks.detach();
}

void World::RunWorld()
{
	CreateWorld();

	while (true)
	{
	}

	printf(CSI "?1049l"); // enable main buffer
}

