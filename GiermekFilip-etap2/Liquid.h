
#ifndef GIERMEKFILIP_ETAP2_TOWAR_H
#define GIERMEKFILIP_ETAP2_TOWAR_H
#include "Product.h"
#include <string>

class Liquid : public Product   //klasa towarów płynnych
{
    double _l_quant;
public:
    Liquid(std::string Name, int ID, double quant, std::string unit="l") //konstruktor
    {
        _Name = Name;
        _ID = ID;
        _l_quant = quant;
        _unit = unit;
    }

    double get_num_of_items() override;  //wirtualna funk. pobierania liczby sztuk

    void set_num_of_items(float) override;  //wirtualna proc. ustawiania liczby sztuk
};

#endif