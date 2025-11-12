#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <stdio>
#include <limits>
using namespace std;

// ====================== Khai bao ======================

struct Customer {
    string name, gender, cccd, accountNumber, date;
    int age, months;
    double deposit, interestRate;
    Customer* next;
};

struct Staff {
    string name, gender, cccd, position;
    int age;
    Staff* next;
};

struct Account {
    string username, password, role;
    Account* next;
};

struct Date { int d, m, y; };

// ====================== HÀM NGÀY THÁNG ======================

Date parseDate(string s) {
    Date dt;
    int numbers[3];
    int idx = 0, num = 0;

    for (int i = 0; i <= s.size(); i++) {
        if (i == s.size() || s[i] == '/') {
            numbers[idx++] = num;
            num = 0;
        } else {
            num = num * 10 + (s[i] - '0');
        }
    }

    dt.d = numbers[0];
    dt.m = numbers[1];
    dt.y = numbers[2];
    return dt;
}

int monthsBetween(Date start, Date end) {
    int m = (end.y - start.y) * 12 + (end.m - start.m);
    if (end.d < start.d) m--;
    if (m < 0) m = 0;
    return m;
}

// ====================== CUSTOMER ======================

Customer* makeCustomer(string name,string gender,int age,string cccd,string acc,
                       double dep,double rate,int mon,string date) {
    Customer* c = new Customer();
    c->name = name;
    c->gender = gender;
    c->age = age;
    c->cccd = cccd;
    c->accountNumber = acc;
    c->deposit = dep;
    c->interestRate = rate;
    c->months = mon;
    c->date = date;
    c->next = NULL;
    return c;
}

double computeTotalReceive(double p, double rate, int m) {
    double r = (rate / 100.0) / 12.0;
    return p * pow(1 + r, m);
} 

void pushBackCustomer(Customer* &head, Customer* node) {
    if (head == NULL) {
        head = node;
        return;
    }
    Customer* t = head;
    while (t->next != NULL)
        t = t->next;
    t->next = node;
}

Customer* findCustomerByAccount(Customer* h, const string &acc) {
    while (h != NULL) {
        if (h->accountNumber == acc) return h;
        h = h->next;
    }
    return NULL;
}

void listCustomers(Customer* h, bool admin) {
    if (h == NULL) {
        cout << "Danh sach khach hang rong!\n";
        return;
    }
    cout << left << setw(20) << "Ten" << setw(8) << "Gioi" << setw(6) << "Tuoi"
         << setw(15) << "CCCD" << setw(15) << "SoTK" << setw(12) << "TienGui"
         << setw(8) << "Lai%" << setw(8) << "Thang" << setw(12) << "NgayGui"
         << setw(15) << "TongNhan\n";
         cout << string(120,'-') << "\n";

    double total = 0, lai = 0;
    while (h != NULL) {
        double tong = computeTotalReceive(h->deposit,h->interestRate,h->months);
        total += h->deposit;
        lai += (tong - h->deposit);

        cout << left << setw(20) << h->name
             << setw(8) << h->gender
             << setw(6) << h->age
             << setw(15) << h->cccd
             << setw(15) << h->accountNumber
             << setw(12) << fixed << setprecision(2) << h->deposit
             << setw(8) << h->interestRate
             << setw(8) << h->months
             << setw(12) << h->date
             << setw(15) << tong << "\n";
        h = h->next;
    }
    if (admin) {
        cout << "\nTong tien gui: " << total;
        cout << "\nTong lai: " << lai << "\n";
    }
}

void deleteCustomersByName(Customer* &head, const string &name) {
    while (head != NULL && head->name == name) {
        Customer* t = head;
        head = head->next;
        delete t;
    }
    Customer* cur = head;
    while (cur != NULL && cur->next != NULL) {
        if (cur->next->name == name) {
            Customer* t = cur->next;
            cur->next = t->next;
            delete t;
        } else cur = cur->next;
    }
}
void sortCustomersByName(Customer* &head){
    if (head == NULL || head->next == NULL) return;

    for (Customer* i = head; i->next != NULL; i = i->next){
        for (Customer* j = i->next; j != NULL; j = j->next){
            if (i->name > j->name){
                swap(i->name, j->name);
                swap(i->gender, j->gender);
                swap(i->age, j->age);
                swap(i->cccd, j->cccd);
                swap(i->accountNumber, j->accountNumber);
                swap(i->deposit, j->deposit);
                swap(i->interestRate, j->interestRate);
                swap(i->months, j->months);
                swap(i->date, j->date);
            }
        }
    }
}

Customer* inputNewCustomerInteractive(){
    string n, g, cccd, acc, date;
    double dep, rate;
    int mon, age;

    cin.ignore();   
    cout << "Ten: ";
    getline(cin, n);
    cout << "Gioi tinh: ";
    getline(cin, g);
    cout << "Tuoi: ";
    cin >> age;

    if (age < 16){
        cout << "Khong the tao khach hang duoi 16 tuoi.\n";
        return NULL;
    }
    cin.ignore();  
    cout << "CCCD: ";
    getline(cin, cccd);
    cout << "So tai khoan: ";
    getline(cin, acc);
    cout << "So tien gui: ";
    cin >> dep;
    cout << "Lai suat % nam: ";
    cin >> rate;
    cout << "Ky han (thang): ";
    cin >> mon;
    cin.ignore(); 
    cout << "Ngay gui (dd/mm/yyyy): ";
    getline(cin, date);

    return makeCustomer(n, g, age, cccd, acc, dep, rate, mon, date);
}

// ====================== STAFF ======================

Staff* makeStaff(string n,string g,int a,string cccd,string p){
    Staff* s = new Staff();
    s->name=n;
    s->gender=g;
    s->age=a;
    s->cccd=cccd;
    s->position=p;
    s->next = NULL;
    return s;
}

void pushBackStaff(Staff* &head, Staff* node) {
    if (head == NULL) { 
        head = node; 
        return; 
    }
    Staff* t = head;
    while (t->next != NULL)
    t = t->next;
    t->next = node;
}

void listStaffs(Staff* head){
    if (head == NULL) {
        cout << "Danh sach nhan vien rong!\n";
        return;
    }

    cout << left << setw(20) << "Ten" << setw(8) << "Gioi" << setw(6) << "Tuoi"
         << setw(16) << "CCCD" << setw(20) << "Vi tri\n";
         cout << string(80,'-') << "\n";

    Staff* cur = head;
    while (cur != NULL){
        cout << left << setw(20) << cur->name
             << setw(8) << cur->gender
             << setw(6) << cur->age
             << setw(16) << cur->cccd
             << setw(20) << cur->position << "\n";
        cur = cur->next;
    }
}

void deleteStaffByName(Staff* &head, const string &name){
    while (head != NULL && head->name == name){
        Staff* t = head;
        head = head->next;
        delete t;
    }
    Staff* cur = head;
    while (cur != NULL && cur->next != NULL){
        if (cur->next->name == name){
            Staff* t = cur->next;
            cur->next = t->next;
            delete t;
        } else
        cur = cur->next;
    }
}

Staff* inputNewStaffInteractive(){
    string n,g,cccd,pos;
    int age;

    cin.ignore(); 
    cout << "Ten: ";
    getline(cin,n);
    cout << "Gioi tinh: ";
    getline(cin,g);
    cout << "Tuoi: ";
    cin >> age;

    if (age < 18){
        cout << "Khong the tao nhan vien duoi 18 tuoi.\n";
        return NULL;
    }

    cin.ignore(); 
    cout << "CCCD: ";
    getline(cin,cccd);
    cout << "Vi tri lam viec: ";
    getline(cin,pos);

    return makeStaff(n,g,age,cccd,pos);
}

// ====================== ACCOUNT ======================

void pushBackAccount(Account* &head, string u, string p, string r){
    Account* a = new Account();
    a->username=u;
    a->password=p;
    a->role=r;
    a->next = NULL;
    if (head == NULL) {
        head = a;
        return;
        }
    Account* t=head;
    while(t->next != NULL)
    t=t->next;
    t->next = a;
}

Account* findAccount(Account* head, string u, string p){
    while (head != NULL){
        if (head->username == u && head->password == p)
        return head;
        head = head->next;
    }
    return NULL;
}

// ====================== chức năng ======================

void depositToCustomer(Customer* c){
    double x;
    cout << "Nhap so tien nap: ";
    cin >> x;
    if (x <= 0){
        cout << "So tien khong hop le!\n";
        return;
        }
    c->deposit += x;
    cout << "Nap thanh cong! So du moi: " << c->deposit << endl;
}

void withdrawFromCustomer(Customer* c){
    string wd;
    cout << "Nhap ngay rut (dd/mm/yyyy): ";

    cin.ignore();          
    getline(cin, wd);

    Date start = parseDate(c->date);
    Date end   = parseDate(wd);
    int m = monthsBetween(start, end);

    double rate = c->interestRate;
    if (m < c->months){
        cout << "Rut truoc han -> Lai con 20%\n";
        rate *= 0.2;
    }
    double total = computeTotalReceive(c->deposit, rate, m);
    cout << "Tong tien co the nhan: " << total << "\n";

    double x;
    cout << "Nhap so tien muon rut: ";
    cin >> x;

    if (x > total){
        cout << "Khong du tien!\n";
        return;
    }

    c->deposit = total - x;
    cout << "Rut thanh cong. So du con lai: " << c->deposit << "\n";
}


// ====================== MAIN ======================

int main(){
    Customer* customers = NULL;
    Staff* staffs = NULL;
    Account* accounts = NULL;

    // Tài khoản mặc định
    pushBackAccount(accounts, "admin", "123", "quanly");
    pushBackAccount(accounts, "staff", "123", "nhanvien");
    pushBackAccount(accounts, "user", "123", "khach");

    cout << "=== HE THONG QUAN LY TIET KIEM (DSLK Don) ===\n";

    while (true) {
        cout << "\n--- DANG NHAP ---\nUsername: ";
        string username; 
        cin >> username;
        if (username == "exit") break;

        cout << "Password: ";
        string password; 
        cin >> password;

        Account* acc = findAccount(accounts, username, password);

        if (acc == NULL) {
            cout << "Sai username / password.\n";
            continue;
        }

        cout << "Dang nhap voi vai tro: " << acc->role << "\n";

        // ================== QUAN LY ==================
        if (acc->role == "quanly") {
            while (true) {
                cout << "\n--- MENU QUAN LY ---\n"
                     << "1. Tao danh sach khach hang\n"
                     << "2. Them khach hang\n"
                     << "3. Xem danh sach khach hang + thong ke\n"
                     << "4. Sap xep khach hang theo ten\n"
                     << "5. Xoa khach hang theo ten\n"
                     << "6. Tao danh sach nhan vien\n"
                     << "7. Them nhan vien\n"
                     << "8. Xem danh sach nhan vien\n"
                     << "9. Xoa nhan vien theo ten\n"
                     << "10. Dang xuat\n"
                     << "0. Thoat\n"
                     << "Chon: ";

                int c; cin >> c;
                switch(c) {
                    case 1: {
                        int n; cout << "So khach hang: "; cin >> n;
                        for(int i=0;i<n;i++){
                            Customer* k = inputNewCustomerInteractive();
                            if(k != NULL)
                            pushBackCustomer(customers,k);
                        }
                        break;
                    }
                    case 2: {
                        Customer* k = inputNewCustomerInteractive();
                        if(k != NULL)
                        pushBackCustomer(customers,k);
                        break;
                    }
                    case 3:
                        listCustomers(customers,true);
                        break;
                    case 4:
                        sortCustomersByName(customers);
                        cout << "Da sap xep.\n";
                        break;
                    case 5: {
                        cin.ignore();
                        cout << "Nhap ten can xoa: ";
                        string x; getline(cin,x);
                        deleteCustomersByName(customers,x);
                        break;
                    }
                    case 6: {
                        int n; cout << "So nhan vien: "; cin >> n;
                        for(int i=0;i<n;i++){
                            Staff* s = inputNewStaffInteractive();
                            if(s != NULL)
                            pushBackStaff(staffs,s);
                        }
                        break;
                    }
                    case 7: {
                        Staff* s = inputNewStaffInteractive();
                        if(s != NULL)
                        pushBackStaff(staffs,s);
                        break;
                    }
                    case 8:
                        listStaffs(staffs);
                        break;
                    case 9: {
                        cin.ignore();
                        cout << "Nhap ten nhan vien: ";
                        string x; getline(cin,x);
                        deleteStaffByName(staffs,x);
                        break;
                    }
                    case 10: 
                        cout << "Dang xuat thanh cong!\n";
                        break; 
                    case 0:
                        return 0;
                    default:
                        cout << "Lua chon khong hop le!\n";
                }
                if (c == 10) break;
            }
        }

        // ================== NHAN VIEN ==================
        else if (acc->role == "nhanvien") {
            if (staffs == NULL){
                cout << "chua co nhan vien nao trong danh sach. "
                     << endl;
                continue;
            }
            while (true) {
                cout << "\n--- MENU NHAN VIEN ---\n"
                     << "1. Tao danh sach khach hang\n"
                     << "2. Them khach hang\n"
                     << "3. Xem khach hang\n"
                     << "4. Nap tien\n"
                     << "5. Rut tien\n"
                     << "6. Dang xuat\n"
                     << "0. Thoat\n"
                     << "Chon: ";

                int c; cin >> c;
                switch (c) {
                    case 1: {
                        int n; cout << "So khach hang: "; cin >> n;
                        for(int i=0;i<n;i++){
                            Customer* k = inputNewCustomerInteractive();
                            if(k != NULL)
                            pushBackCustomer(customers,k);
                        }
                        break;
                    }
                    case 2: {
                        Customer* k = inputNewCustomerInteractive();
                        if(k != NULL)
                        pushBackCustomer(customers,k);
                        break;
                    }
                    case 3:
                        listCustomers(customers,false);
                        break;
                    case 4: {
                        string ac; cout << "So tai khoan: "; cin >> ac;
                        Customer* k = findCustomerByAccount(customers,ac);
                        if(k == NULL)
                        cout << "Khong tim thay\n";
                        else depositToCustomer(k);
                        break;
                    }
                    case 5: {
                        string ac; cout << "So tai khoan: "; cin >> ac;
                        Customer* k = findCustomerByAccount(customers,ac);
                        if(k == NULL)
                        cout << "Khong tim thay\n";
                        else withdrawFromCustomer(k);
                        break;
                    }
                    case 6:
                        cout << "Dang xuat thanh cong!\n";
                        break; 
                    case 0:
                        return 0;
                    default:
                        cout << "Lua chon khong hop le!\n";
                }
                if (c == 6) break;
            }
        }

        // ================== KHACH HANG ==================
        else {
            cout << "Nhap so tai khoan: ";
            string accNum;
            cin >> accNum;
            Customer* k = findCustomerByAccount(customers, accNum);
            if (k == NULL) {
                cout << "Sai so tai khoan!\n";
                continue;
            }

            while (true) {
                cout << "\n--- MENU KHACH HANG ---\n"
                     << "1. Xem thong tin\n"
                     << "2. Gui tien\n"
                     << "3. Rut tien\n"
                     << "4. Dang xuat\n"
                     << "0. Thoat\n"
                     << "Chon: ";

                int c; cin >> c;
                switch (c) {
                    case 1:
                        cout << "Ten: " << k->name
                             << "\nSo du: " << k->deposit
                             << endl;
                        break;
                    case 2:
                        depositToCustomer(k);
                        break;
                    case 3:
                        withdrawFromCustomer(k);
                        break;
                    case 4:
                        cout << "Dang xuat thanh cong!\n";
                        break;
                    case 0:
                        return 0;
                    default:
                        cout << "Lua chon khong hop le!\n";
                }
                if (c == 4) break;
            }
        }
    }

    cout << "Tam biet!\n";
    return 0;
}

