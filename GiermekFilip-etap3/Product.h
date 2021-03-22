
#ifndef GIERMEKFILIP_ETAP2_PRODUCT_H
#define GIERMEKFILIP_ETAP2_PRODUCT_H

#include <string>

class Product //klasa abstrakcyjna
{
protected:
    int _ID;
    std::string _Name;
    std::string _unit; //pole jednostki do wyświetlania na liście

public:
    int get_ID() const;   //funk. pobierania ID

    std::string get_name() const;   //funk. pobierania nazwy

    std::string get_unit() const;   //funk. pobierania jednostki

    virtual double get_num_of_items() = 0;   //wirtualna funk. pobierania liczby sztuk

    virtual void set_num_of_items(float) = 0;   //wirtualna proc. ustawiania liczby sztuk
};
#endif
