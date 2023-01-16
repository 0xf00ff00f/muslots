A minimal signal/slot library.

There are many like it, but this one is mine. In a real project you probably want to use something like [sigslot](https://github.com/palacaze/sigslot) instead.

## Example

    void foo(int a, int b) { }
    
    int main()
    {
        Signal<int, int> signal;
    
        // connect function ptr
        auto c1 = signal.connect(foo);
    
        // connect lambda
        auto c2 = signal.connect([](int a, double b) { });
    
        // notify slots
        signal(3, 5);
    
        // disconnect
        c1.disconnect();
        assert(!c1.connected());
    
        // only foo should be called
        signal(4, 7);
    }
