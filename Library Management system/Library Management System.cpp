#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;


struct Book{ // user define datatype - Book is now datatype
   
   int bookID;
   string author;
   string title;
   string genre;
   string borrower;
   bool Availablity;

};

struct borrower{ // similarly borrower is a datatype.
    int bookID;
    string borrowername;
    string borrowerID;
    string duedate;
};

const int max_borrowers = 100;
const int max_books=100;
Book library[max_books];
borrower borrowers[max_borrowers];
int bookcount=0;
int borrowercount=0;


void loadbooksfromcsv(const string& filename){
    ifstream file(filename);
    if(file.is_open())
    {
        string line;
        while(getline(file,line)){
            stringstream ss(line);
            string item;
            int col=0;
            Book book;

            while(getline(ss,item,',')){
                item.erase(remove_if(item.begin(),item.end(), :: isspace),item.end()); //remove the spaces between the items for traversing properly.

                switch(col){
                    case 0 : book.bookID == stoi(item);
                    break;

                    case 1: book.author=item;
                    break;

                    case 2: book.title=item;
                    break;

                    case 3: book.genre=item;
                    break;

                    case 4: book.Availablity =(item=="true");
                    break;

                }
                col++;
            }
            library[bookcount]=book;
            bookcount++;
        }
        file.close();
    }
    else{
        cout<<"Unable to open the file : "<<filename<<endl;
    }
}

void appendbooktocsv(const Book& book,const string& filename){
    ofstream file(filename,ios::app); //ios :: app (input/output stream ,app - append) it is use to avoid overwriting, it will always put the data e=in the end.
    if(file.is_open()){
        file<<book.bookID << " , "
        <<book.author << " , "
        <<book.title << " , "
        <<book.genre << " , "
        <<(book.Availablity ? "true" : "false")<<"\n";
    
    file.close();
    }
    else{
        cout<<"unable to open the file  : "<<filename<<endl;
    }
}

void appendborrowertocsv(const borrower& b,const string& filename){
    ofstream file(filename,ios::app); //ios :: app (input/output stream ,app - append) it is use to avoid overwriting, it will always put the data e=in the end.
    if(file.is_open()){
        file<<b.bookID << " , "
        <<b.borrowername << " , "
        <<b.borrowerID << " , "
        <<b.duedate << "\n";
        
    file.close();
    }
    else{
        cout<<"unable to open the file  : "<<filename<<endl;
    }
}


void addbook(int bookID , string author , string title, string genre , bool Availablity){
   if (bookcount<max_books){
    library[bookcount].bookID=bookID; // first .bookID is the member of our "Book" structure and we are equating it with variable "bookID" which is declared in addbook function.
    library[bookcount].author=author;
    library[bookcount].title=title;
    library[bookcount].genre=genre;
    library[bookcount].Availablity=Availablity;
    cout<<" Book Added Successfully ! "<<endl;

    appendbooktocsv(library[bookcount],"library.csv"); // because bookcount has already been increamented thats why we use [bookcount - 1]
    bookcount++;
   }

   else{
    cout<<"Library is full , can not add more books "<<endl;
   }

}

void  deletebook(int bookID){
    bool found = false;

    for (int i = 0; i < bookcount; i++)
    {
        if(library[i].bookID==bookID){
            found = true;
      // shifting the books after the deleted book 
            for (int j = i; j < bookcount-1; j++) // "i" stores the bookID that has to be delete , "j" will itrerate upto (bookcount - 1)
            {
                library[j]=library[j+1]; //placing "j+1" position book to the "j" position
            }
            bookcount--;
            cout<<"Book deleted successfully ! "<<endl;

            ofstream file("library.csv");
            if(file.is_open()){
                for (int k = 0; k < bookcount; k++)
                {
                    file<<library[k].bookID<<" , "
                    <<library[k].author<<" , "
                    <<library[k].title<<" , "
                    <<library[k].genre<<" , "
                    <<(library[k].Availablity ? "true" : "false"  )<<"\n";
                }
                file.close();
                
            }
            else{
                cout<<"unable to open file :  Library.csv " << endl;
            }
            return;
        }
    }

    if(!found){
        cout<<"Book ID not found ! "<<endl;
    }    
}

void searchbook(int bookID){
    for(int i=0; i<bookcount;++i){
        if (library[i].bookID == bookID){
            cout<<"Book ID : "<<library[i].bookID<<endl;
            cout<<"Title : "<<library[i].title<<endl;
            cout<<"Author : "<<library[i].author<<endl;
            cout<<"genre : "<<library[i].genre<<endl;
            cout << "Availability: ";
               if (library[i].Availablity == true) {

                   cout << "Available";
             } 
             else {
                cout << "Not Available";
              }          
              cout<<endl;
              return;
        }
        
    }
    cout<<"Book ID not found ! "<<endl;
}

// UPDATE BOOK INFORMATION

void updateinfo(int bookID,string newtitle,string newauthor,string newgenre,bool newavailablity){
    for(int i =0;i<bookcount; ++i){
        if(library[i].bookID==bookID){
            library[i].author=newauthor;
            library[i].title=newtitle;
            library[i].genre=newgenre;
            library[i].Availablity=newavailablity;
            cout<<"Book information updates successfully !"<<endl;
            
            ofstream file("library.csv");
            if(file.is_open()){
                for (int k = 0; k < bookcount; k++)
                {
                    file<<library[k].bookID<<" , "
                    <<library[k].author<<" , "
                    <<library[k].title<<" , "
                    <<library[k].genre<<" , "
                    <<(library[k].Availablity ? "true" : "false"  )<<"\n";
                }
                file.close();
                
            }
            else{
                cout<<"unable to open file :  Library.csv " << endl;
            }
            return;
        }
        
    }
    cout<<"Book ID not found ! "<<endl;
}

// LIST ALL THE BOOKS

void listbooks(){
    for (int i = 0; i < bookcount; i++)
    {
        cout<<"Book ID : "<<library[i].bookID<<endl;
        cout<<"Author : "<<library[i].author<<endl;
        cout<<"Title : "<<library[i].title<<endl;
        cout<<"Genre : "<<library[i].genre<<endl;
        cout << "Availability: ";
               if (library[i].Availablity) {

                   cout << "Available";
             } 
             else {
                cout << "Not Available  \n";
              }       

         cout<<"__________________________: "<<endl;

           
         }
    
}

void addbookintractive(){
    int bookID;
    string author,title,genre;
    char availibilitychar;
    bool availability;

    cout<< " Enter book ID : ";
    cin>>bookID;
    cin.ignore();

    cout<<"Enter Author : ";
    getline(cin,author);

    cout<<"Enter Title : ";
    getline(cin,title);

    cout<<"Enter Genre : ";
    getline(cin,genre);

    cout<<"Is the book available? (y/n) : ";
    cin>>availibilitychar;
    availability=(availibilitychar=='y' || availibilitychar =='Y');

    addbook(bookID, author,title,genre,availability);
}

void managermenu(){
    char choice;
    do{
        cout<< "\n Manager Menu  \n";
        cout<<endl;
        cout<<"1. Add book \n";
        cout<<"2. Delete book \n";
        cout<<"3. Update book information \n";
        cout<<"4. List all the books \n";
        cout<<"5. Exit \n";
        cout<<" Enter your choice :  \n";
        cin>>choice;

        switch(choice){
            case '1' :{
                addbookintractive();
                break;
            }
            case '2' :{
                int bookID;
                cout<<"Enter book ID to delete : ";
                cin>>bookID;
                deletebook(bookID);
                break;}

            case '3' :{
                int bookID;
                string newtitle,newauthor,newgenre;
                char availablitychar;
                bool newavailablity;

                cout<<"Enter book ID to update : ";
                cin>>bookID;
                cin.ignore();

                cout<<"Enter new author : ";
                getline(cin,newauthor);

                cout<<"Enter new Title : ";
                getline(cin,newtitle);

                cout<<"Enter new genre : ";
                getline(cin,newgenre);

                cout<<"Is book avaialable> ( y / n) : ";
                cin>>availablitychar;
                newavailablity=(availablitychar=='y' || availablitychar=='Y');

                updateinfo(bookID,newauthor,newtitle,newgenre,newavailablity);
                break;
                }

            case '4' :{
                listbooks();
                break;
                }

            case '5':{
                cout<<"Exiting the manager menu. \n";
                break;
                }

            default:{
                cout<<"Invalid choice. Please try again. \n";
                }
        }
    }

    while(choice!='5');
}

void borrowbookintractive(){
    int bookID;
    string borrowername;
    string UID;
    string duedate;

    cout<<"Enter Book ID to borrow : ";
    cin>>bookID;

    bool bookfound=false;

    for (int i = 0; i < bookcount; i++)
    {
        if(library[i].bookID==bookID){
            bookfound= true;

            if(library[i].Availablity==true){
                cout<<"Enter your name : ";
                cin.ignore();
                getline(cin,borrowername);

                cout<<"Enter your UID : ";
                getline(cin,UID);

                cout<<"Enter Due Date (yyyy-mm-dd) : ";
                getline(cin,duedate);

                //borrower record
                library[i].Availablity=false; //updated book is not available now. 
                borrowers[borrowercount].bookID=bookID;
                borrowers[borrowercount].borrowername=borrowername;
                borrowers[borrowercount].borrowerID=UID;
                borrowers[borrowercount].duedate=duedate;

                appendborrowertocsv(borrowers[borrowercount],"borrowers.csv");
                borrowercount++;

                cout<<"Book '"<<library[i].title<<"'hasbeen borrowed by "<< borrowername<<". \n";

            }
            else{
                cout<<"Sorry, the book is currently not available. \n";
            }
            return;
        }
    }
    if(!bookfound){
        cout<<"Book ID not found! \n";
    }
    
}

void studentmenu(){
    char choice;

    do{
        cout<< "\n student Menu  \n";
        cout<<endl;
        cout<<"1. Search book \n";
        cout<<"2. Borrow book \n";
        cout<<"3. Exit \n";
        cout<<"Enter your choice :  \n";
        cin>>choice;

        switch(choice){
            case '1' : {
                int bookID;
                cout<<"Enter book ID to search : ";
                cin>>bookID;
                searchbook(bookID);
                break;
            }

            case '2' : {
                borrowbookintractive();
                return;
            }

            case '3' : {
                cout<<"Exiting the student menu. \n";
                break;
            }

            default:{
                cout<<"invalid choice.  Please try again later. \n";
            }
        }
    }
    while(choice!='3');
}

int main(){

        loadbooksfromcsv("library.csv");

        char choice;

        while(true){
            cout<< "Welcome to the Library Management System \n";
            cout<<"Are you a Student or Manager ? (s/m) : ";
            cin>>choice;

            if(choice=='s' || choice=='S'){
                studentmenu();
            }

            else if (choice=='m'||choice=='M'){
                managermenu();
            }
            else{
                cout<<"Invalid choice. Please try again. \n";
            }
        }
   return 0;

}