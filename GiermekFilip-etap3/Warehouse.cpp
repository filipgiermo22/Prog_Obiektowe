
#include "Product.h"
#include "Article.h"
#include "Loose.h"
#include "Liquid.h"
#include "Warehouse.h"

#include <iostream>
#include <vector>
#include <iomanip>
#include <unistd.h>

int is_file_open;

template<typename T>
Product * switch_create_product(int type, std::string name, int ID, T quant) // tworzenie obiektu (szablon)
{
    Product *p; //tworzenie wskaźnika do produktu

    if(type == 1)
        p = new Article(name, ID, quant);
    if(type == 2)
        p = new Liquid(name, ID, quant);
    if(type == 3)
        p = new Loose(name, ID, quant);

    return p;
}

template<typename T>
inline void swap_warehouse(T &a,T &b) //zamiana obiektów (szablon) wykorzystany w procedurze poniżej
{
    T tmp=a;
    a=b;
    b=tmp;
}

void Warehouse::sort_warehouse(int ware_num_access, std::istream& in) //sortowanie magazynu
{
    if (warehouses[ware_num_access].empty()) //warunek dla pustego magazynu
    {
        std::cout << "\n" << std::string(9, ' ') << "Warehouse state: empty." << std::endl;
        sleep(2);
    }
    else
        {
        int choice, type;
        std::cout << "\n" << std::string(9, ' ') << "Would You like to sort by ID <1>, or quantity <2>: ";
        choice = read_num_ware(in);
        std::cout << "\n" << std::string(9, ' ') << "Descending <1> or ascending <different number>: ";
        type = read_num_ware(in);

        for (int i = 0; i < warehouses[ware_num_access].size(); ++i)
        {
            for (int j = i + 1; j < warehouses[ware_num_access].size(); ++j)
            {
                switch (choice)
                {
                    case 1:
                        if (warehouses[ware_num_access][i]->get_ID() < warehouses[ware_num_access][j]->get_ID())
                        {
                            if (type == 1)
                                swap_warehouse(warehouses[ware_num_access][i], warehouses[ware_num_access][j]);
                            else
                                swap_warehouse(warehouses[ware_num_access][j], warehouses[ware_num_access][i]);
                        }
                        break;
                    case 2:
                        if (warehouses[ware_num_access][i]->get_num_of_items() < warehouses[ware_num_access][j]->get_num_of_items())
                        {
                            if (type == 1)
                                swap_warehouse(warehouses[ware_num_access][i], warehouses[ware_num_access][j]);
                            else
                                swap_warehouse(warehouses[ware_num_access][j], warehouses[ware_num_access][i]);
                        }
                        break;
                    default:
                        std::cout << "\n" << std::string(9, ' ') << "Error. Entered values does not exists on the list. Try again." << std::endl;
                }
            }
        }
    }
    std::cout << "\n" << std::string(9, ' ') << "Sorting ended successfully." << std::endl;
    sleep(2);
}

int Warehouse::add_warehouses(std::istream& in) //tworzenie magazynów
{
    int ware_num_create;
    std::cout << "\n" << std::string(9, ' ') << "How many warehouses would you like to ";

    if (warehouses.empty()) { std::cout << "use?: "; } //warunek pytania gdy nie ma magazynów
    else { std::cout << "add?: "; }

    ware_num_create = read_num_ware(in);

    if(warehouses.empty() && ware_num_create == 0) //warunek na rzucanie wyjątku
        throw "\n         In order to use program properly,\n         You must create more than 0 warehouses.";
    else
    {
        for (int i = 0; i < ware_num_create; ++i)   //pętla tworzenia magazynów
        {
            warehouses.emplace_back(std::vector<Product *>());
        }
        return ware_num_create;
    }
}

void Warehouse::content_warehouse(int ware_num_access) //wypisywanie zawartości danego magazynu
{
    if (warehouses[ware_num_access].empty()) //warunek dla pustego magazynu
    {
        std::cout << "\n" << std::string(9, ' ') << "Warehouse state: empty."  << std::endl;
        sleep(2);
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
    sleep(2);
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

        int type;
        std::cout << std::string(9, ' ') << "Type (countable <1>; liquid <2>; Loose <3>): ";

        type = read_num_ware(in);  //zapisanie typu towaru (użyte w switchu w dalszej części)

        if(type != 1 && type != 2 && type != 3)
            throw std::invalid_argument("You entered wrong number."); //rzucanie obiektu invalid_argument

        for (int l = 0; l < ware_num_create; ++l)
        {
            if (!warehouses[l].empty()) //pętla znajdująca niepusty magazyn
            {
                int max_ID = warehouses[l][0]->get_ID();
                for(int d = 0; d < ware_num_create; ++d)
                {
                    for(int b = 0; b < warehouses[d].size(); ++b)
                    {
                        if (max_ID < warehouses[d][b]->get_ID())
                            max_ID = warehouses[d][b]->get_ID();
                    }
                }
                warehouses[ware_num_access].push_back(switch_create_product(type, name, max_ID + 1, 0)); //dodanie towaru do magazynu
                break;
            }
            else
            {
                warehouses[ware_num_access].push_back(switch_create_product(type, name, 0, 0)); //dodanie towaru do magazynu
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

void Warehouse::remove_product(int ID, double num_of_items, int ware_num_access) //odejmowanie sztuk towaru
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

void Warehouse::put_on_forklift(Forklift &forklift, int ware_num_access, std::istream& in) //przenoszenie towaru na paleciak (proc. 'wydaj')
{
    if (warehouses[ware_num_access].empty()) //sprawdzenie czy wektor jest niepusty
    {
        std::cout << "\n" << std::string(9, ' ') << "Warehouse number " << ware_num_access+1 << " state: empty."  << std::endl;
        sleep(2);
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
                sleep(2);
                break;
            }

        }
    }
}


void Warehouse::take_off_forklift(Forklift &forklift, int ware_num_access,  std::istream& in) //przenoszenie towaru do magazynu
{
    if (forklift.get_size() == 0) //sprawdzenie czy paleciak jest niepusty
    {
        std::cout << "\n" << std::string(9, ' ') << "Forklift state: empty."  << std::endl;
        sleep(2);
    }
    else
    {
        //pobranie ID towaru do przełożenia
        int ID;
        std::cout << "\n" << std::string(9, ' ') << "Insert info about the Article You want to take off." << std::endl;
        std::cout << std::string(9, ' ') << "ID: ";
        ID = read_num_ware(in);

        Product *p;
        p = forklift.return_object(ID);

        warehouses[ware_num_access].push_back(p); //dodanie wskaźnika do towaru z paleciaka
        forklift.erase_fork(ID); //usunięcie wskaźnika z paleciaka
        forklift.set_size(forklift.get_size() - 1, 1); //zmiana rozmiaru paleciaka
        std::cout << "\n" << std::string(9, ' ') << "Article transferred successfully." << std::endl;
        sleep(2);
    }
}


void Warehouse::merge_article(int ware_num_access, std::istream& in) //łączenie artykułów wewnątrz magazynu
{
    if (warehouses[ware_num_access].empty()) //warunek na niepusty magazyn
    {
        std::cout << "\n" << std::string(9, ' ') << "Warehouse state: empty." << std::endl;
        sleep(2);
    }
    else
    {
        int num_to_merge, type;
        float new_num_of_elements = 0;
        std::string name;

        //pobranie info o łączonych towarach
        std::cout << "\n" << std::string(9, ' ') << "How many Articles would you like to merge? ";
        num_to_merge = read_num_ware(in);

        int tab_ID[num_to_merge]; //tablica posłuży w pętlach poniżej

        std::cout << "\n" << std::string(9, ' ') << "Give a name for new (merged) Article: ";
        name = read_string_ware(in);

        std::cout << "\n" << std::string(9, ' ') << "Type (countable <1>; liquid <2>; Loose <3>): ";
        type = read_num_ware(in);

        if(type != 1 && type != 2 && type != 3)
            throw std::invalid_argument("You entered wrong number."); //rzucanie obiektu invalid_argument

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

        warehouses[ware_num_access].push_back(switch_create_product(type, name, tab_ID[0], new_num_of_elements)); //dodanie towaru do magazynu
        std::cout << "\n" << std::string(9, ' ') << "Merging ended successfully." << std::endl;
        sleep(2);
    }
}

void Warehouse::split_article(int ware_num_access, std::istream& in) //rozdzielanie towarów wewnątrz magazynu
{
    if (warehouses[ware_num_access].empty()) //warunek na niepusty magazyn
    {
        std::cout << "\n" << std::string(9, ' ') << "Warehouse state: empty." << std::endl;
        sleep(2);
    }
    else
    {
        int num_to_split, type, max_ID, ID;
        double new_num_of_elements;
        std::string name;

        //pobranie info o towarze do rozdzielnia
        std::cout << "\n" << std::string(9, ' ') << "Which Article do You want to split?: ";
        ID = read_num_ware(in);

        std::cout << "\n" << std::string(9, ' ') << "In how many pieces would you like to split the Article? ";
        num_to_split = read_num_ware(in);

        std::cout << "\n" << std::string(9, ' ') << "Type (countable <1>; liquid <2>; Loose <3>): ";
        type = read_num_ware(in);

        if(type != 1 && type != 2 && type != 3)
            throw std::invalid_argument("You entered wrong number."); //rzucanie obiektu invalid_argument

            max_ID = warehouses[ware_num_access][0]->get_ID(); //max_ID pierwotne
            for (int j = 1; j < warehouses[ware_num_access].size(); ++j) //pętla wyszukująca max_ID
                {
                    if (max_ID < warehouses[ware_num_access][j]->get_ID())
                        max_ID = warehouses[ware_num_access][j]->get_ID();
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
                    std::cout << "\n" << std::string(9, ' ') << "There is less (" << old_num_of_elements << ") pieces left.";
                    z = 1;
                }
                else { z = 2; }
            } while(z == 1);

            warehouses[ware_num_access].push_back(switch_create_product(type, name, max_ID + 1, new_num_of_elements)); //dodanie towaru do magazynu

            old_num_of_elements -= new_num_of_elements; //zmniejszenie pozostałej liczby sztuk do rozdzielenia
            max_ID += 1;
        }

        warehouses[ware_num_access].erase(warehouses[ware_num_access].begin() + ID); //usunięcie wskaźnika towaru rozdzielanego

        std::cout << "\n" << std::string(9, ' ') << "Splitting ended successfully." << std::endl;
        sleep(2);
    }
}

int Warehouse::size(int ware_num_access) const { return warehouses[ware_num_access].size(); } //pobieranie rozmiaru magazynu

int Warehouse::last_ID(int ware_num_access) const { return warehouses[ware_num_access].back()->get_ID(); } //wyznaczanie ostatniego ID

int Warehouse::first_ID(int ware_num_access) const { return warehouses[ware_num_access].front()->get_ID(); } //wyznaczanie pierwszego ID

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
    if(is_file_open == 1) { std::cout << line << std::endl; }
    return line;
}