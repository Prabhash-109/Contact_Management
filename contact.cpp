#include<iostream>
#include<conio.h>
#include<fstream>
using namespace std;
class contact{
    private:
    char fName[50],lName[50],address[50],email[50];
    long long phone_no;
    public:
    void createContact(){
        cout<<"Enter First Name: ";
        cin>>fName;

        cout<<"Enter Last Name: ";
        cin>>lName;

        cout<<"Enter Phone Number: ";
        cin>>phone_no;

        cout<<"Enter Address: ";
        cin>>address;

        cout<<"Enter Email: ";
        cin>>email;

        
    }

    void showContact(){
        cout<<"Name: "<<fName<<" "<<lName<<endl;
        cout<<"Phone: "<<phone_no<<endl;
        cout<<"Address: "<<address<<endl;
        cout<<"Email: "<<email<<endl;
    }
    void writeContact(){
        char ch;
        ofstream file1;
        file1.open("contact.dat",ios::binary|ios::app);
        do{
            createContact();
            file1.write(reinterpret_cast<char*>(this),sizeof(*this));
            cout<<"Do you want to add another contact? (y/n): ";
            cin>>ch;
        }while(ch=='y'||ch=='Y');
        cout<<"Contact Saved Successfully.......!"<<endl;
        file1.close();
    }
    void readFromFile(){
        ifstream file2;
        file2.open("contact.dat",ios::binary);
        
        cout<<"\n====================================\n";
        cout<<"Contact List\n";
        cout<<"\n====================================\n";
        while(!file2.eof()){
            if(file2.read(reinterpret_cast<char*>(this),sizeof(*this))){
                showContact();
                cout<<"\n====================================\n";
            }
            
        }
        file2.close();

    }
    void searchContact(){
        ifstream file3;
        long long phone;
        cout<<"Enter Phone Number to search......: ";
        cin>>phone;

        file3.open("contact.dat",ios::binary);
        while(!file3.eof()){
            if(file3.read(reinterpret_cast<char*>(this),sizeof(*this))){
                if(phone==phone_no){
                    showContact();
                    return;
                }
            }
        }
        cout<<"\n\nContact Not Found......!"<<endl;
        file3.close();
    }
    void deleteContact(){
        ofstream file4;
        ifstream file5;
        long long phone;
        int flag=0;
       
        file5.open("contact.dat",ios::binary);
        file4.open("temp.dat",ios::binary);
        cout<<"Enter Phone Number to delete: ";
        cin>>phone;
        while(!file5.eof()){
            if(file5.read(reinterpret_cast<char*>(this),sizeof(*this))){
                if(phone!=phone_no){
                    file4.write(reinterpret_cast<char*>(this),sizeof(*this));
                }
                else flag=1;
            }
        }
        file5.close();
        file4.close();
        remove("contact.dat");
        rename("temp.dat","contact.dat");
        flag==1?cout<<"\n\nContact Deleted Successfully....!"<<endl: cout<<"\n\nContact Not Found.....!"<<endl;
    }
    void editContact(){
        long long phone;
        fstream file6;

        cout<<"Edit Contact\n";
        cout<<"\n====================================\n";
        cout<<"Enter Phone Number to edit..: ";
        cin>>phone;
        file6.open("contact.dat",ios::in|ios::out|ios::binary);
        while(!file6.eof()){
            if(file6.read(reinterpret_cast<char*>(this),sizeof(*this))){
                if(phone==phone_no){
                    showContact();
                    cout<<"\n====================================\n";
                    cout<<"Enter New Details\n";
                    createContact();
                    int pos=-1*sizeof(*this);
                    file6.seekp(pos,ios::cur);
                    file6.write(reinterpret_cast<char*>(this),sizeof(*this));
                    cout<<"\n\nContact Updated Successfully........!"<<endl;
                    return;
                }
            }
        }
        cout<<"\n\nContact Not Found......!"<<endl;
        file6.close();
    }


};
int main(){
    system("cls");
    system("Color 37"); // Change Background and Text Color 3(blue) is for Background and F(white) is for Text
    cout<<"\n\n\n\n\n\n\t WELCOME TO The  CONTACT MANAGEMENT SYSTEM\n";
    getch();
    while(1){
        contact c1;
        int choice;

        system("cls");
        system("Color 03");
        cout<<"\nCONTACT MANAGEMENT SYSTEM\n";
        cout<<"\n\nMAIN MENU\n";
        cout<<"\n================================================\n";
        cout<<"[1] Add a new Contact\n";
        cout<<"[2] List all Contacts\n";
        cout<<"[3] Search for Contact\n";
        cout<<"[4] Delete a Contact\n";
        cout<<"[5] Edit a Contact\n";
        cout<<"[0]EXIT";
        cout<<"\n================================================\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice){
            case 1:
                system("cls");
                c1.writeContact();
                break;
            case 2:
                system("cls");
                c1.readFromFile();
                break;
            case 3:
                system("cls");
                c1.searchContact();
                break;
            case 4:
                system("cls");
                c1.deleteContact();
                break;
            case 5:
                system("cls");
                c1.editContact();
                break;
            case 0:
                system("cls");
                cout<<"Thank You for using the Contact Management System\n";
                exit(0);
                break;
            default:
            continue;
        }
        int opt;
        cout<<"\n\n..::Enter the Choice:\n[1] Main Menu\t\t[0] Exit\n";
        cin>>opt;
        switch(opt){
            case 0:
                system("cls");
                cout<<"Thank You for using the Contact Management System\n";
                exit(0);
                break;
            default:
                continue;
        }
    }
    return 0;
}