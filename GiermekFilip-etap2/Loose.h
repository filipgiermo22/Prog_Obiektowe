
#ifndef GIERMEKFILIP_ETAP2_LOOSE_H
#define GIERMEKFILIP_ETAP2_LOOSE_H

#include "Product.h"
#include <string>

class Loose : public Product //klasa towarów sypkich
{
    double _kg_quant;
public:
    Loose(std::string Name, int ID, double quant, std::string unit="kg") //konstruktor
    {
        _Name = Name;
        _ID = ID;
        _kg_quant = quant;
        _unit = unit;
    }

    double get_num_of_items() override; //wirtualna funk. pobierania liczby sztuk

    void set_num_of_items(float) override;  //wirtualna proc. ustawiania liczby sztuk
};


#endif
