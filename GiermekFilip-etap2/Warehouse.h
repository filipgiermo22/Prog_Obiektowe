
#ifndef GIERMEKFILIP_ETAP2_MAGAZYN_H
#define GIERMEKFILIP_ETAP2_MAGAZYN_H

#include "Product.h"
#include "Forklift.h"
#include <vector>
#include <string>

class Warehouse
{
   std::vector<std::vector<Product*>> warehouses;//wektor magazynów

public:

    int add_warehouses(std::istream& in); // funk. tworzenia magazynów

    void content_warehouse(int ware_num_access); //proc wypisywania zawartości danego magazynu

    void insert_new_type_product(int ware_num_access, int ware_num_create, std::istream& in); // proc. dodawania typów towarów

    void add_product(int ID, float num_of_items, int ware_num_access);  //proc. dodawania sztuk towaru

    void remove_product(int ID, float num_of_items, int ware_num_access);  //proc. odejmowania sztuk towaru

    void put_on_forklift(Forklift &forklift, int ware_num_create, int ware_num_access, std::istream& in); //proc. 'wydaj'

    // void take_off_forklift(Forklift &forklift, int ware_num_create, std::istream& in); //proc. 'przyjmij'

    void merge_article(int ware_num_access,  std::istream& in); //proc. łączenia artykułów wewnątrz magazynu

    void split_article(int ware_num_access, int ware_num_create,  std::istream& in); //proc. rozdzielania towarów wewnątrz magazynu

    int size(int ware_num_access) const; //funk pobrania rozmiaru magazynu

    int last_ID(int ware_num_access) const;  //funk wyznaczania ostatniego ID

    double read_num_ware(std::istream& in); //funkcja pobrania inta

    std::string read_string_ware(std::istream& in); //funkcja pobrania stringa
};
#endif