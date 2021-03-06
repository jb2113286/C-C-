/*#include "ScanConterts.h"
std::string chosenColour;
void  MainScan(ScandContents scan);
void CheckColour(COLORREF pixel, int x, int y);

bool  ColourMatch(COLORREF pixel);


int main()
{
	std::string gameWindow;
	std::cout << "Enter game window to triggerbot  // 回车继续" << std::endl;
	std::getline(std::cin, gameWindow);
	gameWindow = "Zenmap";
	HWND appWnd = FindWindow(0, gameWindow.c_str());
	RECT rcClientPositioning;
	while (!appWnd)
	{

		system("CLS");
		appWnd = FindWindow(0, gameWindow.c_str());
		std::cout << "Looking for // 正在寻找" << gameWindow << std::endl;
		Sleep(1000);

	}


	std::cout << "Found game window // 找到游戏窗口" << gameWindow << std::endl;

	while (atoi(chosenColour.c_str()) < 1 || atoi(chosenColour.c_str()) > 3)
	{

		system("CLS");
		std::cout << "Choose whiich color to trigger against\n 选择透视颜色\n" <<
			"1.Red \\ 红色 \n2.Green \\ 绿色 \n3.Blue \\ 蓝色"
			<< std::endl;
		std::getline(std::cin, chosenColour);
	}


	std::string color;
	if (chosenColour == "1")color = "Red ";
	else if (chosenColour == "2")color = "Green ";
	else if (chosenColour == "3")color = "Blue ";
	system("CLS");
	
	std::cout << "Triggerbot ONLINE , hover over" << color << "to shoot ..." << std::endl;


	GetWindowRect(appWnd, &rcClientPositioning);


	HDC hdcMain = GetDC(HWND_DESKTOP);
	int startingX = rcClientPositioning.right - ((rcClientPositioning.right - rcClientPositioning.left) / 2);
	int startingY = rcClientPositioning.bottom - ((rcClientPositioning.bottom - rcClientPositioning.top) / 2);


	ScandContents scan(startingX, startingY, hdcMain, 30, 40, -30, -30);
	MainScan(scan);

	
	system("PAUSE");

}


void  MainScan(ScandContents scan)
{
	int debugRuntime = clock();
	while (true)
	{

		for (int y = scan.StartY + scan.DeductY; y < scan.StartY + scan.CompareY; y+=3)
		{
			for (int x = scan.StartX + scan.DeductX; x < scan.StartX + scan.CompareX; x+=3)
			{
				//Sleep(100);
				SetCursorPos(x, y);
				CheckColour(GetPixel(scan.Hdc, x, y), x, y);
				if (GetAsyncKeyState(VK_DELETE)) 
				{	
					exit(0);
				}
			
			}
		}

		std::cout <<  " Took " << clock() - debugRuntime << "milliseconds" << std::endl;
		debugRuntime = clock();

	}
}




void CheckColour(COLORREF pixel, int x, int y) 
{
	if (ColourMatch(pixel)) 
	{
		mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);



	}



}

bool  ColourMatch(COLORREF pixel) 
{
	int r = GetRValue(pixel);
	int g = GetRValue(pixel);
	int b = GetRValue(pixel);
	//red
	if (chosenColour == "1") 
	{
		if (r > 50 && g < 40 && b < 40)
		{
			return true;
		}
	}
	//green
	if (chosenColour == "2")
	{
		if (r < 40 && g < 50 && b < 40)
		{
			return true;
		}
	}
	//blue
	if (chosenColour == "3")
	{
		if (r < 50 && g < 40 && b < 50)
		{
			return true;
		}
	}

	return false;



}




*/
