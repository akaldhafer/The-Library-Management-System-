#include <iostream>
#include <string>
#include <cstring> //This header file defines several functions to manipulate C strings and arrays.

using namespace std;

/*The Library Management System 
the system designed to be used by the library admin and the patrons

Techniques used: 
1. linked list
2. array

The system developed by Abdulmalek Aldhafer
for any question please send me email: Ak_aldhafer@hotmail.com
linkedin account: https://www.linkedin.com/in/abdulmalek-aldhafer-206485173 
Github account: https://github.com/akaldhafer*/


/*declare the linked list variables*/
struct PatronRecord { // this struct will hold Patron details
	string PID; //Patron number
	string PName; //Patron name
	string Phone; //Patron phone
	int BorrowNo;/*number of borrowing book*/
	int ReturnNo;/*number of returing book*/
	string BorrowingBook[3][5];/*ID- titl -category-genre-date*/
	string ReturningBook[15][5];
	PatronRecord* Next; /*linked list next*/
};
struct BookRecord {/*book strcutre*/
	string bID;/*book ID*/
	string btitle; /*book title*/
	string category; /*book category*/
	string genre; /*book genre */
	bool availability; /*book availability*/
	BookRecord* Next2;/*linked list next*/
};

// Drclare the Head of the linked list//
PatronRecord* Head = NULL; //Patrons linkedlist 
BookRecord* Head2 = NULL; //Book linkedlist 
/*decalre some public veriable */
int place = 0, place2 = 0, posi = 0;
char choice, option1, option2;
int position;

string Booktitle, bcateg, bgenre, borrowdate, bkid, pid;

string PIDInput; //Patron number
string PNameInput; //Patron name
string PhoneInput; //Patron phone
string BorrowingBookInput[3][5];/*book ID- book titl -book-borrowing date-*/
string ReturningBookInput[15][5];
int BorrowNoInput;/*number of borrowing book*/

string bIDInput;
string btitleInput;
string categoryInput;
string genreInput;
bool availabilityInput;
/*declare the genres*/
string genre1 = "Fantasy";
string genre2 = "Science";
string genre3 = "Historical";
string genre4 = "Realistic";
string genre5 = "Fan";
string genre6 = "Narrative";
string genre7 = "Biography";
string genre8 = "Periodicals";
string genre9 = "Self-help";
string genre10 = "Reference";
string category1 = "Fiction";
string category2 = "Non-Fiction";
/*declare the functions*/
void Login();
void AddBook();
void AddPatron();
void DisplayBook(BookRecord* Head);
void DisplayBookA(BookRecord* Head);
BookRecord* SearchBook(string title, BookRecord* Head);
bool SearchP(string pid, PatronRecord* Head);
bool Searchb(string bid, BookRecord* Head);
void returnbook();
void borrowBook(string biD, BookRecord* Head2);
void borrowBookp(string biD, PatronRecord* Head);
void SearchPRecord(PatronRecord* Head);
void PLastBorrowedB(PatronRecord* Head);
BookRecord* UpdateBook(string biD, BookRecord* Head);
void UpdatePInfo();
void DisplayPatrons(PatronRecord* Head);
void InsertArbitraryp(string patronid, string pname, string phone, int index);
void InsertArbitraryb(string bid, string Btitle, string bcategory, string bgerne, bool avaiable, int index);

/*insert new record arbitrary for patron */
void InsertArbitraryp(string patronid, string pname, string phone, int index)
{
	PatronRecord* New_node = new PatronRecord; // create new node
	New_node->PID = patronid;    // Assign the variable to its data
	New_node->PName = pname;
	New_node->Phone = phone;
	New_node->BorrowNo = 0;
	New_node->ReturnNo = 0;
	if (index <= place) {
		if (index == 0) { //insert at the beginning
			PatronRecord* Position = new PatronRecord;
			Position->PID = patronid;    // Assign the variable to its data
			Position->PName = pname;
			Position->Phone = phone;
			Position->BorrowNo = 0;
			Position->ReturnNo = 0;
			Position->Next = Head;
			Head = Position;}
		else if (index == place) { //insert at the end of the linked list
			PatronRecord* Position2 = new PatronRecord; //create new node
			Position2->PID = patronid;    // Assign the variable to its data
			Position2->PName = pname;
			Position2->Phone = phone;
			Position2->BorrowNo = 0;
			Position2->ReturnNo = 0;
			Position2->Next = NULL;   // assign the next of the position to NULL
			if (Head == NULL)
				Head = Position2; // insert at the beginning of the linked list
			else { //insert at the end of the linked list
				PatronRecord* MyCurrent1 = Head;//create new node that equal the head 
				while (MyCurrent1->Next != NULL) {//while will work until it reaches the NULL(end of linked list)
					MyCurrent1 = MyCurrent1->Next; // move from position to the next one until reach the end of the linked list
				}
				MyCurrent1->Next = Position2; // my last position->next in the linked list ->
			}                                 //-> will be equal the position that the new recode will be saved at
		}
		else { //insert at the given position
			PatronRecord* new_record = new PatronRecord; // create new node
			new_record->PID = patronid;    // Assign the variable to its data
			new_record->PName = pname;
			new_record->Phone = phone;
			new_record->BorrowNo = 0;
			new_record->ReturnNo = 0;
			PatronRecord* prev = Head; //create new node and assgin it to the head of the linked list
			for (int i = 0; i < index - 1; i++)
				prev = prev->Next;
			new_record->Next = prev->Next;
			prev->Next = new_record;
		}
	}
	else if (index > place)
	{
		PatronRecord* Position2 = new PatronRecord; // create new recode
		Position2->PID = patronid;    // Assign the variable to its data
		Position2->PName = pname;
		Position2->Phone = phone;
		Position2->BorrowNo = 0;
		Position2->ReturnNo = 0;
		Position2->Next = NULL;
		if (Head == NULL) {
			Head = Position2; // insert at the beginning of the linked list
		}
		else {
			PatronRecord* MyCurrent1 = Head; //insert at the end of the linked list
			while (MyCurrent1->Next != NULL) {//while will work until it reaches the NULL(end of linked list)
				MyCurrent1 = MyCurrent1->Next;}
			MyCurrent1->Next = Position2;
		}
	}
}

/*insert arbitrary book*/
void InsertArbitraryb(string bid, string Btitle, string bcategory, string bgerne, bool avaiable, int index){
	BookRecord* New_node = new BookRecord; // create new node
	New_node->bID = bid;
	New_node->btitle = Btitle;
	New_node->category = bcategory;
	New_node->genre = bgerne;
	New_node->availability = avaiable;
	if (index <= place2) { /*if the given position less than the linked list size*/
		/*when the linked list still empty- insert at the begnning*/
		if (index == 0) { //insert at the beginning
			BookRecord* Position = new BookRecord;
			Position->bID = bid;
			Position->btitle = Btitle;
			Position->category = bcategory;
			Position->genre = bgerne;
			Position->availability = avaiable;
			Position->Next2 = Head2;
			Head2 = Position;
		} 
		/*if the given position is equal the linked list size: insert at the end*/
		else if (index == place2)
		{ //insert at the end of the linked list
			BookRecord* Position2 = new BookRecord; //create new node
			Position2->bID = bid;
			Position2->btitle = Btitle;
			Position2->category = bcategory;
			Position2->genre = bgerne;
			Position2->availability = avaiable;
			Position2->Next2 = NULL;   // assign the next of the position to NULL
			if (Head2 == NULL)
				Head2 = Position2; // insert at the beginning of the linked list
			else { //insert at the end of the linked list
				BookRecord* MyCurrent1 = Head2;//create new node that equal the head 
				while (MyCurrent1->Next2 != NULL) {//while will work until it reaches the NULL(end of linked list)
					MyCurrent1 = MyCurrent1->Next2; // move from position to the next one until reach the end of the linked list
				}
				MyCurrent1->Next2 = Position2; // my last position->next in the linked list ->
			}                                 //-> will be equal the position that the new recode will be saved at
		}
		/*insert at the given position*/
		else { //insert at the given position
			BookRecord* new_record = new BookRecord; // create new node
			new_record->bID = bid;
			new_record->btitle = Btitle;
			new_record->category = bcategory;
			new_record->genre = bgerne;
			new_record->availability = avaiable;
			BookRecord* prev = Head2; //create new node and assgin it to the head of the linked list
			for (int i = 0; i < index - 1; i++)
				prev = prev->Next2;
			new_record->Next2 = prev->Next2;
			prev->Next2 = new_record;
		}
	}
	/*when the linked list size is bigger than the given position*/
	else if (index > place2){ 
		BookRecord* Position2 = new BookRecord; // create new recode
		Position2->bID = bid;
		Position2->btitle = Btitle;
		Position2->category = bcategory;
		Position2->genre = bgerne;
		Position2->availability = avaiable;
		Position2->Next2 = NULL;
		if (Head2 == NULL) {
			Head2 = Position2; // insert at the beginning of the linked list
		}
		else {
			BookRecord* MyCurrent1 = Head2; //insert at the end of the linked list
			while (MyCurrent1->Next2 != NULL) {//while will work until it reaches the NULL(end of linked list)
				MyCurrent1 = MyCurrent1->Next2;
			}
			MyCurrent1->Next2 = Position2;
		}
	}
}

/*display record info*/
void DisplayBook(BookRecord* Head) {
	BookRecord* MyCurrent1 = Head;
	if (MyCurrent1 == NULL) {/*checking if the linked list is empty or not*/
		cout << "NO recode yet!!, please insert new recodes first..." << endl;}
	while (MyCurrent1 != NULL) { /*displaying the inserted nodes*/
		cout << " Book ID           : " << MyCurrent1->bID << endl;
		cout << " Book title        : " << MyCurrent1->btitle << endl;
		cout << " Book category     : " << MyCurrent1->category << endl;
		cout << " Book Genre        : " << MyCurrent1->genre << endl;
		cout << " Book availability(1=True & 0= False) : " << MyCurrent1->availability << endl;
		cout << "|------------------------------------------------------------------|" << endl;
		MyCurrent1 = MyCurrent1->Next2;// go to next
	}
}
/*display patrons records with the active borrowed books*/
void DisplayPatrons(PatronRecord* Head) {
	PatronRecord* MyCurrent1 = Head;
	if (MyCurrent1 == NULL) {
		cout << "NO recode yet!!, please insert new recodes first..." << endl;
	}
	while (MyCurrent1 != NULL) {
		cout << " Patron ID              : " << MyCurrent1->PID << endl;
		cout << " Patron Name            : " << MyCurrent1->PName << endl;
		cout << " Patron Phone NO        : " << MyCurrent1->Phone << endl;
		cout << " Number of borrowed book: " << MyCurrent1->BorrowNo << endl;
		cout << " The borrowed books: \n"<<endl;
		for (int i = 0; i < MyCurrent1->BorrowNo; i++)
		{
			cout << " Book ID                : " << MyCurrent1->BorrowingBook[i][0] << endl;
			cout << " Book title             : " << MyCurrent1->BorrowingBook[i][1] << endl;
			cout << " Book category          : " << MyCurrent1->BorrowingBook[i][2] << endl;
			cout << " Book Genre             : " << MyCurrent1->BorrowingBook[i][3] << endl;
			cout << " Borrow Date            : " << MyCurrent1->BorrowingBook[i][4] << endl;
			cout << "|------------------------------------------------|" << endl;
		}
		MyCurrent1 = MyCurrent1->Next;// go to next
	}
}
/*display last 10 borrowed book*/
void PLastBorrowedB(PatronRecord* Head) {
	PatronRecord* MyCurrent1 = Head;
	string name;
	cout << "\nEnter Patron Name or ID: "; cin >> name;
	if (MyCurrent1 == NULL) {
		cout << "NO recode yet!!, please insert new recodes first..." << endl;
	}
	while (MyCurrent1 != NULL) {
		if (name == MyCurrent1->PName || name == MyCurrent1->PID) {
			cout << " Patron ID              : " << MyCurrent1->PID << endl;
			cout << " Patron Name            : " << MyCurrent1->PName << endl;
			cout << " Patron Phone NO        : " << MyCurrent1->Phone << endl;
			cout << " Number of borrowed book: " << MyCurrent1->BorrowNo << endl;
			cout << " The borrowed books: \n" << endl;
			for (int i = 0; i < MyCurrent1->ReturnNo; i++)
			{
				if (i ==10)/*to display only the last 10 borrowed books*/
				{
					break;
				}
				cout << " Book ID                : " << MyCurrent1->ReturningBook[i][0] << endl;
				cout << " Book title             : " << MyCurrent1->ReturningBook[i][1] << endl;
				cout << " Book category          : " << MyCurrent1->ReturningBook[i][2] << endl;
				cout << " Book Genre             : " << MyCurrent1->ReturningBook[i][3] << endl;
				cout << " Borrow Date            : " << MyCurrent1->ReturningBook[i][4] << endl;
				cout << "|------------------------------------------------|" << endl;
			}
			break;
		}
		else
		{
			MyCurrent1 = MyCurrent1->Next;// go to next
		}
	}
}
/*search patron record*/
void SearchPRecord(PatronRecord* Head) {
	PatronRecord* MyCurrent1 = Head;
	string sname;
	cout << "\nEnter Patron Name or ID: "; cin >> sname;
	if (MyCurrent1 == NULL) {
		cout << "NO recode yet!!, please insert new recodes first..." << endl;}
	while (MyCurrent1 != NULL) {
		if (sname == MyCurrent1->PName || sname == MyCurrent1->PID) {
			cout << " Patron ID              : " << MyCurrent1->PID << endl;
			cout << " Patron Name            : " << MyCurrent1->PName << endl;
			cout << " Patron Phone NO        : " << MyCurrent1->Phone << endl;
			cout << " Number of borrowed book: " << MyCurrent1->BorrowNo << endl;
			cout << " The borrowed books: \n" << endl;
			for (int i = 0; i < MyCurrent1->BorrowNo; i++)
			{
				cout << " Book ID                : " << MyCurrent1->BorrowingBook[i][0] << endl;
				cout << " Book title             : " << MyCurrent1->BorrowingBook[i][1] << endl;
				cout << " Book category          : " << MyCurrent1->BorrowingBook[i][2] << endl;
				cout << " Book Genre             : " << MyCurrent1->BorrowingBook[i][3] << endl;
				cout << " Borrow Date            : " << MyCurrent1->BorrowingBook[i][4] << endl;
				cout << "|------------------------------------------------|" << endl;
			}
			break;
		}
		else
		{
			MyCurrent1 = MyCurrent1->Next;// go to next
		}
	}
}
/*display the avaiable books*/
void DisplayBookA(BookRecord* Head) {
	BookRecord* MyCurrent1 = Head;
	if (MyCurrent1 == NULL) {
		cout << "NO recode yet!!, please insert new recodes first..." << endl;
	}
	while (MyCurrent1 != NULL) {
		if (MyCurrent1->availability == true) {

			cout << " Book ID           : " << MyCurrent1->bID << endl;
			cout << " Book title        : " << MyCurrent1->btitle << endl;
			cout << " Book category     : " << MyCurrent1->category << endl;
			cout << " Book Genre        : " << MyCurrent1->genre << endl;
			cout << " Book availability(1=True & 0= False) : " << MyCurrent1->availability << endl;
		}
		cout << "|-------------------------------------------------------------------------|" << endl;
		MyCurrent1 = MyCurrent1->Next2;// go to next
	}
}
/*search book*/
BookRecord* SearchBook(string title, BookRecord* Head) {
	BookRecord* MyCurrent = Head;
	if (MyCurrent == NULL) {
		cout << "NO recode yet!!, please insert new recodes first..." << endl;
	}
	while (MyCurrent != NULL) { 
		if (MyCurrent->btitle == title|| MyCurrent->genre == title|| MyCurrent->category == title || MyCurrent->availability == true) {
			cout << " Book ID           : " << MyCurrent->bID << endl;
			cout << " Book title        : " << MyCurrent->btitle << endl;
			cout << " Book category     : " << MyCurrent->category << endl;
			cout << " Book Genre        : " << MyCurrent->genre << endl;
			cout << " Book availability(1=True & 0= False) : " << MyCurrent->availability << endl;
			cout << "|-------------------------------------------------------------------------|" << endl;
			return MyCurrent;
		}
		else {
			MyCurrent = MyCurrent->Next2; //go to next record
		}
	}
	return NULL;
}

/*search the avaiability*/
bool Searchb(string bid, BookRecord* Head)
{
	BookRecord* MyCurrent = Head;
	while (MyCurrent != NULL) {
		if (MyCurrent->bID == bid) {
			return true;
		}
		else {
			MyCurrent = MyCurrent->Next2; //go to next record
		}
	}
	return false;
}

/*search function for patron */
bool SearchP(string pid, PatronRecord* Head) 
{
	PatronRecord* MyCurrent = Head;
	while (MyCurrent != NULL) {
		if (MyCurrent->PID == pid) {
			return true;
		}
		else {
			MyCurrent = MyCurrent->Next; //go to next record
		}
	}
	return false;
}
/*update the book record*/
BookRecord* UpdateBook(string biD, BookRecord* Head) {
	BookRecord* MyCurrent1 = Head;
	string Booktitle, bcategory, bgenre;
	while (MyCurrent1 != NULL) { 
		if (MyCurrent1->bID == biD) { 
			getchar();
			cout << "Enter Book title: ";
			getline(cin, Booktitle, '\n');
			cout << "Enter Book Category(1. Fiction  2. Non-Fiction): "; cin >> option1;
			if (option1 == '1') {
				bcategory = category1;
				cout << "\nBook genres: ";
				cout << "1. Fantasy   2. Science   3. Historical  4. Realistic  5. Fan\nEnter one option:  ";
				cin >> option2;
				if (option2 == '1') {
					bgenre = genre1;
				}
				else if (option2 == '2') {
					bgenre = genre2;
				}
				else if (option2 == '3') {
					bgenre = genre3;
				}
				else if (option2 == '4') {
					bgenre = genre4;
				}
				else {
					bgenre = genre5;
				}
			}
			else {
				bcategory = category2;
				cout << "Book genres: ";
				cout << "1. Fantasy   2. Science   3. Historical  4. Realistic  5. Fan\nEnter one option:  ";
				cin >> option2;
				if (option2 == '1') {
					bgenre = genre6;
				}
				else if (option2 == '2') {
					bgenre = genre7;
				}
				else if (option2 == '3') {
					bgenre = genre8;
				}
				else if (option2 == '4') {
					bgenre = genre9;
				}
				else {
					bgenre = genre10;
				}
			}
			MyCurrent1->btitle = Booktitle;
			MyCurrent1->category = bcategory;
			MyCurrent1->genre = bgenre;
			cout << "The New Details" << endl;
			cout << " Book ID           : " << MyCurrent1->bID << endl;
			cout << " Book title        : " << MyCurrent1->btitle << endl;
			cout << " Book category     : " << MyCurrent1->category << endl;
			cout << " Book Genre        : " << MyCurrent1->genre << endl;
			cout << " Book availability(1=True & 0= False) : " << MyCurrent1->availability << endl;
			cout << "|-------------------------------------------------------------------------|" << endl;
			return MyCurrent1;
		}
		else
			MyCurrent1 = MyCurrent1->Next2; 	
	}
	return NULL;
}
/*update patron info*/
void UpdatePInfo()
{
	PatronRecord* MyCurrent = Head;
	cout << "Enter Patron ID: "; cin >> PIDInput;/*getting the patron record*/
	while (MyCurrent != NULL) {
		if (MyCurrent->PID == PIDInput) {/*find the patron record*/
			cout << "\nPlease fill up The new info: \n" << endl;
			getchar();
			cout << "Enter Patron Name: "; getline(cin, PNameInput, '\n');
			cout << "Enter Phone No   : "; getline(cin, PhoneInput, '\n');
			MyCurrent->PName = PNameInput;/*assigning the new data*/
			MyCurrent->Phone = PhoneInput;
			break;
		}
		else {
			MyCurrent = MyCurrent->Next; //go to next record
		}
	}
	return;
}
/*borrow a book*/
void borrowBookp(string piD, PatronRecord* Head) {
	PatronRecord* MyCurrent2 = Head;
	while (MyCurrent2 != NULL){
		if (MyCurrent2->BorrowNo >=3) {/*if the number of the borrow book is equal or less than 3 will be allowed*/
			cout << "\n <!>  The patron has reached the maximum number of borrowing books(which is 3 books)<!>\n";
			cout << "\nNoted: The patron may return one of the borrowed book to be able to borrow a new book\n";
			break;}
		if (MyCurrent2->PID == pid) {
			cout << "\nNote: return the book within 15 days after the borrowing date!\n";
			cout << "Enter borrowing date(Y/M/D): "; cin >> borrowdate;
			for (int i = MyCurrent2->BorrowNo; i < MyCurrent2->BorrowNo+1; i++){
				MyCurrent2->BorrowingBook[i][0] = bkid;/*copying the book detail into borrowbook array*/
				MyCurrent2->BorrowingBook[i][1] = Booktitle;
				MyCurrent2->BorrowingBook[i][2] = bcateg;
				MyCurrent2->BorrowingBook[i][3] = bgenre;
				MyCurrent2->BorrowingBook[i][4] = borrowdate;}		
			MyCurrent2->BorrowNo += 1;/*increase the number of the borrow books*/
			cout << "The Borrowing Details" << endl;/*displaying the borrow book details*/
			cout << " Patron ID         : " << MyCurrent2->PID << endl;
			cout << " Patron Name       : " << MyCurrent2->PName << endl;
			cout << " Book ID           : " << MyCurrent2->BorrowingBook[MyCurrent2->BorrowNo-1][0] << endl;
			cout << " Book title        : " << MyCurrent2->BorrowingBook[MyCurrent2->BorrowNo - 1][1] << endl;
			cout << " Book category     : " << MyCurrent2->BorrowingBook[MyCurrent2->BorrowNo - 1][2] << endl;
			cout << " Book Genre        : " << MyCurrent2->BorrowingBook[MyCurrent2->BorrowNo - 1][3] << endl;
			cout << " Borrow Date       : " << MyCurrent2->BorrowingBook[MyCurrent2->BorrowNo - 1][4] << endl;
			cout << "|-------------------------------------------------------------------------|" << endl;
			break;
		}
		else
			MyCurrent2 = MyCurrent2->Next;/*go to the next record*/
	}
}
void borrowBook(string biD,BookRecord* Head2) {
	BookRecord* MyCurrent1 = Head2;
	while (MyCurrent1 != NULL) {
		if (MyCurrent1->bID == biD && MyCurrent1->availability == true) {
			bkid= MyCurrent1->bID; /*getting the book details*/
			Booktitle = MyCurrent1->btitle;
			bcateg = MyCurrent1->category;
			bgenre = MyCurrent1->genre;
			cout << "Enter Patron ID: "; cin >> pid;
			if (SearchP(pid, Head) == false)/*checking the patron id*/
			{
				cout << "\nThis PID is not avaiable yet. Pls try again with new ID\n" << endl;
				break;}
			else {
				borrowBookp(pid,Head); /*calling the borrow function*/
				MyCurrent1->availability = false;/*set the borrowed book to not available*/
				break;
			}
		}
		else
			MyCurrent1 = MyCurrent1->Next2;
	}
}

/*return the book*/
void returnbook() {
	PatronRecord* MyCurrent1 = Head;
	string Patronid,bid;
	cout << "\nEnter Patron ID: "; cin >> Patronid;
	cout << "\nEnter Book ID to return it: "; cin >> bid;
	if (MyCurrent1 == NULL) {
		cout << "NO recode yet!!, please insert new recodes first..." << endl;}
	while (MyCurrent1 != NULL) {
		if (Patronid == MyCurrent1->PID) {
			for (int i = 0; i < MyCurrent1->BorrowNo; i++){
				if (MyCurrent1->BorrowingBook[i][0] == bid) {
					for (int ii = MyCurrent1->ReturnNo; ii < MyCurrent1->ReturnNo+1; ii++)
					{   /*copy the date from the borrow book array into the returning book array*/
						MyCurrent1->ReturningBook[ii][0] = MyCurrent1->BorrowingBook[ii][0];
						MyCurrent1->ReturningBook[ii][1] = MyCurrent1->BorrowingBook[ii][1];
						MyCurrent1->ReturningBook[ii][2] = MyCurrent1->BorrowingBook[ii][2];
						MyCurrent1->ReturningBook[ii][3] = MyCurrent1->BorrowingBook[ii][3];
						MyCurrent1->ReturningBook[ii][4] = MyCurrent1->BorrowingBook[ii][4];}
					/*making the book avaiable again*/
					BookRecord* reader = Head2;
					while (reader != NULL){
						if (reader->bID == bid) {
							reader->availability = true;
							break;}
						reader = reader->Next2;}
					/*deleting the returning book from the borrow book array*/
					int a, j, k;
					int NoColumn = 5;
					int NORows = 3;
					for (a = 0; a < NORows; a++) {
						for (k = a; k < NORows - 1; k++) {
							for (j = 0; j < NoColumn; j++) {
								MyCurrent1->BorrowingBook[k][j] = MyCurrent1->BorrowingBook[k + 1][j];}
						}
						a--;
						NORows--;
					}
				}		
			}
			MyCurrent1->ReturnNo += 1;/*increase the number of the returning book*/
			MyCurrent1->BorrowNo -= 1;/*decreasing the number of the borrowed book*/
			cout << "\n <!> The book has been returned successfully  <!>\n";
			break;
		}
		else
		{
			MyCurrent1 = MyCurrent1->Next;// go to next
		}
	}
}
/*function to store the book details such as id, title, categorey, genre, avaiability*/
void AddBook(){
	cout << "\nPlease fill up the following requirements: \n" << endl;
	cout << "Enter Book ID: "; cin >> bIDInput;
	if (Searchb(bIDInput, Head2) == true) {
		cout << "\n This ID has been used before !!\n" << endl;}
	else {
		getchar();
		cout << "Enter Book Title: "; getline(cin, btitleInput, '\n');
		cout << "Enter Book Category(1. Fiction  2. Non-Fiction): "; cin >> option1;
		if (option1 == '1') {
			categoryInput = category1;
			cout << "Enter Book genre: ";
			cout << "1. Fantasy   2. Science   3. Historical  4. Realistic  5. Fan\nEnter one option:  ";
			cin >> option2;
			if (option2 == '1') {
				genreInput = genre1;
			}
			else if (option2 == '2') {
				genreInput = genre2;
			}
			else if (option2 == '3') {
				genreInput = genre3;
			}
			else if (option2 == '4') {
				genreInput = genre4;
			}
			else {
				genreInput = genre5;
			}
		}
		else {
			categoryInput = category2;
			cout << "Enter Book genre: ";
			cout << "1. Fantasy   2. Science   3. Historical  4. Realistic  5. Fan\nEnter one option:  ";
			cin >> option2;
			if (option2 == '1') {
				genreInput = genre6;
			}
			else if (option2 == '2') {
				genreInput = genre7;
			}
			else if (option2 == '3') {
				genreInput = genre8;
			}
			else if (option2 == '4') {
				genreInput = genre9;
			}
			else {
				genreInput = genre10;
			}
		}
		availabilityInput = true;
		cout << "Enter the position you want to save the recode: "; cin >> position;
		InsertArbitraryb(bIDInput, btitleInput, categoryInput, genreInput, availabilityInput, position);
		place2++;
	}
	return;
}

/*add patron account*/
void AddPatron()
{
	cout << "\nPlease fill up the following requirements: \n" << endl;
	cout << "Enter Patron ID: "; cin >> PIDInput;
	if (SearchP(PIDInput, Head) == true) {
		cout << "\n This ID has been used before !!\n" << endl;
	}
	else
	{
		getchar();
		cout << "Enter Patron Name: "; getline(cin, PNameInput, '\n');
		cout << "Enter Phone No: "; getline(cin, PhoneInput, '\n');
		cout << "Enter the position you want to save the recode: "; cin >> position;
		InsertArbitraryp(PIDInput, PNameInput, PhoneInput, position);
		place++;
	}
	return;
}

/*login page*/
void Login() {
	string pin;
	cout << "\n       <=======>  Library Management System(LMS) <=======>\n";
	cout << "\nEnter Password PIN To Access: "; cin >> pin;
	if (pin == "1234") {
		cout << "\n  <>  Correct PIN <> \n";
		system("pause");
		system("cls");
	}
	else {
		cout << "\n  <> Wrong PIN <>\n";
		Login();
	}
}

/*the main function of the system */
int main() {
	string sbtitle;
	string bookid, borrowid;
	Login();
	system("color 2");/*changing the color to green*/

	do{
		cerr << "\n\n       <=======>  Library Management System <=======>\n"
			"  1. Book Services       2. Patrons Services     3. Exit"<<endl;
		cout << "Enter one choice: "; cin >> choice;
		switch (choice){
		case '1':
			do{
				cerr << "\n\n       <=======>  Book Service  <=======>\n"
					"  1. Add New Book    2. Display Books   3. Search Book\n  4. Update Book Information    5. Back" << endl;
				cout << "Enter one choice: "; cin >> choice;
				switch (choice)
				{
				case '1':
					AddBook();
					break;
				case '2':
					cout << "\n1. Display all books.     2. Display the avaiable books only. \nEnter one option: "; cin >> choice;
					if (choice == '1') {
						DisplayBook(Head2);
					}
					else {
						DisplayBookA(Head2);
					}
					cout << "\nDo you want to borrow any book: (1. Yes  2. NO): "; cin >> choice;
					if (choice == '1') {

						cout << "Enter Book ID: "; cin >> borrowid;
						borrowBook(borrowid, Head2);
					}
					else {
						cout << "\n Backing to the main menu....\n" << endl;
					}
					break;
				case '3':
					getchar();
					cout << "\nEnter the book title or category or genre to search: "; getline(cin, sbtitle, '\n');
					SearchBook(sbtitle, Head2);
					cout << "\nDo you want to borrow any book: (1. Yes  2. NO): "; cin>> choice;
					if (choice == '1') {
						
						cout << "Enter Book ID: "; cin >> borrowid;
						borrowBook(borrowid, Head2);
					}
					else {
						cout << "\n Backing to the main menu....\n" << endl;
					}
					break;
				case '4':
					cout << "\nEnter Book ID to update: "; cin >> bookid;
					UpdateBook(bookid, Head2);
					break;
				case '5':
					cout << "\n Backing to the main menu....\n" << endl;
					break;
				default:
					cerr << "\n\n <!!!>    Wrong Choice   <!!!>" << endl;
					break;
				}
				system("pause");
				system("cls");
			} while (choice != '5');
			break;
		case '2':
			do
			{
				cerr << "\n\n       <=======>  Patrons Service  <=======>\n"
					"  1. Add New Patron    2. Display the last 10 books borrowed by a patron\n"
					"  3. Search Patron     4. Update Patron Info       5. Return a Borrowed book\n"
					"  6. View all patrons with active book borrowed.   7. Back" << endl;
				cout << "Enter one choice: "; cin >> choice;
				switch (choice)
				{
				case '1':
					AddPatron();
					break;
				case '2':
					PLastBorrowedB(Head);
					break;
				case '3':
					SearchPRecord(Head);
					break;
				case '4':
					UpdatePInfo();
					break;
				case '5':
					returnbook();
					break;
				case '6':
					DisplayPatrons(Head);
					break;
				case '7':
					cout << "\n Backing to the main menu....\n" << endl;
					break;
				default:
					cerr << " <!!!>    Wrong Choice   <!!!>" << endl;
					break;
				}
				system("pause");
				system("cls");
			} while (choice != '7');
			break;
		case '3':
			cout <<"\n <***>  See You Soon ! :)    <***>\n"<<endl;
			break;
		default:
			cerr << "\n\n <!!!>    Wrong Choice   <!!!>"<<endl;
			break;
		}
		system("pause");/*pause the screen until the user press a key*/
		system("cls");/*clean the old displayed menu*/
	} while (choice != '3');
	return 0;
}
