#include <bits/stdc++.h>
using namespace std;

class symbol_table
{
private:
    //vector containing the symbol strings
    vector<string> symbol = {"SP", "LCL", "ARG", "THIS", "THAT", "R0", "R1",
                             "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9",
                             "R10", "R11", "R12", "R13", "R14", "R15",
                             "SCREEN", "KBD"};
    //vector containing the address integers
    vector<int> address = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                           11, 12, 13, 14, 15, 16384, 24576};

public:
    //constructor
    symbol_table(){};

    //adds a new entry to the symbol table
    void add_entry(string _symbol, int _address)
    {
        symbol.push_back(_symbol);
        address.push_back(_address);
    }

    //if the passed string is present in the vector, returns bool and the 
    //index of the string
    pair<bool, int> contains(string _symbol)
    {
        int i = 0;
        while (i < symbol.size())
        {
            if (symbol[i] == _symbol)
            {
                return make_pair(true, i);
            }
            ++i;
        }
        return make_pair(false, -1);
    }

    //returns the address integer of the passed string
    int get_address(string _symbol)
    {
        pair<bool, int> flag = contains(_symbol);
        if (flag.first == true)
        {
            return address[flag.second];
        }
        return -1;
    }
};