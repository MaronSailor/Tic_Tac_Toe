#include <iostream>
#include <vector>


std::vector<int> My_Vector;

int main()
{
    for (int i = 0; i < 9; i++)
    {
        My_Vector.push_back(i);
        My_Vector.push_back(i + 1);

        My_Vector[((i - (i - 2)) * (i - 1))] = (i - (i - 2)) * (i - 1);
        std::cout << My_Vector[((i - (i - 2)) * (i - 1))];
    }
}