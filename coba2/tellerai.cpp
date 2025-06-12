/*******************
 * Nama File : main.cpp
 * Pembuat : Andrian James Siregar (241402096)
 *           Darren Wangsa (241402074)
 *           Sanny Lie (241402093)
 * Deskripsi : Program ini adalah isi function dari sistem queue kami (versi perbaikan).
 ******************/

#include <iostream>
#include <queue>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

#define RESET       "\033[0m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define CYAN        "\033[36m"
#define BOLD        "\033[1m"

struct customer {
    int idCust;
    string namaCust, noTelpCust;
    time_t waktuMasuk, waktuPanggil, waktuKeluar;

    bool empty() {
        return namaCust.empty() && noTelpCust.empty() && idCust == 0;
    }
};

class konter {
private:
    customer listKonter[6];
    int MAX = 6;

public:
    void displayKonter();
    double AvgService();
    void DequeueKonter();
    void clearKonter();
    void assignCustomer(customer cust);
};

void konter::displayKonter() {
    for (int i = 0; i < MAX; i++) {
        if (!listKonter[i].empty()) {
            cout << "Konter " << i + 1 << " sedang melayani: " << listKonter[i].namaCust << endl;
        } else {
            cout << "Konter " << i + 1 << " sedang kosong." << endl;
        }
    }
}

void konter::DequeueKonter() {
    int nomorKonter;
    cout << "Masukkan nomor konter yang selesai melayani: ";
    cin >> nomorKonter;
    cin.ignore();

    if (nomorKonter > 0 && nomorKonter <= MAX && !listKonter[nomorKonter - 1].empty()) {
        time_t selesai = time(0);
        int durasiLayanan = rand() % 5 + 1;

        cout << "Pelanggan " << listKonter[nomorKonter - 1].namaCust << " selesai dilayani di konter " << nomorKonter << "." << endl;

        ofstream history("history.txt", ios::app);
        history << listKonter[nomorKonter - 1].namaCust << "|"
                << listKonter[nomorKonter - 1].noTelpCust << "|"
                << put_time(localtime(&listKonter[nomorKonter - 1].waktuMasuk), "%H:%M:%S") << "|"
                << durasiLayanan << "|"
                << put_time(localtime(&selesai), "%H:%M:%S") << endl;

        listKonter[nomorKonter - 1] = customer();
    } else {
        cout << "Nomor konter tidak valid atau konter kosong." << endl;
    }
}

double konter::AvgService() {
    ifstream history("history.txt");
    string line;
    int total = 0, count = 0;

    while (getline(history, line)) {
        stringstream ss(line);
        string nama, telp, waktuMasuk, durasiStr, waktuSelesai;
        getline(ss, nama, '|');
        getline(ss, telp, '|');
        getline(ss, waktuMasuk, '|');
        getline(ss, durasiStr, '|');
        getline(ss, waktuSelesai);

        total += stoi(durasiStr);
        count++;
    }

    if (count == 0) return 0;
    return (double)total / count;
}



void konter::clearKonter() {
    ofstream history("history.txt", ios::app);

    for (int i = 0; i < MAX; i++) {
        if (!listKonter[i].empty()) {
            time_t selesai = time(0);
            int durasiLayanan = rand() % 5 + 1;

            cout << "Pelanggan " << listKonter[i].namaCust << " selesai dilayani di konter " << i + 1 << "." << endl;

            history << listKonter[i].namaCust << "|"
                    << listKonter[i].noTelpCust << "|"
                    << put_time(localtime(&listKonter[i].waktuMasuk), "%H:%M:%S") << "|"
                    << durasiLayanan << "|"
                    << put_time(localtime(&selesai), "%H:%M:%S") << endl;

            listKonter[i] = customer(); // kosongkan konter
        }
    }

    cout << "Semua konter telah dikosongkan." << endl;
    history.close();

}

void konter::assignCustomer(customer cust) {
    for (int i = 0; i < MAX; i++) {
        if (listKonter[i].empty()) {
            cust.waktuPanggil = time(0); // waktu mulai dilayani
            listKonter[i] = cust;
            cout << "Pelanggan " << cust.namaCust << " masuk ke konter " << i + 1 << endl;
            return;
        }
    }
    cout << "Semua konter sedang sibuk." << endl;
}


class antrian {
private:
    vector<customer> cust;
    int MAX = 100;
    int front = -1, rear = -1, lastId = 0;

public:
    antrian();
    void updateVector();
    bool isEmpty();
    void enqueueAntrian();
    customer dequeueAntrian(konter &k);
    int cekAntrian();
    void removeFront();
};

antrian::antrian() {
    front = -1;
    rear = -1;
    lastId = 0;
}

void antrian::updateVector() {
    string x;
    ifstream readFile("antrian.txt");

    cust.clear();
    int i = 0;

    while (getline(readFile, x) && i < MAX) {
        stringstream ss(x);
        string idTemp, namaTemp, notelpTemp, timeStr;

        getline(ss, idTemp, '|');
        getline(ss, namaTemp, '|');
        getline(ss, notelpTemp, '|');
        getline(ss, timeStr);

        customer c;
        c.idCust = stoi(idTemp);
        c.namaCust = namaTemp;
        c.noTelpCust = notelpTemp;
        c.waktuMasuk = static_cast<time_t>(stoll(timeStr));

        cust.push_back(c);

        if (c.idCust > lastId)
            lastId = c.idCust;

        i++;
    }

    if (!cust.empty()) {
        front = 0;
        rear = cust.size();
    } else {
        front = -1;
        rear = -1;
    }
}

bool antrian::isEmpty() {
    return front == -1 || front >= rear;
}

int antrian::cekAntrian() {
    return cust.size();
}

void antrian::enqueueAntrian() {
    if (cekAntrian() >= 100) {
        cout << BOLD RED << "Maaf, Antrian sedang penuh.\n" << RESET;
        return;
    }

    string namaTemp, noTelpTemp;
    time_t waktuMasukTemp;
    cin.ignore();
    cout << GREEN << "Masukkan nama: ";
    getline(cin, namaTemp);
    cout << GREEN << "Masukkan nomor telepon: ";
    getline(cin, noTelpTemp);
    waktuMasukTemp = time(0);

    if (namaTemp.empty() || noTelpTemp.empty()) {
        cout << RED << "Nama dan nomor telepon tidak boleh kosong!" << RESET << endl;
        return;
    }

    ofstream listAntrian("antrian.txt", ios::app);
    listAntrian << lastId + 1 << "|" << namaTemp << "|" << noTelpTemp << "|" << waktuMasukTemp << endl;
}

void antrian::removeFront() {
    ofstream tempFile("temp.txt");
    for (size_t i = 1; i < cust.size(); i++) {
        tempFile << cust[i].idCust << "|" << cust[i].namaCust << "|" << cust[i].noTelpCust << "|" << cust[i].waktuMasuk << endl;
    }
    tempFile.close();
    remove("antrian.txt");
    rename("temp.txt", "antrian.txt");
}

customer antrian::dequeueAntrian(konter &k) {
    updateVector(); // Refresh antrian dari file

    if (isEmpty()) {
        cout << BOLD RED << "Antrian Kosong!\n" << RESET;
        return customer(); // Kembalikan customer kosong
    } else {
        customer nextCustomer = cust[front];

        cout << BOLD CYAN << nextCustomer.namaCust << RESET BLUE << " dipersilahkan untuk masuk ke konter.\n" << RESET;
        k.assignCustomer(nextCustomer);

        // Proses hapus data pertama dari file
        ifstream inputFile("antrian.txt");
        ofstream tempFile("temp.txt");

        string line;
        bool isFirstLine = true;

        while (getline(inputFile, line)) {
            if (isFirstLine) {
                isFirstLine = false; // Skip baris pertama (yang sudah dipanggil)
                continue;
            }
            tempFile << line << endl; // Tulis ulang sisanya
        }

        inputFile.close();
        tempFile.close();

        // Hapus file lama, ganti dengan file baru
        remove("antrian.txt");
        rename("temp.txt", "antrian.txt");

        return nextCustomer;
    }
}




int main() {
    antrian a;
    konter k;
    k.clearKonter(); // Inisialisasi konter kosong
    int inp;
    string loop;

    do {
        system("cls");
        cout << BOLD CYAN << setfill('=') << setw(100) << "=" << RESET << endl
             << setfill(' ') << setw(30) << " " << BOLD BLUE << "Tugas 4 Pemrograman Berorientasi Objek\n"
             << BOLD CYAN << setfill('=') << setw(100) << "=" << RESET << endl << setfill(' ');

        cout << YELLOW << "1. Daftar Pasien\n2. Panggil Pasien\n3. Manajemen Konter\n4. Rata-rata lama layanan\n5. Exit\n"
             << BOLD CYAN << setfill('=') << setw(100) << "=" << RESET << YELLOW << endl << setfill(' ') << "Apa yang ingin anda lakukan? (1/2/3/4/5) : " << GREEN;
        cin >> inp;

        switch (inp) {
            case 1:
                a.enqueueAntrian();
                break;
            case 2:
            {
                a.dequeueAntrian(k); 
                break;
            }

            case 3:
            {
                int subMenu;
                cout << "1. Tampilkan Isi Konter\n2. Selesaikan Layanan di Konter\n3. Kosongkan Semua Konter\nPilih: ";
                cin >> subMenu;
                cin.ignore();

                if (subMenu == 1) {
                    k.displayKonter();
                } else if (subMenu == 2) {
                    k.DequeueKonter();
                } else if (subMenu == 3) {
                    k.clearKonter();
                }
                break;
            }

            case 4:
            {
                double rataRata = k.AvgService();
                cout << "Rata-rata lama layanan: " << rataRata << " menit.\n";
                break;
            }

            case 5:
                cout << BOLD CYAN << setfill('=') << setw(100) << "=" << RESET << endl
                     << setfill(' ') << setw(38) << " " << BOLD RED << "Program berhenti...\n"
                     << BOLD CYAN << setfill('=') << setw(100) << "=" << RESET << endl << setfill(' ');
                return 0;
        }

        cout << BOLD CYAN << setfill('=') << setw(100) << "=" << RESET << endl << setfill(' ');
        cout << GREEN << "Apakah anda melanjutkan program? (Yes/No) " << RESET;
        cin >> loop;

        for (char &c : loop) {
            c = tolower(c);
        }
    } while (loop != "no" && loop != "n");

    cout << BOLD CYAN << setfill('=') << setw(100) << "=" << RESET << endl
         << setfill(' ') << setw(38) << " " << BOLD RED << "Program berhenti...\n"
         << BOLD CYAN << setfill('=') << setw(100) << "=" << RESET << endl << setfill(' ');
    return 0;
}
