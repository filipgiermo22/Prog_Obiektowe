//
// Created by Filip on 19.11.2020.
//
/* 
   Program "Warehouse" symuluje dzia�anie magazynu, w kt�rym skladowane s� towary.
   Program umozliwia: wypisanie listy magazynowanych towar�w, 
   dodanie nowego typu towaru oraz dodanie lub usuni�cie towar�w tego samego typu.

   Wykonany w ramach przedmiotu "Programowanie Obiektowe" AGH 2020.
*/

#include <iostream>
#include <vector>
#include <string>
#include "Article.h"
#include "Warehouse.h"

//nag��wki funkcji 
void Menu();                 
void insert_collectArticle(Warehouse *warehouse); 

int main()
{
   std::cout << "\n" << " // ==================================================== \\\\\n"
                        " ||   _    _                _                            ||\n"
                        " ||  | |  | |              | |                           ||\n"
                        " ||  | |  | | __ _ _ __ ___| |__   ___  _   _ ___  ___   ||\n"
                        " ||  | |/\\| |/ _` | '__/ _ \\ '_ \\ / _ \\| | | / __|/ _ \\  ||\n"
                        " ||  \\  /\\  / (_| | | |  __/ | | | (_) | |_| \\__ \\  __/  ||\n"
                        " ||   \\/  \\/ \\__,_|_|  \\___|_| |_|\\___/ \\__,_|___/\\___|  ||\n"
                        " ||                                                      ||\n"
                        " \\\\ ==================================================== //"
                        "\n\n                  Welcome to the Warehouse!" << std::endl;

   auto& warehouse = *new Warehouse; //referencja adresu utworzonego wektora

    int k = 1;

    while (k == 1) //p�tla (opr�cz case 4) wy�wietla menu ponownie
    {
        Menu();
       
        int choice;
        std::cout << "\n" << std::string(9, ' ') << "Choose option: ";
        std::cin >> choice;
        
        switch (choice)  //switch obs�uguj�cy Menu
        {
            case 1: warehouse.ContentWarehouse();
                    break;
            case 2: warehouse.Insert_new_type_Article();
                    break;
            case 3: insert_collectArticle(&warehouse);
                    break;
            case 4: k = 0;  //warunek przerwania p�tli while i zako�czenia programu
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
        << std::string(9, ' ') << "| 1. Check the content of the Warehouse   |\n"
        << std::string(9, ' ') << "| 2. Enter new type of Article            |\n"
        << std::string(9, ' ') << "| 3. Insert or collect Article            |\n"
        << std::string(9, ' ') << "| 4. EXIT                                 |\n"
        << std::string(9, ' ') << std::string(42, '-') << std::endl;
}

void insert_collectArticle(Warehouse *warehouse) 
{
    int ID;
    int num_of_items;
    std::string command;
    int quantity;

    int a;
    do      //p�tla sprawdzaj�ca poprawno�� komendy
    {
        a = 0;
        std::cout << "\n" << std::string(9, ' ') << "Enter what would you like to do (\"insert\" or \"collect\"): ";
        std::cin >> command;
        if (command != "insert" && command != "collect") //warunek powt�rzenia
        {
            std::cout << "\n" << std::string(9, ' ') << "Entered command does not exist. Try again.\n";
            a = 1;
        }
    } while (a == 1);

    if (warehouse->size() == 0)     
    {
        std::cout << "\n" << std::string(9, ' ') << "The Warehouse is empty. New type of Article must be entered first." << std::endl;
        return;
    }

    warehouse->ContentWarehouse();  //wypisanie listy towar�w
    
    int b = 0;
    while (b == 0) //p�tla powtarzana, gdy liczba podana przewy�sza liczbe wszystkich typ�w towaru
    {
        std::cout << "\n" << std::string(9, ' ') << "How many types of Articles do You want to";
        if (command == "insert") { std::cout << " insert: "; }
        if (command == "collect") { std::cout << " collect: "; }
            
        std::cin >> quantity;
        
        if (quantity > warehouse->size())
            std::cout << "\n" << std::string(9, ' ') << "There is less types of Articles in Warehouse than you want to move." << std::endl;
        else
            b = 1;
    }
   
    for (int i = 0; i < quantity; ++i) //p�tla podawania ID i liczby sztuk do pobrania/dodania
    {
        int c;
        do {
            c = 0;
            std::cout << "\n" << std::string(9, ' ') << "Enter ID: ";
            std::cin >> ID;
            std::cout << std::string(9, ' ') << "Enter number of items: ";
            std::cin >> num_of_items;

            if(ID > warehouse->last_ID()) //warunek sprawdzaj�cy istnienie podanego ID przez por�wnanie z ID ostatniego towaru
            {
                std::cout << "\n" << std::string(9, ' ') << "Given ID does not exists. Try again." << std::endl;
                c = 1;
            }
            
            else
            {
                if (command == "insert") { warehouse->addArticle(ID, num_of_items); }    //wywo�anie dodawania towar�w
                if (command == "collect") { warehouse->removeArticle(ID, num_of_items); }  //wywo�anie odbierania towar�w
            }

        } while (c == 1);
    }
}

