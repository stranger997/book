#ifndef UNICODE
#define UNICODE
#endif 

#include <iostream>
#include "catalog.h"
#include <vector>
#include <string>
#include <ctype.h>
#include <time.h>
#include <iomanip>
#include <stdlib.h>
#include <list>
#include <fstream>
#define K 4

struct ListedWord
{
    std::string key;
    int page_loc;
    int line_loc;
    int word_loc;
};

class Book {



private:
    std::string bookname; //name of the book. Will be the file name.
    int pages;
    int lines;
    int words;
    int keysize;



public:
    std::vector<ListedWord> Keylist; // list of user keys
    std::string BIP_words[2048];
    std::vector<ListedWord> Wordlist; //words to be printed

// Default Constructor. Basically there to avoid errors.
    Book()
    {
        bookname = "book";
        pages = 1;
        lines = 48;
        words = 10;
        keysize = K;
        create_catalog(BIP_words);
    }

    // Constructor where you can also adjust the name and page number of the book. This is the more appropriate one.
    Book(std::string ubookname, int upage)
    {
        bookname = ubookname;
        pages = upage;
        lines = 48;
        words = 10;
        keysize = K;
        create_catalog(BIP_words);
    }

    //Constructor where you can adjust all parameters of the book. UNDER CONSTRUCTION, NO PUN INTENDED
    Book(std::string ubookname, int upage, int uline, int uword, int ukeysize)
    {
        bookname = ubookname;
        pages = upage;
        lines = uline;
        words = uword;
        keysize = ukeysize;
        create_catalog(BIP_words);
    }

    //Creation of random book
    void generate_book()
    {
        // std::vector<ListedWord>::iterator it;
        // it=Wordlist.begin();
        int it = 0;
        int pp = 0;
        int ll = 0;
        int ww = 0;
        ListedWord newword;

        srand(time(NULL));
        int random_digit = -1;

        for (pp = 0; pp < pages; pp++)
        {
            for (ll = 0; ll < lines; ll++)
            {
                for (ww = 0; ww < words; ww++)
                {

                    random_digit = rand() % 2048;
                    newword.key.assign(BIP_words[random_digit]);
                    newword.page_loc = pp;
                    newword.line_loc = ll;
                    newword.word_loc = ww;
                    Wordlist.push_back(newword);
                }
            }
        }



    }

    //Getting keys into keylist
    void fetch_keys(char ukeys[K][10], char upages[K][4], char ulines[K][3], char uwords[K][3])
    {
        int it = 0;
        int vecloc = 0;
        ListedWord keyword;
        for (it = 0; it < K; it++)
        {
            keyword.key = ukeys[it];
            keyword.page_loc = atoi(upages[it]);
            keyword.page_loc--;
            keyword.line_loc = atoi(ulines[it]);
            keyword.line_loc--;
            keyword.word_loc = atoi(uwords[it]);
            keyword.word_loc--;

            Keylist.push_back(keyword);

        }

    }


    //Errors check // UNDER CONSTRUCTION
    // Error codes:
    //1: 2 or more words in the same place
    //2: 1 or more words not in catalogue
    //3: 1 or more words have blank fields
    int errorflag()
    {
        ListedWord currentword;

        int it = 0;

        bool found = 0;

        for (it = 0; it < keysize; it++)
        {
            found = 0;
            currentword = Keylist.at(it);

            for (int i = 0; i < keysize; i++)
            {
                if (i == it) continue;

                if ((currentword.page_loc == Keylist.at(i).page_loc) && (currentword.line_loc == Keylist.at(i).line_loc) && (currentword.word_loc == Keylist.at(i).word_loc)) return 1;
            }

            for (std::string str : BIP_words)
            {
                if (currentword.key == str)
                {
                    found = 1;
                    break;
                }
            }
            if (!found) return 2;


        }

    }





    //Placing words in text
    void place_words()
    {
        int it = 0;
        int vecloc = 0;

        for (it = 0; it < keysize; it++)
        {
            vecloc = Keylist.at(it).page_loc * lines * words + Keylist.at(it).line_loc * words + Keylist.at(it).word_loc;
            Wordlist.at(vecloc).key = Keylist.at(it).key;

        }


    }

    //Write to .txt. Pretty self explanatory
    void write_to_txt()
    {
        std::string printname;
        printname += bookname; //add values to string
        printname += ".txt"; //add more values to string
        std::ofstream out_file(printname);
        int it = 0;

        for (int i = 0; i < pages; i++)
        {
            out_file << "Page " << i + 1 << std::endl;
            for (int j = 0; j < lines; j++)
            {
                for (int k = 0; k < words; k++)
                {
                    out_file << Wordlist.at(it).key << " ";
                    it++;
                }
                out_file << std::endl;
            }
        }


    }

};