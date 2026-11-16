#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <fstream>
using namespace std;

bool laSoNguyenHopLe(const string& s) {
    if (s.empty()) return false;
    int start = 0;
    if (s[0] == '-') {
        if (s.length() == 1) return false;
        start = 1;
    }
    for (int i = start; i < (int)s.length(); i++) {
        if (!isdigit((unsigned char)s[i])) return false;
    }
    return true;
}

bool laSoThucHopLe(const string& s) {
    if (s.empty()) return false;
    int start = 0;
    if (s[0] == '-') {
        if (s.length() == 1) return false;
        start = 1;
    }
    int dotCount = 0;
    bool hasDigit = false;
    for (int i = start; i < (int)s.length(); i++) {
        if (s[i] == '.') {
            dotCount++;
            if (dotCount > 1) return false;
        } else if (isdigit((unsigned char)s[i])) {
            hasDigit = true;
        } else {
            return false;
        }
    }
    return hasDigit;
}

bool laChiGomSo(string s) {
    if (s.empty()) return false;
    string clean = "";
    for (int i = 0; i < (int)s.length(); i++) {
        if (!isspace((unsigned char)s[i])) clean += s[i];
    }
    if (clean.empty()) return false;
    for (int i = 0; i < (int)clean.length(); i++) {
        if (!isdigit((unsigned char)clean[i])) return false;
    }
    return true;
}

bool batDauBangSo(const string& s) {
    if (s.empty()) return false;
    int i = 0;
    while (i < (int)s.length() && isspace((unsigned char)s[i])) {
        i++;
    }
    if (i < (int)s.length() && isdigit((unsigned char)s[i])) {
        return true;
    }
    return false;
}

string chuanHoaId(string s) {
    for (int i = 0; i < (int)s.length(); i++) {
        s[i] = toupper((unsigned char)s[i]);
    }
    return s;
}

string chuanHoaSanPham(string s) {
    if (s.empty()) return s;
    s[0] = toupper((unsigned char)s[0]);
    for (int i = 1; i < (int)s.length(); i++) {
        s[i] = tolower((unsigned char)s[i]);
    }
    return s;
}

string chuanHoaTenKhach(string s) {
    if (s.empty()) return s;
    bool space = true;
    for (int i = 0; i < (int)s.length(); i++) {
        if (s[i] == ' ' || s[i] == '\t') {
            space = true;
        } else {
            if (space) {
                s[i] = toupper((unsigned char)s[i]);
                space = false;
            } else {
                s[i] = tolower((unsigned char)s[i]);
            }
        }
    }
    return s;
}

string numToString(long long n) {
    if (n == 0) return "0";
    bool isNegative = false;
    if (n < 0) {
        isNegative = true;
        n = -n;
    }
    string res = "";
    while (n > 0) {
        char digit = '0' + (n % 10);
        res = digit + res;
        n /= 10;
    }
    if (isNegative) res = "-" + res;
    return res;
}

string khoangTrang(string str, int width) {
    if ((int)str.length() >= width) return str;
    return str + string(width - str.length(), ' ');
}

struct ItemNode {
    string id;
    string name;
    double price;
    int soLuong;
    ItemNode* next;

    ItemNode(string id, string name, double price, int soLuong)
        : id(id), name(name), price(price), soLuong(soLuong), next(NULL) {}
};

class ShoppingCart {
private:
    ItemNode* head;

public:
    ShoppingCart() : head(NULL) {}

    ~ShoppingCart() {
        clear();
    }

    void clear() {
        ItemNode* current = head;
        while (current != NULL) {
            ItemNode* temp = current;
            current = current->next;
            delete temp;
        }
        head = NULL;
    }

    bool kiemTraId(string id) const {
        ItemNode* current = head;
        while (current != NULL) {
            if (current->id == id) return true;
            current = current->next;
        }
        return false;
    }

    void addItem(string id, string name, double price, int soLuong) {
        if (soLuong <= 0) {
            cout << "-> Loi: So luong phai lon hon 0!\n";
            return;
        }

        ItemNode* newItem = new ItemNode(id, name, price, soLuong);
        if (head == NULL) {
            head = newItem;
        } else {
            ItemNode* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newItem;
        }
        cout << "-> Da them san pham: " << name << "\n";
    }

   bool capNhatSoLuong(string id, int soLuongMoi) {
        ItemNode* current = head;
        while (current != NULL) {
            if (current->id == id) {
                if (soLuongMoi == 0) {
                    removeItem(id);
                    cout << "-> So luong = 0, da xoa san pham khoi gio hang.\n";
                } else {
                    current->soLuong = soLuongMoi;
                    cout << "-> Da cap nhat so luong san pham ma " << id << " thanh: " << soLuongMoi << "\n";
                }
                return true;
            }
            current = current->next;
        }
        cout << "-> Khong tim thay san pham co ma " << id << " trong gio hang !\n";
        return false;
    }

    bool removeItem(string id) {
        if (head == NULL) return false;

        if (head->id == id) {
            ItemNode* temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        ItemNode* current = head;
        while (current->next != NULL && current->next->id != id) {
            current = current->next;
        }
        if (current->next != NULL) {
            ItemNode* temp = current->next;
            current->next = temp->next;
            delete temp;
            return true;
        }
        return false;
    }

    double tinhTongTien() const {
        double total = 0;
        ItemNode* current = head;
        while (current != NULL) {
            total += current->price * current->soLuong;
            current = current->next;
        }
        return total;
    }

    bool isEmpty() const {
        return head == NULL;
    }

    ItemNode* copyItems() const {
        if (head == NULL) return NULL;

        ItemNode* newHead = new ItemNode(head->id, head->name, head->price, head->soLuong);
        ItemNode* currentOld = head->next;
        ItemNode* currentNew = newHead;

        while (currentOld != NULL) {
            currentNew->next = new ItemNode(currentOld->id, currentOld->name, currentOld->price, currentOld->soLuong);
            currentNew = currentNew->next;
            currentOld = currentOld->next;
        }
        return newHead;
    }

    void display() const {
        if (head == NULL) {
            cout << "\n[!] Gio hang hien dang trong!\n";
            return;
        }
        cout << "\n================ CHI TIET GIO HANG HIEN TAI ================\n";
        cout << khoangTrang("Ma SP", 10)
             << khoangTrang("Ten san pham", 25)
             << khoangTrang("Don gia (VND)", 15)
             << khoangTrang("So luong", 12)
             << khoangTrang("Thanh tien", 15) << endl;
        cout << string(77, '-') << endl;

        ItemNode* current = head;
        while (current != NULL) {
            cout << khoangTrang(current->id, 10)
                 << khoangTrang(current->name, 25)
                 << khoangTrang(numToString((long long)current->price), 15)
                 << khoangTrang(numToString(current->soLuong), 12)
                 << khoangTrang(numToString((long long)(current->price * current->soLuong)), 15) << endl;
            current = current->next;
        }
        cout << string(77, '-') << endl;
        cout << "TONG TIEN: " << numToString((long long)tinhTongTien()) << " VND\n";
        cout << "=============================================================\n";
    }
};

struct OrderNode {
    int orderId;
    string customerName;
    ItemNode* itemsHead;
    double totalAmount;
    OrderNode* next;

    OrderNode(int id, string custName, ItemNode* items, double total)
        : orderId(id), customerName(custName), itemsHead(items), totalAmount(total), next(NULL) {}

    ~OrderNode() {
        ItemNode* current = itemsHead;
        while (current != NULL) {
            ItemNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
};

class OrderQueue {
private:
    OrderNode* front;
    OrderNode* rear;
    OrderNode* historyHead;

    template <typename T>
    void mySwap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

    void luuHoaDonVaoFile(OrderNode* order) {
        string fileName = "HoaDon_" + numToString(order->orderId) + ".txt";
        ofstream outFile(fileName.c_str());

        if (!outFile.is_open()) {
            cout << "-> Loi: Khong the tao file hoa don!\n";
            return;
        }

        outFile << "======================================================\n";
        outFile << "               HOA DON THANH TOAN " << order->orderId << "\n";
        outFile << " Khach hang: " << order->customerName << "\n";
        outFile << "------------------------------------------------------\n";
        outFile << khoangTrang("Ma SP", 10)
                << khoangTrang("Ten san pham", 20)
                << khoangTrang("Don gia", 12)
                << khoangTrang("SL", 8)
                << khoangTrang("Thanh tien", 15) << "\n";

        ItemNode* item = order->itemsHead;
        while (item != NULL) {
            outFile << khoangTrang(item->id, 10)
                    << khoangTrang(item->name, 20)
                    << khoangTrang(numToString((long long)item->price), 12)
                    << khoangTrang(numToString(item->soLuong), 8)
                    << khoangTrang(numToString((long long)(item->price * item->soLuong)), 15) << "\n";
            item = item->next;
        }

        outFile << "------------------------------------------------------\n";
        outFile << "TONG TIEN THANH TOAN: " << numToString((long long)order->totalAmount) << " VND\n";
        outFile << "======================================================\n";

        outFile.close();
        cout << "-> Da xuat hoa don vao file: " << fileName << "\n";
    }

public:
    OrderQueue() : front(NULL), rear(NULL), historyHead(NULL) {}

    ~OrderQueue() {
        while (!isEmpty()) {
            xoaDonDau();
        }
        OrderNode* current = historyHead;
        while (current != NULL) {
            OrderNode* temp = current;
            current = current->next;
            delete temp;
        }
    }

    bool isEmpty() const {
        return front == NULL;
    }

    void hangDoi(int orderId, string customerName, ItemNode* items, double total) {
        OrderNode* newOrder = new OrderNode(orderId, customerName, items, total);
        if (rear == NULL) {
            front = rear = newOrder;
        } else {
            rear->next = newOrder;
            rear = newOrder;
        }
        cout << "-> Da dua don hang " << orderId << " cua khach hang " << customerName << " vao hang doi thanh toan.\n";
    }

    void xuLyGiaoDich() {
        if (isEmpty()) {
            cout << "\n[!] Hang doi thanh toan dang trong!\n";
            return;
        }

        OrderNode* orderToProcess = front;
        front = front->next;
        if (front == NULL) {
            rear = NULL;
        }

        cout << "\n======================================================\n";
        cout << "     XU LY GIAO DICH THANH TOAN DON HANG " << orderToProcess->orderId << "\n";
        cout << " Khach hang: " << orderToProcess->customerName << "\n";
        cout << "------------------------------------------------------\n";
        cout << khoangTrang("Ma SP", 10)
             << khoangTrang("Ten san pham", 20)
             << khoangTrang("Don gia", 12)
             << khoangTrang("SL", 8)
             << khoangTrang("Thanh tien", 15) << "\n";

        ItemNode* item = orderToProcess->itemsHead;
        while (item != NULL) {
            cout << khoangTrang(item->id, 10)
                 << khoangTrang(item->name, 20)
                 << khoangTrang(numToString((long long)item->price), 12)
                 << khoangTrang(numToString(item->soLuong), 8)
                 << khoangTrang(numToString((long long)(item->price * item->soLuong)), 15) << "\n";
            item = item->next;
        }

        cout << "------------------------------------------------------\n";
        cout << "TONG TIEN THANH TOAN: " << numToString((long long)orderToProcess->totalAmount) << " VND\n";
        cout << "-> Xu ly thanh toan don hang " << orderToProcess->orderId << " thanh cong!\n";
        cout << "======================================================\n";

        luuHoaDonVaoFile(orderToProcess);

        orderToProcess->next = historyHead;
        historyHead = orderToProcess;
    }

    bool huyDonHang(int orderId) {
        if (isEmpty()) {
            cout << "\n[!] Hang doi thanh toan dang trong, khong co don de huy!\n";
            return false;
        }

        if (front->orderId == orderId) {
            OrderNode* temp = front;
            front = front->next;
            if (front == NULL) {
                rear = NULL;
            }
            delete temp;
            cout << "-> Da huy thanh cong don hang " << orderId << " khoi hang doi.\n";
            return true;
        }

        OrderNode* current = front;
        while (current->next != NULL && current->next->orderId != orderId) {
            current = current->next;
        }

        if (current->next != NULL) {
            OrderNode* temp = current->next;
            current->next = temp->next;
            if (temp == rear) {
                rear = current;
            }
            delete temp;
            cout << "-> Da huy thanh cong don hang " << orderId << " khoi hang doi.\n";
            return true;
        }

        cout << "-> Khong tim thay don hang co ma " << orderId << " trong hang doi cho thanh toan!\n";
        return false;
    }

    void xoaDonDau() {
        if (isEmpty()) return;
        OrderNode* temp = front;
        front = front->next;
        if (front == NULL) rear = NULL;
        delete temp;
    }

    void sapXepTheoTongTien(bool giamDan = true) {
        if (front == NULL || front->next == NULL) {
            cout << "-> Hang doi rong hoac chi co 1 don, khong can sap xep.\n";
            return;
        }

        for (OrderNode* i = front; i != NULL; i = i->next) {
            for (OrderNode* j = i->next; j != NULL; j = j->next) {
                bool shouldSwap = giamDan ? (i->totalAmount < j->totalAmount) : (i->totalAmount > j->totalAmount);
                if (shouldSwap) {
                    mySwap(i->orderId, j->orderId);
                    mySwap(i->customerName, j->customerName);
                    mySwap(i->itemsHead, j->itemsHead);
                    mySwap(i->totalAmount, j->totalAmount);
                }
            }
        }
        cout << "-> Da sap xep hang doi don hang theo tong tien thanh cong!\n";
    }

    void displayQueue() const {
        if (isEmpty()) {
            cout << "\n[!] Hang doi thanh toan hien dang trong!\n";
            return;
        }
        cout << "\n=========== DANH SACH DON HANG DANG CHO THANH TOAN ===========\n";
        cout << khoangTrang("Ma don", 10)
             << khoangTrang("Ten khach hang", 25)
             << khoangTrang("Tong tien (VND)", 20) << endl;
        cout << string(55, '-') << endl;

        OrderNode* current = front;
        while (current != NULL) {
            cout << khoangTrang(numToString(current->orderId), 10)
                 << khoangTrang(current->customerName, 25)
                 << khoangTrang(numToString((long long)current->totalAmount), 20) << endl;
            current = current->next;
        }
        cout << string(55, '-') << endl;
    }

    void displayHistory() const {
        if (historyHead == NULL) {
            cout << "\n[!] Lich su giao dich hien dang trong!\n";
            return;
        }
        cout << "\n================= LICH SU GIAO DICH DA THANH TOAN ================\n";
        cout << khoangTrang("Ma don", 10)
             << khoangTrang("Ten khach hang", 25)
             << khoangTrang("Tong tien VND", 20) << endl;
        cout << string(55, '-') << endl;

        OrderNode* current = historyHead;
        while (current != NULL) {
            cout << khoangTrang(numToString(current->orderId), 10)
                 << khoangTrang(current->customerName, 25)
                 << khoangTrang(numToString((long long)current->totalAmount), 20) << endl;
            current = current->next;
        }
        cout << string(55, '-') << endl;
    }
};

int main() {
    ShoppingCart cart;
    OrderQueue queue;
    int autoOrderId = 101;
    int choice;

    do {
        cout << "\n======================================================\n";
        cout << "     HE THONG QUAN LY GIO HANG & HANG DOI THANH TOAN    \n";
        cout << "======================================================\n";
        cout << " 1. Them san pham vao gio hang \n";
        cout << " 2. Cap nhat so luong san pham trong gio hang \n";
        cout << " 3. Xoa san pham khoi gio hang \n";
        cout << " 4. Xem chi tiet gio hang hien tai\n";
        cout << " 5. Chuyen gio hang thanh don hang \n";
        cout << " 6. Xem danh sach don trong hang cho thanh toan \n";
        cout << " 7. Huy don hang trong hang cho thanh toan \n";
        cout << " 8. Sap xep don hang theo tong tien giam dan \n";
        cout << " 9. Xu ly thanh toan don hang dau tien va xuat file \n";
        cout << " 10. Xem lich su giao dich da thanh toan \n";
        cout << " 0. Thoat chuong trinh \n";
        cout << "======================================================\n";
        cout << " Lua chon cua ban: ";
        
        string choiceStr;
        getline(cin, choiceStr);
        if (!laSoNguyenHopLe(choiceStr)) {
            cout << "-> Loi: Lua chon khong hop le! Vui long nhap so.\n";
            continue;
        }
        choice = atoi(choiceStr.c_str());

        switch (choice) {
        case 1: {
            string id, name, inputStr;
            double price;
            int qty;
            
            while (true) {
                cout << " Nhap ma san pham: "; 
                getline(cin, id);
                id = chuanHoaId(id);
                
                if (id.empty()) {
                    cout << "-> Loi: Ma san pham khong duoc de trong!\n";
                } else if (cart.kiemTraId(id)) {
                    cout << "-> Loi: Ma san pham " << id << " da ton tai trong gio hang! Vui long nhap ma khac.\n";
                } else {
                    break;
                }
            }

            while (true) {
                cout << " Nhap ten san pham: "; 
                getline(cin, name);
                if (name.empty()) {
                    cout << "-> Loi: Ten san pham khong duoc de trong!\n";
                } else if (laChiGomSo(name)) {
                    cout << "-> Loi: Ten san pham khong duoc toan la so! Vui long nhap lai.\n";
                } else if (batDauBangSo(name)) {
                    cout << "-> Loi: Ten san pham khong duoc bat dau bang so! Vui long nhap lai.\n";
                } else {
                    name = chuanHoaSanPham(name);
                    break;
                }
            }

            while (true) {
                cout << " Nhap don gia VND: "; 
                getline(cin, inputStr);
                
                if (!laSoThucHopLe(inputStr)) {
                    cout << "-> Loi: Don gia chi duoc phep nhap so!\n";
                    continue;
                }
                
                price = atof(inputStr.c_str());
                if (price < 0) {
                    cout << "-> Loi: Don gia khong duoc am!\n";
                } else {
                    break;
                }
            }

            while (true) {
                cout << " Nhap so luong: "; 
                getline(cin, inputStr);
                
                if (!laSoNguyenHopLe(inputStr)) {
                    cout << "-> Loi: So luong chi duoc phep nhap so nguyen!\n";
                    continue;
                }
                
                qty = atoi(inputStr.c_str());
                if (qty <= 0) {
                    cout << "-> Loi: So luong phai lon hon 0!\n";
                } else {
                    break;
                }
            }
            
            cart.addItem(id, name, price, qty);
            break;
        }
        case 2: {
            if (cart.isEmpty()) {
                cout << "-> Gio hang dang trong, khong co san pham de cap nhat !\n";
                break;
            }
            string id;
            cout << " Nhap ma san pham can cap nhat: ";
            getline(cin, id);
            id = chuanHoaId(id);
            if (id.empty() || !cart.kiemTraId(id)) {
                cout << "-> Loi: Khong tim thay san pham co ma " << id << " trong gio hang ! \n";
                break;
            }
            string inputStr;
            int qty;
            while (true) {
                cout << " Nhap so luong moi: ";
                getline(cin, inputStr);
                if (!laSoNguyenHopLe(inputStr)) {
                    cout << "-> Loi: So luong chi duoc chua so nguyen !\n";
                    continue;
                }
                qty = atoi(inputStr.c_str());
                if (qty < 0) {
                    cout << "-> Loi: So luong khong duoc am !\n";
                    continue;
                }
                break;
            }
            cart.capNhatSoLuong(id, qty);
            break;
        }
        case 3: {
            string id;
            cout << " Nhap ma san pham can xoa: ";
            getline(cin, id);
            id = chuanHoaId(id);
            
            if (cart.removeItem(id)) {
                cout << "-> Da xoa san pham Ma " << id << " khoi gio hang!\n";
            } else {
                cout << "-> Khong tim thay san pham co ma " << id << "!\n";
            }
            break;
        }
        case 4: {
            cart.display();
            break;
        }
        case 5: {
            if (cart.isEmpty()) {
                cout << "-> Gio hang dang trong, khong the tao don hang!\n";
            } else {
                string custName;
                while (true) {
                    cout << " Nhap ten khach hang: ";
                    getline(cin, custName);
                    if (custName.empty()) {
                        cout << "-> Loi: Ten khach hang khong duoc de trong!\n";
                    } else if (laChiGomSo(custName)) {
                        cout << "-> Loi: Ten khach hang khong duoc la so! Vui long nhap lai.\n";
                    } else if (batDauBangSo(custName)) {
                        cout << "-> Loi: Ten khach hang khong duoc bat dau bang so!\n";
                    } else {
                        custName = chuanHoaTenKhach(custName);
                        break;
                    }
                }

                ItemNode* itemsCopy = cart.copyItems();
                double total = cart.tinhTongTien();
                queue.hangDoi(autoOrderId++, custName, itemsCopy, total);

                cart.clear();
                cout << "-> Gio hang da duoc lam rong de san sang cho lan mua tiep theo.\n";
            }
            break;
        }
        case 6: {
            queue.displayQueue();
            break;
        }
        case 7: {
            string inputStr;
            int cancelId;
            while (true) {
                cout << " Nhap ma don hang can huy: ";
                getline(cin, inputStr);
                if (!laSoNguyenHopLe(inputStr)) {
                    cout << "-> Loi: Ma don hang chi duoc chua so!\n";
                    continue;
                }
                cancelId = atoi(inputStr.c_str());
                break;
            }
            queue.huyDonHang(cancelId);
            break;
        }
        case 8: {
            queue.sapXepTheoTongTien(true);
            break;
        }
        case 9: {
            queue.xuLyGiaoDich();    
            break;
        }
        case 10: {
            queue.displayHistory();
            break;
        }
        case 0:
            cout << "Cam on ban da su dung he thong!\n";
            break;
        default:
            cout << "-> Loi: Lua chon khong hop le, vui long thu lai!\n";
        }
    } while (choice != 0);

    return 0;
}
