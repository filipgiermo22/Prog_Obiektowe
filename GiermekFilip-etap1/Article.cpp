//
// Created by Filip on 19.11.2020.
//

#include <iostream>
#include <string>
#include "Article.h"

int Article::get_ID() { return ID; }

int Article::get_num_of_items() { return num_of_items; }

std::string Article::get_Name() { return Name; }

void Article::set_num_of_items(int n_num_of_items) { this->num_of_items = n_num_of_items; }


