#ifndef UNICODE
#define UNICODE
#endif 

//includes
#include <windows.h> //Windows GUI
#include <stdio.h>   //Why do we need it in this file?
#include <stdlib.h>  //Why do we need it in this file?
#include <iostream>  //Why do we need it in this file?
#include <string>    //Why do we need it in this file?
#include <iomanip>   //Why do we need it in this file?
#include <time.h>    //Why do we need it in this file?
#include <vector>    //Why do we need it in this file?
#include "catalog.h" //Why do we need it in this file?
#include <cstring>   //Why do we need it in this file?
#include <fstream>   //Why do we need it in this file?
#include <wchar.h>   //Why do we need it in this file?
#include "book.h"    //Why do we need it in this file?

#define FILE_MENU_NEW 1
//#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define NEXT_BUTTON 4
#define BACK_BUTTON 5
#define CREATE_BUTTON 6
#define LI 48
#define W 10
#define K 4

using namespace std; //Why (exactly) do we need it?

// Register the window class.
const wchar_t CLASS_NAME[] = L"myWindowClass";
//const wchar_t MENU_NAME[] = L"myMenuClass";

ListedWord wallet_key[K];
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void AddMenus(HWND);    //top bar menu function, declaration 
void fControls(HWND);   //first controls function, declaration 
void advControls(HWND); //advanced controls function, declaration 
void sControls(HWND);   //second controls function, declaration 
char hpages[3];         //pages quantity as character string
char booknamec[100];    //book name, character string
char out[2400];         // on screen output, character string

//User input arrays
char key1c[K][10];      // user keyword, character string
char page1c[K][4];      // user keyword target page, character string
char line1c[K][3];      // user keyword target line, character string
char word1c[K][3];      // user keyword target inline position, character string

//Define handlers (Handlers )
HWND hKey[K];           // user keyword, handler
HWND hPage[K];          // user keyword target page, handler
HWND hLine[K];          // user keyword target line, handler
HWND hWord[K];          // user keyword target inline position, handler
HWND hLabel[K];         // user keyword label, handler
HWND hname;             //book name handler
HWND hnpages;           //number of pages, handler
HWND hOut;              //output, handler
HWND hACBox;            //advanced menu checkbox, handler
HWND hCCBox;            //allow custom words checkbox, handler
HMENU hMenu;            //top bar menu FUNCTION, handler ************** <- Might help me do something like that on controls

//Made them public, to allow one other function to hide or destroy them
HWND hNBut;             // next button, handler
HWND hBBut;             // back button, handler
HWND hCBut;             // create button, handler
HWND hbnlabel;          //name your book label, handler
HWND hplabel;           //select pages quantity label, handler
HWND label1;            //label1, handler
HWND label2;            //label2, handler
HWND label3;            //label3, handler
HWND label4;            //label4, handler
HWND label5;            //label5, handler
HWND label6;            //label6, handler
HWND label7;            //label7, handler
HWND label8;            //label8, handler

// handle to current instance // handle to previous instance // address of command-line string // show-window type 
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	WNDCLASSW wc = { 0 };

	// Register the main window class.
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = CLASS_NAME;
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc))
		return -1;

	// Optional window styles. // Window class // Window text // Window style // Position and size // Parent window // Menu // Instance handle // Additional application data
	CreateWindowW(CLASS_NAME, L"My Book!", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 640, 480,                NULL,       NULL,        NULL,          NULL);

	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

// handle to window // message identifier// first message parameter// second message parameter
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{

	int val;
	switch (msg)
	{
	case WM_COMMAND:

		switch (wp)
		{
		case FILE_MENU_NEW:
			MessageBeep(MB_ICONINFORMATION);
			break;

		case FILE_MENU_EXIT:
			val = MessageBoxW(NULL, L"Program Terminate", L"Exit", MB_OK | MB_ICONINFORMATION);
			if (val == IDOK)
			{
				DestroyWindow(hWnd);
			}
			break;

		case NEXT_BUTTON:
			sControls(hWnd);
			GetWindowTextA(hname, booknamec, 100);
			GetWindowTextA(hnpages, hpages, 3);			
			for (int i = 0; i < K; i++) {
				SetWindowTextA(hKey[i], key1c[i]);
				SetWindowTextA(hPage[i], page1c[i]);
				SetWindowTextA(hLine[i], line1c[i]);
				SetWindowTextA(hWord[i], word1c[i]);
			}
			DestroyWindow(hNBut); 
			DestroyWindow(hACBox);
			DestroyWindow(hbnlabel);
			DestroyWindow(hname);
			DestroyWindow(hplabel);
			DestroyWindow(hnpages);
			//TerminateProcess(fControls, NULL);
			break;

		case BACK_BUTTON:
			fControls(hWnd);
			strcpy(out, booknamec);
			SetWindowTextA(hname, out);
			strcpy(out, hpages);
			SetWindowTextA(hnpages, out);
			for (int i = 0; i < K; i++)
			{
				GetWindowTextA(hKey[i], key1c[i], 10);
				GetWindowTextA(hPage[i], page1c[i], 4);
				GetWindowTextA(hLine[i], line1c[i], 3);
				GetWindowTextA(hWord[i], word1c[i], 3);
			}
			for (int i = 0; i < K; i++)
			{
				DestroyWindow(hLabel[i]);
				DestroyWindow(hKey[i]);
				DestroyWindow(hPage[i]);
				DestroyWindow(hLine[i]);
				DestroyWindow(hWord[i]);
			}
			DestroyWindow(label1);
			DestroyWindow(label2);
			DestroyWindow(label3);
			DestroyWindow(label4);
			DestroyWindow(label5);
			DestroyWindow(label6);
			DestroyWindow(label7);
			DestroyWindow(label8);
			DestroyWindow(hCBut);
			DestroyWindow(hBBut);
			DestroyWindow(hOut);

			break;			  

		case CREATE_BUTTON:

			//char hpages[3];
			int pages = atoi(hpages);
			
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
		AddMenus(hWnd);
		fControls(hWnd);
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
	//TO DO: FIX MENU Functionality
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
//	HMENU hSubMenu = CreateMenu();

//	AppendMenuA(hSubMenu, MF_STRING, NULL, "iTEM");
	AppendMenuA(hFileMenu, MF_STRING, FILE_MENU_NEW, "New Book");
//	AppendMenuA(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Open :P");
	AppendMenuA(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenuA(hFileMenu, MF_STRING, FILE_MENU_EXIT, "kILL");
	AppendMenuA(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
//	AppendMenuA(hMenu, MF_STRING, NULL, "Help");

	SetMenu(hWnd, hMenu);
}

//Labels, Inputs, onscreen output
void fControls(HWND hWnd)
{
	//nextButton
	hNBut = CreateWindow(L"button", L"Next", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 512, 284, 80, 120, hWnd, (HMENU)NEXT_BUTTON, NULL, NULL);
	//Load CheckBox
	hACBox = CreateWindow(TEXT("BUTTON"), TEXT("Advanced Settings"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFTTEXT, 250, 0, 150, 20, hWnd, NULL, NULL, NULL);
	//Bookname Label
	hbnlabel = CreateWindowW(L"static", L"Name your book:", WS_VISIBLE | WS_CHILD | SS_CENTER, 20, 3, 120, 20, hWnd, NULL, NULL, NULL);
	//Bookname Input
	hname = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 140, 0, 100, 20, hWnd, NULL, NULL, NULL);
	//Pages Label
	hplabel = CreateWindowW(L"static", L"Pages: ", WS_VISIBLE | WS_CHILD, 512, 3, 100, 20, hWnd, NULL, NULL, NULL);
	//PagesInput
	hnpages = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 0, 20, 20, hWnd, NULL, NULL, NULL);
}

void advControls(HWND) 
{
	/* how many lines, how many words per line, fonttype, how big letters, where do we save */


}

void sControls(HWND hWnd)
{	
	//TO DO: DROPDOWN WORDS
	//TO DO: DONT LET CUSTON INPUT UNLESS ->
	//TO DO: INPUT CONFIRMATION CHECKBOX 
	// ???? SAVE AS OR AS IT IS?
	//EXIT BUTTON AFTER COMPLETION

	//Left Head
	label1 = CreateWindowW(L"static", L"Key", WS_VISIBLE | WS_CHILD | SS_CENTER, 46, 20, 100, 20, hWnd, NULL, NULL, NULL);
	label2 = CreateWindowW(L"static", L"Page", WS_VISIBLE | WS_CHILD | SS_CENTER, 156, 20, 40, 20, hWnd, NULL, NULL, NULL);
	label3 = CreateWindowW(L"static", L"Line", WS_VISIBLE | WS_CHILD | SS_CENTER, 196, 20, 40, 20, hWnd, NULL, NULL, NULL);
	label4 = CreateWindowW(L"static", L"Word", WS_VISIBLE | WS_CHILD | SS_CENTER, 236, 20, 40, 20, hWnd, NULL, NULL, NULL);

	//Right Head
	label5 = CreateWindowW(L"static", L"Key", WS_VISIBLE | WS_CHILD | SS_CENTER, 366, 20, 100, 20, hWnd, NULL, NULL, NULL);
	label6 = CreateWindowW(L"static", L"Page", WS_VISIBLE | WS_CHILD | SS_CENTER, 476, 20, 40, 20, hWnd, NULL, NULL, NULL);
	label7 = CreateWindowW(L"static", L"Line", WS_VISIBLE | WS_CHILD | SS_CENTER, 516, 20, 40, 20, hWnd, NULL, NULL, NULL);
	label8 = CreateWindowW(L"static", L"Word", WS_VISIBLE | WS_CHILD | SS_CENTER, 556, 20, 40, 20, hWnd, NULL, NULL, NULL);

	int ypos = -1;
	wchar_t index[3];
	LPCWSTR windex;
	//Left Key Label
	ypos = 40;

	for (int i = 0; i < K / 2; i++)
	{
		_itow(i + 1, index, 10);
		windex = index;
		hLabel[i] = CreateWindowExW(NULL, L"static", windex, WS_VISIBLE | WS_CHILD, 20, ypos, 40, 20, hWnd, NULL, NULL, NULL);
		ypos += 20;
	}

	//Right Key Label
	ypos = 40;

	for (int i = K / 2; i < K; i++)
	{
		_itow(i + 1, index, 10);
		windex = index;

		hLabel[i] = CreateWindowExW(NULL, L"static", windex, WS_VISIBLE | WS_CHILD, 340, ypos, 40, 20, hWnd, NULL, NULL, NULL);
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

	//createButtonControl
	hCBut = CreateWindow(L"button", L"Create", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 512, 284, 80, 120, hWnd, (HMENU)CREATE_BUTTON, NULL, NULL);

	//createButtonControl
	hBBut = CreateWindow(L"button", L"Back", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 20, 284, 80, 120, hWnd, (HMENU)BACK_BUTTON, NULL, NULL);

	//On screen output 
	hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 120, 284, 380, 120, hWnd, NULL, NULL, NULL);

	//Load CheckBox
	hCCBox = CreateWindow(TEXT("BUTTON"), TEXT("Allow custom words"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFTTEXT, 250, 260, 150, 20, hWnd, NULL, NULL, NULL);
}