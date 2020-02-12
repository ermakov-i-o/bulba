#include <bulba/greeting.hpp>

#include <thread>
#include <iostream>

namespace bulba {

POTATO_BULBA_EXPORT void greet(std::string name)
{
    std::thread{[name = std::move(name)]
        {
            std::cout << "Hello, " << name << '!' << std::endl;
        }
    }.join();
}

} // namespace bulba
