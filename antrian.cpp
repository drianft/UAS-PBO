/*******************
 * Nama File : antrian.hpp
 * Pembuat : Andrian James Siregar
 *           Darren Wangsa
 *           Sanny Lie
 * Deskripsi : Program ini adalah header dari sistem queue kami.
 ******************/
#include "antrian.hpp"
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

void antrian :: updateVector() {
        string x;
        ifstream readFile("antrian.txt");

        int i = 0;

        while (getline(readFile, x) && i < MAX) {
            stringstream ss(x);
            string idTemp, namaTemp, notelpTemp, timeStr;

            getline(ss, idTemp, '|');
            getline(ss, namaTemp, '|');
            getline(ss, notelpTemp, '|');
            getline(ss, timeStr);

            cust[i].idCust = stoi(idTemp);
            cust[i].namaCust = namaTemp;
            cust[i].noTelpCust = notelpTemp;

            cust[i].waktuMasuk = static_cast<time_t>(stoll(timeStr));

            if (cust[i].idCust > lastId)
                lastId = cust[i].idCust;

            i++;
        }
}

bool antrian :: isEmpty(){
    return front == -1 || front > rear;
}

void antrian :: enqueueAntrian(){
    // updateVector();
    if(cekAntrian() >= 100){
        cout << BOLD RED << "Maaf, Antrian sedang penuh.\n" << RESET;
        return;
    }

    string namaTemp, noTelpTemp;
    time_t waktuMasukTemp;
    cout << GREEN << "Masukkan nama: ";
    getline(cin, namaTemp);
    cout << GREEN << "Masukkan nomor telepon: ";
    getline(cin, noTelpTemp);
    waktuMasukTemp = time(0);

    //Cek input kosong atau tidak
    if (namaTemp.empty() || noTelpTemp.empty()) {
        cout << RED << "Nama dan nomor telepon tidak boleh kosong!" << RESET << endl;
        return;
    }

    ofstream listAntrian("antrian.txt", ios::app);
        listAntrian << lastId+1 << "|" << namaTemp << "|" << noTelpTemp << "|" << waktuMasukTemp << endl;
}

int antrian :: cekAntrian(){
    int jlh=0;
    for(int i = 0; i < MAX; i++){
        if(!cust[i].empty()) 
            jlh++;
        else{
            lastId = jlh;
            return jlh+1;
        }
    }
}