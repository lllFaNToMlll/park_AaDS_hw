#include <iostream>
#include <sstream>
#include <assert.h>
/*
Подсчитать кол-во единичных бит в входном числе , стоящих на четных позициях.
Позиции битов нумеруются с 0.
Необходимо использование битовых операций.
Использование арифметических операций запрещено.
 */

void countUnitsAtEven(std::istream& in, std::ostream& out) {
    int counter = 0, userInput = 0;
    in >> userInput;
    while (userInput) {
        if (userInput & 1) {
            counter++;
        }
        userInput >>= 2;
    }
    out << counter << std::endl;
}

void testLogic() {
    {
        std::stringstream in;
        std::stringstream out;
        in << 1 << std::endl;
        countUnitsAtEven(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "1\n");
    }

    {
        std::stringstream in;
        std::stringstream out;
        in << 255 << std::endl;
        countUnitsAtEven(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "4\n");
    }

    {
        std::stringstream in;
        std::stringstream out;
        in << 5 << std::endl;
        countUnitsAtEven(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "2\n");
    }

    {
        std::stringstream in;
        std::stringstream out;
        in << 25 << std::endl;
        countUnitsAtEven(in, out);
        std::cout << out.str() << std::endl;
        assert(out.str() == "2\n");
    }
}

int main() {
    countUnitsAtEven(std::cin,std::cout);
    //testLogic();
    return 0;
}
