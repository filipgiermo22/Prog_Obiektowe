

#include "Forklift.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <unistd.h>

int Forklift::get_size() { max_load = forklift.size(); return max_load; } //funk. pobrania rozmiaru

void Forklift::set_size(int amount, int condition) //proc. zmiany rozmiaru
{
    if(condition == 1)      //warunek, gdy dodawanie do wektora
        max_load += amount;
    else
        max_load -= amount;
}

void Forklift::push_back(Product *product) { forklift.push_back(product); } //proc. dodania wskaźnika towaru

Product* Forklift::return_object(int ID) //funk. zwracania wskaźnika towaru
{
    int i;
    for (i = 0; i < forklift.size(); ++i)
    {
        if (forklift[i]->get_ID() == ID)
        {
            break;
        }
    }
    return forklift[i];
}

void Forklift::content_forklift() //proc. wypisywania zawartości Paleciaka
{
    if (forklift.empty()) //warunek na niepusty wektor
    {
        std::cout << "\n" << std::string(9, ' ') << "Forklift state: empty."  << std::endl;
        sleep(2);
    }
    else //wypisanie listy towarów
    {
        std::cout << "\n" << std::string(21, ' ') << "Forklift  content\n"<< std::string(21, ' ') << "------------------\n" << std::endl;
        std::cout <<std::string(9, ' ') << "ID |" << "         Name        |" << "     Quantity" << std::endl;
        std::cout << std::string(9, ' ') << "---------------------------------------------" << std::endl;

        for (int i = 0; i < forklift.size(); ++i) //pętla wypisująca towary poniżej wiersza z nazwami kolumn
        {
            std::cout << std::setw(11) << forklift[i]->get_ID() << " |" << std::setw(20) <<
            forklift[i]->get_name() << " |" << std::setw(16) << forklift[i]->get_num_of_items()
            << " " << forklift[i]->get_unit() << std::endl;
        }
    }
    sleep(2);
}

void Forklift::erase_fork(int ID) //proc. usuwania wskaźnika
{
    for (int i = 0; i < forklift.size(); ++i)
    {
        if (forklift[i]->get_ID() == ID)
        {
            i -=1;
            forklift.erase(forklift.begin() + i);
            break;
        }
    }
}