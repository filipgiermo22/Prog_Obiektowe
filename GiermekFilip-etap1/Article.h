//
// Created by Filip on 19.11.2020.
//

#ifndef PROJEKT_MAGAZYN_TOWAR_H
#define PROJEKT_MAGAZYN_TOWAR_H
#include <string>

class Article
{
    int ID;
    std::string Name;
    int num_of_items;

public:
    Article(std::string _Name, int _ID, int _num_of_items)  //konstruktor
    {
        Name = _Name;
        ID = _ID;
        num_of_items = _num_of_items;
    }

    //funkcje pobieraj¹ce wartoœci obiektu
    int get_ID();
    int get_num_of_items();
    std::string get_Name();

    //procedura ustawiaj¹ca liczbê sztuk towaru
    void set_num_of_items(int n_sztuki);
};

#endif