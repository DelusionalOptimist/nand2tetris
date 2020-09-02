/*  
    This is the file that you'll compile in order to use the assembler.
    Pass the file containing the assembly source code as an argument while 
    executing the binary. The machine code will be stored in a file named 
    out.hack.
*/
#include <bits/stdc++.h>
#include <regex>
#include <bitset>
#include <fstream>
#include "symbol_table.h"
#include "parser.h"
#include "code.h"

using namespace std;

int main(int argc, char *argv[])
{
    //creates a symbol table object
    symbol_table s_table;

    //creates a parser object for the first pass of source file
    parser first_pass(*++argv);

    //this will be used to store the rom address of pseudo-commands in the
    //symbol table
    int rom_address = 0;

    /*
    first pass: reads from the source file and stores the symbol and rom 
    address of a pseudo-command in the symbol table
    */
    while (first_pass.has_more_commands())
    {
        first_pass.advance();

        //adds the pseudo-command to the symbol table
        if (first_pass.command_type() == first_pass.L_COMMAND)
        {
            s_table.add_entry(first_pass.symbol(), rom_address);
        }

        //if the command type is an A or C-command, increments the rom-address by 1
        if (first_pass.command_type() == first_pass.C_COMMAND || first_pass.command_type() == first_pass.A_COMMAND)
        {
            ++rom_address;
        }
    }

    //new object for the second pass
    parser second_pass(*argv);

    //this is the memory address allocated to user-defined variables found in
    //the second pass. Memory allocation begins from the 16th ram address.
    int ram_address = 16;

    //opens a file which will contain the translated code
    ofstream out;
    out.open("out.hack");

    /*
    second pass: 
    
    -Reads the source code line by line, translates the program and
     store it in the destination file.
    
    -If an A-command is encountered which is present in the symbol 
     table then it implies that is a reference to the label. So, 
     replace it with the address from the symbol table and translate 
     the integer address to binary and write to destination file.
    
    -If the encountered A-command is binary then just translate to 
     binary and write to destination file.
    
    -If the encountered command is a C-command then
     bit[15] = 1 (opcode) and bit[13..14] = true (useless bits).
     Translate the remaining command to binary using the functions
     defined in the code.h module and write the binary code to 
     destination file.
    */

    while (second_pass.has_more_commands())
    {
        second_pass.advance();
        if (second_pass.command_type() == second_pass.A_COMMAND)
        {
            regex a_command_type_check("([0-9]*)");

            if (!regex_match(second_pass.symbol(), a_command_type_check))
            {
                pair<bool, int> symbol_address = s_table.contains(second_pass.symbol());
                if (symbol_address.first)
                {
                    bitset<16> bit_converted(s_table.get_address(second_pass.symbol()));
                    out << bit_converted << endl;
                }
                else
                {
                    s_table.add_entry(second_pass.symbol(), ram_address);
                    ++ram_address;
                    bitset<16> bit_converted(s_table.get_address(second_pass.symbol()));
                    out << bit_converted << endl;
                }
            }
            else
            {
                int a_command_converted_to_int = stoi(second_pass.symbol());
                bitset<16> bit_converted(a_command_converted_to_int);
                out << bit_converted << endl;
            }
        }

        if (second_pass.command_type() == second_pass.C_COMMAND)
        {
            bitset<3> op_code_bits(string("111"));
            out << op_code_bits << comp(second_pass.comp()) << dest(second_pass.dest()) << jump(second_pass.jump()) << endl;
        }
    }

    return 0;
}