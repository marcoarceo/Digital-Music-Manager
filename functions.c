/*******************************************************************************************
* Programmer: Marco Arceo
* Class: CptS 122, Spring 2018; Lab Section
* Programming Assignment: PA2
* Due Date: Jan, 31st, 2018
* Description: Digital Music Manager and Doubly Linked Lists
*******************************************************************************************/
#include "Header.h"

void display_menu() // Displays the menu options
{
	printf("Welcome to the Digital Music Manager!\n\n");
	printf("1. Load\n");
	printf("2. Store\n");
	printf("3. Display\n");
	printf("4. Insert\n");
	printf("5. Delete\n");
	printf("6. Edit\n");
	printf("7. Sort\n");
	printf("8. Rate\n");
	printf("9. Play\n");
	printf("10. Shuffle\n");
	printf("11. Exit\n\n");
}

int get_option(void)
{
	int option = 0, status = 0;

	printf("Enter your option: ");
	status = scanf("%d", &option);
	if (status == 0)
	{
		printf("Failed at reading the option!\n");
	}
	return option;
}

int determine_option(void)
{
	int option = 0;

	do // input validation loop
	{
		display_menu();
		option = get_option();
		system("cls");
	} while ((option < 1) || (option > 11));

	return option;
}

Node *makeNode(Record newData)
{ // Used class code given 1/26/18 to set up Doubly Link List

	Node *pHead = NULL; // Initialize pMem to NULL;

	pHead = (Node*)malloc(sizeof(Node)); // Allocate data for the node

	if (pHead != NULL) // Checks to make sure the space was allocated
	{
		pHead->pPrev = NULL;
		pHead->pNext = NULL;
		pHead->data.plays = newData.plays;
		pHead->data.rating = newData.rating;
		pHead->data.song_length.minutes = newData.song_length.minutes;
		pHead->data.song_length.seconds = newData.song_length.seconds;
		pHead->data.played.played = newData.played.played;
		strcpy(pHead->data.artists, newData.artists);
		strcpy(pHead->data.album, newData.album);
		strcpy(pHead->data.genre, newData.genre);
		strcpy(pHead->data.song, newData.song);
	}

	return pHead;
}

Node insertAtFront(Node **pList, Record newData)
{ // Used class code given 1/26/18 to set up Doubly Link List
	Node *pHead = NULL;

	pHead = makeNode(newData);

	if (pHead != NULL)
	{
		if (*pList != NULL)
		{
			pHead->pNext = *pList;
			(*pList)->pPrev = pHead;
			*pList = pHead;
		}
		else
		{
			*pList = pHead;
		}
	}
}

void getData(Node **pList, Record *newData, int index, FILE *infile)
{ // A copy of my function from PA1 with modifications for this PA
	const char delimiter[2] = ",", length_delim[2] = ":"; // tutorialspoint.com
	char *token; // tutorialspoint.com
	char record[100];

	Node *pHead = NULL;
	pHead = pList;

	fgets(record, 100, infile);

	token = strtok(record, delimiter);
	strcpy(newData[index].artists, token);

	if (record[0] == '\"') // GITHUB Korina0430, I didnt know how to get the artists full name
	{
		strcat(newData[index].artists, ",");
		token = strtok(NULL, delimiter);
		strcat(newData[index].artists, token);
	}
	//printf("%s\n", newData[index].artists);

	token = strtok(NULL, delimiter);
	strcpy(newData[index].album, token);
	//printf("%s\n", newData[index].album);

	token = strtok(NULL, delimiter);
	strcpy(newData[index].song, token);
	//printf("%s\n", newData[index].song);

	token = strtok(NULL, delimiter);
	strcpy(newData[index].genre, token);
	//printf("%s\n", newData[index].genre);

	token = strtok(NULL, length_delim);
	newData[index].song_length.minutes = atoi(token);

	token = strtok(NULL, delimiter);
	newData[index].song_length.seconds = atoi(token);
	//printf("%d:%d\n", newData[index].song_length.minutes, newData[index].song_length.seconds);

	token = strtok(NULL, delimiter);
	newData[index].plays = atoi(token);
	//printf("%d\n", newData[index].plays);

	token = strtok(NULL, delimiter);
	newData[index].rating = atoi(token);
	//printf("%d\n\n", newData[index].rating);

	insertAtFront(pList, newData[index]); // Inserts the data to the front
}

void store(Node *pList, FILE *outfile)
{
	Node *pHead = NULL;
	pHead = pList;

	while (pHead != NULL) // Works backwards storing the data like the original
	{
		fprintf(outfile, "%s,%s,%s,%s,%d:%d,%d,%d\n", pHead->data.artists, pHead->data.album, pHead->data.song, pHead->data.genre, pHead->data.song_length.minutes, pHead->data.song_length.seconds, pHead->data.plays, pHead->data.rating);
		pHead = pHead->pNext; // Work backwards to display the data like the original
	}
	printf("Stored Successfully!\n");
}

void display(Node *pList, int choice)
{ // Got help at the Fiz for this function (CS 121 TA)
	Node *pHead = NULL;
	char artist[100] = "";

	switch (choice)
	{
	case 1:
		pHead = pList;
		while (pHead != NULL)
		{ // Works backwards displaying the original list
			printf("Artist: %s\n", pHead->data.artists);
			printf("Album: %s\n", pHead->data.album);
			printf("Song: %s\n", pHead->data.song);
			printf("Genre: %s\n", pHead->data.genre);
			printf("Length: %d:%d\n", pHead->data.song_length.minutes, pHead->data.song_length.seconds);
			printf("Plays: %d\n", pHead->data.plays);
			printf("Rating: %d\n\n", pHead->data.rating);
			pHead = pHead->pNext; // Work backwards to display the data like the original
			Sleep(2000); // 2 second delay
		}
		break;

	case 2:
		pHead = pList;

		printf("\nWhich artist are you looking for?\n");
		printf("If First and Last name (Example: \"Swift, Taylor\"), Single name (Example: Adele): ");
		scanf(" %[^\n]s ", &artist); // Stackoverflow
		printf("\n");
		
		while (pHead != NULL) // Checks to make sure its not null
		{
 			if (stricmp(pHead->data.artists, artist) == 0) // stricmp( ) 2braces.com, compares the artists
			{
				printf("Artist: %s\n", pHead->data.artists);
				printf("Album: %s\n", pHead->data.album);
				printf("Song: %s\n", pHead->data.song);
				printf("Genre: %s\n", pHead->data.genre);
				printf("Length: %d:%d\n", pHead->data.song_length.minutes, pHead->data.song_length.seconds);
				printf("Plays: %d\n", pHead->data.plays);
				printf("Rating: %d\n\n", pHead->data.rating);
			}
			pHead = pHead->pNext;
		}
		Sleep(3000); // 3 second delay
		break;
	}
}

void rate(Node **pList)
{	
	Node *pHead = NULL;
	pHead = *pList;

	char song[100];
	int rating = 0;

	while (pHead->pNext != NULL)
	{
		pHead = pHead->pNext;
	}

	while (pHead != NULL)
	{
		printf("%s\n", pHead->data.song);
		pHead = pHead->pPrev; // Work backwards to display the data like the original
	}

	printf("\nWhich song's rating do you want to change?\n");
	scanf(" %[^\n]s ", &song); // Stackoverflow
	printf("\n");

	pHead = *pList;

	while (pHead != NULL)
	{
		if (stricmp(pHead->data.song, song) == 0) // stricmp( ) 2braces.com
		{
			do
			{
				printf("Enter a new rating between 1-5: ");
				scanf("%d", &rating);
			} while (rating < 1 || rating > 6);

			printf("Valid, changes have been made!\n");
			pHead->data.rating = rating;
		}
		pHead = pHead->pNext;
	}
}

void play(Node *pList)
{
	Node *pHead = NULL;
	pHead = pList;
	char song[100];

	while (pHead->pNext != NULL)
	{
		pHead = pHead->pNext;
	}

	while (pHead != NULL)
	{
		printf("%s\n", pHead->data.song);
		pHead = pHead->pPrev; // Work backwards to display the data like the original
	}

	printf("\nWhich song do you want to play first?\n");
	scanf(" %[^\n]s ", &song); // Stackoverflow
	printf("\n");

	pHead = pList;
	
	while (pHead != NULL)
	{
		if (stricmp(pHead->data.song, song) == 0) // stricmp( ) 2braces.com
		{
			printf("Artist: %s\n", pHead->data.artists);
			printf("Album: %s\n", pHead->data.album);
			printf("Song: %s\n", pHead->data.song);
			printf("Genre: %s\n", pHead->data.genre);
			printf("Length: %d:%d\n", pHead->data.song_length.minutes, pHead->data.song_length.seconds);
			printf("Plays: %d\n", pHead->data.plays);
			printf("Rating: %d\n", pHead->data.rating);
			pHead->data.played.played = true;
			Sleep(3000);
			system("cls");
		}
		pHead = pHead->pNext;
	}

	pHead = pList;

	while (pHead != NULL)
	{
		if (pHead->data.played.played == true)
		{
			pHead = pHead->pNext;
		}
		else if (pHead->data.played.played != true)
		{
			printf("Artist: %s\n", pHead->data.artists);
			printf("Album: %s\n", pHead->data.album);
			printf("Song: %s\n", pHead->data.song);
			printf("Genre: %s\n", pHead->data.genre);
			printf("Length: %d:%d\n", pHead->data.song_length.minutes, pHead->data.song_length.seconds);
			printf("Plays: %d\n", pHead->data.plays);
			printf("Rating: %d\n", pHead->data.rating);
			pHead->data.played.played = true;
			pHead = pHead->pNext;
			Sleep(3000);
			system("cls");
		}
	}

	pHead = pList;

	while (pHead != NULL)
	{
		pHead->data.played.played = false;
		pHead = pHead->pNext;
	}

	printf("Your playlist finished playing\n");
}

void edit(Node **pList)
{ // Allows the user to edit any aspect of the list
	Node *pHead = NULL;
	pHead = *pList;
	char artist[100], song[100], newString[100];
	int recurrence = 0, category = 0, newNumber1 = 0, newNumber2 = 0;

	while (pHead != NULL)
	{
		printf("%s\n", pHead->data.artists);
		pHead = pHead->pNext; // Work backwards to display the data like the original
	}

	printf("\nWhich artist do you want to edit?\n");
	printf("If First and Last name (Example: \"Swift, Taylor\"), Single name (Example: Adele): ");
	scanf(" %[^\n]s ", &artist); // Stackoverflow
	printf("\n");

	pHead = *pList;

	while (pHead != NULL) // Traverses through the list from the front to end
	{
		if (stricmp(pHead->data.artists, artist) == 0) // stricmp( ) 2braces.com
		{
			recurrence++;
			printf("Artist: %s\n", pHead->data.artists);
			printf("Album: %s\n", pHead->data.album);
			printf("Song: %s\n", pHead->data.song);
			printf("Genre: %s\n", pHead->data.genre);
			printf("Length: %d:%d\n", pHead->data.song_length.minutes, pHead->data.song_length.seconds);
			printf("Plays: %d\n", pHead->data.plays);
			printf("Rating: %d\n\n", pHead->data.rating);
		}
		pHead = pHead->pNext;
	}

	printf("Which song do you want to edit?: "); // My problem with this function is here
	gets();
	fgets(song, 100, stdin);
	strtok(song, "\n");

	pHead = *pList;

	if (recurrence == 1) // Ryan N. TA (Problem solved)
	{
		while (pHead != NULL)
		{
			if (stricmp(pHead->data.song, song) == 0) // stricmp( ) 2braces.com
			{
				printf("Song chosen was: %s\n", pHead->data.song);
				break;
			}
			pHead = pHead->pNext;
		}
	}
	if (recurrence >= 2) // Ryan N. TA
	{
		while (pHead != NULL)
		{
			if (stricmp(pHead->data.song, song) == 0) // stricmp( ) 2braces.com
			{
				printf("Song chosen was: %s\n", pHead->data.song);
				break;
			}
			pHead = pHead->pNext;
		}
	}

	printf("\nWhich category do you want to edit?");
	printf("\n1.) Artist Name\n2.) Album Name\n3.) Song Name\n4.) Genre\n5.) Length\n6.) Plays\n7.) Rating\n");
	scanf("%d", &category);

	switch (category) // Choose the case location that corresponds to the users option
	{
	case 1:
		printf("\nPlease enter a new name: ");
		gets();
		fgets(newString, 100, stdin);
		strtok(newString, "\n");
		strcpy(pHead->data.artists, newString);
		break;
	case 2:
		printf("\nPlease enter a new album name: ");
		gets();
		fgets(newString, 100, stdin);
		strtok(newString, "\n");
		strcpy(pHead->data.album, newString);
		break;
	case 3:
		printf("\nPlease enter a new name: ");
		gets();
		fgets(newString, 100, stdin);
		strtok(newString, "\n");
		strcpy(pHead->data.song, newString);
		break;
	case 4:
		printf("\nPlease enter a new name: ");
		gets();
		fgets(newString, 100, stdin);
		strtok(newString, "\n");
		strcpy(pHead->data.genre, newString);
		break;
	case 5:
		printf("\nEnter a new minute value followed by a space for the seconds value: ");
		scanf("%d %d", &newNumber1, &newNumber2);
		pHead->data.song_length.minutes = newNumber1;
		pHead->data.song_length.seconds = newNumber2;
		break;
	case 6:
		printf("\nEnter a new amount of plays: ");
		scanf("%d", &newNumber1);
		pHead->data.plays = newNumber1;
		break;
	case 7:
		printf("\nEnter a new rating: ");
		scanf("%d", &newNumber1);
		pHead->data.rating = newNumber1;
		break;
	}
}

Node * insert(Node **pList, Record newData)
{ // Used aspects of the makeNode( ) and insertAtFront( ) functions to make this
	Node *pHead = NULL;
	pHead = makeNode(newData);

	char artist[100], album[100], genre[100], song[100];
	int minutes, seconds, plays, rating;

	if (pHead != NULL)
	{
		if (*pList != NULL)
		{
			printf("Artist Name: ");
			gets();
			fgets(artist, 100, stdin);
			strtok(artist, "\n");
			strcpy(pHead->data.artists, artist);

			printf("Song: ");
			fgets(song, 100, stdin);
			strtok(song, "\n");
			strcpy(pHead->data.song, song);

			printf("Album: ");
			fgets(album, 100, stdin);
			strtok(album, "\n");
			strcpy(pHead->data.album, album);

			printf("Genre: ");
			fgets(genre, 100, stdin);
			strtok(genre, "\n");
			strcpy(pHead->data.genre, genre);

			printf("Minutes: ");
			scanf("%d", &minutes);
			pHead->data.song_length.minutes = minutes;

			printf("Seconds: ");
			scanf("%d", &seconds);
			pHead->data.song_length.seconds = seconds;

			printf("Plays: ");
			scanf("%d", &plays);
			pHead->data.plays = plays;

			printf("Rating (out of 5): ");
			scanf("%d", &rating);
			pHead->data.rating = rating;
		}
		pHead->pNext = *pList; // Connects the two nodes together
		(*pList)->pPrev = pHead;
		*pList = pHead;
	}
}

Node * deleteSong(Node **pList)
{ // Read parts of the book for this function and used some aspects of o'Fallons code
	Node *pHead = NULL, *pTemp = NULL;
	pHead = *pList;
	pTemp = pHead->pPrev;

	char song[100] = { '\0' };

	while (pHead != NULL)
	{
		printf("%s\n", pHead->data.song);
		pHead = pHead->pNext; // Work backwards to display the data like the original
	}

	pHead = *pList;

	if (pHead != NULL)
	{
		printf("What song do you want deleted?: ");
		gets();
		fgets(song, 100, stdin);
		strtok(song, "\n");

		while (pHead != NULL)
		{
			if (stricmp(pHead->data.song, song) == 0)
			{
				printf("The song was found...\n");
				break;
			}
			pTemp = pHead;
			pHead = pHead->pNext; 
		}

		if (pTemp == NULL)
		{
			*pList = (*pList)->pNext;
			free(pTemp);
		}
		else
		{
			pTemp->pNext = pHead->pNext;
			free(pHead);
		}
		printf("The song has been deleted!\n");
	}
	else
	{
		printf("An error occured!\n");
	}
}

void shuffle(Node *pList)
{ // Reverse engineered my Play( ) function to make it more random
	int list_size = 0, index = 0, shuffle = 0, plays = 0;
	bool played = true;
	char *song[100] = { "\0" };

	Node *pHead = NULL;
	pHead = pList;

	if (pHead != NULL)
	{
		while (pHead != NULL)
		{
			pHead = pHead->pNext;
			list_size += 1;
		}

		pHead = pList;

		for (int index = 0; index < list_size; index++)
		{
			song[index] = pHead->data.song;
			pHead = pHead->pNext;
		}

		do
		{
			pHead = pList;
			shuffle = rand() % list_size; // Gets a random nummber from 0 to n
			while (pHead != NULL)
			{
				if ((stricmp(pHead->data.song, song[shuffle]) == 0) && pHead->data.played.played != true) // stricmp( ) 2braces.com
				{
					printf("Artist: %s\n", pHead->data.artists);
					printf("Album: %s\n", pHead->data.album);
					printf("Song: %s\n", pHead->data.song);
					printf("Genre: %s\n", pHead->data.genre);
					printf("Length: %d:%d\n", pHead->data.song_length.minutes, pHead->data.song_length.seconds);
					printf("Plays: %d\n", pHead->data.plays);
					printf("Rating: %d\n\n", pHead->data.rating);
					pHead->data.played.played = true;
					plays++;
					Sleep(3000);
				}
				pHead = pHead->pNext;
			}
		} while (plays < list_size);

		pHead = pList;

		while (pHead != NULL)
		{
			pHead->data.played.played = false;
			pHead = pHead->pNext;
		}

		list_size = 0; // reset back to zero
		printf("Your playlist finished playing...\n");
	}
}

Node *sort(Node **pList)
{
	// https://stackoverflow.com/questions/30615735/bubble-sort-double-linked-list
	// "Typically 6 pointers need to be updated" this is for a doubly linked list
	// Bubble sort was copied from jamarFraction gitHub
	// Realized I was running out of time and the exams all week didnt allow me to finish this one alone
	// But i do fully understand the implementation of this code

	Node *pHead = NULL, *nextNode = NULL, *tempHead = NULL, *tempNext = NULL, *temp = NULL; // other pointer is the pList
	int size = 0, option = 0;

	pHead = *pList;
	
	if (pHead != NULL)
	{
		while (pHead != NULL)
		{
			pHead = pHead->pNext;
			size += 1;
		}
	}

	do
	{
		printf("How would you like to sort the list? \n1.) Artist\n2.) Album\n3.) Rating\n4.) Plays\nEnter your option: ");
		scanf("%d", &option);
	} while (option < 1 && option > 4);

	if (option == 1)
	{
		for (int i = 0; i < size; i++)
		{
			///////////////////////////////////////
			pHead = *pList;
			nextNode = (*pList)->pNext;          // FIZ TA helped me finish the code since it was crashing without this
			//////////////////////////////////////
			for (int j = 0; j < size - 1; j++)
			{
				if (stricmp(pHead->data.artists, nextNode->data.artists) >= 0)
				{
					////////////////////////////////////////////////////////
					tempHead = pHead->pPrev;
					tempNext = nextNode->pNext;
					pHead = nextNode;
					nextNode = nextNode->pPrev;

					if (tempHead == NULL)
					{
						*pList = pHead;
					}
					else // Code between these boundaries is from jamarFraction (github)
					{
						tempHead->pNext = pHead;
					}
					if (tempNext != NULL)
					{
						tempNext->pPrev = nextNode;
					}
					pHead->pNext = nextNode;
					pHead->pPrev = tempHead;
					nextNode->pPrev = pHead;
					nextNode->pNext = tempNext;
					/////////////////////////////////////////////////////////
				}
				temp = nextNode;
				nextNode = nextNode->pNext;
				pHead = temp;
			}
		}
		printf("Sorting was complete!\n");
	}

	if (option == 2)
	{
		for (int i = 0; i < size; i++)
		{
			///////////////////////////////////////
			pHead = *pList;
			nextNode = (*pList)->pNext;          // FIZ TA helped me finish the code since it was crashing without this
			//////////////////////////////////////
			for (int j = 0; j < size - 1; j++)
			{
				if (stricmp(pHead->data.album, nextNode->data.album) >= 0)
				{
					////////////////////////////////////////////////////////
					tempHead = pHead->pPrev;
					tempNext = nextNode->pNext;
					pHead = nextNode;
					nextNode = nextNode->pPrev;

					if (tempHead == NULL)
					{
						*pList = pHead;
					}
					else // Code between these boundaries is from jamarFraction (github)
					{
						tempHead->pNext = pHead;
					}
					if (tempNext != NULL)
					{
						tempNext->pPrev = nextNode;
					}
					pHead->pNext = nextNode;
					pHead->pPrev = tempHead;
					nextNode->pPrev = pHead;
					nextNode->pNext = tempNext;
					/////////////////////////////////////////////////////////
				}
				temp = nextNode;
				nextNode = nextNode->pNext;
				pHead = temp;
			}
		}
		printf("Sorting was complete!\n");
	}

	if (option == 3)
	{
		for (int i = 0; i < size; i++)
		{
			///////////////////////////////////////
			pHead = *pList;
			nextNode = (*pList)->pNext;          // FIZ TA helped me finish the code since it was crashing without this
			//////////////////////////////////////
			for (int j = 0; j < size - 1; j++)
			{
				if (pHead->data.rating <= nextNode->data.rating)
				{
					////////////////////////////////////////////////////////
					tempHead = pHead->pPrev;
					tempNext = nextNode->pNext;
					pHead = nextNode;
					nextNode = nextNode->pPrev;

					if (tempHead == NULL)
					{
						*pList = pHead;
					}
					else // Code between these boundaries is from jamarFraction (github)
					{
						tempHead->pNext = pHead;
					}
					if (tempNext != NULL)
					{
						tempNext->pPrev = nextNode;
					}
					pHead->pNext = nextNode;
					pHead->pPrev = tempHead;
					nextNode->pPrev = pHead;
					nextNode->pNext = tempNext;
					/////////////////////////////////////////////////////////
				}
				temp = nextNode;
				nextNode = nextNode->pNext;
				pHead = temp;
			}
		}
		printf("Sorting was complete!\n");
	}

	if (option == 4)
	{
		for (int i = 0; i < size; i++)
		{
			///////////////////////////////////////
			pHead = *pList;
			nextNode = (*pList)->pNext;          // FIZ TA helped me finish the code since it was crashing without this
			//////////////////////////////////////
			for (int j = 0; j < size - 1; j++)
			{
				if (pHead->data.plays <= nextNode->data.plays)
				{
					////////////////////////////////////////////////////////
					tempHead = pHead->pPrev;
					tempNext = nextNode->pNext;
					pHead = nextNode;
					nextNode = nextNode->pPrev;

					if (tempHead == NULL)
					{
						*pList = pHead;
					}
					else // Code between these boundaries is from jamarFraction (github)
					{
						tempHead->pNext = pHead;
					}
					if (tempNext != NULL)
					{
						tempNext->pPrev = nextNode;
					}
					pHead->pNext = nextNode;
					pHead->pPrev = tempHead;
					nextNode->pPrev = pHead;
					nextNode->pNext = tempNext;
					/////////////////////////////////////////////////////////
				}
				temp = nextNode;
				nextNode = nextNode->pNext;
				pHead = temp;
			}
		}
		printf("Sorting was complete!\n");
	}
}
