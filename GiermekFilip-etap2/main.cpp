
/* 
   Program "Warehouse Inc." symuluje działanie magazynu, w którym skladowane są towary.
   Program umożliwia: tworzenie wielu magazynów jednocześnie, wypisanie listy magazynowanych towarów,
   dodanie nowego typu towaru, dodanie lub usunięcie towarów tego samego typu, rozdzielanie i
   łączenie towarów, oraz przenoszenie towarów między magazynami a paleciakiem.

   Wykonany w ramach przedmiotu "Programowanie Obiektowe" AGH 2020.
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Article.h"
#include "Warehouse.h"


//nagłówki funkcji 
void Menu();                 
void insert_collect_article(Warehouse &warehouses, int ware_num_access, std::istream& in);
double read_num(std::istream &in);

int main(int argc, char* argv[])
{
    std::ifstream f;
    if (argc >= 2) { //pętla sprawdzania, czy czytanie z pliku jest możliwe
        f.open(argv[1]);
    }
    std::istream& in = (argc >= 2) ? f : std::cin;

   std::cout << "\n" << " // ======================================================== \\\\\n"
                        " ||   _    _                _                                ||\n"
                        " ||  | |  | |              | |                               ||\n"
                        " ||  | |  | | __ _ _ __ ___| |__   ___  _   _ ___  ___       ||\n"
                        " ||  | |/\\| |/ _` | '__/ _ \\ '_ \\ / _ \\| | | / __|/ _ \\      ||\n"
                        " ||  \\  /\\  / (_| | | |  __/ | | | (_) | |_| \\__ \\  __/      ||\n"
                        " ||   \\/  \\/ \\__,_|_|  \\___|_| |_|\\___/ \\__,_|___/\\___| Inc. ||\n"
                        " ||                                                          ||\n"
                        " \\\\ ======================================================== //"
                        "\n\n                  * Welcome to the Warehouse! *" << std::endl;

    //wskaźniki do wektora magazynów i paleciaka
    auto *warehouses = new Warehouse;
    auto *forklift = new Forklift;

    int ware_num_create = 0;
    ware_num_create += warehouses->add_warehouses(in); //wywołanie funkcji dodania magazynów i zwiększenie zmiennej

    int k = 1;
    while (k == 1) //pętla (oprócz case 10) wyświetla Menu ponownie
    {
        Menu();
       
        int choice;
        int ware_num_access;

        //pobranie wybranej  pozycji z Menu
        std::cout << "\n" << std::string(9, ' ') << "Choose option: ";
        choice = read_num(in);

        //blok warunkowy z pytanie o wskazanie magazynu (jeśli jest więcej niż 1)
        if(choice == 1 || choice == 3 || choice == 4 || choice == 5 || choice == 6 || choice == 8 || choice == 9)
        {
            int g;
            do {
                g = 0;
                if (ware_num_create == 1) { //przerwanie gdy jest tylko 1 magazyn
                    ware_num_access = 1;
                    break;
                }

                //blok wskazywania magazynu (sprawdzenie czy istnieje)
                std::cout << "\n" << std::string(9, ' ') << "Choose warehouse (" << ware_num_create << " available): ";
                ware_num_access = read_num(in);
                if (ware_num_access > ware_num_create) {
                    std::cout << "\n" << std::string(9, ' ') << "There is less (" << ware_num_create
                              << ") warehouses available! Try again." << std::endl;
                    g = 1;
                }
            } while (g == 1);

            ware_num_access -= 1;
        }

        switch (choice)  //switch obsługujący Menu
        {
            case 1: warehouses->content_warehouse(ware_num_access);
                    break;
            case 2: ware_num_create += warehouses->add_warehouses(in);
                    break;
            case 3: warehouses->insert_new_type_product(ware_num_access, ware_num_create, in);
                    break;
            case 4: insert_collect_article(*warehouses, ware_num_access, in);
                    break;
            case 5: warehouses->merge_article(ware_num_access, in);
                    break;
            case 6: warehouses->split_article(ware_num_access, ware_num_create, in);
                    break;
            case 7: forklift->content_forklift();
                    break;
            case 8: warehouses->put_on_forklift(*forklift, ware_num_create, ware_num_access, in);
                    break;
            case 9: //warehouses->take_off_forklift(*forklift, ware_num_access, in);
                    break;
            case 10: k = 0;  //warunek przerwania pętli while i zakończenia programu
                    std::cout << "\n" << std::string(9, ' ') << "Thank you for using our Warehouse!\n";
                    break;
            default: std::cout << "\n" << std::string(9, ' ') << "Error. Entered values does not exists on the list. Try again." << std::endl;
        }
    }
    return 0;
}

void Menu()
{
    std::cout << "\n" << std::string(16, ' ') << "       --- MENU ---        \n"
        << std::string(9, ' ') << std::string(42, '-') << std::endl
        << std::string(9, ' ') << "|    Warehouse                           |\n"
        << std::string(9, ' ') << "| 1. Check the content                   |\n"
        << std::string(9, ' ') << "| 2. Add new Warehouse                   |\n"
        << std::string(9, ' ') << "| 3. Enter new type of Article           |\n"
        << std::string(9, ' ') << "| 4. Insert or collect Article           |\n"
        << std::string(9, ' ') << "| 5. Merge Articles                      |\n"
        << std::string(9, ' ') << "| 6. Split the Article                   |\n"
        << std::string(9, ' ') << "|                                        |\n"
        << std::string(9, ' ') << "|    Forklift                            |\n"
        << std::string(9, ' ') << "| 7. Check the content                   |\n"
        << std::string(9, ' ') << "| 8. Put Article on the Forklift         |\n"
        << std::string(9, ' ') << "| 9. Take Article off (doesn't work)     |\n"
        << std::string(9, ' ') << "|                                        |\n"
        << std::string(9, ' ') << "| 10. EXIT                               |\n"
        << std::string(9, ' ') << std::string(42, '-') << std::endl;
}

void insert_collect_article(Warehouse &warehouses, int ware_num_access, std::istream& in)
{
    int ID, quantity;
    float num_of_items;

    if (warehouses.size(ware_num_access) == 0)
    {
        std::cout << "\n" << std::string(9, ' ') << "The Warehouse is empty. New type of Article must be entered first." << std::endl;
        return;
    }

    int command;

    int a;
    do      //pętla sprawdzająca poprawność komendy
    {
        a = 0;
        std::cout << "\n" << std::string(9, ' ') << "Enter what would you like to do (insert <1> or collect <0>): ";
        command = read_num(in);
        if (command != 1 && command != 0) //warunek powtórzenia
        {
            std::cout << "\n" << std::string(9, ' ') << "Entered command does not exist. Try again.\n";
            a = 1;
        }
    } while (a == 1);

    warehouses.content_warehouse(ware_num_access);  //wypisanie listy towarów
    
    int b = 0;
    while (b == 0) //pętla powtarzana, gdy liczba podana przewyższa liczbe wszystkich typów towaru
    {
        if(warehouses.size(ware_num_access) > 1)
        {
            std::cout << "\n" << std::string(9, ' ') << "How many types of Articles do You want to";
            if (command == 1) { std::cout << " insert: "; }
            if (command == 0) { std::cout << " collect: "; }

            quantity = read_num(in);
        
            if (quantity > warehouses.size(ware_num_access))
                std::cout << "\n" << std::string(9, ' ') << "There is less types of Articles in Warehouse than you want to access." << std::endl;
            else
                b = 1;
        }
        else { quantity = 1; b = 1;}
    }
   
    for (int i = 0; i < quantity; ++i) //pętla podawania ID i liczby sztuk do pobrania/dodania
    {
        int c;
        do {
            c = 0;
            std::cout << "\n" << std::string(9, ' ') << "Enter ID: ";
            ID = read_num(in);
            std::cout << std::string(9, ' ') << "Enter number of items (to three decimal places): ";
            num_of_items = read_num(in);

            if(ID > warehouses.last_ID(ware_num_access)) //warunek sprawdzający istnienie podanego ID przez porównanie z ID ostatniego towaru
            {
                std::cout << "\n" << std::string(9, ' ') << "Given ID does not exists. Try again." << std::endl;
                c = 1;
            }
            
            else
            {
                if (command == 1) { warehouses.add_product(ID, num_of_items, ware_num_access); }    //wywołanie dodawania towarów
                if (command == 0) { warehouses.remove_product(ID, num_of_items, ware_num_access); }  //wywołanie odbierania towarów
            }

        } while (c == 1);
    }
}

double read_num(std::istream& in)  //funkcja pobrania inta
{
    std::string line;
    getline(in, line);
    std::cout << line << std::endl;
    return atof(line.c_str());
}
