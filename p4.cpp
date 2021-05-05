#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
class Person { // The person's personal information
    public:
    string firstName;
    string lastName;
    string iD;
    string city;
    string state;
    string zCode;
    string email;
    string pNum;
    Person* nextPerson;
    Person() {
        nextPerson = nullptr;
    }
};

class Key{ // the specific key being checked for like Id or State
    public:
    Person* head;
    int numPeople;
    string value;
    Key* nextKey;
    Key() {
        head =nullptr;
        nextKey = nullptr;
    }
};

class HashBucket { // individual bucket
    public:
    Key* headKey;
    HashBucket() {
        headKey = nullptr;
    }
};
class HashTable { // the whole table
    public:
    HashBucket* table;
    HashTable() {
        table = nullptr;
    }
};

unsigned long djb2(string str) {
    const char *ptr = str.c_str();
    unsigned long hash = 5381;
    int c;
    while ((c = *ptr++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

void getVal(istream &is, string &str) {
    char ch;
    string line;

    is >> ch;
    getline(is, line);

    str = ch + line;
}

bool isValidKey(const string &key) {
    string validKeys[8] = { "Id", "FirstName", "LastName", "Email", "Phone", "City", "State", "PostalCode" };
    for (int i = 0; i < 8; i++) {
        if (key == validKeys[i]) {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        cout << "Usage: ./a.out filename.txt table_size key" << endl;
        return 1;
    }

    string filename = argv[1];
    int tableSize = stoi(argv[2]);
    string key = argv[3];
    
    ifstream file(filename);
    if (!file) {
        cout << "Unable to open " << filename << endl;
        return 2;
    }

    if (!isValidKey(key)) {
        cout << "Invalid key: " << key << endl;
        return 3;
    }
    
    
    // This is an example of how to retreive the tokens from the input file
    // You will need to modify this to fit your needs to build the hash table
    string line, token;
    HashTable* hash = new HashTable;
    hash -> table = new HashBucket[tableSize];
    int id;
    int firstName;
    int lastName;
    int mail;
    int city;
    int state;
    int pCode;
    int phone;
    int index;
    int count = 0;

        getline(file, line);
        istringstream iss(line);
        while (getline(iss, token, '\t')) {
            if (token == "Id") {
                id = count;
                if (token == key) {
                    index = count;
                }
            }
            else if (token == "FirstName") {
                firstName = count;
                if (token == key) {
                    index = count;
                }
            }
            else if (token == "LastName") {
                lastName = count;
                if (token == key) {
                    index = count;
                }
            }
            else if (token == "Email") {
                mail = count;
                if (token == key) {
                    index = count;
                }
            }
            else if (token == "Phone") {
                phone = count;
                if (token == key) {
                    index = count;
                }
            }
            else if (token == "City") {
                city = count;
                if (token == key) {
                    index = count;
                }
            }
            else if (token == "State") {
                state = count;
                if (token == key) {
                    index = count;
                }
            }
            else if (token == "PostalCode") {
                pCode = count;
                if (token == key) {
                    index = count;
                }
            }
            count++;
        }
        count = 0;
        string value;
        unsigned long hashnum;
        while (getline(file, line)) {
            Person* p1 = new Person;
            count = 0;
            istringstream nss(line);
            while (getline(nss, token, '\t')) {
                if (count == id){
                    p1 -> iD = token;
                }
                else if (count == firstName) {
                    p1 -> firstName = token;
                }
                else if (count == lastName) {
                    p1 -> lastName = token;
                }
                else if (count == mail) {
                    p1 -> email = token;
                }
                else if (count == phone) {
                    p1 -> pNum = token;
                }
                else if (count == city) {
                    p1->city = token;
                }
                else if (count == state) {
                    p1 -> state = token;
                }
                else if (count == pCode) {
                    p1-> zCode = token;
                }
                if (index == count) {
                    value = token;
                    hashnum = djb2(value);
                } 
                count++;
            }
            int hkey = hashnum % tableSize;
            if (hash->table[hkey].headKey == nullptr) {
                Key* k1 = new Key;
                k1 -> head = p1;
                k1 ->nextKey = nullptr;
                k1 -> numPeople = 1;
                k1 -> value = value;
                hash -> table[hkey].headKey = k1;
            }
            else {
                Key* cur = hash -> table[hkey].headKey;
                bool keyChecker = true;
                
                while (cur != nullptr) {
                    if (cur -> value.compare(value) == 0) {
                        Person* newP = cur -> head;
                        while (newP -> nextPerson != nullptr) {
                            newP = newP -> nextPerson;
                        }
                        newP -> nextPerson = p1;
                        cur -> numPeople += 1;
                        keyChecker = false;
                    }
                    cur = cur -> nextKey;
                }
                if (keyChecker == true) {
                    Key* newKey = new Key;
                    cur = hash -> table[hkey].headKey;
                    newKey -> head = p1; 
                    newKey -> numPeople = 1;
                    newKey -> value = value;
                    while (cur -> nextKey != nullptr) {
                        cur = cur -> nextKey;
                    }
                    cur -> nextKey = newKey;
                    newKey -> nextKey = nullptr;
                }
            }
        }

    cout << "Commands:" << endl << "\tprint" << endl << "\tlookup <key>" << endl << "\tquit" << endl;
    string cmd, val;
    while (1) {
        cout << endl << "Enter a command:" << endl;
        cin >> cmd;
        if (cmd == "quit") {
            break;
        }
        else if (cmd == "print") {
            for (int i = 0; i < tableSize; i++) {
                if (hash->table[i].headKey != nullptr) {
                    Key* temp = hash->table[i].headKey;
                    cout << i << ": ";
                    while (temp != nullptr) {
                        cout << temp -> value << " (" << temp -> numPeople << "),";
                        temp = temp -> nextKey;
                    }
                    cout << endl;
                }
            }
        }
        else if (cmd == "lookup") {
            getVal(cin, val);
            unsigned long hashnum = djb2(val);
            int hkey = hashnum % tableSize;
            if (hash->table[hkey].headKey == nullptr) {
                cout << "No results" << endl;
            }
            else {
                Key* temp = hash -> table[hkey].headKey;
                Person* dude = temp -> head;
                    
                while (temp -> value != val) {
                    if (temp -> nextKey == nullptr) {
                        cout << "No results" << endl;
                        break;
                    }
                    temp = temp -> nextKey;  
                } 
                
                dude = temp -> head;
                if (temp -> value.compare(val) == 0) {
                    cout << "Id,FirstName,LastName,Email,Phone,City,State,PostalCode" << endl;
                    while (dude != nullptr) {
                        cout << dude -> iD << "," << dude -> firstName << "," << dude -> lastName << "," << dude -> email << "," << dude -> pNum << "," << dude -> city << "," << dude -> state << "," << dude -> zCode << endl;
                        dude = dude -> nextPerson;
                    }
                }
            }
        }
        else {
            getline(cin, val);
            cout << "Invalid command" << endl;
        }
    }

    return 0;
}
