#include <iostream>
#include <fstream>
#include <vector>

struct patient {
    int age;
    std::string name;
    std::string disease;
    int pid;
};
struct doctor {
    int did;
    std::string dname;
    std::string speacialization; // keeping your spelling
};

class patients {
private:
    std::vector<patient> pati;

public:
    void addpatient(int pid, int age, std::string name, std::string disease);
    void findpatient(int pid);
    void showpatients();
    void savepatients();
    void loadpatients();
};

void patients::addpatient(int pid, int age, std::string name, std::string disease) {
    patient p;
    p.age = age;
    p.name = name;
    p.pid = pid;
    p.disease = disease;
    pati.push_back(p);
    std::cout << "PATIENT ADDED SUCCESSFULLY\n";
};

void patients::findpatient(int pid) {
    for (auto &a : pati) {
        if (a.pid == pid) {
            std::cout << "ID " << a.pid;
            std::cout << "\nNAME " << a.name;
            std::cout << "\nDISEASE " << a.disease;
            std::cout << "\nAGE " << a.age << "\n";
        }
    }
};

void patients::showpatients() {
    for (auto &a : pati) {
        std::cout << "ID - " << a.pid << "  AGE - " << a.age << "  NAME - " << a.name << "  DISEASE - " << a.disease << "\n";
    }
};

void patients::savepatients() {
    std::ofstream fout("patients.txt");
    for (auto &a : pati) {
        fout << a.pid << " " << a.age << " " << a.name << "|" << a.disease << "\n"; 
        // delimiter "|" for safe spaces
    }
    fout.close();
}

void patients::loadpatients() {
    std::ifstream fin("patients.txt");
    patient p;
    std::string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        size_t firstSpace = line.find(" ");
        size_t secondSpace = line.find(" ", firstSpace + 1);
        size_t bar = line.find("|", secondSpace + 1);

        p.pid = stoi(line.substr(0, firstSpace));
        p.age = stoi(line.substr(firstSpace + 1, secondSpace - firstSpace - 1));
        p.name = line.substr(secondSpace + 1, bar - secondSpace - 1);
        p.disease = line.substr(bar + 1);

        pati.push_back(p);
    }
    fin.close();
}

class doctors {
private:
    std::vector<doctor> doct;

public:
    void adddoctor(int did, std::string name, std::string speacialization);
    void showdoctors();
    void finddoctor(int did);
    void savedoctors();
    void loaddoctors();
};

void doctors::adddoctor(int did, std::string dname, std::string speacialization) {
    doctor d;
    d.did = did;
    d.dname = dname;
    d.speacialization = speacialization;
    doct.push_back(d);
    std::cout << "\nNEW DOCTOR HIRED\n";
};

void doctors::showdoctors() {
    for (auto &a : doct) {
        std::cout << "ID - " << a.did << "  NAME - " << a.dname << "  SPEACIALIZATION " << a.speacialization << "\n";
    }
};

void doctors::finddoctor(int did) {
    for (auto &a : doct) {
        if (a.did == did) {
            std::cout << "ID " << a.did;
            std::cout << "\nNAME " << a.dname;
            std::cout << "\nSPEACIALIZATION " << a.speacialization << "\n";
        }
    }
};

void doctors::savedoctors() {
    std::ofstream fout("doctors.txt");
    for (auto &a : doct) {
        fout << a.did << " " << a.dname << "|" << a.speacialization << "\n"; 
    }
    fout.close();
}

void doctors::loaddoctors() {
    std::ifstream fin("doctors.txt");
    doctor d;
    std::string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        size_t firstSpace = line.find(" ");
        size_t bar = line.find("|", firstSpace + 1);

        d.did = stoi(line.substr(0, firstSpace));
        d.dname = line.substr(firstSpace + 1, bar - firstSpace - 1);
        d.speacialization = line.substr(bar + 1);

        doct.push_back(d);
    }
    fin.close();
}

struct appointment {
    int pid;
    int did;
    std::string date;
};

class appointments {
private:
    std::vector<appointment> app;

public:
    void addappointment(int pid, int did, std::string date);
    void showappointments();
    void saveappointments();
    void loadappointments();
};

void appointments::addappointment(int pid, int did, std::string date) {
    appointment a;
    a.pid = pid;
    a.did = did;
    a.date = date;
    app.push_back(a);
    std::cout << "APPOINTMENT BOOKED SUCCESSFULLY\n";
}

void appointments::showappointments() {
    for (auto &a : app) {
        std::cout << "PATIENT ID: " << a.pid << "  DOCTOR ID: " << a.did << "  DATE: " << a.date << "\n";
    }
}

void appointments::saveappointments() {
    std::ofstream fout("appointments.txt");
    for (auto &a : app) {
        fout << a.pid << " " << a.did << " " << a.date << "\n";
    }
    fout.close();
}

void appointments::loadappointments() {
    std::ifstream fin("appointments.txt");
    appointment a;
    while (fin >> a.pid >> a.did) {
        fin.ignore();
        getline(fin, a.date);
        app.push_back(a);
    }
    fin.close();
}

int main() {
    patients p1;
    doctors d1;
    appointments a1;

    p1.loadpatients();
    d1.loaddoctors();
    a1.loadappointments();

    int choice;
    int pc; // patient
    int ac;
    int pid;
    int age;
    std::string name;
    std::string disease;
    int dc; // doctor
    int did;
    std::string dname;
    std::string speacialization;
    std::string date;

    while (true) {
        std::cout << "\n-----WELCOME TO RAMGARHIA HOSPITAL-----\n";
        std::cout << "1.PATIENTS\n";
        std::cout << "2.DOCTORS\n";
        std::cout << "3.APPOINTMENTS\n";
        std::cout << "4.EXIT\n\n";
        std::cout << "INPUT DOMAIN:";
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1:
            std::cout << "1.ADD PATIENT\n";
            std::cout << "2.FIND PATIENT\n";
            std::cout << "3.SHOW PATIENTS ADDED\n";
            std::cout << "INPUT CHOICE:";
            std::cin >> pc;
            std::cin.ignore();
            switch (pc) {
            case 1:
                std::cout << "INPUT PATIENT ID: ";
                std::cin >> pid;
                std::cout << "INPUT AGE: ";
                std::cin >> age;
                std::cin.ignore();
                std::cout << "INPUT NAME: ";
                getline(std::cin, name);
                std::cout << "INPUT DISEASE: ";
                getline(std::cin, disease);
                p1.addpatient(pid, age, name, disease);
                p1.savepatients();
                break;
            case 2:
                std::cout << "INPUT PID: ";
                std::cin >> pid;
                p1.findpatient(pid);
                break;
            case 3:
                p1.showpatients();
                break;
            default:
                std::cout << "\nINVALID INPUT";
            }
            break;

        case 2:
            std::cout << "1.ADD DOCTOR\n";
            std::cout << "2.FIND DOCTOR\n";
            std::cout << "3.SHOW DOCTORS ADDED\n";
            std::cout << "INPUT CHOICE: ";
            std::cin >> dc;
            std::cin.ignore();
            switch (dc) {
            case 1:
                std::cout << "INPUT DOCTOR ID: ";
                std::cin >> did;
                std::cin.ignore();
                std::cout << "INPUT NAME: ";
                getline(std::cin, dname);
                std::cout << "INPUT SPEACIALIZATION: ";
                getline(std::cin, speacialization);
                d1.adddoctor(did, dname, speacialization);
                d1.savedoctors();
                break;
            case 2:
                std::cout << "INPUT ID: ";
                std::cin >> did;
                d1.finddoctor(did);
                break;
            case 3:
                d1.showdoctors();
                break;
            default:
                std::cout << "\nINVALID INPUT";
            }
            break;

        case 3:
            std::cout << "1.BOOK APPOINTMENT\n";
            std::cout << "2.SHOW APPOINTMENTS\n";
            std::cout << "INPUT CHOICE: ";
            std::cin >> ac;
            std::cin.ignore();
            switch (ac) {
            case 1:
                std::cout << "INPUT PATIENT ID: ";
                std::cin >> pid;
                std::cout << "INPUT DOCTOR ID: ";
                std::cin >> did;
                std::cin.ignore();
                std::cout << "INPUT DATE (e.g. 05 March 2025): ";
                getline(std::cin, date);
                a1.addappointment(pid, did, date);
                a1.saveappointments();
                break;
            case 2:
                a1.showappointments();
                break;
            default:
                std::cout << "\nINVALID INPUT";
            }
            break;

        case 4:
            std::cout << "SAVING & EXITING...\n";
            p1.savepatients();
            d1.savedoctors();
            a1.saveappointments();
            exit(0);

        default:
            std::cout << "INVALID CHOICE";
        }
    }

    return 0;
}
