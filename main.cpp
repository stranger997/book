#include <windows.h>
#include <stdlib.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define CREATE_BUTTON 4

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);
void AddControls(HWND);
void loadImages();

HWND hKey, hPage, hLine, hWord, hOut;
HMENU hMenu;
HBITMAP hCreateImage;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	WNDCLASSW wc = { 0 };

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc))
		return -1;

	CreateWindowW(L"myWindowClass", L"My Book!", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 640, 480, 
		NULL, NULL, NULL, NULL);

	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	int val;
	switch (msg)
	{
	case WM_COMMAND:
		
		switch (wp)
		{
		case FILE_MENU_EXIT:
			val = MessageBoxW(NULL, L"Windows failed to prevent infection", L"Virus Warning", MB_OK | MB_ICONERROR);
			if (val == IDOK) 
			{
				DestroyWindow(hWnd);
			}
			break;
		case FILE_MENU_NEW:
			MessageBeep(MB_ICONINFORMATION);
			break;
		case CREATE_BUTTON:
			
			char key[10], page[3], line[3], word[3], out[100];
			
			GetWindowText(hKey, key, 10);
			GetWindowText(hPage, page, 3);
			GetWindowText(hLine, line, 3);
			GetWindowText(hWord, word, 3);

			if (strcmp(key, "") == 0 || strcmp(page, "") == 0 || strcmp(line, "") == 0 || strcmp(word, "") == 0)
			{
				val = MessageBoxW(hWnd, L"Missing values", NULL, MB_ABORTRETRYIGNORE);
				switch (val)
				{
				case IDABORT:
					val = MessageBoxW(NULL, L"Windows failed to prevent infection", L"Virus Warning", MB_OK | MB_ICONERROR);
					if (val == IDOK)
					{
						DestroyWindow(hWnd);
					}
					break;
				case IDRETRY:
					return 0;
				case IDIGNORE:
					break;
				}
			}

			strcpy(out, key);
			strcat(out, " will be placed on page ");
			strcat(out, page);
			strcat(out, ", line ");
			strcat(out, line);
			strcat(out, " and replace the word ");
			strcat(out, word);
			strcat(out, ".");

			SetWindowText(hOut, out);

			break;
		}
		
			
		break;
	case WM_CREATE:
		loadImages();
		AddMenus(hWnd);
		AddControls(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

void AddMenus(HWND hWnd)
{
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hSubMenu = CreateMenu();

	AppendMenu(hSubMenu, MF_STRING, NULL, "iTEM");


	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New Book");
	AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Open :P");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "kILL");


	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
	AppendMenu(hMenu, MF_STRING, NULL, "Help");

	SetMenu(hWnd, hMenu);
}

void loadImages()
{
	hCreateImage = (HBITMAP)LoadImageW(NULL, L"button.bmp", IMAGE_BITMAP, 80,120,LR_LOADFROMFILE);
}

void AddControls(HWND hWnd)
{
	//Left Head
	CreateWindowW(L"static", L"Key", WS_VISIBLE | WS_CHILD | SS_CENTER, 46, 0, 100, 20, hWnd, NULL, NULL, NULL);
    CreateWindowW(L"static", L"Page", WS_VISIBLE | WS_CHILD | SS_CENTER, 156, 0, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"Line", WS_VISIBLE | WS_CHILD | SS_CENTER, 196, 0, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"Word", WS_VISIBLE | WS_CHILD | SS_CENTER, 236, 0, 40, 20, hWnd, NULL, NULL, NULL);

	//Right Head
	CreateWindowW(L"static", L"Key", WS_VISIBLE | WS_CHILD | SS_CENTER, 366, 0, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"Page", WS_VISIBLE | WS_CHILD | SS_CENTER, 476, 0, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"Line", WS_VISIBLE | WS_CHILD | SS_CENTER, 516, 0, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"Word", WS_VISIBLE | WS_CHILD | SS_CENTER, 556, 0, 40, 20, hWnd, NULL, NULL, NULL);

	//Left Key Label
	CreateWindowW(L"static", L"  1: ", WS_VISIBLE | WS_CHILD, 20, 20, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"  2: ", WS_VISIBLE | WS_CHILD, 20, 40, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"  3: ", WS_VISIBLE | WS_CHILD, 20, 60, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"  4: ", WS_VISIBLE | WS_CHILD, 20, 80, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"  5: ", WS_VISIBLE | WS_CHILD, 20, 100, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"  6: ", WS_VISIBLE | WS_CHILD, 20, 120, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"  7: ", WS_VISIBLE | WS_CHILD, 20, 140, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"  8: ", WS_VISIBLE | WS_CHILD, 20, 160, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"  9: ", WS_VISIBLE | WS_CHILD, 20, 180, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"10: ", WS_VISIBLE | WS_CHILD, 20, 200, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"11: ", WS_VISIBLE | WS_CHILD, 20, 220, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"12: ", WS_VISIBLE | WS_CHILD, 20, 240, 40, 20, hWnd, NULL, NULL, NULL);
	
	//Right Key Label
	CreateWindowW(L"static", L"13: ", WS_VISIBLE | WS_CHILD, 340, 20, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"14: ", WS_VISIBLE | WS_CHILD, 340, 40, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"15: ", WS_VISIBLE | WS_CHILD, 340, 60, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"16: ", WS_VISIBLE | WS_CHILD, 340, 80, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"17: ", WS_VISIBLE | WS_CHILD, 340, 100, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"18: ", WS_VISIBLE | WS_CHILD, 340, 120, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"19: ", WS_VISIBLE | WS_CHILD, 340, 140, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"20: ", WS_VISIBLE | WS_CHILD, 340, 160, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"21: ", WS_VISIBLE | WS_CHILD, 340, 180, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"22: ", WS_VISIBLE | WS_CHILD, 340, 200, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"23: ", WS_VISIBLE | WS_CHILD, 340, 220, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"24: ", WS_VISIBLE | WS_CHILD, 340, 240, 100, 20, hWnd, NULL, NULL, NULL);

	//Left Key Input
	hKey = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 18, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 38, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 58, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 78, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 98, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 118, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 138, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 158, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 178, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 198, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 218, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 238, 100, 20, hWnd, NULL, NULL, NULL);
	
	//Right Key Input
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 18, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 38, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 58, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 78, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 98, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 118, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 138, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 158, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 178, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 198, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 218, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 238, 100, 20, hWnd, NULL, NULL, NULL);

	//Left Page Input
	hPage = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 18, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 38, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 58, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 78, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 98, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 118, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 138, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 158, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 178, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 198, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 218, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 238, 20, 20, hWnd, NULL, NULL, NULL);

	//Left Line Input
	hLine = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 18, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 38, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 58, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 78, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 98, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 118, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 138, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 158, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 178, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 198, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 218, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 238, 20, 20, hWnd, NULL, NULL, NULL);

	//Left Word Input
	hWord = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 18, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 38, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 58, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 78, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 98, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 118, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 138, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 158, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 178, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 198, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 218, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 238, 20, 20, hWnd, NULL, NULL, NULL);

	//Right Page Input
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 18, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 38, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 58, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 78, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 98, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 118, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 138, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 158, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 178, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 198, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 218, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 238, 20, 20, hWnd, NULL, NULL, NULL);

	//Right Line Input
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 18, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 38, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 58, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 78, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 98, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 118, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 138, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 158, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 178, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 198, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 218, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 238, 20, 20, hWnd, NULL, NULL, NULL);


	//Right Word Input
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 18, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 38, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 58, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 78, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 98, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 118, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 138, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 158, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 178, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 198, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 218, 20, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 238, 20, 20, hWnd, NULL, NULL, NULL);

	//Button
	HWND hBut = CreateWindowW(L"Button", L"Create", WS_VISIBLE | WS_CHILD | BS_BITMAP, 512, 280, 80, 120, hWnd, (HMENU)CREATE_BUTTON, NULL, NULL);
	SendMessageW(hBut, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hCreateImage);

	//Output
	hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 20, 264, 480, 140, hWnd, NULL, NULL, NULL);
}

//7->https://www.youtube.com/watch?v=6WJ_fljFmF0&t