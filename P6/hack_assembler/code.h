#include <bits/stdc++.h>
using namespace std;

//vector containing the dest symbols
vector<string> dest_mnemonic = {"", "M", "D", "MD", "A", "AM", "AD", "AMD"};

//vector containing the jump symbols
vector<string> jump_mnemonic = {"", "JGT", "JEQ", "JGE", "JLT", "JNE", "JLE",
                                "JMP"};

//vector containing the comp symbols
vector<string> comp_mnemonic = {"0", "1", "-1", "D", "A", "M", "!D", "!A", "!M",
                                "-D", "-A", "-M", "D+1", "A+1", "M+1", "D-1",
                                "A-1", "M-1", "D+A", "D+M", "D-A", "D-M", "A-D",
                                "M-D", "D&A", "D&M", "D|A", "D|M"};

//search for the input_bit string in a vector of strings and return its index 
int search(vector<string> strings, string input_bit)
{
    int i;
    for (i = 0; i < sizeof(strings); ++i)
    {
        if (strings[i] == input_bit)
        {
            return i;
        }
    }
    return -1;
}

//converts the dest symbol to bits 
bitset<3> dest(string dest_str)
{
    bitset<3> bset(search(dest_mnemonic, dest_str));
    return bset;
}

//converts the jump symbol to bits
bitset<3> jump(string jump_str)
{
    bitset<3> bset(search(jump_mnemonic, jump_str));
    return bset;
}

//converts the comp symbol to bits
bitset<7> comp(string comp_str)
{
    //index of the input string in the comp vector
    int index = search(comp_mnemonic, comp_str);
    string binary_str;

    //switches index and sets the string to a binary string 
    switch (index)
    {
    case (0):
        binary_str = "0101010"; //0
        break;
    case (1):
        binary_str = "0111111"; //1
        break;
    case (2):
        binary_str = "0111010"; //-1
        break;
    case (3):
        binary_str = "0001100"; //D
        break;
    case (4):
        binary_str = "0110000"; //A
        break;
    case (5):
        binary_str = "1110000"; //M
        break;
    case (6):
        binary_str = "0001101"; //!D
        break;
    case (7):
        binary_str = "0110001"; //!A
        break;
    case (8):
        binary_str = "1110001"; //!M
        break;
    case (9):
        binary_str = "0001111"; //-D
        break;
    case (10):
        binary_str = "0110011"; //-A
        break;
    case (11):
        binary_str = "1110011"; //-M
        break;
    case (12):
        binary_str = "0011111"; //D+1
        break;
    case (13):
        binary_str = "0110111"; //A+1
        break;
    case (14):
        binary_str = "1110111"; //M+1
        break;
    case (15):
        binary_str = "0001110"; //D-1
        break;
    case (16):
        binary_str = "0110010"; //A-1
        break;
    case (17):
        binary_str = "1110010"; //M-1
        break;
    case (18):
        binary_str = "0000010"; //D+A
        break;
    case (19):
        binary_str = "1000010"; //D+M
        break;
    case (20):
        binary_str = "0010011"; //D-A
        break;
    case (21):
        binary_str = "1010011"; //D-M
        break;
    case (22):
        binary_str = "0000111"; //A-D
        break;
    case (23):
        binary_str = "1000111"; //M-D
        break;
    case (24):
        binary_str = "0000000"; //D&A
        break;
    case (25):
        binary_str = "1000000"; //D&M
        break;
    case (26):
        binary_str = "0010101"; //D|A
        break;
    case (27):
        binary_str = "1010101"; //D|M
        break;
    default:
        binary_str = "-1";
    }

    //converts the binary string to bits
    bitset<7> bset(binary_str);
    return bset;
}