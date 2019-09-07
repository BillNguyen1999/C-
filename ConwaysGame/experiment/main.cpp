/*
 * Use this file for experimenting with your code,
 * testing things that don't work, debugging, etc.
 *
 * You can compile and run this via 'make experiment'
 *
 * This file will not be graded
 */
#include <algorithm>
#include <iostream>
#include <vector>

#include "Conway.h"

 int main() {
     Conway hello("src/input.txt");
     // hello.set_value(2, 4);
     // hello.set_value(3, 4);
     // hello.set_value(4, 4);
     // std::cout<<hello.get_matrix().size()<<"\n";
     // std::cout<<hello.get_matrix()[2][4]<<"\n";
      hello.next();
//     hello.remove_value(6, 0);
     hello.output_graphic();
     // hello.next();
     std::cout<<hello.get_matrix()[6][1]<<"\n";
     return 0;
 }
