#ifndef UNICODE
#define UNICODE
#endif 

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
//#include <filesystem>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define CREATE_BUTTON 4
#define LI 48
#define W 10
#define K 4

using namespace std;

ListedWord wallet_key[K];

//wIN
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);
void AddControls(HWND);
void loadImages();
void get_keys();




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

char hpages[3];

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
	case WM_CREATE: //more comments needed
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




//Function for window menu
void AddMenus(HWND hWnd)
{
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hSubMenu = CreateMenu();

	AppendMenuA(hSubMenu, MF_STRING, NULL, "iTEM");

	AppendMenuA(hFileMenu, MF_STRING, FILE_MENU_NEW, "New Book");
	AppendMenuA(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Open :P");
	AppendMenuA(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenuA(hFileMenu, MF_STRING, FILE_MENU_EXIT, "kILL");

	AppendMenuA(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
	AppendMenuA(hMenu, MF_STRING, NULL, "Help");

	SetMenu(hWnd, hMenu);
}

//Loads image on button
void loadImages()
{
	hCreateImage = (HBITMAP)LoadImageW(NULL, L"button.bmp", IMAGE_BITMAP, 80, 120, LR_LOADFROMFILE);
}
//Labels, Inputs, onscreen output
void AddControls(HWND hWnd)
{
	//Bookname Label
	CreateWindowW(L"static", L"Name your book:", WS_VISIBLE | WS_CHILD | SS_CENTER, 20, 3, 120, 20, hWnd, NULL, NULL, NULL);
	//Bookname Input
	hname = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 140, 0, 100, 20, hWnd, NULL, NULL, NULL);
	//Pages Label
	CreateWindowW(L"static", L"Pages: ", WS_VISIBLE | WS_CHILD, 512, 3, 100, 20, hWnd, NULL, NULL, NULL);
	//PagesInput
	hnpages = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 0, 20, 20, hWnd, NULL, NULL, NULL);

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


	//Button
	HWND hBut = CreateWindowW(L"Button", L"Create", WS_VISIBLE | WS_CHILD | BS_BITMAP, 512, 284, 80, 120, hWnd, (HMENU)CREATE_BUTTON, NULL, NULL);
	SendMessageW(hBut, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hCreateImage);

	//On screen output 
	hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 20, 284, 480, 120, hWnd, NULL, NULL, NULL);

}

/* OLD
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
#include <filesystem>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define CREATE_BUTTON 4
#define LI 48
#define W 10
#define K 24

using namespace std;

struct codeword
{
	string word;
	int pos;
	int page_loc;
	int line_loc;
	int word_loc;
};

struct node
{
	string value;
	int page_no;
	int line_no;
	int word_no;
	int is_in_password;
	struct node* next;
}*head;

//Declaration of: 
//pages: number of pages in generated book
//hpages: char array with the value of pages
//BIP_words: catalogue of available words. Found in catalog.h
//wallet_key[K]: the words in the user's code
//existing_word_flag: used for checking whether or not the word provided by the user is in the list of available words
//cw: current word counter. Used for location check.

int pages = 0;
char hpages[3];
string BIP_words[2048];
codeword wallet_key[K];
int existing_word_flag = -1;
int cw = -1;


//Each word in the book is a node, therefore insert_at_end is used to fill the book
void insert_at_end(int page, int line, int word_loc, string new_word)
{
	node* temp;
	temp = new node;
	temp->page_no = page;
	temp->line_no = line;
	temp->word_no = word_loc;
	temp->value = new_word;
	temp->is_in_password = 0;
	temp->next = NULL;

	if (head == NULL)
	{
		head = temp;
	}
	else
	{
		node* temphead;
		temphead = head;

		while (temphead->next != NULL)
		{
			temphead = temphead->next;
		}

		temphead->next = temp;
	}
}

//wIN
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);
void AddControls(HWND);
void loadImages();
void generate_book();
void get_keys();
void place_words();
void write_to_txt();

//Define handlers
HWND hKey[24];
HWND hPage[24];
HWND hLine[24];
HWND hWord[24];
HWND hname;
HWND hnpages;
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

			//char hpages[3];
			GetWindowText(hnpages, hpages, 3);
			int pages = atoi(hpages);

			char booknamec[100];
			GetWindowText(hname, booknamec, 100);


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

			create_catalog(BIP_words);
			generate_book();
			get_keys();
			place_words();
			write_to_txt();

			SetWindowText(hOut, out);

			break;
		}

		break;
	case WM_CREATE: //more comments needed
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

//Generating a book of random BIP words. Page amount is determined by the user.
void generate_book()
{
	//char hpages[3];
	GetWindowText(hnpages, hpages, 3);
	int pages = atoi(hpages);

	int pp = -1; //page counter
	int ll = -1; //line counter
	int ww = -1; //word counter
	string new_word;

	srand(time(NULL));
	int random_digit;

	for (pp = 0; pp < pages; pp++)
	{
		for (ll = 0; ll < LI; ll++)
		{
			for (ww = 0; ww < W; ww++)
			{
				random_digit = rand() % 2048;
				new_word.assign(BIP_words[random_digit]);
				insert_at_end(pp, ll, ww, new_word);
			}
		}
	}
}

void get_keys()
{

	char key1c[K][10];
	char page1c[K][4];
	char line1c[K][3];
	char word1c[K][3];

	for (int i = 0; i < K; i++)
	{
		GetWindowText(hKey[i], key1c[i], 10);
		wallet_key[i].word = key1c[i];

		GetWindowText(hPage[i], page1c[i], 4);
		wallet_key[i].page_loc = atoi(page1c[i]);

		GetWindowText(hLine[i], line1c[i], 3);
		wallet_key[i].line_loc = atoi(line1c[i]);

		GetWindowText(hWord[i], word1c[i], 3);
		wallet_key[i].word_loc = atoi(word1c[i]);
	}

	MessageBeep(MB_ICONINFORMATION);
}

//Placing user's words in the nodelist
void place_words()
{
	int pageno;
	int lineno;
	int wordno;
	string chosen_word;

	node* temphead = head;

	for (int i = 0; i < K; i++)
	{
		pageno = wallet_key[i].page_loc;
		lineno = wallet_key[i].line_loc;
		wordno = wallet_key[i].word_loc;
		chosen_word = wallet_key[i].word;

		while (temphead->page_no != pageno)
		{
			temphead = temphead->next;
			if (temphead == NULL) temphead = head;
		}
		while (temphead->line_no != lineno)
		{
			temphead = temphead->next;
			if (temphead == NULL) temphead = head;
		}
		while (temphead->word_no != wordno)
		{
			temphead = temphead->next;
			if (temphead == NULL) temphead = head;
		}
		temphead->value = chosen_word;
		temphead->is_in_password = 1;
	}
}

void write_to_txt()
{
	//char hpages[3]; //3 char array declaration
	GetWindowText(hnpages, hpages, 3); //parse values from handle to char array
	int pages = atoi(hpages); //convert to integer

	char booknamec[100]; //100 char array declaration
	GetWindowText(hname, booknamec, 100); //parse values from handle to char array
	string bookname; //declare string
	bookname += booknamec; //add values to string
	bookname += ".txt"; //add more values to string
	ofstream out_file(bookname);

	node* temphead = head;
	for (int i = 0; i < pages; i++)
	{
		out_file << "Page " << i + 1 << endl;
		for (int j = 0; j < 48; j++)
		{
			for (int k = 0; k < 10; k++)
			{
				out_file << temphead->value << " ";
				temphead = temphead->next;
			}
			out_file << endl;
		}
	}
}

//Function for window menu
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

//Loads image on button
void loadImages()
{
	hCreateImage = (HBITMAP)LoadImageW(NULL, L"button.bmp", IMAGE_BITMAP, 80, 120, LR_LOADFROMFILE);
}
//Labels, Inputs, onscreen output
void AddControls(HWND hWnd)
{
	//Bookname Label
	CreateWindowW(L"static", L"Name your book:", WS_VISIBLE | WS_CHILD | SS_CENTER, 20, 3, 120, 20, hWnd, NULL, NULL, NULL);
	//Bookname Input
	hname = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 140, 0, 100, 20, hWnd, NULL, NULL, NULL);
	//Pages Label
	CreateWindowW(L"static", L"Pages: ", WS_VISIBLE | WS_CHILD, 512, 3, 100, 20, hWnd, NULL, NULL, NULL);
	//PagesInput
	hnpages = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 0, 20, 20, hWnd, NULL, NULL, NULL);

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

	//Left Key Label
	CreateWindowW(L"static", L"  1: ", WS_VISIBLE | WS_CHILD, 20, 40, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"  2: ", WS_VISIBLE | WS_CHILD, 20, 60, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"  3: ", WS_VISIBLE | WS_CHILD, 20, 80, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"  4: ", WS_VISIBLE | WS_CHILD, 20, 100, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"  5: ", WS_VISIBLE | WS_CHILD, 20, 120, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"  6: ", WS_VISIBLE | WS_CHILD, 20, 140, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"  7: ", WS_VISIBLE | WS_CHILD, 20, 160, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"  8: ", WS_VISIBLE | WS_CHILD, 20, 180, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"  9: ", WS_VISIBLE | WS_CHILD, 20, 200, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"10: ", WS_VISIBLE | WS_CHILD, 20, 220, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"11: ", WS_VISIBLE | WS_CHILD, 20, 240, 40, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"12: ", WS_VISIBLE | WS_CHILD, 20, 260, 40, 20, hWnd, NULL, NULL, NULL);
	//Right Key Label
	CreateWindowW(L"static", L"13: ", WS_VISIBLE | WS_CHILD, 340, 40, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"14: ", WS_VISIBLE | WS_CHILD, 340, 60, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"15: ", WS_VISIBLE | WS_CHILD, 340, 80, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"16: ", WS_VISIBLE | WS_CHILD, 340, 100, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"17: ", WS_VISIBLE | WS_CHILD, 340, 120, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"18: ", WS_VISIBLE | WS_CHILD, 340, 140, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"19: ", WS_VISIBLE | WS_CHILD, 340, 160, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"20: ", WS_VISIBLE | WS_CHILD, 340, 180, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"21: ", WS_VISIBLE | WS_CHILD, 340, 200, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"22: ", WS_VISIBLE | WS_CHILD, 340, 220, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"23: ", WS_VISIBLE | WS_CHILD, 340, 240, 100, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"24: ", WS_VISIBLE | WS_CHILD, 340, 260, 100, 20, hWnd, NULL, NULL, NULL);

	//Left Key Input
	int handleYpos = 38;
	for (int i = 0; i < 12; i++)
	{
		hKey[i] = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, handleYpos, 100, 20, hWnd, NULL, NULL, NULL);
		handleYpos += 20;
	}

	//Right Key Input
	handleYpos = 38;
	for (int i = 12; i < 24; i++)
	{
		hKey[i] = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, handleYpos, 100, 20, hWnd, NULL, NULL, NULL);
		handleYpos += 20;
	}


	//Left Page Input
	handleYpos = 38;
	for (int i = 0; i < 12; i++)
	{
		hPage[i] = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, handleYpos, 20, 20, hWnd, NULL, NULL, NULL);
		handleYpos += 20;
	}

	//Right Page Input
	handleYpos = 38;
	for (int i = 12; i < 24; i++)
	{
		hPage[i] = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, handleYpos, 20, 20, hWnd, NULL, NULL, NULL);
		handleYpos += 20;
	}

	//Left Line Input
	handleYpos = 38;
	for (int i = 0; i < 12; i++)
	{
		hLine[i] = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, handleYpos, 20, 20, hWnd, NULL, NULL, NULL);
		handleYpos += 20;
	}

	//Right Line Input
	handleYpos = 38;
	for (int i = 12; i < 24; i++)
	{
		hLine[i] = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, handleYpos, 20, 20, hWnd, NULL, NULL, NULL);
		handleYpos += 20;
	}

	//Left Word Input
	handleYpos = 38;
	for (int i = 0; i < 12; i++)
	{
		hWord[i] = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, handleYpos, 20, 20, hWnd, NULL, NULL, NULL);
		handleYpos += 20;
	}


	//Right Word Input
	handleYpos = 38;
	for (int i = 12; i < 24; i++)
	{
		hWord[i] = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, handleYpos, 20, 20, hWnd, NULL, NULL, NULL);
		handleYpos += 20;
	}


	//Button
	HWND hBut = CreateWindowW(L"Button", L"Create", WS_VISIBLE | WS_CHILD | BS_BITMAP, 512, 284, 80, 120, hWnd, (HMENU)CREATE_BUTTON, NULL, NULL);
	SendMessageW(hBut, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hCreateImage);

	//On screen output 
	hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 20, 284, 480, 120, hWnd, NULL, NULL, NULL);

}

*/