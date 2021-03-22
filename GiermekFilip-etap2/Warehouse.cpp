
#include "Product.h"
#include "Article.h"
#include "Loose.h"
#include "Liquid.h"
#include "Warehouse.h"
#include <iostream>
#include <vector>
#include <iomanip>

int Warehouse::add_warehouses(std::istream& in) //tworzenie magazynów
{
    int ware_num_create;
    std::cout << "\n" << std::string(4, ' ') << "How many warehouses would you like to ";

    if (warehouses.empty()) { std::cout << "use? (more than 0): "; } //warunek pytania za pierwszym razem
    else { std::cout << "add?: "; }

    ware_num_create = read_num_ware(in);
    for(int i=0; i<ware_num_create; ++i)   //pętla tworzenia magazynów
    {
        warehouses.push_back(std::vector<Product*>());
    }
    return ware_num_create;
}

void Warehouse::content_warehouse(int ware_num_access) //wypisywanie zawartości danego magazynu
{
    if (warehouses[ware_num_access].empty()) //warunek dla pustego magazynu
    {
        std::cout << "\n" << std::string(9, ' ') << "Warehouse state: empty."  << std::endl;
    }
    else //wypisanie listy towarów
    {
        std::cout << "\n" << std::string(19, ' ') << "Warehouse No." <<ware_num_access+1<<" content\n"
        << std::string(19, ' ') << "----------------------\n" << std::endl;
        std::cout <<std::string(9, ' ') << "ID |" << "         Name        |" << "     Quantity" << std::endl;
        std::cout << std::string(9, ' ') << "---------------------------------------------" << std::endl;

         for (int i = 0; i < warehouses[ware_num_access].size(); ++i) //pętla wypisująca towary poniżej wiersza z nazwami kolumn
         {
            std::cout << std::setw(11) << warehouses[ware_num_access][i]->get_ID() << " |" << std::setw(20) <<
            warehouses[ware_num_access][i]->get_name() << " |" << std::setw(16) << warehouses[ware_num_access][i]->get_num_of_items()
                    << " " << warehouses[ware_num_access][i]->get_unit() << std::endl;
         }
    }
}

void Warehouse::insert_new_type_product(int ware_num_access, int ware_num_create, std::istream& in) //dodawanie typów towarów
{
    std::string name;
    int quantity;

    std::cout << "\n" << std::string(9, ' ') << "How many types of articles do You want to insert: ";
    quantity = read_num_ware(in);

    for (int i = 0; i < quantity; ++i) {        //pętla dodająca towary z unikatowym ID na przstrzeni magazynu
        if (i == 0) //wejście tylko na początku
        {
            std::cout << "\n" << std::string(9, ' ') << "Enter name of new article's type (max. 20 char): ";
            name = read_string_ware(in);
        } else //wejście za każdym razem oprócz pierwszego
        {
            std::cout << "\n" << std::string(9, ' ') << "Next: ";
            name = read_string_ware(in);
        }

        Product *p; //tworzenie wskaźnika do produktu
        int type;
        std::cout << std::string(9, ' ') << "Type (countable <1>; liquid <2>; Loose <3>): ";
        type = read_num_ware(in);  //zapisanie typu towaru (użyte w switchu w dalszej części

        //fragment dodający obiekt do wektora z unikatowym ID
         for (int l = 0; l < ware_num_create; ++l)
         {
             if (!warehouses[l].empty()) //pętla znajdująca niepusty magazyn
             {
                 int k = 0;
                 while (k < ware_num_create) //pętla znajdująca niepusty magazyn do wyznaczenia max_ID
                 {
                     if (!warehouses[k].empty())
                     {
                         break;
                     }
                     k++;
                 }
                 int max_ID = warehouses[k][warehouses[k].size() - 1]->get_ID(); //wstępne max_ID (ostatni element magazynu k)

                 for (int j = k + 1; j < ware_num_create; ++j) //pętla wyznaczająca największe ID przez przeszukanie kolejnych magazynów
                 {
                     if (!warehouses[j].empty())
                     {
                         if (max_ID < warehouses[j][warehouses[j].size() - 1]->get_ID())
                             max_ID = warehouses[j][warehouses[j].size() - 1]->get_ID();
                     }
                 }
                 if (max_ID >= warehouses[k][warehouses[k].size() - 1]->get_ID()) //warunek na stworzenie towaru z ID o 1 większym
                 {
                     switch (type)
                     {
                         case 1:
                             p = new Article(name, max_ID + 1, 0);
                             break;
                         case 2:
                             p = new Liquid(name, max_ID + 1, 0);
                             break;
                         case 3:
                             p = new Loose(name, max_ID + 1, 0);
                             break;
                         default: std::cout << "\n" << std::string(9, ' ') << "Error. Entered number is not assigned to any type." << std::endl;
                     }
                     warehouses[ware_num_access].push_back(p); //dodanie towaru do magazynu
                     break;
                 }
             }
             else //stworzenie towaru z ID = 0
             {
                 switch (type)
                 {
                     case 1:
                         p = new Article(name, 0, 0);
                         break;
                     case 2:
                         p = new Liquid(name, 0, 0);
                         break;
                     case 3:
                         p = new Loose(name, 0, 0);
                         break;
                     default: std::cout << "\n" << std::string(9, ' ') << "Error. Entered number is not assigned to any type." << std::endl;
                 }
                 warehouses[ware_num_access].push_back(p); //dodanie towaru do magazynu
                 break;
             }
         }
    }
}

void Warehouse::add_product(int ID, float num_of_items, int ware_num_access) //dodawanie sztuk towaru
{
    for(int i = 0; i < warehouses[ware_num_access].size(); ++i) //pętla wyszukująca pozycję towaru o wskazanym ID
    {
        if(warehouses[ware_num_access][i]->get_ID() == ID)
        {
            warehouses[ware_num_access][i]->set_num_of_items(warehouses[ware_num_access][i]->get_num_of_items() + num_of_items);
            break;
        }
    }
}

void Warehouse::remove_product(int ID, float num_of_items, int ware_num_access) //odejmowanie sztuk towaru
{
    for(int i = 0; i < warehouses[ware_num_access].size(); ++i) //pętla wyszukująca pozycję towaru o wskazanym ID
    {
        if(warehouses[ware_num_access][i]->get_ID() == ID)
        {
            //jeśli wektor posiada 0 sztuk danego towaru
            if (warehouses[ware_num_access][i]->get_num_of_items() == 0)
                std::cout << "\n" << std::string(9, ' ') << "There is 0 articles of this type." << std::endl;

                //jeśli wektor mam mniej sztuk danego towaru niż użytk. chce usunąć
            else if (warehouses[ware_num_access][i]->get_num_of_items() - num_of_items < 0)
                std::cout << "\n" << std::string(9, ' ') << "There is less (" << warehouses[ware_num_access][ID]->get_num_of_items() << ") articles of this type." << std::endl;

                //jeśli usunięcie danej liczby sztuk jest możliwe
            else
                warehouses[ware_num_access][i]->set_num_of_items(warehouses[ware_num_access][i]->get_num_of_items() - num_of_items);
        }
    }
}

void Warehouse::put_on_forklift(Forklift &forklift, int ware_num_create, int ware_num_access, std::istream& in) //przenoszenie towaru na paleciak (proc. 'wydaj')
{
    if (warehouses[ware_num_access].empty()) //sprawdzenie czy wektor jest niepusty
    {
        std::cout << "\n" << std::string(9, ' ') << "Warehouse number " << ware_num_access+1 << " state: empty."  << std::endl;
    }
    else
    {
        int ID;

        //pobranie ID towaru do przełożenia
        std::cout << "\n" << std::string(9, ' ') << "Insert info about the Article You want to put on." << std::endl;
        std::cout << std::string(9, ' ') << "ID: ";
        ID = read_num_ware(in);

        for(int i = 0; i < warehouses[ware_num_access].size(); ++i) //pętla wyszukująca pozycję towaru o wskazanym ID
        {
            if(warehouses[ware_num_access][i]->get_ID() == ID)
            {
                forklift.push_back(warehouses[ware_num_access][i]); //dodanie wskaźnika towaru na paleciaka
                warehouses[ware_num_access].erase(warehouses[ware_num_access].begin() + i); //usuwanie wskaźnika towaru z magazynu (proc. 'przyjmij')
                forklift.set_size(1, 1); //funkcja zmieniająca rozmiar paleciaka
                std::cout << "\n" << std::string(9, ' ') << "Article transferred successfully." << std:: endl;
                break;
            }

        }
    }
}

/*
void Warehouse::take_off_forklift(Forklift &forklift, int ware_num_access,  std::istream& in) //przenoszenie towaru do magazynu
{
    if (forklift.get_size() == 0) //sprawdzenie czy paleciak jest niepusty
    {
        std::cout << "\n" << std::string(9, ' ') << "Forklift state: empty."  << std::endl;
    }
    else
    {
        int ID;

        //pobranie ID towaru do przełożenia
        std::cout << "\n" << std::string(9, ' ') << "Insert info about the Article You want to take off." << std::endl;
        std::cout << std::string(9, ' ') << "ID: ";
        ID = readInt_ware(in);

        for (int i = 0; i < forklift.get_size(); ++i) //przeszukiwanie paleciaka
        {
            if (forklift.return_object(i)->get_ID() == ID)
            {
                warehouses[ware_num_access].push_back(forklift.return_object(i)); //dodanie wskaźnika do towaru z paleciaka
                forklift.erase_fork(i); //usunięcie wskaźnika z paleciaka
                forklift.set_size(forklift.get_size() - 1, 1); //zmiana rozmiaru paleciaka
                std::cout << "\n" << std::string(9, ' ') << "Article transferred successfully." << std::endl;
                break;
            }
        }
    }
}
*/

void Warehouse::merge_article(int ware_num_access, std::istream& in) //łączenie artykułów wewnątrz magazynu
{
    if (warehouses[ware_num_access].empty()) //warunek na niepusty magazyn
    {
        std::cout << "\n" << std::string(9, ' ') << "Warehouse state: empty." << std::endl;
    }
    else
    {
        int num_to_merge, type;
        float new_num_of_elements = 0;
        std::string name;

        //pobranie info o łączonych towarach
        std::cout << "\n" << std::string(9, ' ') << "How many Articles would you like to merge?";
        num_to_merge = read_num_ware(in);

        int tab_ID[num_to_merge]; //tablica posłuży w pętlach poniżej

        std::cout << "\n" << std::string(9, ' ') << "Give a name for new (merged) Article: ";
        name = read_string_ware(in);

        std::cout << "\n" << std::string(9, ' ') << "Type (countable <1>; liquid <2>; Loose <3>): ";
        type = read_num_ware(in);

        for (int i = 0; i < num_to_merge; ++i) //pętla do pobierania ID towarów do połączenia i ich usuwania
        {
            std::cout << "\n" << std::string(9, ' ') << "Give " << i+1 << " ID: ";
            tab_ID[i] = read_num_ware(in);

            for(int j = 0; j<warehouses[ware_num_access].size(); ++j) //pętla wyszukująca pozycję towaru o wskazanym ID
            {
                if(warehouses[ware_num_access][j]->get_ID() == tab_ID[i])
                {
                    new_num_of_elements += warehouses[ware_num_access][j]->get_num_of_items(); //łączenie liczby sztuk
                    warehouses[ware_num_access].erase(warehouses[ware_num_access].begin() + j); //usuwanie
                }
            }
        }

        Product *p; //tworzenie wskaźnika do produktu

        switch (type)
        {
            case 1:
                p = new Article(name, tab_ID[0], new_num_of_elements);
                break;
            case 2:
                p = new Liquid(name, tab_ID[0], new_num_of_elements);
                break;
            case 3:
                p = new Loose(name, tab_ID[0], new_num_of_elements);
                break;
            default:
                std::cout << "\n" << std::string(9, ' ') << "Error. Entered number is not assigned to any type."<< std::endl;
        }
        warehouses[ware_num_access].push_back(p); //dodawanie do magazynu
        std::cout << "\n" << std::string(9, ' ') << "Merging ended successfully." << std::endl;
    }
}

void Warehouse::split_article(int ware_num_access, int ware_num_create,  std::istream& in) //rozdzielanie towarów wewnątrz magazynu
{
    if (warehouses[ware_num_access].empty()) //warunek na niepusty magazyn
    {
        std::cout << "\n" << std::string(9, ' ') << "Warehouse state: empty." << std::endl;
    }
    else
    {
        int num_to_split, type, max_ID, ID;
        double new_num_of_elements;
        std::string name;

        //pobranie info o towarze do rozdzielnia
        std::cout << "\n" << std::string(9, ' ') << "Which Article do You want to split?: ";
        ID = read_num_ware(in);

        std::cout << "\n" << std::string(9, ' ') << "In how many pieces would you like to split the Article?";
        num_to_split = read_num_ware(in);

        std::cout << "\n" << std::string(9, ' ') << "Type (countable <1>; liquid <2>; Loose <3>): ";
        type = read_num_ware(in);

        Product *p; //tworzenie wskaźnika do towaru

                int k = 0;
                while (k < ware_num_create) //pętla wyznaczająca pierwszy niepusty magazyn
                {
                    if (!warehouses[k].empty())
                    {
                        break;
                    }
                    k++;
                }
                max_ID = warehouses[k][0]->get_ID(); //max_ID pierwotne

                for (int j = 1; j < warehouses[k].size(); ++j) //pętla wyszukująca max_ID
                {
                    if (max_ID < warehouses[k][j]->get_ID())
                        max_ID = warehouses[k][j]->get_ID();
                }

        for(int i = 0; i<warehouses[ware_num_access].size(); ++i) //pętla wyszukująca pozycję towaru o wskazanym ID
        {
            if(warehouses[ware_num_access][i]->get_ID() == ID)
            {
                ID = i;
                break;
            }

        }

        double old_num_of_elements = warehouses[ware_num_access][ID]->get_num_of_items(); //pobranie liczby sztuk

        for (int i = 0; i < num_to_split; ++i) //pętla łącząca towary
        {
            //pobieranie nazw dla nowych towarów
            std::cout << "\n" << std::string(9, ' ') << "Give a name for " << i + 1 << " new Article: ";
            name = read_string_ware(in);

            int z;
            do     //pętla do rozdzielania liczby towarów z puli
            {
                std::cout << "\n" << std::string(9, ' ') << "How many elements should " << i + 1
                          << " new Article have? (" << old_num_of_elements << " left): ";
                new_num_of_elements = read_num_ware(in);
                if ((new_num_of_elements > old_num_of_elements)) //warunek na nieprzekroczenie liczby sztuk
                {
                    std::cout << "\n" << std::string(9, ' ') << "There is less (" << old_num_of_elements
                              << ") pieces left.";
                    z = 1;
                }
                else { z = 2; }
            } while(z == 1);

            switch (type)
            {
                case 1:
                    p = new Article(name, max_ID + i + 1, new_num_of_elements);
                    break;
                case 2:
                    p = new Liquid(name, max_ID + i + 1, new_num_of_elements);
                    break;
                case 3:
                    p = new Loose(name, max_ID + i + 1, new_num_of_elements);
                    break;
                default:
                    std::cout << "\n" << std::string(9, ' ') << "Error. Entered number is not assigned to any type."
                              << std::endl;
            }
            old_num_of_elements -= new_num_of_elements; //zmniejszenie pozostałej liczby sztuk do rozdzielenia

            warehouses[ware_num_access].push_back(p); //dodanie wskaźnika do magazynu
        }
        for (int i = 0; i < warehouses[ware_num_access].size(); ++i)
        {
            if (warehouses[ware_num_access][i]->get_ID() == ID)
            {
                warehouses[ware_num_access].erase(warehouses[ware_num_access].begin() + i); //usunięcie wskaźnika towaru rozdzielanego
            }
        }
        std::cout << "\n" << std::string(9, ' ') << "Splitting ended successfully.";
    }
}

int Warehouse::size(int ware_num_access) const { return warehouses[ware_num_access].size(); } //pobieranie rozmiaru magazynu

int Warehouse::last_ID(int ware_num_access) const { return warehouses[ware_num_access].back()->get_ID(); } //wyznaczanie ostatniego ID

double Warehouse::read_num_ware(std::istream& in) //pobranie inta
{
        std::string line;
        getline(in, line);
        std::cout << line << std::endl;
        return atof(line.c_str());
}

std::string Warehouse::read_string_ware(std::istream& in) //pobranie stringa
{
    std::string line;
    getline(in, line);
    std::cout << line << std::endl;
    return line;
}