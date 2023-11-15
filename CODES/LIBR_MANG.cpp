// LIBRARY BOOKS MANAGEMENT SYSTEM USING OOP’S C++
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>
#include <windows.h>
using namespace std;
// ***********************student class***********************************************
class Student
{
protected:
    char std_usn[12];
    char std_name[30];
    char gender;
    unsigned long long int phone_num;
    unsigned int num_book_issued;

public:
    Student();
    void Read_stud_data();
    void Disp_stud_data();
    void Disp_stud_in_row();

    void Store_Student_Details();
    int Remove_Student_Details(char *usn, char *name);
    void Veiw_All_Student_Details();
    int Seacher_Student(char *usn, int x);
    int Update_Student_Details(char *usn, char *name, int x);
};

Student::Student()
{
    strcpy(std_usn, "");
    strcpy(std_name, "STUDENT_NAME");
    gender = '-';
    phone_num = 0;
    num_book_issued = 0;
}

void Student::Read_stud_data()
{
    system("cls");
    cout << "\n\n\t\tENTER STUDENT DETAILS:";
    cout << "\n\t\tUSN      :";
    getchar();
    cin.getline(std_usn, 11);
    cout << "\t\tNAME     :";
    cin.getline(std_name, 29);
    cout << "\t\tGENDER   :";
    cin >> gender;
    cout << "\t\tPHONE No.:";
    cin >> phone_num;
}

void Student::Disp_stud_data()
{
    system("cls");
    cout << "\n\n\t\tSTUDENT DETAILS:";
    cout << "\n\tSTUDENT USN      :" << std_usn;
    cout << "\n\tSTUDENT NAME     :" << std_name;
    cout << "\n\tSTUDENT GENDER   :" << gender;
    cout << "\n\tSTUDENT PHONE No.:" << phone_num;
}

void Student::Disp_stud_in_row()
{
    cout << "\n\tSTUDENT ID:" << std_usn << "\tNAME :" << std_name << "\tNUMBER OF BOOK ISSUED :" << num_book_issued;
}

void Student::Store_Student_Details()
{
    if (!(strcmp(std_usn, "")))
    {
        cout << "\n\n\tstudent is data not stored";
    }
    else
    {
        ofstream fout;
        fout.open("Students_Details.dat", ios::app | ios::binary);
        fout.write((char *)this, sizeof(*this));
        fout.close();
    }
}

int Student::Remove_Student_Details(char *usn, char *name)
{
    int x = 0, y = 0;
    ifstream fin;
    ofstream fout;
    fin.open("Students_Details.dat", ios::in | ios::binary);
    if (!fin)
        cout << "\n file is not found ";
    else
    {
        fout.open("TempStudents_Details.dat", ios::out | ios::binary);
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            x++;
            if ((strcmp(usn, std_usn)) && (strcmp(name, std_name)))
            {
                fout.write((char *)this, sizeof(*this));
                y++;
            }
            fin.read((char *)this, sizeof(*this));
        }
        fin.close();
        fout.close();
        remove("Students_Details.dat");
        rename("TempStudents_Details.dat", "Students_Details.dat");
    }
    return (x - y);
}

void Student::Veiw_All_Student_Details()
{
    ifstream fin;
    fin.open("Students_Details.dat", ios::in | ios::binary);
    if (!fin)
    {
        cout << "\nfile is not opened ";
    }
    else
    {
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            Disp_stud_in_row();
            fin.read((char *)this, sizeof(*this));
        }
        fin.close();
    }
}

int Student::Seacher_Student(char *usn, int x)
{
    int Cunt = 0;
    ifstream fin;
    fin.open("Students_Details.dat", ios::in | ios::binary);
    if (!fin)
        cout << "file is not found ";
    else
    {
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            if (!strcmp(usn, std_usn))
            {
                if (x == 1)
                {
                    Disp_stud_in_row();
                    Cunt++;
                }
                else if (x == 2)
                {
                    Disp_stud_data();
                    Cunt++;
                }
            }
            fin.read((char *)this, sizeof(*this));
        }
        if (Cunt == 0)
            cout << "\n RECORD NOT FOUND IN THIS USN " << usn << endl;
        fin.close();
    }
    return 0;
}

int Student::Update_Student_Details(char *usn, char *name, int x)
{
    int a = 0, b = 0;
    fstream file;
    file.open("Books_Details.dat", ios::in | ios::out | ios::ate | ios::binary);
    file.seekg(0);
    file.read((char *)this, sizeof(*this));
    while (!file.eof())
    {
        if (x == 1)
        {
            a++;
            if ((!strcmp(usn, std_usn)) && (!strcmp(name, std_name)))
            {
                b++;

                Read_stud_data();
                file.seekp(-sizeof(*this), ios::cur);
                file.write((char *)this, sizeof(*this));
            }
        }
        file.read((char *)this, sizeof(*this));
    }
    file.close();
    return (b);
}

// ******************book class****************************************

class Books
{
protected:
    unsigned int book_id;
    char book_name[30];
    char book_authr[30];
    unsigned int rack_no;
    unsigned int stock;

public:
    Books();
    void Read_book_data();
    void Disp_book_data();
    void Disp_book_in_row();
    void Disp_book_name();

    void Store_Book_Details();
    void Veiw_All_Book_Details();
    void Seacher_Book(char *ttl, unsigned int ID, int x);
    int Remove_Book(char *ttl, unsigned int ID);
    int Update_Book_Details(char *ttl, unsigned int ID, int x);
};

Books::Books()
{
    book_id = 0;
    strcpy(book_name, "NAME_BOOK");
    strcpy(book_authr, "NAME_AUTHOR");
    rack_no = 0;
    stock = 0;
}

void Books::Read_book_data()
{
    system("cls");
    cout << "\n\n\t\tENTER BOOK DETAILS:";
    cout << "\n\t\tID          :";
    cin >> book_id;
    cout << "\t\tNAME        :";
    getchar();
    cin.getline(book_name, 29);
    cout << "\t\tNAME_AUTHOR:";
    // getchar();
    cin.getline(book_authr, 29);
    cout << "\t\tRACK NUMBER :";
    cin >> rack_no;
    cout << "\t\tSTOCK       :";
    cin >> stock;
}

void Books::Disp_book_data()
{
    system("cls");
    cout << "\n\n\t\tBOOK DETAILS:";
    cout << "\n\tBOOK ID          :" << book_id;
    cout << "\n\tBOOK NAME        :" << book_name;
    cout << "\n\tBOOK NAME AUTHOR:" << book_authr;
    cout << "\n\tBOOK RACK NUMBER :" << rack_no;
    cout << "\n\tBOOK STOCK       :" << stock;
}
void Books::Disp_book_in_row()
{

    cout << "\n\tBOOK ID :" << book_id << "\tNAME  :" << book_name << "\tAUTHOR " << book_authr;
}
void Books::Disp_book_name()
{
    cout << book_name;
}

void Books::Store_Book_Details()
{
    if (book_id == 0)
    {
        cout << "\n\n\tbook is data not stored";
    }
    else
    {
        ofstream fout;
        fout.open("Books_Details.dat", ios::app | ios::binary);
        fout.write((char *)this, sizeof(*this));
        fout.close();
    }
}
void Books::Veiw_All_Book_Details()
{
    ifstream fin;
    fin.open("Books_Details.dat", ios::in | ios::binary);
    if (!fin)
    {
        cout << "\nfile is not opened ";
    }
    else
    {
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            Disp_book_in_row();
            fin.read((char *)this, sizeof(*this));
        }
        fin.close();
    }
}

void Books::Seacher_Book(char *ttl, unsigned int ID, int x)
{
    int C = 0;
    ifstream fin;
    fin.open("Books_Details.dat", ios::in | ios::binary);
    if (!fin)
        cout << "file is not found ";
    else
    {
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            if ((!strcmp(ttl, book_name)) || (ID == book_id))
            {
                if (x == 1)
                {
                    Disp_book_data();
                    C++;
                }
                else if (x == 2)
                {
                    Disp_book_name();
                }
            }
            fin.read((char *)this, sizeof(*this));
        }
        if ((x == 1) && (C == 0))
            cout << "\n Record not found in the name " << *ttl << endl;
        fin.close();
    }
}
int Books::Remove_Book(char *ttl, unsigned int ID)
{
    ifstream fin;
    ofstream fout;
    int x = 0, y = 0;
    fin.open("Books_Details.dat", ios::in | ios::binary);
    if (!fin)
        cout << "\n file is not found ";
    else
    {
        fout.open("TempBooks_Details.dat", ios::out | ios::binary);
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            x++;
            if ((strcmp(book_name, ttl)) && (ID != book_id))
            {
                fout.write((char *)this, sizeof(*this));
                y++;
            }
            fin.read((char *)this, sizeof(*this));
        }
        fin.close();
        fout.close();
        remove("Books_Details.dat");
        rename("TempBooks_Details.dat", "Books_Details.dat");
    }
    return (x - y);
}
int Books::Update_Book_Details(char *ttl, unsigned int ID, int x)
{
    int a = 0, b = 0;
    fstream file;
    file.open("Books_Details.dat", ios::in | ios::out | ios::ate | ios::binary);
    file.seekg(0);
    file.read((char *)this, sizeof(*this));
    while (!file.eof())
    {
        if (x == 1)
        {
            a++;
            if (!(strcmp(ttl, book_name)) && (ID == book_id))
            {
                b++;
                Read_book_data();
                file.seekp(-sizeof(*this), ios::cur);
                file.write((char *)this, sizeof(*this));
            }
        }
        file.read((char *)this, sizeof(*this));
    }

    file.close();
    return (b);
}

//**************************main menu*******************************************
void mainmenu()
{
    system("cls");
    system("Color 06");

    cout << "\n\t\tMAIN MENU\t\t\t";
    cout << "\n\t1.SEARCH BOOK";
    cout << "\n\t2.ADD,DELETE,UPDATE A BOOK";
    cout << "\n\t3.VIEW ALL BOOK DETATILS";
    cout << "\n\t4.SEARCH STUDENT DETATILS";
    cout << "\n\t5.REGISTER or DELIST A STUDENT"; // delist
    cout << "\n\t6.VIEW ALL STUDENT DETATILS";
    cout << "\n\t0.EXIT";
}

bool choice_op(int ip_ch)
{
    bool op_ch; // used to return back
    switch (ip_ch)
    {
    case (1):
    {
        system("Color 09");

        int chs = 0;
        unsigned int ID = 0;
        Books b;
        char Bk_Name[30];
        strcpy(Bk_Name, "");
        system("cls");
        cout << "\n\n\t\tSEARCH A BOOK BY:";
        cout << "\n\t\t1.BOOK NAME";
        cout << "\n\t\t2.BOOK ID";
        cout << "\n\n\t\tENTER YOUR CHOICE :";
        cin >> chs;
        if (chs == 1)
        {
            cout << "\n\n\t\tENTER NAME OF BOOK ";
            getchar();
            cin.getline(Bk_Name, 29);
            b.Seacher_Book(Bk_Name, ID, 1);
        }
        else if (chs == 2)
        {
            cout << "\n\n\t\tENTER ID OF BOOK ";
            cin >> ID;
            b.Seacher_Book(Bk_Name, ID, 1);
        }
        else
            cout << "\n\t\tERROR:WRONG INPUT";

        chs = 5;
        while (!(chs == 0))
        {
            cout << "\n\n\t\tENTER 0.EXIT : ";
            cin >> chs;
            if (chs == 0)
                return true;
            else
                cout << "\n\n\t\tERROR:WRONG INPUT ";
        }
        break;
    }
    case (2):
    {
        int chs = 0;
        Books b;
        system("cls");
        system("Color 04");
        cout << "\n\n\t\tADD,DELETE,UPDATE A BOOK:";
        cout << "\n\n\t\tPRESS";
        cout << "\n\t\t1.ADD BOOK";
        cout << "\n\t\t2.DELETE BOOK ";
        cout << "\n\t\t3.UPDATE BOOK ";
        cout << "\n\n\t\tENTER YOUR CHOICE :";
        cin >> chs;
        switch (chs)
        {
        case (1):
        {
            chs = 0;
            b.Read_book_data();
            b.Disp_book_data();
            cout << "\n\n\t\tENTER 1 TO SAVE DETAILS OR 0 SKIP : ";
            cin >> chs;
            if (chs == 1)
            {
                b.Store_Book_Details();
                cout << "\n\tBOOK DETAILS ARE SAVED SUCCESSFULLY";
            }
            else
                cout << "\n\n\t\tERROR:WRONG INPUT ";
        }
        break;
        case (2):
        {
            unsigned int ID;
            char Bk_Name[30];
            system("cls");
            cout << "\n\n\t\tDELETE A BOOK :";
            cout << "\n\n\tENTER NAME OF BOOK ";
            getchar();
            cin.getline(Bk_Name, 29);
            cout << "\n\tENTER ID OF BOOK ";
            cin >> ID;
            cout << "\n\n\t\tPRESS 1 CONFIRM OR 0 SKIP : ";
            cin >> chs;
            if (chs == 1)
            {
                if (b.Remove_Book(Bk_Name, ID))
                    cout << "\n\tBOOK RECORD IS DELETED SUCCESSFULLY";
                else
                    cout << "\n\tERROR:WRONG INPUT NO BOOK RECORD IS FOUND";
            }
            else
                cout << "\n\n\t\tERROR:WRONG INPUT ";
        }
        break;
        case (3):
        {
            unsigned int ID;
            char Bk_Name[30];
            system("cls");

            cout << "\n\n\t\tUPDATE A BOOK :";
            cout << "\n\n\tENTER NAME OF BOOK ";
            getchar();
            cin.getline(Bk_Name, 29);
            cout << "\n\n\tENTER ID OF BOOK ";
            cin >> ID;
            cout << "\n\n\t\tPRESS 1 CONFIRM OR 0 SKIP : ";
            cin >> chs;
            if (chs == 1)
            {
                if (b.Update_Book_Details(Bk_Name, ID, 1))
                    cout << "\n\tBOOK RECORD IS UPDATEDED SUCCESSFULLY";
                else
                    cout << "\n\tERROR:WRONG INPUT NO BOOK RECORD IS FOUND";
            }
            else
                cout << "\n\n\t\tERROR:WRONG INPUT ";
        }
        break;
        default:
            cout << "\n\t\tERROR:WRONG INPUT";
            break;
        }

        chs = 5;
        while (!(chs == 0))
        {
            cout << "\n\n\t\tENTER 0.EXIT : ";
            cin >> chs;
            if (chs == 0)
                return true;
            else
                cout << "\n\n\t\tERROR:WRONG INPUT ";
        }
        break;
    }
    case (3):
    {
        system("cls");
        system("Color 05");
        Books b;
        int chs = 5;
        cout << "\n\t\tALL BOOKS DETAILS";
        cout << "\n\tBOOK ID \t\tBOOK NAME  \t\tAUTHOR";
        b.Veiw_All_Book_Details();
        while (!(chs == 0))
        {
            cout << "\n\n\t\tENTER 0.EXIT : ";
            cin >> chs;
            if (chs == 0)
                return true;
            else
                cout << "\n\n\t\tERROR:WRONG INPUT ";
        }
        break;
    }
    case (4):
    {
        system("cls");
        system("Color 06");
        char usn[12], name[30];
        Student s;

        cout << "\n\n\t\tENTER STUDENT DETAILS TO SEARCH:";
        cout << "\n\t\tUSN      :";
        getchar();
        cin.getline(usn, 11);
        s.Seacher_Student(usn, 2);
        int chs = 5;
        while (!(chs == 0))
        {
            cout << "\n\n\t\tENTER 0.EXIT : ";
            cin >> chs;
            if (chs == 0)
                return true;
            else
                cout << "\n\n\t\tERROR:WRONG INPUT ";
        }
        break;
    }
    case (5):
    {
        Student s;
        int chs = 0;
        system("cls");
        system("Color 07");
        cout << "\n\n\t\t  SEARCH A BOOK BY:";
        cout << "\n\t\t1.REGISTER STUDENT";
        cout << "\n\t\t2.DEREGISTER STUDENT";
        cout << "\n\n\t\t  ENTER YOUR CHOICE :";
        cin >> chs;
        if (chs == 1)
        {
            s.Read_stud_data();
            s.Disp_stud_data();
            cout << "\n\n\t\t  PRESS 1 CONFIRM OR 0 SKIP : ";
            cin >> chs;
            if (chs == 1)
            {
                s.Store_Student_Details();
                cout << "\n\n\tSTUDENT DETAILS SAVED SUCCESSFULLY";
            }
        }
        else if (chs == 2)
        {
            char usn[12], name[30];
            cout << "\n\n\t\tENTER STUDENT DETAILS TO DERESGISTER:";
            cout << "\n\t\tUSN      :";
            getchar();
            cin.getline(usn, 11);
            cout << "\t\tNAME     :";
            cin.getline(name, 29);
            cout << "\n\n\t\tPRESS 1 CONFIRM OR 0 SKIP : ";
            cin >> chs;
            if (chs == 1)
            {
                if (s.Remove_Student_Details(usn, name))
                    cout << "\n\n\tSTUDENT RECORD IS DELETED SUCCESSFULLY";
                else
                    cout << "\n\n\tERROR:WRONG INPUT,STUDENT RECORD IS NOT FOUND";
            }
        }
        else
            cout << "\n\t\tERROR:WRONG INPUT";
        chs = 5;
        while (!(chs == 0))
        {
            cout << "\n\n\t\tENTER 0.EXIT : ";
            cin >> chs;
            if (chs == 0)
                return true;
            else
                cout << "\n\n\t\tERROR:WRONG INPUT ";
        }
        break;
    }
    case (6):
    {
        system("cls");
        system("Color 08");
        Student s;
        int chs = 5;
        cout << "\n\t\tALL STUDENT DETAILS";
        cout << "\n\t\tSTUDENT ID \t\tNAME\t\t  NUMBER OF BOOK ISSUED";
        s.Veiw_All_Student_Details();
        while (!(chs == 0))
        {
            cout << "\n\n\t\tENTER 0.EXIT : ";
            cin >> chs;
            if (chs == 0)
                return true;
            else
                cout << "\n\n\t\tERROR:WRONG INPUT ";
        }
        break;
    }
    case (0):
    {
        system("cls");
        system("Color 09");
        cout << "\n\n\n\n\t\tTHANK YOU\n\n\n\n";
        return false;
        break;
    }
    default:
    {
        cout << "\n\n\tERROR:ENTER CORRET CHOISE";
        Sleep(2000); // to make delay
        return true;
        break;
    }
    }
    return false;
}

int main()
{
    int ch;
    bool x = true;
    while (x == true)
    {
        mainmenu();
        cout << "\n\n\t  ENTER YOUR CHOICE :";
        cin >> ch;
        x = choice_op(ch);
        if (x == false)
        {
            exit;
        }
    }
}