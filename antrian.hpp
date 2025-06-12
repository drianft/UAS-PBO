/*******************
 * Nama File : main.cpp
 * Pembuat : Andrian James Siregar (241402096)
 *           Darren Wangsa (241402074)
 *           Sanny Lie (241402093)
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
#include "customer.hpp"
using namespace std;

class konter; // Forward declaration of konter class


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

#endif