#include <thread>
#include <iostream>

int main()
{
    std::thread{[] { std::cout << "Hello, Bulba!" << std::endl; }}.join();
    return 0;
}
