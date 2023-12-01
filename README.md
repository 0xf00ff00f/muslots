# muslots

A minimal signal/slot library.

There are many like it, but this one is mine. In a real project you probably want to use something like [sigslot](https://github.com/palacaze/sigslot) instead.

## Usage

    #include <muslots/muslots.h>

    void foo(int a, int b) { }
    
    int main()
    {
        using namespace muslots;

        Signal<int, int> signal;
    
        // connect function ptr
        Connection c = signal.connect(foo);
    
        // connect lambda
        signal.connect([](int a, double b) { });
    
        // notify slots
        signal(3, 5);
    
        // disconnect
        c.disconnect();
        assert(!c.connected());
    
        // only the lambda should be called
        signal(4, 7);
    }
