/*******************
 * Nama File : main.cpp
 * Pembuat : Andrian James Siregar (241402096)
 *           Darren Wangsa (241402074)
 *           Sanny Lie (241402093)
 * Deskripsi : Program ini adalah isi function dari sistem queue kami.
 ******************/
#include "antrian.hpp"
#include "konter.hpp"
#include <iostream>
#include <queue>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <sstream> 

#define RESET       "\033[0m"
#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
#define BOLD        "\033[1m"
#define BR_BLACK    "\033[90m"
#define BR_RED      "\033[91m"
#define BR_GREEN    "\033[92m"
#define BR_YELLOW   "\033[93m"
#define BR_BLUE     "\033[94m"
#define BR_MAGENTA  "\033[95m"
#define BR_CYAN     "\033[96m"
#define BR_WHITE    "\033[97m"

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
    updateVector(); // Refresh antrian dari file
    return front == -1 || front >= rear;
}

int antrian::cekAntrian() {
    return cust.size();
}

void antrian::enqueueAntrian() {
    updateVector(); // Refresh antrian dari file
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
    k.readStatusKonter();

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
        k.logStatusKonter();

        return nextCustomer;
    }
}
