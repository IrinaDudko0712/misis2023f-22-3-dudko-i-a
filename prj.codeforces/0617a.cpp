#include <iostream>
#include <string>
int main()
{
    int x;
   std:: cin >> x;
    int numb = 0;
    if (x / 5 != 0)
    {
        if (x % 5 == 0)
            numb = x / 5;
        else
            numb = x / 5 + 1;
    }
    else {
        numb = 1;
    }
    std::cout << numb << std::endl;
}
