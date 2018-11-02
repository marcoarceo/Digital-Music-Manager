#ifndef DMM_H
#define DMM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

typedef struct duration
{
	int minutes;
	int seconds;
}Duration;

typedef struct played
{
	bool played;
}Played;

typedef struct record
{
	char artists[30];
	char album[30];
	char song[30];
	char genre[10];
	Duration song_length;
	int plays;
	int rating;
	Played played;
}Record;

typedef struct node
{
	Record data;
	struct Node *pNext;
	struct Node *pPrev;
}Node;


/*******************************************************************************************
* Programmer: Marco Arceo
* Date: Jan, 27th, 2018
* Description: Displays the menu options
* Sources: N/A
*******************************************************************************************/
void display_menu();

/*******************************************************************************************
* Programmer: Marco Arceo
* Date: Jan, 27th, 2018
* Description: Gets the user option for the menu
* Sources: N/A
*******************************************************************************************/
int get_option(void);

/*******************************************************************************************
* Programmer: Marco Arceo
* Date: Jan, 27th, 2018
* Description: Determines if the user's option is valid
* Sources: N/A
*******************************************************************************************/
int determine_option(void);

/*******************************************************************************************
* Programmer: Marco Arceo
* Date: Jan, 28th, 2018
* Description: Makes the Node used in the program
* Sources: Class Code with modifications
*******************************************************************************************/
Node *makeNode(Record newData);

/*******************************************************************************************
* Programmer: Marco Arceo
* Date: Jan, 28th, 2018
* Description: Inserts the data to the front of the list
* Sources: Class code with modifications to convert into doubly linked list
*******************************************************************************************/
Node insertAtFront(Node **pList, Record newData);

/*******************************************************************************************
* Programmer: Marco Arceo
* Date: Jan, 28th, 2018
* Description: Gets the data from the csv file
* Sources: PA 1 code with a small snipet of code from Github (Korina0430)
*******************************************************************************************/
void getData(Node **pList, Record *newData, int index, FILE *infile);

/*******************************************************************************************
* Programmer: Marco Arceo
* Date: Jan, 29th, 2018
* Description: Stores the data back into the csv file
* Sources: N/A
*******************************************************************************************/
void store(Node *pList, FILE *outfile);

/*******************************************************************************************
* Programmer: Marco Arceo
* Date: Jan, 29th, 2018
* Description: Displays all the artists or an individual one
* Sources: Small help from TA at FIZ (logic errors)
*******************************************************************************************/
void display(Node *pList, int choice);

/*******************************************************************************************
* Programmer: Marco Arceo
* Date: Jan, 30th, 2018
* Description: Allows the user to change the song rating
* Sources: N/A
*******************************************************************************************/
void rate(Node **pList);

/*******************************************************************************************
* Programmer: Marco Arceo
* Date: Jan, 30th, 2018
* Description: Allows the user to play the whole playlist from any position
* Sources: N/A
*******************************************************************************************/
void play(Node *pList);

/*******************************************************************************************
* Programmer: Marco Arceo
* Date: Jan, 31th, 2018
* Description: Allows the user to edit the playlist
* Sources: Small help from Ryan N. TA (logic error)
*******************************************************************************************/
void edit(Node **pList);

/*******************************************************************************************
* Programmer: Marco Arceo
* Date: Feb, 6th, 2018
* Description: Allows the user to add a song to the list
* Sources: N/A
*******************************************************************************************/
Node * insert(Node **pList, Record newData);

/*******************************************************************************************
* Programmer: Marco Arceo
* Date: Feb, 7th, 2018
* Description: Allows the user to delete a song from the list
* Sources: N/A
*******************************************************************************************/
Node * deleteSong(Node **pList);

/*******************************************************************************************
* Programmer: Marco Arceo
* Date: Feb, 8th, 2018
* Description: Plays the list in a random order
* Sources: N/A
*******************************************************************************************/
void shuffle(Node *pList);

/*******************************************************************************************
* Programmer: Marco Arceo
* Date: Feb, 9th, 2018
* Description: Sorts the list in order
* Sources: Stackoverflow, github, textbook (Names in Function)
*******************************************************************************************/
Node * sort(Node **pList);

/*******************************************************************************************
* Help/Code was received/used for functions: Display( ), edit( ), and sort( ) 
* All sources have been given credit to the best of my knowledge and memory.
*******************************************************************************************/

#endif