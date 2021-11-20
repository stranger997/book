#ifndef UNICODE
#define UNICODE
#endif 

#include <Windows.h>
#include "book.h"    //ListedWord

#define FILE_MENU_NEW   1
#define FILE_MENU_OPEN  2
#define FILE_MENU_EXIT  3

#define NEXT_BUTTON    21
#define BACK_BUTTON    22
#define CREATE_BUTTON  23

#define ADV_CHECKBOX   31
#define FONT_BUTTON    32
#define FONT_CHECKBOX  33
#define FONT_EXAMPLE   34

#define L_COMBOBOX     41
#define R_COMBOBOX     42 

#define LI 48
#define W 10
#define K 4

ListedWord wallet_key[K];
HINSTANCE   g_hInst;
//HWND        g_hwndApp;  // Owner window
HWND        g_hwndText; // static text window

HWND chFButton;
HWND sAFCheckbox;      //Allow all font types

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

// Forward declarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void InitDefaultLF(LOGFONT* lf);
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

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	g_hInst = hInstance; // Save our hInstance for later
	WCHAR const szWindowName[] = L"My book!";
	WCHAR const szWindowClass[] = L"myWindowClass";

	WNDCLASSEX wndclass{};

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszClassName = szWindowClass;

	RegisterClassEx(&wndclass);

	HWND g_hwndApp = CreateWindow(szWindowClass, szWindowName, WS_EX_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);

	::ShowWindow(g_hwndApp, SW_SHOW);
	::UpdateWindow(g_hwndApp);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		if (!IsDialogMessage(g_hwndApp, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static LOGFONT lf = {};
	int val;
	switch (uMsg)
	{
	case WM_COMMAND:
	{
		switch (wParam)
		{
		case FILE_MENU_NEW:
			MessageBeep(MB_ICONINFORMATION);
			break;

		case FILE_MENU_EXIT:
			val = MessageBoxW(NULL, L"Program Terminate", L"Exit", MB_OK | MB_ICONINFORMATION);
			if (val == IDOK)
			{
				DestroyWindow(hwnd);
			}
			break;
		case ADV_CHECKBOX:
			if (BST_CHECKED == IsDlgButtonChecked(hwnd, ADV_CHECKBOX))
			{
				advControls(hwnd);
			}
			else
			{
				DestroyWindow(chFButton);
				DestroyWindow(sAFCheckbox);
				DestroyWindow(g_hwndText);
			}
			break;
		case FONT_BUTTON:
			if (LOWORD(wParam) == FONT_BUTTON)
			{
				CHOOSEFONT cf = { sizeof(cf) };
				cf.hwndOwner = hwnd;
				cf.lpLogFont = &lf;
				if (BST_CHECKED == IsDlgButtonChecked(hwnd, FONT_CHECKBOX))
				{
					// show all fonts (ignore auto-activation)
					cf.Flags |= CF_INACTIVEFONTS;
				}

				if (ChooseFont(&cf) == TRUE)
				{
					HFONT hfont = CreateFontIndirect(&lf);
					if (hfont)
					{
						// delete the old font if being used for the control if there is one
						HFONT hfontOld = (HFONT)SendMessage(g_hwndText, WM_GETFONT, 0, 0);
						if (hfontOld)
						{
							DeleteObject(hfontOld);
						}
						SendMessage(g_hwndText, WM_SETFONT, (WPARAM)hfont, MAKELPARAM(TRUE, 0));
					}
				}
			}
			break;
		case NEXT_BUTTON:
			sControls(hwnd);
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
			DestroyWindow(chFButton);
			DestroyWindow(sAFCheckbox);
			DestroyWindow(g_hwndText);
			//TerminateProcess(fControls, NULL);
			break;

		case BACK_BUTTON:
			fControls(hwnd);
			strcpy_s(out, booknamec);
			SetWindowTextA(hname, out);
			strcpy_s(out, hpages);
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
			DestroyWindow(hCCBox);
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
				val = MessageBoxW(hwnd, L"Missing values", NULL, MB_ABORTRETRYIGNORE | MB_ICONWARNING);
				switch (val)
				{
				case IDABORT:
					val = MessageBoxW(NULL, L"Please insert how many pages you want", L"Warning", MB_OK | MB_ICONERROR);
					if (val == IDOK)
					{
						DestroyWindow(hwnd);
					}
					break;
				case IDRETRY:
					return 0;
				case IDIGNORE:
					break;
				}
			}

			strcpy_s(out, "The book is named \"");
			strcat_s(out, booknamec);
			strcat_s(out, "\" and it has ");
			strcat_s(out, hpages);
			strcat_s(out, " pages. ");

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
	}
	case WM_CREATE:
	{
		AddMenus(hwnd);
		fControls(hwnd);
		InitDefaultLF(&lf);
		break;
	}
	case WM_DESTROY:
	{
		// cleanup font resources created above
		HFONT hfontOld = (HFONT)SendMessage(g_hwndText, WM_GETFONT, 0, 0);
		if (hfontOld)
		{
			DeleteObject(hfontOld);
		}
		PostQuitMessage(0);
		return 0;
	}

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

void InitDefaultLF(LOGFONT* plf)
{
	HDC hdc = GetDC(NULL);
	ZeroMemory(plf, sizeof(*plf));
	plf->lfCharSet = (BYTE)GetTextCharset(hdc);
	plf->lfOutPrecision = OUT_DEFAULT_PRECIS;
	plf->lfClipPrecision = CLIP_DEFAULT_PRECIS;
	plf->lfQuality = DEFAULT_QUALITY;
	plf->lfPitchAndFamily = DEFAULT_PITCH;
	plf->lfWeight = FW_NORMAL;
	plf->lfHeight = -MulDiv(10, GetDeviceCaps(hdc, LOGPIXELSY), 2);

	ReleaseDC(NULL, hdc);
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

////////////////////////////////////////////////////////////////////////////
void CreateEdit(const HWND& parent, const int& x, const int& y, const int& id) {
	CreateWindow(L"EDIT", L"", WS_BORDER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, x, y, 200, 20, parent, (HMENU)id, NULL, NULL);
}
////////////////////////////////////////////////////////////////////////////

void fControls(HWND g_hwndApp)
{
	//Creating Controls~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	int x = 10, y = 20, id = 100;
	/*
	HWND    g1 = CreateWindowEx(WS_EX_CONTROLPARENT, L"button", L"Group1", WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_TABSTOP | WS_GROUP, 0, 50, 220, 200, g_hwndApp, (HMENU)++id, NULL, NULL);
	//Controls in Group1
	CreateEdit(g1, x, (y += 30), ++id);
	CreateEdit(g1, x, (y += 30), ++id);
	CreateEdit(g1, x, (y += 30), ++id);
	CreateEdit(g1, x, (y += 30), ++id);

	HWND    g2 = CreateWindowEx(WS_EX_CONTROLPARENT, L"button", L"Group2", WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_TABSTOP | WS_GROUP, 260, 50, 220, 200, g_hwndApp, (HMENU)++id, NULL, NULL);
	y = 20;
	//Controls in Group2
	CreateEdit(g2, x, (y += 30), ++id);
	CreateEdit(g2, x, (y += 30), ++id);
	CreateEdit(g2, x, (y += 30), ++id);
	CreateEdit(g2, x, (y += 30), ++id);

	//The controls that create  directly in the main window
	y = 270;
	CreateWindow(L"static", L"Main Window Controls", WS_CHILD | WS_VISIBLE, x, y, 200, 30, g_hwndApp, (HMENU)++id, NULL, NULL);

	CreateEdit(g_hwndApp, x, (y += 30), ++id);
	CreateEdit(g_hwndApp, x, (y += 30), ++id);
	CreateEdit(g_hwndApp, x, (y += 30), ++id);
	CreateEdit(g_hwndApp, x, (y += 30), ++id);
	*/
	//Bookname Label
	hbnlabel = CreateWindowW(L"static", L"Name your book:", WS_CHILD | WS_VISIBLE | SS_CENTER, 20, 3, 120, 20, g_hwndApp, NULL, g_hInst, NULL);
	//Bookname Input
	hname = CreateWindowW(L"Edit", L"", WS_BORDER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 140, 0, 100, 20, g_hwndApp, (HMENU)++id, g_hInst, NULL);
	//Pages Label
	hplabel = CreateWindowW(L"static", L"Pages: ", WS_CHILD | WS_VISIBLE, 512, 3, 100, 20, g_hwndApp, NULL, g_hInst, NULL);
	//PagesInput
	hnpages = CreateWindowW(L"Edit", L"", WS_BORDER | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 566, 0, 20, 20, g_hwndApp, (HMENU)++id, g_hInst, NULL);
	//Load CheckBox
	hACBox = CreateWindow(L"BUTTON", L"Advanced Settings", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_AUTOCHECKBOX, 20, 264, 150, 20, g_hwndApp, (HMENU)ADV_CHECKBOX, g_hInst, NULL);
	//nextButton
	hNBut = CreateWindow(L"button", L"Next", WS_BORDER | WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON, 512, 284, 80, 120, g_hwndApp, (HMENU)NEXT_BUTTON, g_hInst, NULL);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

void advControls(HWND g_hwndApp)
{
	// Create "Choose Font" button
	chFButton = CreateWindow(L"button", L"Choose Font", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_PUSHBUTTON, 20, 284, 100, 20, g_hwndApp, (HMENU)FONT_BUTTON, g_hInst, NULL);
	// Create "Show all fonts?" checkbox
	sAFCheckbox = CreateWindow(L"button", L"Show all fonts?", BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE | WS_TABSTOP, 20, 304, 120, 20, g_hwndApp, (HMENU)FONT_CHECKBOX, g_hInst, NULL);
	// Create the static label with our sample text 
	g_hwndText = CreateWindow(L"static", L"abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 123456789", SS_CENTER | WS_CHILD | WS_VISIBLE, 180, 284, 300, 60, g_hwndApp, (HMENU)FONT_EXAMPLE, g_hInst, NULL);
	// Create the static label with our sample text 
	g_hwndText = CreateWindow(L"static", L"abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 123456789", SS_CENTER | WS_CHILD | WS_VISIBLE, 180, 284, 300, 60, hwnd, (HMENU)FONT_EXAMPLE, g_hInst, NULL);
}

void sControls(HWND hWnd)
{
	int ypos = -1;
	wchar_t index[3];
	LPCWSTR windex;
	ypos = 40;
	int handleYpos = 38;
	int x = 10, y = 20, id = 100;

	//Left 
	label1 = CreateWindowW(L"static", L"Key", WS_VISIBLE | WS_CHILD | SS_CENTER, 46, 20, 100, 20, hWnd, NULL, NULL, NULL);
	label2 = CreateWindowW(L"static", L"Page", WS_VISIBLE | WS_CHILD | SS_CENTER, 156, 20, 40, 20, hWnd, NULL, NULL, NULL);
	label3 = CreateWindowW(L"static", L"Line", WS_VISIBLE | WS_CHILD | SS_CENTER, 196, 20, 40, 20, hWnd, NULL, NULL, NULL);
	label4 = CreateWindowW(L"static", L"Word", WS_VISIBLE | WS_CHILD | SS_CENTER, 236, 20, 40, 20, hWnd, NULL, NULL, NULL);

	for (int i = 0; i < K / 2; i++)
	{
		_itow_s(i + 1, index, 10);
		windex = index;
		hLabel[i] = CreateWindowExW(NULL, L"static", windex, WS_VISIBLE | WS_CHILD, 20, ypos, 40, 20, hWnd, NULL, NULL, NULL);
		ypos += 20;
		hKey[i] = CreateWindowEx(WS_EX_STATICEDGE, L"Combobox", L"", CBS_SIMPLE | CBS_SORT | WS_CHILD | WS_VISIBLE | CBS_LOWERCASE | WS_VSCROLL | WS_TABSTOP, 46, handleYpos, 100, 20, hWnd, HMENU(L_COMBOBOX), g_hInst, NULL);
		hPage[i] = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, 166, handleYpos, 20, 20, hWnd, (HMENU)++id, NULL, NULL);
		hLine[i] = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, 206, handleYpos, 20, 20, hWnd, (HMENU)++id, NULL, NULL);
		hWord[i] = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, 246, handleYpos, 20, 20, hWnd, (HMENU)++id, NULL, NULL);
		handleYpos += 20;
	}

	//Right 

	ypos = 40;
	handleYpos = 38;

	label5 = CreateWindowW(L"static", L"Key", WS_VISIBLE | WS_CHILD | SS_CENTER, 366, 20, 100, 20, hWnd, NULL, NULL, NULL);
	label6 = CreateWindowW(L"static", L"Page", WS_VISIBLE | WS_CHILD | SS_CENTER, 476, 20, 40, 20, hWnd, NULL, NULL, NULL);
	label7 = CreateWindowW(L"static", L"Line", WS_VISIBLE | WS_CHILD | SS_CENTER, 516, 20, 40, 20, hWnd, NULL, NULL, NULL);
	label8 = CreateWindowW(L"static", L"Word", WS_VISIBLE | WS_CHILD | SS_CENTER, 556, 20, 40, 20, hWnd, NULL, NULL, NULL);

	for (int i = K / 2; i < K; i++)
	{
		_itow_s(i + 1, index, 10);
		windex = index;
		hLabel[i] = CreateWindowExW(NULL, L"static", windex, WS_VISIBLE | WS_CHILD, 340, ypos, 40, 20, hWnd, NULL, NULL, NULL);
		ypos += 20;
		hKey[i] = CreateWindowEx(WS_EX_STATICEDGE, L"Combobox", L"", CBS_DROPDOWN | CBS_SORT | WS_CHILD | WS_VISIBLE | CBS_LOWERCASE | WS_VSCROLL | WS_TABSTOP, 366, handleYpos, 100, 20, hWnd, HMENU(R_COMBOBOX), g_hInst, NULL);
		hPage[i] = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, 486, handleYpos, 20, 20, hWnd, (HMENU)++id, NULL, NULL);
		hLine[i] = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, 526, handleYpos, 20, 20, hWnd, (HMENU)++id, NULL, NULL);
		hWord[i] = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, 566, handleYpos, 20, 20, hWnd, (HMENU)++id, NULL, NULL);
		handleYpos += 20;
	}
	//Buttons
	//createButtonControl
	hBBut = CreateWindow(L"button", L"Back", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP, 20, 284, 80, 120, hWnd, (HMENU)BACK_BUTTON, NULL, NULL);
	//createButtonControl
	hCBut = CreateWindow(L"button", L"Create", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP, 512, 284, 80, 120, hWnd, (HMENU)CREATE_BUTTON, NULL, NULL);
	//On screen output 
	hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 120, 284, 380, 120, hWnd, NULL, NULL, NULL);
	//Load CheckBox
	hCCBox = CreateWindow(TEXT("BUTTON"), TEXT("Allow custom words"), WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_LEFTTEXT | WS_TABSTOP, 250, 260, 150, 20, hWnd, (HMENU)++id, NULL, NULL);
}