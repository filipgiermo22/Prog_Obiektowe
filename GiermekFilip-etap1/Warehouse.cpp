//
// Created by Filip on 19.11.2020.
//

#include "Warehouse.h"
#include <iostream>
#include <vector>
#include <iomanip>

void Warehouse::ContentWarehouse()
{
    if (warehouse.size() == 0) 
    {
        std::cout << "\n" << std::string(9, ' ') << "Warehouse state: empty."  << std::endl;
    }
    else //wypisanie listy towarów
    {
        std::cout << "\n" << std::string(21, ' ') << "Warehouse  content\n"<< std::string(21, ' ') << "------------------\n" << std::endl;
        std::cout <<std::string(9, ' ') << "ID |" << "         Name        |" << " Number of items" << std::endl;
        std::cout << std::string(9, ' ') << "------------------------------------------" << std::endl;

         for (int i = 0; i <warehouse.size(); ++i) //pêtla wypisuj¹ca towary poni¿ej wiersza z nazwami kolumn
         {
            std::cout << std::setw(11) << warehouse[i].get_ID() << " |" << std::setw(20) << warehouse[i].get_Name() << " |" <<std::setw(16) << warehouse[i].get_num_of_items() <<std::right << std::endl;
         }
    }
}

void Warehouse::Insert_new_type_Article() {

    std::string name;
    int quantity;

    std::cout << "\n" << std::string(9, ' ') << "How many types of articles do You want to insert: ";
    std::cin >> quantity;
    
    for (int i = 0; i < quantity; ++i)
    {
        if (i == 0) //wejœcie tylko na pocz¹tku
        {
            //trzy linijki zapisuj¹ce string (ze spacjami) do zmiennej "name"
            std::cout << "\n" << std::string(9, ' ') << "Enter name of new article's type (max. 20 char): ";
            std::cin.ignore();
            std::getline(std::cin, name);
        }
        
        else //wejœcie za ka¿dym razem oprócz pierwszego
        {
            std::cout << std::string(9, ' ') << "Next: ";
            std::getline(std::cin, name); 
        }

        //fragment dodaj¹cy obiekt do wektora 
        if (warehouse.size() == 0)                  
            warehouse.push_back(Article(name,0,0)); //gdy wektor pusty - dodanie obiektu z ID=0
        else
            warehouse.push_back(Article(name, warehouse[warehouse.size() - 1].get_ID() + 1, 0)); //gdy nie jesy pusty - ID+1 od poprzedniego
    }
}

void Warehouse::addArticle(int ID, int num_of_items)
{
    warehouse[ID].set_num_of_items(warehouse[ID].get_num_of_items() + num_of_items);
}

void Warehouse::removeArticle(int ID, int num_of_items) 
{
    //jeœli wektor posiada 0 sztuk danego towaru
    if (warehouse[ID].get_num_of_items() == 0)           
        std::cout << "\n" << std::string(9, ' ') << "There is 0 articles of this type." << std::endl;
    
    //jeœli wektor mam mniej sztuk danego towaru ni¿ u¿ytk. chce usun¹æ
    else if (warehouse[ID].get_num_of_items() - num_of_items < 0)  
        std::cout << "\n" << std::string(9, ' ') << "There is less (" << warehouse[ID].get_num_of_items() << ") articles of this type." << std::endl;
    
    //jeœli usuniêcie danej liczby sztuk jest mozliwe
    else
        warehouse[ID].set_num_of_items(warehouse[ID].get_num_of_items() - num_of_items);
}

int Warehouse::size() { return warehouse.size(); }

int Warehouse::last_ID() { return warehouse.back().get_ID(); }