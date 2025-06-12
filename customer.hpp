#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <string>
#include <ctime>
using namespace std;

struct customer {
    int idCust;
    string namaCust, noTelpCust;
    time_t waktuMasuk, waktuPanggil, waktuKeluar;

    bool empty() {
        return namaCust.empty() && noTelpCust.empty() && idCust == 0;
    }
};

#endif
