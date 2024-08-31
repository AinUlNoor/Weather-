#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Contact 
{
private:
    string name;
    string phone;
public:
    Contact(string n, string p) : name(n), phone(p) {}
    string getName() const
	 {
        return name;
    }
    string getPhone() const
	 {
        return phone;
    }
    void display() const 
	{
        cout<<"Name: " << name <<endl ;
		cout<<"Phone: " << phone << endl;
    }
    void saveToFile(ofstream &file) const 
	{
        file << name << endl;
        file << phone << endl;
    }
    static bool loadFromFile(ifstream &file, Contact &contact) 
	{
        string name, phone;
        if (getline(file, name) && getline(file, phone)) 
		{
            contact = Contact(name, phone);
            return true;
        }
        return false;
    }
   };
class ContactManager
 {
private:
    const string fileName = "contacts.txt";
public:
    void addContact(const string& name, const string& phone) 
	{
        ofstream file(fileName, ios::app);
        if (!file.is_open()) 
		{
            cout << "\t\t\tError opening file.\n";
            return;
        }
        Contact newContact(name, phone);
        newContact.saveToFile(file);
        cout << "\t\t\tContact added successfully.\n";
        file.close();
    }
    void viewContacts() const
	 {
        ifstream file(fileName);
        if (!file.is_open()) 
		{
            cout << "No contacts available.\n";
            return;
        }
        Contact contact("", "");
        int count = 0;
        while (Contact::loadFromFile(file, contact)) 
		{
            cout << ++count << ". ";
            contact.display();
        }

        if (count == 0)
            cout << "\t\t\tNo contacts available.\n";

        file.close();
    }
    void deleteContact(const string& name)
	 {
        ifstream file(fileName);
        ofstream tempFile("temp.txt");

        if (!file.is_open() || !tempFile.is_open()) 
		{
            cout << "\t\t\tError opening file.\n";
            return;
        }

        Contact contact("", "");
        bool found = false;
        while (Contact::loadFromFile(file, contact)) 
		{
            if (contact.getName() != name) 
			{
                contact.saveToFile(tempFile);  // Write contact to temp file if it's not the one to delete
            } else {
                found = true;
            }
        }

        file.close();
        tempFile.close();

        if (found) 
		{
            remove(fileName.c_str());
            rename("temp.txt", fileName.c_str());
            cout << "\t\t\tContact deleted successfully.\n";
        }
		 else
		  {
            remove("temp.txt");
            cout << "\t\t\tContact not found.\n";
        }
    }
};
void displayMenu(ContactManager& manager) 
{
    int choice;
    string name, phone;
    do
	 {
	 	cout<<"\n\n\t\t\t*******************************"<<endl;
        cout << "\t\t\tContact Management System\n";
        cout << "\t\t\t1. Add Contact\n";
        cout << "\t\t\t2. View Contacts\n";
        cout << "\t\t\t3. Delete Contact\n";
        cout << "\t\t\t4. Exit\n";
        cout<<"\t\t\t*******************************"<<endl;
        cout << "\n\t\t\tEnter your choice: ";
        cin >> choice;
        switch (choice)
		 {
            case 1:
                cout << "\n\t\t\tEnter Name: ";
                cin.ignore(); 
                getline(cin, name);
                cout << "\t\t\tEnter Phone Number: ";
                getline(cin, phone);
                manager.addContact(name, phone);
                break;
            case 2:
                manager.viewContacts();
                break;
            case 3:
                cout << "\t\t\tEnter Name of Contact to Delete: ";
                cin.ignore();
                getline(cin, name);
                manager.deleteContact(name);
                break;
            case 4:
                cout << "\t\t\tExiting the program.\n";
                break;
            default:
                cout << "\t\t\tInvalid choice. Please try again.\n";
                break;
        }
    } while (choice != 4);
}
int main()
 {
    ContactManager manager;
    displayMenu(manager);
    return 0;
}
