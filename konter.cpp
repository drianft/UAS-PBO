#include "konter.hpp"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <sstream> 

using namespace std;

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
        logStatusKonter();

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
            logStatusKonter();

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
    logStatusKonter();

}

bool konter::isFull() {
    for (int i = 0; i < MAX; i++) {
        if (listKonter[i].empty()) {
            return false; // Masih ada konter kosong
        }
    }
    return true; // Semua konter sibuk
}

void konter::logStatusKonter() {
    ofstream file("status_konter.txt"); // overwrite setiap update

    if (file.is_open()) {
        time_t now = time(0);
        file << "Waktu update: " << put_time(localtime(&now), "%H:%M:%S") << endl;
        file << "===================================" << endl;

        for (int i = 0; i < MAX; i++) {
            file << "Konter " << i + 1 << ": ";
            if (listKonter[i].empty()) {
                file << "Kosong" << endl;
            } else {
                file << listKonter[i].namaCust << " (No.Telp: " << listKonter[i].noTelpCust << ")" << endl;
            }
        }

        file << "===================================" << endl << endl;
        file.close();
    } else {
        cout << "Gagal membuka file status_konter.txt" << endl;
    }
}



