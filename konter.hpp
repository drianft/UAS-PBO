/*******************
 * Nama File : konter.hpp
 * Pembuat : Andrian James Siregar
 *           Darren Wangsa
 *           Sanny Lie
 * Deskripsi : Header file untuk class konter pada sistem antrian.
 ******************/

#ifndef KONTER_HPP
#define KONTER_HPP

#include "antrian.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "customer.hpp"
using namespace std;



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
    bool isFull();
    void logStatusKonter();
    void readStatusKonter();
};

#endif
