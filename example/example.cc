#include <muslots/muslots.h>

#include <iostream>
#include <cassert>

using namespace muslots;

void foo(int a, int b)
{
    std::cout << "foo " << a << ' ' << b << '\n';
}

int main()
{
    Signal<int, int> signal;

    // connect function ptr
    auto c1 = signal.connect(foo);

    // connect lambda
    auto c2 = signal.connect([](int a, double b) { std::cout << "lambda " << a << ' ' << b << '\n'; });

    // notify slots
    signal(3, 5);

    // disconnect
    c1.disconnect();
    assert(!c1.connected());

    // only foo should be called
    signal(4, 7);
}
