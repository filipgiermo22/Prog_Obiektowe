//
// Created by Filip on 19.11.2020.
//

#ifndef PROJEKT_MAGAZYN_MAGAZYN_H
#define PROJEKT_MAGAZYN_MAGAZYN_H

#include "Article.h"
#include <vector>
#include <string>

class Warehouse
{
    std::vector<Article> warehouse; //wektor obiektów klasy Article

public:

    void ContentWarehouse(); //wypisywanie zawartoœci magazynu w formie tabeli

    void Insert_new_type_Article(); //procedura tworzenia nowego typu towaru

    void addArticle(int ID, int num_of_items);  //procedura dodania sztuk danego towaru

    void removeArticle(int ID, int num_of_items);   //procedura odjêcia sztuk danego towaru

    int size(); //funkcja pobrania rozmiaru wektora 

    int last_ID();  //funkcja pobrania ID ostatniego obiektu w wektorze
};

#endif