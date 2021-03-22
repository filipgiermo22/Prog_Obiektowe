
#ifndef GIERMEKFILIP_ETAP2_ARTICLE_H
#define GIERMEKFILIP_ETAP2_ARTICLE_H

#include "Product.h"
#include <string>

class Article : public Product //klasa towarów policzalnych
{
    int _quant;

public:
    Article(std::string Name, int ID, int quant, std::string unit="") //konstruktor
    {
        _Name = Name;
        _ID = ID;
        _quant = quant;
        _unit = unit;
    }

    double get_num_of_items() override;  //wirtualna funk. pobierania liczby sztuk

    void set_num_of_items(float) override;  //wirtualna proc. ustawiania liczby sztuk
};


#endif
