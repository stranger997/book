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
#define K 3

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
//BIP_words: catalogue of available words. Found in catalog.h
//wallet_key[K]: the words in the user's code
//existing_word_flag: used for checking whether or not the word provided by the user is in the list of available words
//cw: current word counter. Used for location check.

int pages = 0;
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
void write_to_txt();

//Define handlers
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

			char hpages[3];
			GetWindowText(hnpages, hpages, 3);

			int pages = atoi(hpages);



			if (strcmp(hpages, "") == 0)
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

			strcpy(out, hpages);
			strcat(out, " pages. ");

			create_catalog(BIP_words);
			generate_book();
			write_to_txt();

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

//Generating a book of random BIP words. Page amount is determined by the user.
void generate_book()
{
	char hpages[3];
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

void write_to_txt()
{
	char hpages[3];
	GetWindowText(hnpages, hpages, 3);
	int pages = atoi(hpages);
	string bookname;
	cout << "Enter a name for your book:" << endl;
	cin >> bookname;
	bookname += ".txt";
	ofstream out_file(bookname);
	if (!out_file)
	{
		cerr << "ERROR: Could not create file" << endl;
	}

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
	hCreateImage = (HBITMAP)LoadImageW(NULL, L"button.bmp", IMAGE_BITMAP, 80, 120, LR_LOADFROMFILE);
}

void AddControls(HWND hWnd)
{
	//PagesLabel
	CreateWindowW(L"static", L"Pages: ", WS_VISIBLE | WS_CHILD, 512, 264, 100, 20, hWnd, NULL, NULL, NULL);

	//PagesInput
	hnpages = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 260, 20, 20, hWnd, NULL, NULL, NULL);

	//Button
	HWND hBut = CreateWindowW(L"Button", L"Create", WS_VISIBLE | WS_CHILD | BS_BITMAP, 512, 284, 80, 120, hWnd, (HMENU)CREATE_BUTTON, NULL, NULL);
	SendMessageW(hBut, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hCreateImage);

	//Output
	hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 20, 264, 480, 140, hWnd, NULL, NULL, NULL);

}