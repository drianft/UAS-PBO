/*******************
 * Nama File : main.cpp
 * Pembuat : Andrian James Siregar (241402096)
 *           Darren Wangsa (241402074)
 *           Sanny Lie (241402093)
 * Deskripsi : Program ini adalah main function dari sistem antrian kami.
 ******************/
#include "konter.hpp"
#include <iostream>
#include <queue>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <sstream> 
using namespace std;

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

int main(){
    antrian a;
    // konter k;
    int inp;
    string loop;

    do{
        system("cls");
        cout << BOLD CYAN << setfill('=') << setw(100) << "=" << RESET << endl
             << setfill(' ') << setw(30) << " " << BOLD BLUE << "Tugas 4 Pemrograman Berorientasi Objek\n"
             << BOLD CYAN << setfill('=') << setw(100) << "=" << RESET << endl << setfill(' ');
        
        cout << YELLOW << "1. Daftar Pasien\n2. Panggil Pasien\n3. Manajemen Konter (Tampilkan isi/Dequeue/Clear Konter)\n4. Rata-rata lama layanan\n5. Exit\n" 
            << BOLD CYAN << setfill('=') << setw(100) << "=" << RESET YELLOW << endl << setfill(' ') << "Apa yang ingin anda lakukan? (1/2/3/4/5) : " << GREEN;
        cin >> inp;
        cout << RESET;

        switch(inp){
            case 1:
                a.enqueueAntrian();
                break;
            case 2:
                a.dequeueAntrian();
                //enqueue konter
                break;
            case 3:
                //main konter
                break;
            case 4:
                //rata-rata lama layanan
                break;
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