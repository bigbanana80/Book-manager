#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <process.h>
#include <string.h>
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include "Header.h"
using namespace std;
class book
{
	char bno[6];
	char bname[50];
	char aname[20];
public:
	void create_book()
	{
		cout << "new book entry\n";
		cout << "Enter the book No:";
		cin >> bno;
		cout << "\nEnter the name of the book:";
		cin >> bname;
		cout << "\nEnter the author's name:";
		cin >> aname;
		cout << "Book created";
	}
	void show_book()
	{
		cout << "Book no. :" << bno;
		cout << "\nBook's name:" << bname;
		cout << "\nBook's author:" << aname;
	}
	void modify_book()
	{

		cout << "\nBook no. : " << bno;
		cout << "\nModify Book Name : ";
		cin >> bname;
		cout << "\nModify Author's Name of Book : ";
		cin >> aname;
	}
	char* retbno()
	{
		return bno;
	}

	void report()
	{
		cout << bno << setw(30) << bname << setw(30) << aname << endl;
	}
};
class student
{
	char admno[6];
	char stuname[20];
	char stbno[6];
	int token;
public:
	void create_student()
	{
		system("CLS");
		cout << "New student entry...\n";
		cout << "Enter the admission no.:";
		cin >> admno;
		cout << "\nEnter student's name:";
		cin >> stuname;
		token = 0;
		stbno[0] = '0';
		cout << "student record created...";
	}
	void show_student()
	{
		cout << "Admission no.:" << admno;
		cout << "\nStudent's name:" << stuname;
		cout << "\nNo of book issued:" << token;
		if (token == 1)
			cout << "Book no.:" << stbno;
	}
	void modify_student()
	{
		cout << "Admission no.:" << admno;
		cout << "Modify student's name:";
		cin >> stuname;
	}
	char* retadmno()
	{
		return admno;
	}
	char* retstbno()
	{
		return stbno;
	}
	char* retstuname()
	{
		return stuname;
	}
	int rettoken()
	{
		return token;
	}
	void add_token()
	{
		token = 1;
	}
	void reset_token()
	{
		token = 0;
	}
	void get_stbno(char t[])
	{
		strcpy_s(stbno, t);///////////Copies the C string pointed by source into the array pointed by destination, including the terminating null character (and stopping at that point).

	}
	void report()
	{
		cout << "\t" << admno << setw(20) << stuname << setw(10) << token << endl;
	}
};
///////////////global objects////////////////////
fstream fp, fp1;
book bk;
student st;
/////////////////////////////////////////////////
void write_book()
{
	char ch;
	fp.open("book.dat", ios::out | ios::app);
	do {
		system("CLS");
		bk.create_book();
		fp.write((char*)&bk, sizeof(book));
		cout << "\n\nDo you want to add more record..(y/n?)";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	fp.close();
}

///////////////////////////////////////////////////////////////////////////////

void write_student()
{
	char ch;
	fp.open("student.dat", ios::out | ios::app);
	do {
		st.create_student();
		fp.write((char*)&st, sizeof(student));
		cout << "\n\ndo you want to add more record..(y/n?)";
		cin >> ch;
	} while (ch == 'y' || ch == 'Y');
	fp.close();
}

///////////////////////////////////////////////////////////////////////////////_strcmpi(,)==Compare Strings Without Case Sensitivity

void display_spb(char n[])
{
	cout << "\nBook details\n";
	int flag = 0;
	fp.open("book.dat", ios::in);
	while (fp.read((char*)&bk, sizeof(book)))
	{
		if (_strcmpi(bk.retbno(), n) == 0)
		{
			bk.show_book();
			flag = 1;
		}
	}
	fp.close();
	if (flag == 0)
		cout << "this book does not exist";
	_getch();
}

///////////////////////////////////////////////////////////////////////////////

void display_sps(char n[])
{
	cout << "\nSTUDENT DETAILS\n";
	int flag = 0;
	fp.open("student.dat", ios::in);
	while (fp.read((char*)&st, sizeof(student)))
	{
		if ((_strcmpi(st.retadmno(), n) == 0))
		{
			st.show_student();
			flag = 1;
		}
	}

	fp.close();
	if (flag == 0)
		cout << "\n\nStudent does not exist";
	_getch();
}

///////////////////////////////////////////////////////////////////////////////////

void modify_book()
{
	char n[6];
	int flag = 0;
	system("CLS");
	cout << "\n\n\tMODIFY BOOK REOCORD.... ";
	cout << "\n\n\tEnter The book no. of The book";
	cin >> n;
	fp.open("book.dat", ios::in | ios::out);
	while (fp.read((char*)&bk, sizeof(book)) && flag == 0)
	{
		if (_strcmpi(bk.retbno(), n) == 0)
		{
			bk.show_book();
			cout << "\nEnter The New Details of book" << endl;
			bk.modify_book();
		    int pos = (unsigned)-1 * sizeof(bk);
			fp.seekp(pos, ios::cur);
			fp.write((char*)&bk, sizeof(book));
			cout << "\n\n\t Record Updated";
			flag = 1;
		}
	}

	fp.close();
	if (flag == 0)
		cout << "\n\n Record Not Found ";
	_getch();
}

//////////////////////////////////////////////////////////////////////////////////

void modify_student()
{
	char n[6];
	int flag=0;
	system("CLS");
	cout << "\n\n\tMODIFY STUDENT RECORD... ";
	cout << "\n\n\tEnter The admission no. of The student";
	cin >> n;
	fp.open("student.dat", ios::in | ios::out);
	while (fp.read((char*)&st, sizeof(student)) && flag == 0)
	{
		if (_strcmpi(st.retadmno(), n) == 0)
		{
			st.show_student();
			cout << "\nEnter The New Details of student" << endl;
			st.modify_student();
			int pos = (unsigned)-1 * sizeof(st);
			fp.seekp(pos, ios::cur);
			fp.write((char*)&st, sizeof(student));
			cout << "\n\n\t Record Updated";
			flag = 1;
		}
	}
	fp.close();
	if(flag ==0)
		cout << "\n\n Record Not Found ";
	_getch();
}

//////////////////////////////////////////////////////////////////////////////////////////////////

void delete_student()
{
	char n[6];
	int flag = 0;
	system("CLS");
	cout << "\n\n\n\tDELETE STUDENT...";
	cout << "\n\nEnter The admission no. of the Student You Want To Delete : ";
	cin >> n;
	fp.open("student.dat", ios::in | ios::out);
	fstream fp2;
	fp2.open("temp.dat", ios::out);
	fp.seekg(0, ios::beg);/////////////////////////////ios_base::beg=====beginning of the stream
	while (fp.read((char*)&st, sizeof(student)));
	{
		if (_strcmpi(st.retadmno(), n) != 0)
			fp2.write((char*)&st, sizeof(student));
		else
			flag = 1;
	}
	fp2.close();
	fp.close();
	remove("student.dat");/////////////////////////// The remove() function takes a single argument filename and returns an integer value. It deletes the file pointed by the parameter.
	rename("temp.dat", "student.dat");//////////////rename(oldname,newname)--->Changes the name of the file or directory specified by oldname to newname.
	if (flag == 1)
		cout << "\n\nrecord deleted...";
	else
		cout << "record not found..";
	_getch();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void delete_book()
{
	char n[6];
	system("CLS");
	cout << "\n\n\n\tDELETE BOOK ...";
	cout << "\n\nEnter The Book no. of the Book You Want To Delete : ";
	cin >> n;
	fp.open("book.dat", ios::in | ios::out);
	fstream fp2;
	fp2.open("Temp.dat", ios::out);
	fp.seekg(0, ios::beg);
	while (fp.read((char*)&bk, sizeof(book)))
	{
		if (_strcmpi(bk.retbno(), n) != 0)
		{
			fp2.write((char*)&bk, sizeof(book));
		}
	}

	fp2.close();
	fp.close();
	remove("book.dat");
	rename("Temp.dat", "book.dat");
	cout << "\n\n\tRecord Deleted ..";
	_getch();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////!s==>s==0

void display_alls()
{
	system("CLS");
	fp.open("student.dat", ios::in);
	if (!fp)
	{
		cout << "ERROR!!! FILE COULD NOT BE OPEN ";
		_getch();
		return;
	}
	cout << "\n\n\t\tSTUDENT LIST\n\n";
	cout << "==================================================================\n";
	cout << "\tAdmission No." << setw(10) << "Name" << setw(20) << "Book Issued\n";
	cout << "==================================================================\n";
	while (fp.read((char*)&st, sizeof(student)))
	{
		st.report();
	}
	fp.close();
	_getch();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void display_allb()
{
	system("CLS");
	fp.open("book.dat", ios::in);
	if (!fp)
	{
		cout << "ERROR!!! FILE COULD NOT BE OPEN ";
	    _getch();
		return;
	}

	cout << "\n\n\t\tBook LIST\n\n";
	cout << "=========================================================================\n";
	cout << "Book Number" << setw(20) << "Book Name" << setw(25) << "Author\n";
	cout << "=========================================================================\n";

	while (fp.read((char*)&bk, sizeof(book)))
	{
		bk.report();
	}
	fp.close();
	_getch();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////&&==r-value reference==the simple explanation is that it doesn't have a memory address

void book_issue()
{
	char sn[6], bn[6];
	int found = 0, flag = 0;
	system("CLS");
	cout << "\n\nBOOK ISSUE ...";
	cout << "\n\n\tEnter The student's admission no.";
	cin >> sn;
	fp.open("student.dat", ios::in | ios::out);
	fp1.open("book.dat", ios::in | ios::out);
	while (fp.read((char*)&st, sizeof(student)) && found == 0)
	{
		if (_strcmpi(st.retadmno(), sn) == 0)
		{
			found = 1;
			if (st.rettoken() == 0)
			{
				cout << "\n\n\tEnter the book no. ";
				cin >> bn;
				while (fp1.read((char*)&bk, sizeof(book)) && flag == 0);
				{
					if (_strcmpi(bk.retbno(), bn) == 0)
					{
						flag = 1;
						st.add_token();
						st.get_stbno(bk.retbno());
						int pos = (unsigned)-1 * sizeof(st);
						fp.seekp(pos, ios::cur);
						fp.write((char*)&st, sizeof(student));
						cout << "\n\n\t Book issued successfully\n\nPlease Note: Write current date in backside of book and submit within 15 days fine Rs. 1 for each day after 15 days period";
					}
				}
				if (flag == 0)
					cout << "Book no does not exist";
			}
			else
				cout << "you have not returned the last book";
		}
	}
	if (found == 0)
		cout << "student record not exist...";
	_getch();
	fp.close();
	fp1.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////#########################

void book_deposit()
{
	char sn[6], bn[6];
	int found = 0, flag = 0, day, fine;
	system("CLS");
	cout << "\n\nBOOK DEPOSIT ...";
	cout << "\n\n\tEnter The student's admission no.";
	cin >> sn;
	fp.open("student.dat", ios::in | ios::out);
	fp1.open("book.dat", ios::in | ios::out);
	while (fp.read((char*)&st, sizeof(student)) && found == 0)
	{
		if (_strcmpi(st.retadmno(), sn) == 0)
		{
			found = 1;
			if (st.rettoken() == 1)
			{
				while (fp1.read((char*)&bk, sizeof(book)) && flag == 0)
				{
					if (_strcmpi(bk.retbno(), st.retstbno()) == 0)
					{
						bk.show_book();
						flag = 1;
						cout << "\n\nBook deposited in no. of days";
						cin >> day;
						if (day > 15)
						{
							fine = (day - 15) * 1;
							cout << "\n\nFine has to deposited Rs. " << fine;
						}
						st.reset_token();
						int pos =(unsigned)-1 * sizeof(st);
						fp.seekp(pos, ios::cur);
						fp.write((char*)&st, sizeof(student));
						cout << "\n\n\t Book deposited successfully";
					}
				}
				if (flag == 0)
					cout << "Book no does not exist";
			}
			else
				cout << "No book is issued..please check!!";
		}
	}
	if (found == 0)
		cout << "Student record not exist...";
	_getch();
	fp.close();
	fp1.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////######################

void intro()
{
	system("CLS");
	cout << "LIBRARY";	
	cout << "\nMANAGEMENT";	
	cout << "\nSYSTEM";
	cout << "\n\nMADE BY : Sepehr Aghajani";
	_getch();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////#######################

void admin_menu()
{
	system("CLS");
	int ch2;
	cout << "\n\n\n\tADMINISTRATOR MENU";
	cout << "\n\n\t1.CREATE STUDENT RECORD";
	cout << "\n\n\t2.DISPLAY ALL STUDENTS RECORD";
	cout << "\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
	cout << "\n\n\t4.MODIFY STUDENT RECORD";
	cout << "\n\n\t5.DELETE STUDENT RECORD";
	cout << "\n\n\t6.CREATE BOOK ";
	cout << "\n\n\t7.DISPLAY ALL BOOKS ";
	cout << "\n\n\t8.DISPLAY SPECIFIC BOOK ";
	cout << "\n\n\t9.MODIFY BOOK ";
	cout << "\n\n\t10.DELETE BOOK ";
	cout << "\n\n\t11.BACK TO MAIN MENU";
	cout << "\n\n\tPlease Enter Your Choice (1-11) ";
	cin >> ch2;
	switch (ch2)
	{
	case 1: system("CLS");
		write_student(); break;
	case 2: display_alls(); break;
	case 3:
		char num[6];
		system("CLS");
		cout << "\n\n\tPlease Enter The Admission No. ";
		cin >> num;
		display_sps(num);
		break;
	case 4: modify_student(); break;
	case 5: delete_student(); break;
	case 6: system("CLS");
		write_book(); break;
	case 7: display_allb(); break;
	case 8: {
		char num[6];
		system("CLS");
		cout << "\n\n\tPlease Enter The book No. ";
		cin >> num;
		display_spb(num);
		break;
	}
	case 9: modify_book(); break;
	case 10: delete_book(); break;
	case 11: return;
	default:cout << "\a";
	}
	admin_menu();
}


int main() 
{
	char ch;
	intro();
	do
	{
		system("CLS");
		cout << "\n\n\n\tMAIN MENU";
		cout << "\n\n\t01. BOOK ISSUE";
		cout << "\n\n\t02. BOOK DEPOSIT";
		cout << "\n\n\t03. ADMINISTRATOR MENU";
		cout << "\n\n\t04. EXIT";
		cout << "\n\n\tPlease Select Your Option (1-4) ";
		ch = _getche();
		switch (ch)
		{
		case '1':system("CLS");
			book_issue();
			break;
		case '2':book_deposit();
			break;
		case '3':admin_menu();
			break;
		case '4':exit(0);
		default:cout << "\a";
		}
	} while (ch != '4');
}