/*******************************************************************************************
* Programmer: Marco Arceo
* Class: CptS 122, Spring 2018; Lab Section
* Programming Assignment: PA2
* Due Date: Jan, 31st, 2018
* Description: Digital Music Manager and Doubly Linked Lists
* Sources: All sources (if any) have been given credit in the header comments
*******************************************************************************************/
#include "Header.h"

int main(void)
{
	int option = 0, index = 0, choice = 0;
	bool flag = true;
	FILE *infile = NULL, *outfile = NULL;
	Node *pList = NULL;

	Record newData[9];
	char *songs[100];

	while (flag)
	{
		do // MENU LOOPboo
		{
			option = determine_option();
			switch (option)
			{
			case 1: // Load the data
				infile = fopen("musicPlayList.csv", "r");
				for (index = 0; index < 9; index++)
				{
				 getData(&pList, &newData, index, infile);
				}
				printf("Data successfully gathered!\n");
				break;

			case 2: // STORE
				outfile = fopen("musicPlaylist.csv", "w");
				store(pList, outfile);
				fclose(outfile);
				break;

			case 3: // DISPLAY
				printf("Would you like to see 1.) all the songs or 2.) specific artists songs?: \n");
				scanf("%d", &choice);
				if (choice == 1)
				{
					display(pList, choice);
				}
				else if (choice == 2)
				{
					display(pList, choice);
				}
				break;

			case 4: // INSERT
				insert(&pList, *newData);
				break;

			case 5: // DELETE
				deleteSong(&pList);
				break;

			case 6: // EDIT
				edit(&pList);
				break;

			case 7: // SORT
				sort(&pList);
				break;

			case 8: // RATE
				rate(&pList);
				break;

			case 9: // PLAY
				play(pList);
				break;

			case 10: // SHUFFLE
				shuffle(pList);
				break;

			case 11: // EXIT
				printf("Goodbye!\n");
				outfile = fopen("musicPlaylist.csv", "w");
				store(pList, outfile);
				fclose(outfile);
				flag = false;
				return 0;
			}

			Sleep(3000);
			system("cls");

		} while (option > 0 && option < 12);
	}
}