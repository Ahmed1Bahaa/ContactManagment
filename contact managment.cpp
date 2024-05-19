#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Contact {
private:
    string Name;
    string PhoneNo;
    string Address;
    string Email;
public:
    Contact() {
        Name = "";
        PhoneNo = "";
        Address = "";
        Email = "";
    }
    Contact(string n, string num, string a, string e) {
        Name = n;
        PhoneNo = num;
        Address = a;
        Email = e;
    }

    void SetName(string n) {
        Name = n;
    }

    void SetPhoneNo(string num) {
        PhoneNo = num;
    }

    void SetAddress(string a) {
        Address = a;
    }

    void SetEmail(string e) {
        Email = e;
    }

    string getName() const {
        return Name;
    }

    string getPhoneNo() const {
        return PhoneNo;
    }

    string getAddress() const {
        return Address;
    }

    string getEmail() const {
        return Email;
    }
};

class FileManager {
public:
     void WriteToFile(const Contact contact) {
        ofstream file("contacts.txt", ios::app);
        file << contact.getName() << " , " << contact.getPhoneNo() << " , " << contact.getAddress() << " , " << contact.getEmail() << endl;
        file.close();
    }

     void ReadFromFile() {
        ifstream file("contacts.txt");
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
};

class ContactManager {
public:
    FileManager fileManager;

    void AddContact() {
        string name, phone, email, address;
        cout << "Enter your name: ";
        cin >> name;
        cout << "Enter your phone number: ";
        cin >> phone;
        cout << "Enter your email: ";
        cin >> email;
        cout << "Enter your address: ";
        cin >> address;
        Contact contact(name, phone, email, address);
        fileManager.WriteToFile(contact);
    }

    void ListContacts() {
        fileManager.ReadFromFile();
    }
    void SearchContactsByName(string name)
    {
        ifstream file("contacts.txt");
        string line;
        while (file >> line) {
            if (line.find(name) != string::npos) {
                cout << line << endl;
            }
        }
        file.close();
    }
    void SearchContactsByPhoneNumber(string phoneNumber)
    {
        ifstream file("contacts.txt");
        string line;
        while (getline(file, line)) {
            if (line.find(phoneNumber) != string::npos) {
                cout << line << endl;
            }
        }
        file.close();
    }
    void EditContact(string name)
    {
        
            ifstream file("contacts.txt");
            ofstream tempFile("temp.txt");
            string line;
            while (getline(file, line)) {
                if (line.find(name) != string::npos) {
                    
                    string newName, newPhone, newEmail, newAddress;
                    cout << "Enter new name: ";
                    cin >> newName;
                    cout << "Enter new phone number: ";
                    cin >> newPhone;
                    cout << "Enter new email: ";
                    cin >> newEmail;
                    cout << "Enter new address: ";
                    cin >> newAddress;
                    line = newName + " , " + newPhone + " , " + newAddress + " , " + newEmail;
                }
                tempFile << line << endl;
            }
            file.close();
            tempFile.close();
            remove("contacts.txt");
            rename("temp.txt", "contacts.txt");
        

    }
    void DeleteContact(string name) {
        ifstream file("contacts.txt");
        ofstream tempFile("temp.txt");
        string line;
        while (getline(file, line)) {
            if (line.find(name) == string::npos) {
                tempFile << line << endl;
            }
        }
        file.close();
        tempFile.close();
        remove("contacts.txt");
        rename("temp.txt", "contacts.txt");

    }
};
class UserInterface {
public:
    void Displaymenu()
    {
        cout << "Contact Managment System Menu " << endl;
        cout << "1. Add Contact " << endl;
        cout << "2. List Contacts " << endl;
        cout << "3. Search Contacts by Name " << endl;
        cout << "4. Search Contacts by Number " << endl;
        cout << "5. Edit Contact " << endl;
        cout << "6. Delete Contact " << endl;
        cout << "7. Exit" << endl;
    }
    int GetuserInput()
    {
        int choice;
        cout << "Enter your choice : ";
        cin >> choice;
        return choice;
    }
};

int main() {
    int choice;
    UserInterface ui;
    ContactManager cm;
    FileManager fileManager;
    do {


        ui.Displaymenu();
        choice = ui.GetuserInput();
        switch (choice) {
        case 1:
            cm.AddContact();
            break;
        case 2:
            cm.ListContacts();
            break;
        case 3:
        {
            string name;
            cout << "Enter a name to search for : ";
            cin >> name;
            cm.SearchContactsByName(name);
        }
        break;
        case 4:
        {
            string number;
            cout << "Enter a number to search for : ";
            cin >> number;
            cm.SearchContactsByPhoneNumber(number);
        }
        break;
        case 5:
        {
            string name;
            cout << "Enter the name of the contact to edit: ";
            cin >> name;
            cm.EditContact(name);
        }
        break;
        case 6:
        {
            string name;
            cout << "Enter the name of the contact to delete: ";
            cin >> name;
            cm.DeleteContact(name);
        }
        break;
        case 7:
            cout << "Goodbye!";
            break;
        }
    }
    while (choice != 7);
    return 0;
}
