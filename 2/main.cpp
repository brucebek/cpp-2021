#include <fstream>
#include "Calculator.h"
#include "exceptions.h"


void run_commands(std::istream &input)
{
    Calculator calculator;
    std::string raw_command;
    while(std::getline(input, raw_command))
    {
        calculator.perform(raw_command);
    }

}


int main(int argc, char *argv[]){
    try
    {
        if(argc == 1)
        {
            run_commands(std::cin);
        }
        else if(argc == 2)
        {

            std::ifstream file;
            file.exceptions ( std::ifstream::badbit );
            file.open(argv[1]);
            run_commands(file);
            file.close();
        }
        else
        {
            throw UnexpectedArgumentsException();
        }
    }
    catch(CalculatorException &e)
    {
        std::cerr << e.what() << std::endl;
        return e.code;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}