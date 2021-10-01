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
void place_words();
void write_to_txt(); 
void get_keys();

//Define handlers
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

			char hpages[3];
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

void get_keys()
{
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
	char hpages[3]; //3 char array declaration
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
	hKey1 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 38, 100, 20, hWnd, NULL, NULL, NULL);
	hKey2 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 58, 100, 20, hWnd, NULL, NULL, NULL);
	hKey3 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 78, 100, 20, hWnd, NULL, NULL, NULL);
	hKey4 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 98, 100, 20, hWnd, NULL, NULL, NULL);
	hKey5 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 118, 100, 20, hWnd, NULL, NULL, NULL);
	hKey6 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 138, 100, 20, hWnd, NULL, NULL, NULL);
	hKey7 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 158, 100, 20, hWnd, NULL, NULL, NULL);
	hKey8 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 178, 100, 20, hWnd, NULL, NULL, NULL);
	hKey9 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 198, 100, 20, hWnd, NULL, NULL, NULL);
	hKey10 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 218, 100, 20, hWnd, NULL, NULL, NULL);
	hKey11 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 238, 100, 20, hWnd, NULL, NULL, NULL);
	hKey12 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 46, 258, 100, 20, hWnd, NULL, NULL, NULL);
	//Right Key Input
	hKey13 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 38, 100, 20, hWnd, NULL, NULL, NULL);
	hKey14 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 58, 100, 20, hWnd, NULL, NULL, NULL);
	hKey15 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 78, 100, 20, hWnd, NULL, NULL, NULL);
	hKey16 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 98, 100, 20, hWnd, NULL, NULL, NULL);
	hKey17 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 118, 100, 20, hWnd, NULL, NULL, NULL);
	hKey18 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 138, 100, 20, hWnd, NULL, NULL, NULL);
	hKey19 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 158, 100, 20, hWnd, NULL, NULL, NULL);
	hKey20 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 178, 100, 20, hWnd, NULL, NULL, NULL);
	hKey21 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 198, 100, 20, hWnd, NULL, NULL, NULL);
	hKey22 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 218, 100, 20, hWnd, NULL, NULL, NULL);
	hKey23 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 238, 100, 20, hWnd, NULL, NULL, NULL);
	hKey24 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 366, 258, 100, 20, hWnd, NULL, NULL, NULL);

	//Left Page Input
	hPage1 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 38, 20, 20, hWnd, NULL, NULL, NULL);
	hPage2 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 58, 20, 20, hWnd, NULL, NULL, NULL);
	hPage3 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 78, 20, 20, hWnd, NULL, NULL, NULL);
	hPage4 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 98, 20, 20, hWnd, NULL, NULL, NULL);
	hPage5 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 118, 20, 20, hWnd, NULL, NULL, NULL);
	hPage6 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 138, 20, 20, hWnd, NULL, NULL, NULL);
	hPage7 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 158, 20, 20, hWnd, NULL, NULL, NULL);
	hPage8 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 178, 20, 20, hWnd, NULL, NULL, NULL);
	hPage9 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 198, 20, 20, hWnd, NULL, NULL, NULL);
	hPage10 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 218, 20, 20, hWnd, NULL, NULL, NULL);
	hPage11 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 238, 20, 20, hWnd, NULL, NULL, NULL);
	hPage12 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 166, 258, 20, 20, hWnd, NULL, NULL, NULL);
	//Right Page Input
	hPage13 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 38, 20, 20, hWnd, NULL, NULL, NULL);
	hPage14 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 58, 20, 20, hWnd, NULL, NULL, NULL);
	hPage15 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 78, 20, 20, hWnd, NULL, NULL, NULL);
	hPage16 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 98, 20, 20, hWnd, NULL, NULL, NULL);
	hPage17 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 118, 20, 20, hWnd, NULL, NULL, NULL);
	hPage18 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 138, 20, 20, hWnd, NULL, NULL, NULL);
	hPage19 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 158, 20, 20, hWnd, NULL, NULL, NULL);
	hPage20 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 178, 20, 20, hWnd, NULL, NULL, NULL);
	hPage21 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 198, 20, 20, hWnd, NULL, NULL, NULL);
	hPage22 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 218, 20, 20, hWnd, NULL, NULL, NULL);
	hPage23 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 238, 20, 20, hWnd, NULL, NULL, NULL);
	hPage24 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 486, 258, 20, 20, hWnd, NULL, NULL, NULL);

	//Left Line Input
	hLine1 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 38, 20, 20, hWnd, NULL, NULL, NULL);
	hLine2 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 58, 20, 20, hWnd, NULL, NULL, NULL);
	hLine3 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 78, 20, 20, hWnd, NULL, NULL, NULL);
	hLine4 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 98, 20, 20, hWnd, NULL, NULL, NULL);
	hLine5 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 118, 20, 20, hWnd, NULL, NULL, NULL);
	hLine6 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 138, 20, 20, hWnd, NULL, NULL, NULL);
	hLine7 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 158, 20, 20, hWnd, NULL, NULL, NULL);
	hLine8 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 178, 20, 20, hWnd, NULL, NULL, NULL);
	hLine9 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 198, 20, 20, hWnd, NULL, NULL, NULL);
	hLine10 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 218, 20, 20, hWnd, NULL, NULL, NULL);
	hLine11 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 238, 20, 20, hWnd, NULL, NULL, NULL);
	hLine12 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 206, 258, 20, 20, hWnd, NULL, NULL, NULL);

	//Right Line Input
	hLine13 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 38, 20, 20, hWnd, NULL, NULL, NULL);
	hLine14 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 58, 20, 20, hWnd, NULL, NULL, NULL);
	hLine15 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 78, 20, 20, hWnd, NULL, NULL, NULL);
	hLine16 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 98, 20, 20, hWnd, NULL, NULL, NULL);
	hLine17 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 118, 20, 20, hWnd, NULL, NULL, NULL);
	hLine18 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 138, 20, 20, hWnd, NULL, NULL, NULL);
	hLine19 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 158, 20, 20, hWnd, NULL, NULL, NULL);
	hLine20 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 178, 20, 20, hWnd, NULL, NULL, NULL);
	hLine21 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 198, 20, 20, hWnd, NULL, NULL, NULL);
	hLine22 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 218, 20, 20, hWnd, NULL, NULL, NULL);
	hLine23 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 238, 20, 20, hWnd, NULL, NULL, NULL);
	hLine24 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 526, 258, 20, 20, hWnd, NULL, NULL, NULL);

	//Left Word Input
	hWord1 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 38, 20, 20, hWnd, NULL, NULL, NULL);
	hWord2 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 58, 20, 20, hWnd, NULL, NULL, NULL);
	hWord3 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 78, 20, 20, hWnd, NULL, NULL, NULL);
	hWord4 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 98, 20, 20, hWnd, NULL, NULL, NULL);
	hWord5 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 118, 20, 20, hWnd, NULL, NULL, NULL);
	hWord6 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 138, 20, 20, hWnd, NULL, NULL, NULL);
	hWord7 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 158, 20, 20, hWnd, NULL, NULL, NULL);
	hWord8 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 178, 20, 20, hWnd, NULL, NULL, NULL);
	hWord9 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 198, 20, 20, hWnd, NULL, NULL, NULL);
	hWord10 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 218, 20, 20, hWnd, NULL, NULL, NULL);
	hWord11 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 238, 20, 20, hWnd, NULL, NULL, NULL);
	hWord12 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 246, 258, 20, 20, hWnd, NULL, NULL, NULL);

	//Right Word Input
	hWord13 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 38, 20, 20, hWnd, NULL, NULL, NULL);
	hWord14 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 58, 20, 20, hWnd, NULL, NULL, NULL);
	hWord15 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 78, 20, 20, hWnd, NULL, NULL, NULL);
	hWord16 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 98, 20, 20, hWnd, NULL, NULL, NULL);
	hWord17 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 118, 20, 20, hWnd, NULL, NULL, NULL);
	hWord18 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 138, 20, 20, hWnd, NULL, NULL, NULL);
	hWord19 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 158, 20, 20, hWnd, NULL, NULL, NULL);
	hWord20 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 178, 20, 20, hWnd, NULL, NULL, NULL);
	hWord21 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 198, 20, 20, hWnd, NULL, NULL, NULL);
	hWord22 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 218, 20, 20, hWnd, NULL, NULL, NULL);
	hWord23 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 238, 20, 20, hWnd, NULL, NULL, NULL);
	hWord24 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 566, 258, 20, 20, hWnd, NULL, NULL, NULL);

	//Button
	HWND hBut = CreateWindowW(L"Button", L"Create", WS_VISIBLE | WS_CHILD | BS_BITMAP, 512, 284, 80, 120, hWnd, (HMENU)CREATE_BUTTON, NULL, NULL);
	SendMessageW(hBut, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hCreateImage);

	//On screen output 
	hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 20, 284, 480, 120, hWnd, NULL, NULL, NULL);

}