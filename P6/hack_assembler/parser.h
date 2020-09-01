#include <bits/stdc++.h>
#include <fstream>
#include <regex>
using namespace std;

class parser
{
    //the file to be parsed
    ifstream source_code;

    //this stores the line read from ifstream on last call of function advance
    string current_command;

public:
    //the possible command types of current command
    enum command_type
    {
        A_COMMAND,
        C_COMMAND,
        L_COMMAND,
        COMMENT,
        BLANK_LINE
    };

    //parameterized constructor
    parser(char *_filename)
    {
        source_code.open(_filename);
        current_command = "";
    }

    //true until EOF of the source file is reached
    bool has_more_commands()
    {
        if (source_code)
        {
            return true;
        }
        return false;
    }

    //gets a line from the source code file
    void advance()
    {
        if (has_more_commands())
        {
            getline(source_code, current_command);
        }
    }

    //Returns the command type using regular expressions
    command_type command_type()
    {
        //finds lines containing C-command
        regex c_command_exp("([,A,M,D](=|=!|=-))|((!||-)[0,1,A,M,D](;)(J|))");
        //finds lines containing A-command
        regex a_command_exp("@(\\w*)");
        //finds lines containing L-command or pseudo-command
        regex l_command_exp("(\\()(\\w*)");
        //finds single line comments
        regex comment_exp("(^/{2})");

        //this creates a match object for all types
        //matches contains the captured strings from the target string
        smatch c_matches, a_matches, l_matches, comment_matches;

        //not using regex_match because it only returns true if the whole
        //line matches

        //regex_search will store the matches in the matches object
        regex_search(current_command, c_matches, c_command_exp);
        regex_search(current_command, a_matches, a_command_exp);
        regex_search(current_command, l_matches, l_command_exp);
        regex_search(current_command, comment_matches, comment_exp);

        //if the number of matches for a particular type are more than 0 then
        //this means that the line contains that type

        if (comment_matches.size() > 0)
        {
            return COMMENT;
        }
        else if (c_matches.size() > 0)
        {
            return C_COMMAND;
        }
        else if (a_matches.size() > 0)
        {
            return A_COMMAND;
        }
        else if (l_matches.size() > 0)
        {
            return L_COMMAND;
        }
        else
        {
            return BLANK_LINE;
        }
    }

    //returns the symbol if the current command is an A-command
    string symbol()
    {
        string command_symbol;
        if (command_type() == A_COMMAND)
        {
            //captures alphanumeric characters which are preceded by @
            regex a_command_exp("@(\\w*)");
            smatch matches;
            regex_search(current_command, matches, a_command_exp);
            return matches.str(1);
        }
        else if (command_type() == L_COMMAND)
        {
            //captures alphanumeric characters which are preceded by '('
            regex l_command_exp("(\\()(\\w*)");
            smatch matches;
            regex_search(current_command, matches, l_command_exp);
            return matches.str(2);
        }
        else
        {
            return "";
        }
    }

    //returns the destination string from the current command
    string dest()
    {
        regex dest_exp("([AMD]*)(=)");
        smatch matches;
        regex_search(current_command, matches, dest_exp);
        if (matches.size() > 0)
        {
            return matches.str(1);
        }
        return "";
    }

    //returns the compute string if the current command
    string comp()
    {
        //there can be two types of the comp string "dest=comp" and "comp;jmp"
        //both are handled differently type determiner determines the type
        //of comp string
        regex type_determiner(";");
        regex comp_type_1("=([\\S]*)");
        regex comp_type_2("([\\S]*);");

        smatch type_determiner_matches;
        regex_search(current_command, type_determiner_matches, type_determiner);

        smatch return_matches;
        if (type_determiner_matches.size() > 0)
        {
            regex_search(current_command, return_matches, comp_type_2);
            return return_matches.str(1);
        }
        regex_search(current_command, return_matches, comp_type_1);
        return return_matches.str(1);
    }

    //returns the jump symbol from the current command
    string jump()
    {
        regex jump_exp(";(J\\w*)");
        smatch jump_matches;
        regex_search(current_command, jump_matches, jump_exp);
        if (jump_matches.size() > 0)
        {
            return jump_matches.str(1);
        }
        return "";
    }
};