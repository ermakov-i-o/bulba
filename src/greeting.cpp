#include <bulba/greeting.hpp>

#include <thread>
#include <iostream>

#ifdef POTATO_BULBA_EXPORT_SYMBOL
#error 1
#else
#error 2
#endif

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
