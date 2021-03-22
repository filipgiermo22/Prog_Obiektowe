
#ifndef GIERMEKFILIP_ETAP2_PALECIAK_H
#define GIERMEKFILIP_ETAP2_PALECIAK_H
#include "Product.h"
#include <vector>

class Forklift //klasa Paleciaka
{
    std::vector<Product *> forklift; //wektor wskaźników do Produktów
    int max_load = 0;  //pole ładowności
public:

   // int get_size(); //funk. pobrania rozmiaru

    void set_size(int amount, int condition); //proc. zmiany rozmiaru

    void push_back(Product *product); //proc. dodania wskaźnika towaru

   // Product* return_object(int ID); //proc. wypisywania zawartości Paleciaka

    void content_forklift(); //proc. wypisywania zawartości Paleciaka

   // void erase_fork(int); //proc. usuwania wskaźnika

   //void take_off_forklift(Warehouse &warehouses, int ware_num_create, int ware_num_access,  std::istream& in);
};
#endif


