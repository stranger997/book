#include <iostream>
#include <stdlib.h>
#include <string>
#include <iomanip>
#include <time.h>
#include <vector>
#include "catalog.h"
#include <cstring>
#include <fstream>
#include <filesystem>
#define L 48
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
    struct node *next;

}*head;


//Declaration of: 
//pages: number of pages in generated book
//BIP_words: catalogue of available words. Found in catalog.h
//wallet_key[K]: the words in the user's code
//existing_word_flag: used for checking whether or not the word provided by the user is in the list of available words
//cw: current word counter. Used for location check.

int pages=0;
string BIP_words[2048];
codeword wallet_key[K];
int existing_word_flag=-1;
int cw=-1;

//Each word in the book is a node, therefore insert_at_end is used to fill the book
void insert_at_end (int page, int line, int word_loc, string new_word)
{
    node* temp;
    temp = new node;
    temp->page_no=page;
    temp->line_no=line;
    temp->word_no=word_loc;
    temp->value=new_word;
    temp->is_in_password=0;
    temp->next=NULL;



    if (head==NULL)
    {
        head=temp;
    }
    else
    {
        node* temphead;
        temphead=head;
        

        while (temphead->next!=NULL) 
        {
            temphead=temphead->next;
        }

        temphead->next=temp;

    }
    

}

//Generating a book of random BIP words. Page amount is determined by the user.
void generate_book()
{


    do
    {
        cout << "Please select the number of pages you wish to have in your book:" << endl;

        cin.clear();
        fflush(stdin);
        cin >> pages;
    } while (pages<=0);

    cout << "Success!" << endl;

    int pp=-1; //page counter
    int ll=-1; //line counter
    int ww=-1; //word counter
    string new_word;

    srand(time(NULL));
    int random_digit;

    for (pp=0; pp<pages;pp++)
    {
        for (ll=0; ll<L; ll++)
        {
            for (ww=0; ww<W; ww++)
            {
                random_digit=rand()%2048;
                new_word.assign(BIP_words[random_digit]);
                insert_at_end(pp, ll, ww, new_word);
            }
        }
    }
}

//Checking whether or not the location provided by the user is not occupied by another word of their password
int location_check (codeword examined_word)
{
    for (int i=0; i<cw; i++)
    {
        if ((wallet_key[i].line_loc==examined_word.line_loc)&&(wallet_key[i].page_loc==examined_word.page_loc)&&(wallet_key[i].word_loc==examined_word.word_loc))
        {
            if (wallet_key[i].word!=examined_word.word) 
            {
                cout << "WARNING! You can't have two words in the same location!!" << endl;
                return 1;
            }
        }

    }
    return 0;
}

//User wallet password input and location input
void get_keys ()
{
    char uinput='X'; //FOR Y/N answers, later

    for (cw=0; cw<K; cw++)
        {
            cout << "Please enter word no." << cw+1 << endl;
            cin >> wallet_key[cw].word;

            do
            {
                do
                {
                    cout << "Please enter desired page(1-" << pages << "): ";
                    cin.clear();
                    fflush(stdin);
                    cin >> wallet_key[cw].page_loc;                
                }while ((wallet_key[cw].page_loc<=0)||(wallet_key[cw].page_loc>pages));
                wallet_key[cw].page_loc--;


                do
                {
                    cout << "Please enter desired line(1-48): ";
                    cin >> wallet_key[cw].line_loc;
                    cin.clear();
                    fflush(stdin);               
                } while ((wallet_key[cw].line_loc<=0)||(wallet_key[cw].line_loc>48));
                wallet_key[cw].line_loc--;
                

                do
                {
                cout << "Please enter desired word location(1-10): ";
                cin >> wallet_key[cw].word_loc;
                cin.clear();
                fflush(stdin);               
                } while ((wallet_key[cw].word_loc<=0)||(wallet_key[cw].word_loc>10));
                wallet_key[cw].word_loc--;


            } while (location_check(wallet_key[cw])==1);
            

             wallet_key[cw].pos=cw+1;


            for (int j=0; j<2048; j++)
             {
                if (wallet_key[cw].word==BIP_words[j])
                 {
                     existing_word_flag=1;
                     break;
                 }
                 else existing_word_flag=0;
             }
             if (existing_word_flag==0)
             {
                 do
                 {
                    cout << endl << "WARNING: The word you provided is not in our catalogue. Do you wish to proceed? (Y/N)" << endl;
                    cin >> uinput;
                 } while ((uinput!='y')&&(uinput!='Y')&&(uinput!='n')&&(uinput!='N'));
                 
                 if ((uinput=='N')||(uinput=='n')) cw--;
                 

             }

        }

}

//Placing user's words in the nodelist
void place_words()
{
    int pageno;
    int lineno;
    int wordno;
    string chosen_word;

    node* temphead=head;

    

    for (int i=0; i<K; i++)
        {
            pageno=wallet_key[i].page_loc;
            lineno=wallet_key[i].line_loc;
            wordno=wallet_key[i].word_loc;
            chosen_word=wallet_key[i].word;

            while (temphead->page_no!=pageno)
            {
                temphead=temphead->next;
                if (temphead==NULL) temphead=head;
            }
            while (temphead->line_no!=lineno)
            {
                temphead=temphead->next;
                if (temphead==NULL) temphead=head;

            }
            while (temphead->word_no!=wordno)
            {
                temphead=temphead->next;
                if (temphead==NULL) temphead=head;

            }
            temphead->value=chosen_word;
            temphead->is_in_password=1;
        }


}

//Printing the book. Will probably change to print the info to an appropriate .txt or .pdf file.
void display_book()
{
    node* temphead=head;
    for (int i=0; i<pages; i++)
     {
        cout << "PAGE " << i+1 << endl;
        for (int j=0; j<48;j++)
        {
            for (int k=0; k<10; k++)
                {
                    cout << temphead->value << " ";
                    temphead=temphead->next;
                }
            cout << endl;
        }


     }
}

//Creation of txt file
void write_to_txt()
{
    string bookname;
    cout << "Enter a name for your book:" << endl;
    cin >> bookname;
    bookname+=".txt";
    ofstream out_file (bookname);
    if (!out_file)
    {
        cerr << "ERROR: Could not create file" << endl;
    }

    node* temphead=head;
    for (int i=0; i<pages; i++)
     {
        // out_file << "Page " << i+1 << endl; // REENABLE
        for (int j=0; j<48;j++)
        {
            for (int k=0; k<10; k++)
                {
                    out_file << temphead->value << " ";
                    temphead=temphead->next;
                }
            out_file << endl;
        }
     }

}

/* 
Main function first of all calls the "create catalog" function, which basically forms an array of all the BIP words.
Subsequently, it calls the functions generate_book, get_keys, place_words, display_book, write_to_text in that order.
Later iterations should have options for
*/
int main ()
{
    create_catalog(BIP_words);
    generate_book();
    get_keys();
    place_words();
    display_book();
    write_to_txt();

    return 0;
}
