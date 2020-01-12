#include <greeting.hpp>

#include <thread>
#include <iostream>

namespace bulba {
void greet()
{
    std::thread{[] { std::cout << "Hello, Bulba!" << std::endl; }}.join();
}
} // namespace bulba