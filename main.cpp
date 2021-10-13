#ifndef UNICODE
#define UNICODE
#endif 

//includes
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>
#include <vector>
#include "catalog.h"
#include <cstring>
#include <fstream>
#include <wchar.h>
#include "book.h"

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define NEXT_BUTTON 4
#define CREATE_BUTTON 5
#define LI 48
#define W 10
#define K 4

using namespace std;
ListedWord wallet_key[K];
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void AddMenus(HWND);
void AddControls(HWND);
void AddControls1(HWND);
void loadImages();
char hpages[3];

//Define handlers
HWND hKey[K];
HWND hPage[K];
HWND hLine[K];
HWND hWord[K];
HWND hname;//book name
HWND hnpages;//number of pages
HWND hOut;//output handle
HMENU hMenu;
HBITMAP hCreateImage;

//Execute
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

	CreateWindowW(L"myWindowClass", L"My Book!", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 640, 480,
		NULL, NULL, NULL, NULL);

	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

//Main Window Functionality
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	//User input arrays
	char key1c[K][10];
	char page1c[K][4];
	char line1c[K][3];
	char word1c[K][3];

	int val;
	switch (msg)
	{
	case WM_COMMAND:

		switch (wp)
		{
		case FILE_MENU_EXIT:
			val = MessageBoxW(NULL, L"Program Terminate", L"Exit", MB_OK | MB_ICONINFORMATION);
			if (val == IDOK)
			{
				DestroyWindow(hWnd);
			}
			break;
		case FILE_MENU_NEW:
			MessageBeep(MB_ICONINFORMATION);
			break;
		case NEXT_BUTTON:

			AddControls(hWnd);

			break;
		case CREATE_BUTTON:

			//Variables from forms to  char
			char out[2400];

			//char hpages[3];
			GetWindowTextA(hnpages, hpages, 3);
			int pages = atoi(hpages);

			char booknamec[100];
			GetWindowTextA(hname, booknamec, 100);

			Book newbook(booknamec, pages);

			if (strcmp(hpages, "") == 0 || strcmp(booknamec, "") == 0)
			{
				val = MessageBoxW(hWnd, L"Missing values", NULL, MB_ABORTRETRYIGNORE | MB_ICONWARNING);
				switch (val)
				{
				case IDABORT:
					val = MessageBoxW(NULL, L"Please insert how many pages you want", L"Warning", MB_OK | MB_ICONERROR);
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

			strcpy(out, "The book is named \"");
			strcat(out, booknamec);
			strcat(out, "\" and it has ");
			strcat(out, hpages);
			strcat(out, " pages. ");

			newbook.generate_book();
			MessageBoxW(NULL, L"Generated book succesfully", L"Warning", MB_OK | MB_ICONEXCLAMATION);//DELETE

			for (int i = 0; i < K; i++)
			{
				GetWindowTextA(hKey[i], key1c[i], 10);

				GetWindowTextA(hPage[i], page1c[i], 4);

				GetWindowTextA(hLine[i], line1c[i], 3);

				GetWindowTextA(hWord[i], word1c[i], 3);
			}

			MessageBoxW(NULL, L"Got keys successfully", L"Warning", MB_OK | MB_ICONEXCLAMATION);//DELETE
			newbook.fetch_keys(key1c, page1c, line1c, word1c);
			MessageBoxW(NULL, L"fetched key succesfully", L"Warning", MB_OK | MB_ICONEXCLAMATION);//DELETE
			newbook.place_words();
			MessageBoxW(NULL, L"Placed words successfully", L"Warning", MB_OK | MB_ICONEXCLAMATION);//DELETE
			newbook.write_to_txt();

			SetWindowTextA(hOut, out);

			break;
		}

		break;
	case WM_CREATE: //By the initial window creation executes
		loadImages();
		AddMenus(hWnd);
		AddControls1(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

//Window menu TOP BAR Functionality
void AddMenus(HWND hWnd)
{
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
//	HMENU hSubMenu = CreateMenu();

//	AppendMenuA(hSubMenu, MF_STRING, NULL, "iTEM");
//	AppendMenuA(hFileMenu, MF_STRING, FILE_MENU_NEW, "New Book");
//	AppendMenuA(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Open :P");
//	AppendMenuA(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenuA(hFileMenu, MF_STRING, FILE_MENU_EXIT, "kILL");
	AppendMenuA(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
//	AppendMenuA(hMenu, MF_STRING, NULL, "Help");

	SetMenu(hWnd, hMenu);
}

//Loading Images on buttons etc
void loadImages()
{
	hCreateImage = (HBITMAP)LoadImageW(NULL, L"button.bmp", IMAGE_BITMAP, 80, 120, LR_LOADFROMFILE);
}

//Labels, Inputs, onscreen output

void AddControls1(HWND hWnd)
{
	//nextButton
	HWND hNBut = CreateWindow(L"button", L"Next", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 512, 284, 80, 120, hWnd, (HMENU)NEXT_BUTTON, NULL, NULL);

	//Bookname Label
	CreateWindowW(L"static", L"Name your book:", WS_VISIBLE | WS_CHILD | SS_CENTER, 20, 3, 120, 20, hWnd, NULL, NULL, NULL);
	//Bookname Input
	hname = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 140, 0, 100, 20, hWnd, NULL, NULL, NULL);
	//Pages Label
	CreateWindowW(L"static", L"Pages: ", WS_VISIBLE | WS_CHILD, 512, 3, 100, 20, hWnd, NULL, NULL, NULL);
	//PagesInput
	hnpages = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 0, 20, 20, hWnd, NULL, NULL, NULL);
}

void AddControls(HWND hWnd)
{
	//Left Head
	CreateWindowW(L"static", L"Key", WS_VISIBLE | WS_CHILD | SS_CENTER, 46, 20, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"Page", WS_VISIBLE | WS_CHILD | SS_CENTER, 156, 20, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"Line", WS_VISIBLE | WS_CHILD | SS_CENTER, 196, 20, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"Word", WS_VISIBLE | WS_CHILD | SS_CENTER, 236, 20, 40, 20, hWnd, NULL, NULL, NULL);

	//Right Head
	CreateWindowW(L"static", L"Key", WS_VISIBLE | WS_CHILD | SS_CENTER, 366, 20, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"Page", WS_VISIBLE | WS_CHILD | SS_CENTER, 476, 20, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"Line", WS_VISIBLE | WS_CHILD | SS_CENTER, 516, 20, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"Word", WS_VISIBLE | WS_CHILD | SS_CENTER, 556, 20, 40, 20, hWnd, NULL, NULL, NULL);

	int ypos = -1;
	wchar_t index[3];
	LPCWSTR windex;
	//Left Key Label
	ypos = 40;

	for (int i = 0; i < K / 2; i++)
	{
		_itow(i + 1, index, 10);
		windex = index;
		CreateWindowExW(NULL, L"static", windex, WS_VISIBLE | WS_CHILD, 20, ypos, 40, 20, hWnd, NULL, NULL, NULL);
		ypos += 20;
	}

	//Right Key Label
	ypos = 40;

	for (int i = K / 2; i < K; i++)
	{
		_itow(i + 1, index, 10);
		windex = index;

		CreateWindowExW(NULL, L"static", windex, WS_VISIBLE | WS_CHILD, 340, ypos, 40, 20, hWnd, NULL, NULL, NULL);
		ypos += 20;
	}

	//Left Key Input
	int handleYpos = 38;
	for (int i = 0; i < K / 2; i++)
	{
		hKey[i] = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, handleYpos, 100, 20, hWnd, NULL, NULL, NULL);
		handleYpos += 20;
	}

	//Right Key Input
	handleYpos = 38;
	for (int i = K / 2; i < K; i++)
	{
		hKey[i] = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, handleYpos, 100, 20, hWnd, NULL, NULL, NULL);
		handleYpos += 20;
	}


	//Left Page Input
	handleYpos = 38;
	for (int i = 0; i < K / 2; i++)
	{
		hPage[i] = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, handleYpos, 20, 20, hWnd, NULL, NULL, NULL);
		handleYpos += 20;
	}

	//Right Page Input
	handleYpos = 38;
	for (int i = K / 2; i < K; i++)
	{
		hPage[i] = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, handleYpos, 20, 20, hWnd, NULL, NULL, NULL);
		handleYpos += 20;
	}

	//Left Line Input
	handleYpos = 38;
	for (int i = 0; i < K / 2; i++)
	{
		hLine[i] = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, handleYpos, 20, 20, hWnd, NULL, NULL, NULL);
		handleYpos += 20;
	}

	//Right Line Input
	handleYpos = 38;
	for (int i = K / 2; i < K; i++)
	{
		hLine[i] = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, handleYpos, 20, 20, hWnd, NULL, NULL, NULL);
		handleYpos += 20;
	}

	//Left Word Input
	handleYpos = 38;
	for (int i = 0; i < K / 2; i++)
	{
		hWord[i] = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, handleYpos, 20, 20, hWnd, NULL, NULL, NULL);
		handleYpos += 20;
	}


	//Right Word Input
	handleYpos = 38;
	for (int i = K / 2; i < K; i++)
	{
		hWord[i] = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, handleYpos, 20, 20, hWnd, NULL, NULL, NULL);
		handleYpos += 20;
	}

	//createButton
	HWND hBut = CreateWindowW(L"Button", L"Create", WS_VISIBLE | WS_CHILD | BS_BITMAP, 512, 284, 80, 120, hWnd, (HMENU)CREATE_BUTTON, NULL, NULL);
	SendMessageW(hBut, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hCreateImage);

	//On screen output 
	hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 20, 284, 480, 120, hWnd, NULL, NULL, NULL);
}