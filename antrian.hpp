/*******************
 * Nama File : antrian.hpp
 * Pembuat : Andrian James Siregar
 *           Darren Wangsa
 *           Sanny Lie
 * Deskripsi : Program ini adalah header dari sistem queue kami.
 ******************/
#ifndef ANTRIAN_HPP
#define ANTRIAN_HPP
#include <iostream>
#include <queue>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <sstream> 

using namespace std;

struct customer{
    int idCust;
    string namaCust, noTelpCust;
    time_t waktuMasuk, waktuPanggil, waktuKeluar;

    bool empty(){
        return namaCust.empty() && noTelpCust.empty() && idCust == 0;
    }
};


class antrian{
    private:
        vector<customer> cust;
        int MAX = 100;
        int front = -1, rear = -1, lastId = 0;
        
    public:
        antrian();
        void updateVector();
        bool isEmpty();
        void enqueueAntrian(); // tulis ke file antrian langsung
        void dequeueAntrian(); // lanjut ke konter (dipanggil ke konter)
        int cekAntrian();
};

#endif