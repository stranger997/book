#include <windows.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define CREATE_BUTTON 4

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);
void AddControls(HWND);
void loadImages();

//Define Variables
HWND hKey1, hPage1, hLine1, hWord1;
HWND hKey2, hPage2, hLine2, hWord2;
HWND hKey3, hPage3, hLine3, hWord3;
HWND hKey4, hPage4, hLine4, hWord4;
HWND hKey5, hPage5, hLine5, hWord5;
HWND hKey6, hPage6, hLine6, hWord6;
HWND hKey7, hPage7, hLine7, hWord7;
HWND hKey8, hPage8, hLine8, hWord8;
HWND hKey9, hPage9, hLine9, hWord9;
HWND hKey10, hPage10, hLine10, hWord10;
HWND hKey11, hPage11, hLine11, hWord11;
HWND hKey12, hPage12, hLine12, hWord12;
HWND hKey13, hPage13, hLine13, hWord13;
HWND hKey14, hPage14, hLine14, hWord14;
HWND hKey15, hPage15, hLine15, hWord15;
HWND hKey16, hPage16, hLine16, hWord16;
HWND hKey17, hPage17, hLine17, hWord17;
HWND hKey18, hPage18, hLine18, hWord18;
HWND hKey19, hPage19, hLine19, hWord19;
HWND hKey20, hPage20, hLine20, hWord20;
HWND hKey21, hPage21, hLine21, hWord21;
HWND hKey22, hPage22, hLine22, hWord22;
HWND hKey23, hPage23, hLine23, hWord23;
HWND hKey24, hPage24, hLine24, hWord24;
HWND hOut;

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
			
			//Variables from forms to  char
			char out[2400];

			char key1[10], page1[3], line1[3], word1[3];
			
			GetWindowText(hKey1, key1, 10);
			GetWindowText(hPage1, page1, 3);
			GetWindowText(hLine1, line1, 3);
			GetWindowText(hWord1, word1, 3);

			char key2[10], page2[3], line2[3], word2[3];

			GetWindowText(hKey2, key2, 10);
			GetWindowText(hPage2, page2, 3);
			GetWindowText(hLine2, line2, 3);
			GetWindowText(hWord2, word2, 3);

			char key3[10], page3[3], line3[3], word3[3];

			GetWindowText(hKey3, key3, 10);
			GetWindowText(hPage3, page3, 3);
			GetWindowText(hLine3, line3, 3);
			GetWindowText(hWord3, word3, 3);

			char key4[10], page4[3], line4[3], word4[3];

			GetWindowText(hKey4, key4, 10);
			GetWindowText(hPage4, page4, 3);
			GetWindowText(hLine4, line4, 3);
			GetWindowText(hWord4, word4, 3);

			char key5[10], page5[3], line5[3], word5[3];

			GetWindowText(hKey5, key5, 10);
			GetWindowText(hPage5, page5, 3);
			GetWindowText(hLine5, line5, 3);
			GetWindowText(hWord5, word5, 3);

			char key6[10], page6[3], line6[3], word6[3];

			GetWindowText(hKey6, key6, 10);
			GetWindowText(hPage6, page6, 3);
			GetWindowText(hLine6, line6, 3);
			GetWindowText(hWord6, word6, 3);

			char key7[10], page7[3], line7[3], word7[3];

			GetWindowText(hKey7, key7, 10);
			GetWindowText(hPage7, page7, 3);
			GetWindowText(hLine7, line7, 3);
			GetWindowText(hWord7, word7, 3);

			char key8[10], page8[3], line8[3], word8[3];

			GetWindowText(hKey8, key8, 10);
			GetWindowText(hPage8, page8, 3);
			GetWindowText(hLine8, line8, 3);
			GetWindowText(hWord8, word8, 3);

			char key9[10], page9[3], line9[3], word9[3];

			GetWindowText(hKey9, key9, 10);
			GetWindowText(hPage9, page9, 3);
			GetWindowText(hLine9, line9, 3);
			GetWindowText(hWord9, word9, 3);

			char key10[10], page10[3], line10[3], word10[3];

			GetWindowText(hKey10, key10, 10);
			GetWindowText(hPage10, page10, 3);
			GetWindowText(hLine10, line10, 3);
			GetWindowText(hWord10, word10, 3);

			char key11[10], page11[3], line11[3], word11[3];

			GetWindowText(hKey11, key11, 10);
			GetWindowText(hPage11, page11, 3);
			GetWindowText(hLine11, line11, 3);
			GetWindowText(hWord11, word11, 3);

			char key12[10], page12[3], line12[3], word12[3];

			GetWindowText(hKey12, key12, 10);
			GetWindowText(hPage12, page12, 3);
			GetWindowText(hLine12, line12, 3);
			GetWindowText(hWord12, word12, 3);


			if (strcmp(key1, "") == 0 || strcmp(page1, "") == 0 || strcmp(line1, "") == 0 || strcmp(word1, "") == 0 ||
				strcmp(key2, "") == 0 || strcmp(page2, "") == 0 || strcmp(line2, "") == 0 || strcmp(word2, "") == 0 || 
				strcmp(key3, "") == 0 || strcmp(page3, "") == 0 || strcmp(line3, "") == 0 || strcmp(word3, "") == 0 || 
				strcmp(key4, "") == 0 || strcmp(page4, "") == 0 || strcmp(line4, "") == 0 || strcmp(word4, "") == 0 || 
				strcmp(key5, "") == 0 || strcmp(page5, "") == 0 || strcmp(line5, "") == 0 || strcmp(word5, "") == 0 || 
				strcmp(key6, "") == 0 || strcmp(page6, "") == 0 || strcmp(line6, "") == 0 || strcmp(word6, "") == 0 || 
				strcmp(key7, "") == 0 || strcmp(page7, "") == 0 || strcmp(line7, "") == 0 || strcmp(word7, "") == 0 || 
				strcmp(key8, "") == 0 || strcmp(page8, "") == 0 || strcmp(line8, "") == 0 || strcmp(word8, "") == 0 || 
				strcmp(key9, "") == 0 || strcmp(page9, "") == 0 || strcmp(line9, "") == 0 || strcmp(word9, "") == 0 || 
				strcmp(key10, "") == 0 || strcmp(page10, "") == 0 || strcmp(line10, "") == 0 || strcmp(word10, "") == 0 || 
				strcmp(key11, "") == 0 || strcmp(page11, "") == 0 || strcmp(line11, "") == 0 || strcmp(word11, "") == 0 || 
				strcmp(key12, "") == 0 || strcmp(page12, "") == 0 || strcmp(line12, "") == 0 || strcmp(word12, "") == 0 
//				|| 
//				strcmp(key13, "") == 0 || strcmp(page13, "") == 0 || strcmp(line13, "") == 0 || strcmp(word13, "") == 0 || 
//				strcmp(key14, "") == 0 || strcmp(page14, "") == 0 || strcmp(line14, "") == 0 || strcmp(word14, "") == 0 || 
//				strcmp(key15, "") == 0 || strcmp(page15, "") == 0 || strcmp(line15, "") == 0 || strcmp(word15, "") == 0 || 
//				strcmp(key16, "") == 0 || strcmp(page16, "") == 0 || strcmp(line16, "") == 0 || strcmp(word16, "") == 0 || 
//				strcmp(key17, "") == 0 || strcmp(page17, "") == 0 || strcmp(line17, "") == 0 || strcmp(word17, "") == 0 || 
//				strcmp(key18, "") == 0 || strcmp(page18, "") == 0 || strcmp(line18, "") == 0 || strcmp(word18, "") == 0 || 
//				strcmp(key19, "") == 0 || strcmp(page19, "") == 0 || strcmp(line19, "") == 0 || strcmp(word19, "") == 0 || 
//				strcmp(key20, "") == 0 || strcmp(page20, "") == 0 || strcmp(line20, "") == 0 || strcmp(word20, "") == 0 || 
//				strcmp(key21, "") == 0 || strcmp(page21, "") == 0 || strcmp(line21, "") == 0 || strcmp(word21, "") == 0 || 
//				strcmp(key22, "") == 0 || strcmp(page22, "") == 0 || strcmp(line22, "") == 0 || strcmp(word22, "") == 0 || 
//				strcmp(key23, "") == 0 || strcmp(page23, "") == 0 || strcmp(line23, "") == 0 || strcmp(word23, "") == 0 || 
//				strcmp(key24, "") == 0 || strcmp(page24, "") == 0 || strcmp(line24, "") == 0 || strcmp(word24, "") == 0 
				)
			{
				val = MessageBoxW(hWnd, L"Missing values", NULL, MB_ABORTRETRYIGNORE | MB_ICONWARNING);
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

			strcpy(out, key1);
			strcat(out, " will be placed on page ");
			strcat(out, page1);
			strcat(out, ", line ");
			strcat(out, line1);
			strcat(out, " and replace the word ");
			strcat(out, word1);
			strcat(out, ".                     ");

			strcat(out, key2);
			strcat(out, " will be placed on page ");
			strcat(out, page2);
			strcat(out, ", line ");
			strcat(out, line2);
			strcat(out, " and replace the word ");
			strcat(out, word2);
			strcat(out, ".                     ");

			strcat(out, key3);
			strcat(out, " will be placed on page ");
			strcat(out, page3);
			strcat(out, ", line ");
			strcat(out, line3);
			strcat(out, " and replace the word ");
			strcat(out, word3);
			strcat(out, ".                     ");

			strcat(out, key4);
			strcat(out, " will be placed on page ");
			strcat(out, page4);
			strcat(out, ", line ");
			strcat(out, line4);
			strcat(out, " and replace the word ");
			strcat(out, word4);
			strcat(out, ".                     ");

			strcat(out, key5);
			strcat(out, " will be placed on page ");
			strcat(out, page5);
			strcat(out, ", line ");
			strcat(out, line5);
			strcat(out, " and replace the word ");
			strcat(out, word5);
			strcat(out, ".                     ");

			strcat(out, key6);
			strcat(out, " will be placed on page ");
			strcat(out, page6);
			strcat(out, ", line ");
			strcat(out, line6);
			strcat(out, " and replace the word ");
			strcat(out, word6);
			strcat(out, ".                     ");

			strcat(out, key7);
			strcat(out, " will be placed on page ");
			strcat(out, page7);
			strcat(out, ", line ");
			strcat(out, line7);
			strcat(out, " and replace the word ");
			strcat(out, word7);
			strcat(out, ".                     ");

			strcat(out, key8);
			strcat(out, " will be placed on page ");
			strcat(out, page8);
			strcat(out, ", line ");
			strcat(out, line8);
			strcat(out, " and replace the word ");
			strcat(out, word8);
			strcat(out, ".                     ");

			strcat(out, key9);
			strcat(out, " will be placed on page ");
			strcat(out, page9);
			strcat(out, ", line ");
			strcat(out, line9);
			strcat(out, " and replace the word ");
			strcat(out, word9);
			strcat(out, ".                     ");

			strcat(out, key10);
			strcat(out, " will be placed on page ");
			strcat(out, page10);
			strcat(out, ", line ");
			strcat(out, line10);
			strcat(out, " and replace the word ");
			strcat(out, word10);
			strcat(out, ".                     ");

			strcat(out, key11);
			strcat(out, " will be placed on page ");
			strcat(out, page11);
			strcat(out, ", line ");
			strcat(out, line11);
			strcat(out, " and replace the word ");
			strcat(out, word11);
			strcat(out, ".                     ");

			strcat(out, key12);
			strcat(out, " will be placed on page ");
			strcat(out, page12);
			strcat(out, ", line ");
			strcat(out, line12);
			strcat(out, " and replace the word ");
			strcat(out, word12);
			strcat(out, ".                     ");

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

	//PagesLabel
	CreateWindowW(L"static", L"Pages: ", WS_VISIBLE | WS_CHILD, 512, 264, 100, 20, hWnd, NULL, NULL, NULL);

	//PagesInput
	CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 260, 20, 20, hWnd, NULL, NULL, NULL);

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
	hKey1 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 18, 100, 20, hWnd, NULL, NULL, NULL);
	hKey2 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 38, 100, 20, hWnd, NULL, NULL, NULL);
	hKey3 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 58, 100, 20, hWnd, NULL, NULL, NULL);
	hKey4 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 78, 100, 20, hWnd, NULL, NULL, NULL);
	hKey5 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 98, 100, 20, hWnd, NULL, NULL, NULL);
	hKey6 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 118, 100, 20, hWnd, NULL, NULL, NULL);
	hKey7 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 138, 100, 20, hWnd, NULL, NULL, NULL);
	hKey8 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 158, 100, 20, hWnd, NULL, NULL, NULL);
	hKey9 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 178, 100, 20, hWnd, NULL, NULL, NULL);
	hKey10 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 198, 100, 20, hWnd, NULL, NULL, NULL);
	hKey11 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 218, 100, 20, hWnd, NULL, NULL, NULL);
	hKey12 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 238, 100, 20, hWnd, NULL, NULL, NULL);
	
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
	hPage1 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 18, 20, 20, hWnd, NULL, NULL, NULL);
	hPage2 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 38, 20, 20, hWnd, NULL, NULL, NULL);
	hPage3 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 58, 20, 20, hWnd, NULL, NULL, NULL);
	hPage4 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 78, 20, 20, hWnd, NULL, NULL, NULL);
	hPage5 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 98, 20, 20, hWnd, NULL, NULL, NULL);
	hPage6 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 118, 20, 20, hWnd, NULL, NULL, NULL);
	hPage7 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 138, 20, 20, hWnd, NULL, NULL, NULL);
	hPage8 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 158, 20, 20, hWnd, NULL, NULL, NULL);
	hPage9 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 178, 20, 20, hWnd, NULL, NULL, NULL);
	hPage10 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 198, 20, 20, hWnd, NULL, NULL, NULL);
	hPage11 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 218, 20, 20, hWnd, NULL, NULL, NULL);
	hPage12 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 238, 20, 20, hWnd, NULL, NULL, NULL);

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

	//Left Line Input
	hLine1 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 18, 20, 20, hWnd, NULL, NULL, NULL);
	hLine2 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 38, 20, 20, hWnd, NULL, NULL, NULL);
	hLine3 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 58, 20, 20, hWnd, NULL, NULL, NULL);
	hLine4 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 78, 20, 20, hWnd, NULL, NULL, NULL);
	hLine5 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 98, 20, 20, hWnd, NULL, NULL, NULL);
	hLine6 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 118, 20, 20, hWnd, NULL, NULL, NULL);
	hLine7 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 138, 20, 20, hWnd, NULL, NULL, NULL);
	hLine8 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 158, 20, 20, hWnd, NULL, NULL, NULL);
	hLine9 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 178, 20, 20, hWnd, NULL, NULL, NULL);
	hLine10 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 198, 20, 20, hWnd, NULL, NULL, NULL);
	hLine11 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 218, 20, 20, hWnd, NULL, NULL, NULL);
	hLine12 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 238, 20, 20, hWnd, NULL, NULL, NULL);

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

	//Left Word Input
	hWord1 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 18, 20, 20, hWnd, NULL, NULL, NULL);
	hWord2 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 38, 20, 20, hWnd, NULL, NULL, NULL);
	hWord3 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 58, 20, 20, hWnd, NULL, NULL, NULL);
	hWord4 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 78, 20, 20, hWnd, NULL, NULL, NULL);
	hWord5 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 98, 20, 20, hWnd, NULL, NULL, NULL);
	hWord6 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 118, 20, 20, hWnd, NULL, NULL, NULL);
	hWord7 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 138, 20, 20, hWnd, NULL, NULL, NULL);
	hWord8 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 158, 20, 20, hWnd, NULL, NULL, NULL);
	hWord9 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 178, 20, 20, hWnd, NULL, NULL, NULL);
	hWord10 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 198, 20, 20, hWnd, NULL, NULL, NULL);
	hWord11 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 218, 20, 20, hWnd, NULL, NULL, NULL);
	hWord12 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 238, 20, 20, hWnd, NULL, NULL, NULL);

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
	HWND hBut = CreateWindowW(L"Button", L"Create", WS_VISIBLE | WS_CHILD | BS_BITMAP, 512, 284, 80, 120, hWnd, (HMENU)CREATE_BUTTON, NULL, NULL);
	SendMessageW(hBut, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hCreateImage);

	//Output
	hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 20, 264, 480, 140, hWnd, NULL, NULL, NULL);
}

//7->https://www.youtube.com/watch?v=6WJ_fljFmF0&t