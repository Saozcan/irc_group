// C++ program to illustrate std::istringstream
// when string has integer followed by character
#include <iostream>
#include <sstream>
#include <string>
using std::istringstream;
using std::string;
using std::cout;

// Driver Code
int main()
{
    // Input string
    string str("Ahmet mehmet ali");

    // Object class of istringstream
    istringstream my_stream(str);

    string a;
    string b;
    string c;
    string d;

    my_stream >> a >> b >> c >> d;

    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;


    return 0;
}