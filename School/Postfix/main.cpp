#include "Utility.h"
#include "Stack.h"
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h> //atof
#include <algorithm>

using namespace std;

char get_commandC();
string get_commandS();
bool do_commandC(char command, Stack& numbers);
bool do_commandS(string command, Stack& numbers);
void introduction(char* argv[]);
void instructions(char* argv[]);

int main(int argc, char* argv[])
/*
Post: The program has executed simple arithmetic
      commands entered by the user.
Uses: The class Stack and the functions
      introduction, instructions, do_command, and get_command.
*/

{
    if (argc == 1) {
        Stack stored_numbers;
        while (do_commandS(get_commandS(), stored_numbers));
    }
    else {
        Stack stored_numbers;
        introduction(argv);
        instructions(argv);
        while (do_commandC(get_commandC(), stored_numbers));
    }
}

void introduction(char* argv[]) {
    
    string arkv = argv[1];
    size_t foundarkv = arkv.find("-p");
    if (foundarkv != string::npos) {
        cout << "The first parameter specifies a valid calculator command." << endl;
        cout << "The command specified by the first parameter has been applied to the Stack of numbers given by the second parameter." << endl;
        cout << "A result of true is returned unless command == 'q'." << endl;
        return;
    }
    else {
        cout << "No match for given option. Exiting program." << endl;
        exit(0);
    }
}

void instructions(char* argv[]) {

    string arkv = argv[1];
    size_t foundarkv = arkv.find("-p");
    if (foundarkv != string::npos) {
        cout << "Please enter a valid command:" << endl
            << "[?]push to stack   [=]print top   [x]exchange 2 top numbers" << endl
            << "[s]sum all numbers in stack [a]average value in stack" << endl
            << "[+] [-] [*] [/] [%] [^] [v]   are arithmetic operations" << endl
            << "[Q]uit." << endl;
        return;
    }
    else {
        cout << "No match for given option. Exiting program." << endl;
        exit(0);
    }
}

string get_commandS()
{
    string command;
    bool waiting = true;

    while (waiting) {
        cin >> command;
        //cout << "get_command loopissa: " << command << endl;
        //cin.get(command);

        if (cin.get() == '\n') {
            //cout << "commandin arvo: " << command << endl;
            command += "z";
            //cout << "commandin arvo lisayksen jalkeen: " << command << endl;
            waiting = false;
        }

        transform(command.begin(), command.end(), command.begin(), ::tolower);        
        
        if (command.find('?') != string::npos || command.find('=') != string::npos || command.find('+') != string::npos ||
            command.find('-') != string::npos || command.find('*') != string::npos || command.find('/') != string::npos || 
            command.find('x') != string::npos || command.find('s') != string::npos || command.find('a') != string::npos ||
            command.find('q') != string::npos || command.find('%') != string::npos || command.find('^') != string::npos ||
            command.find('v') != string::npos && command.length() == 1) waiting = false;

        else if ( command.find_first_not_of("0123456789.") == std::string::npos ) {
            waiting = false;
        }

    }
    return command;
}

char get_commandC()
{
    char command;
    string command2;
    bool waiting = true;

    cout << "Select command and press <Enter>:";

    while (waiting) {
        cin >> command;
        command = tolower(command);
        if (command == '?' || command == '=' || command == '+' ||
            command == '-' || command == '*' || command == '/' || command == 'x' ||
            command == 's' || command == 'a' || command == 'q' ||
            command == '%' || command == '^' || command == 'v') waiting = false;


        else {

            cout << "Please enter a valid command:" << endl
                << "[?]push to stack   [=]print top   [x]exchange 2 top numbers" << endl
                << "[s]sum all numbers in stack [a]average value in stack" << endl
                << "[+] [-] [*] [/] [%] [^] [v]   are arithmetic operations" << endl
                << "[Q]uit." << endl;

        }
    }
    return command;
}

bool do_commandC(char command, Stack& numbers)
/*
Pre:  The first parameter specifies a valid calculator command.
Post: The command specified by the first parameter
      has been applied to the Stack of numbers given by the second parameter.
      A result of true is returned unless command == 'q'.
Uses: The class Stack.
*/
{
    //double p, q;
    double q = 0;
    double p = 0;
    double temp1;
    double temp2;
    int counter;
    int p1, q1;
    double calcpow;
    double numero = 0;

    if (isdigit(command)) {
        numero = ((double)command) - ((double)'0');
        command = 'y';
        cout << "numeron arvo: " << numero << endl;
    }

    switch (command) {
    case '?':
        cout << "Enter a real number: " << flush;
        cin >> p;
        if (numbers.push(p) == overflow)
            cout << "Warning: Stack full, lost number" << endl;
        break;

    case '=':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else
            cout << p << endl;
        break;

    case '+':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            numbers.pop();
            if (numbers.top(q) == underflow) {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
            }

            else {
                numbers.pop();
                if (numbers.push(q + p) == overflow)
                    cout << "Warning: Stack full, lost result" << endl;
            }
        }
        break;

        //   Add options for further user commands.
    case 'x':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            temp1 = p;
            numbers.pop();
            if (numbers.top(p) == underflow)
                cout << "Stack empty" << endl;
            else {
                temp2 = p;
                numbers.pop();
                numbers.push(temp1);
                numbers.push(temp2);
            }
        }
        break;

    case 's':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            temp1 = 0;
            while (!numbers.empty()) {
                numbers.top(p);
                temp1 += p;
                numbers.pop();
            }
            numbers.push(temp1);
        }
        break;

    case 'a':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            temp1 = 0;
            temp2 = 0;
            counter = 0;
            while (!numbers.empty()) {
                numbers.top(p);
                temp1 += p;
                numbers.pop();
                counter++;
            }
            temp2 = temp1 / counter;
            numbers.push(temp2);
        }
        break;

    case '-':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            numbers.pop();
            if (numbers.top(q) == underflow) {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
            }

            else {
                numbers.pop();
                if (numbers.push(q - p) == overflow)
                    cout << "Warning: Stack full, lost result" << endl;
            }
        }
        break;

    case '*':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            numbers.pop();
            if (numbers.top(q) == underflow) {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
            }

            else {
                numbers.pop();
                if (numbers.push(q * p) == overflow)
                    cout << "Warning: Stack full, lost result" << endl;
            }
        }
        break;

    case '/':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            numbers.pop();
            if (numbers.top(q) == underflow) {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
            }

            else {
                numbers.pop();
                if (numbers.push(q / p) == overflow)
                    cout << "Warning: Stack full, lost result" << endl;
            }
        }
        break;

    case '%':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            numbers.pop();
            if (numbers.top(q) == underflow) {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
            }

            else {
                q1 = (int)q;
                p1 = (int)p;
                numbers.pop();
                if (numbers.push(q1 % p1) == overflow)
                    cout << "Warning: Stack full, lost result" << endl;
            }
        }
        break;

    case '^':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            numbers.pop();
            if (numbers.top(q) == underflow) {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
            }

            else {
                temp1 = p;
                temp2 = q;
                numbers.pop();
                calcpow = pow(temp2, temp1);
                numbers.push(calcpow);
            }
        }

        break;

    case 'v':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            temp1 = sqrt(p);
            numbers.pop();
            numbers.push(temp1);
        }
        break;

    case 'q':
        cout << "Calculation finished.\n";
        return false;
    }

    return true;
}

bool do_commandS(string command, Stack& numbers)
/*
Pre:  The first parameter specifies a valid calculator command.
Post: The command specified by the first parameter
      has been applied to the Stack of numbers given by the second parameter.
      A result of true is returned unless command == 'q'.
Uses: The class Stack.
*/
{
    //double p, q;
    double q = 0;
    double p = 0;
    double temp1;
    double temp2;
    int counter;
    int p1, q1;
    double calcpow;
    double numero = 0;
    char command2;
    char command3;

    if (command.find_first_not_of("0123456789.") == std::string::npos) {
        numero = stod(command);
        command2 = 'y';
    }
    else if (command.length() == 2) {
        command3 = command[0];

        switch (command3) {

        case '+':
            if (numbers.top(p) == underflow)
                cout << "Stack empty" << endl;
            else {
                numbers.pop();
                if (numbers.top(q) == underflow) {
                    cout << "Stack has just one entry" << endl;
                    numbers.push(p);
                }

                else {
                    numbers.pop();
                    if (numbers.push(q + p) == overflow)
                        cout << "Warning: Stack full, lost result" << endl;
                }
            }
            break;

            //   Add options for further user commands.
        case 'x':
            if (numbers.top(p) == underflow)
                cout << "Stack empty" << endl;
            else {
                temp1 = p;
                numbers.pop();
                if (numbers.top(p) == underflow)
                    cout << "Stack empty" << endl;
                else {
                    temp2 = p;
                    numbers.pop();
                    numbers.push(temp1);
                    numbers.push(temp2);
                }
            }
            break;

        case 's':
            if (numbers.top(p) == underflow)
                cout << "Stack empty" << endl;
            else {
                temp1 = 0;
                while (!numbers.empty()) {
                    numbers.top(p);
                    temp1 += p;
                    numbers.pop();
                }
                numbers.push(temp1);
            }
            break;

        case 'a':
            if (numbers.top(p) == underflow)
                cout << "Stack empty" << endl;
            else {
                temp1 = 0;
                temp2 = 0;
                counter = 0;
                while (!numbers.empty()) {
                    numbers.top(p);
                    temp1 += p;
                    numbers.pop();
                    counter++;
                }
                temp2 = temp1 / counter;
                numbers.push(temp2);
            }
            break;

        case '-':
            if (numbers.top(p) == underflow)
                cout << "Stack empty" << endl;
            else {
                numbers.pop();
                if (numbers.top(q) == underflow) {
                    cout << "Stack has just one entry" << endl;
                    numbers.push(p);
                }

                else {
                    numbers.pop();
                    if (numbers.push(q - p) == overflow)
                        cout << "Warning: Stack full, lost result" << endl;
                }
            }
            break;

        case '*':
            if (numbers.top(p) == underflow)
                cout << "Stack empty" << endl;
            else {
                numbers.pop();
                if (numbers.top(q) == underflow) {
                    cout << "Stack has just one entry" << endl;
                    numbers.push(p);
                }

                else {
                    numbers.pop();
                    if (numbers.push(q * p) == overflow)
                        cout << "Warning: Stack full, lost result" << endl;
                }
            }
            break;

        case '/':
            if (numbers.top(p) == underflow)
                cout << "Stack empty" << endl;
            else {
                numbers.pop();
                if (numbers.top(q) == underflow) {
                    cout << "Stack has just one entry" << endl;
                    numbers.push(p);
                }

                else {
                    numbers.pop();
                    if (numbers.push(q / p) == overflow)
                        cout << "Warning: Stack full, lost result" << endl;
                }
            }
            break;

        case '%':
            if (numbers.top(p) == underflow)
                cout << "Stack empty" << endl;
            else {
                numbers.pop();
                if (numbers.top(q) == underflow) {
                    cout << "Stack has just one entry" << endl;
                    numbers.push(p);
                }

                else {
                    q1 = (int)q;
                    p1 = (int)p;
                    numbers.pop();
                    if (numbers.push(q1 % p1) == overflow)
                        cout << "Warning: Stack full, lost result" << endl;
                }
            }
            break;

        case '^':
            if (numbers.top(p) == underflow)
                cout << "Stack empty" << endl;
            else {
                numbers.pop();
                if (numbers.top(q) == underflow) {
                    cout << "Stack has just one entry" << endl;
                    numbers.push(p);
                }

                else {
                    temp1 = p;
                    temp2 = q;
                    numbers.pop();
                    calcpow = pow(temp2, temp1);
                    numbers.push(calcpow);
                }
            }

            break;

        case 'v':
            if (numbers.top(p) == underflow)
                cout << "Stack empty" << endl;
            else {
                temp1 = sqrt(p);
                numbers.pop();
                numbers.push(temp1);
            }
            break;
        }

        if (command[1] == 'z') {
            command2 = '=';
        }
    }
    else {
        command2 = command[0];
    }

    switch (command2) {
    case '?':
        cin >> p;
        if (numbers.push(p) == overflow)
            cout << "Warning: Stack full, lost number" << endl;
        break;

    case '=':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else
            cout << p << endl;
        break;

    case '+':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            numbers.pop();
            if (numbers.top(q) == underflow) {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
            }

            else {
                numbers.pop();
                if (numbers.push(q + p) == overflow)
                    cout << "Warning: Stack full, lost result" << endl;
            }
        }
        break;

        //   Add options for further user commands.
    case 'x':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            temp1 = p;
            numbers.pop();
            if (numbers.top(p) == underflow)
                cout << "Stack empty" << endl;
            else {
                temp2 = p;
                numbers.pop();
                numbers.push(temp1);
                numbers.push(temp2);
            }
        }
        break;

    case 's':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            temp1 = 0;
            while (!numbers.empty()) {
                numbers.top(p);
                temp1 += p;
                numbers.pop();
            }
            numbers.push(temp1);
        }
        break;

    case 'a':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            temp1 = 0;
            temp2 = 0;
            counter = 0;
            while (!numbers.empty()) {
                numbers.top(p);
                temp1 += p;
                numbers.pop();
                counter++;
            }
            temp2 = temp1 / counter;
            numbers.push(temp2);
        }
        break;

    case '-':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            numbers.pop();
            if (numbers.top(q) == underflow) {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
            }

            else {
                numbers.pop();
                if (numbers.push(q - p) == overflow)
                    cout << "Warning: Stack full, lost result" << endl;
            }
        }
        break;

    case '*':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            numbers.pop();
            if (numbers.top(q) == underflow) {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
            }

            else {
                numbers.pop();
                if (numbers.push(q * p) == overflow)
                    cout << "Warning: Stack full, lost result" << endl;
            }
        }
        break;

    case '/':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            numbers.pop();
            if (numbers.top(q) == underflow) {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
            }

            else {
                numbers.pop();
                if (numbers.push(q / p) == overflow)
                    cout << "Warning: Stack full, lost result" << endl;
            }
        }
        break;

    case '%':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            numbers.pop();
            if (numbers.top(q) == underflow) {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
            }

            else {
                q1 = (int)q;
                p1 = (int)p;
                numbers.pop();
                if (numbers.push(q1 % p1) == overflow)
                    cout << "Warning: Stack full, lost result" << endl;
            }
        }
        break;

    case '^':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            numbers.pop();
            if (numbers.top(q) == underflow) {
                cout << "Stack has just one entry" << endl;
                numbers.push(p);
            }

            else {
                temp1 = p;
                temp2 = q;
                numbers.pop();
                calcpow = pow(temp2, temp1);
                numbers.push(calcpow);
            }
        }

        break;

    case 'v':
        if (numbers.top(p) == underflow)
            cout << "Stack empty" << endl;
        else {
            temp1 = sqrt(p);
            numbers.pop();
            numbers.push(temp1);
        }
        break;


    case 'q':
        cout << "Calculation finished.\n";
        return false;

    case 'y':
        if (numbers.push(numero) == overflow)
            cout << "Warning: Stack full, lost number" << endl;
        break;

    }


    return true;
}