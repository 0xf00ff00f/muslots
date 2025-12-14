#pragma once

#include <algorithm>
#include <concepts>
#include <memory>
#include <list>

namespace muslots
{

class Disconnectable
{
public:
    virtual ~Disconnectable() = default;

    virtual void disconnect() = 0;
};

class Connection
{
public:
    using DisconnectablePtr = std::weak_ptr<Disconnectable>;

    Connection() = default;

    explicit Connection(DisconnectablePtr ptr)
        : m_ptr(ptr)
    {
    }

    bool connected() const { return !m_ptr.expired(); }

    void disconnect()
    {
        if (auto ptr = m_ptr.lock())
            ptr->disconnect();
    }

private:
    DisconnectablePtr m_ptr;
};

template<typename... Args>
class Signal;

template<typename... Args>
class SlotBase : public Disconnectable
{
public:
    using SignalT = Signal<Args...>;

    explicit SlotBase(SignalT *signal)
        : m_signal(signal)
    {
    }

    void disconnect() override { m_signal->disconnect(this); }

    virtual void invoke(Args... args) = 0;

private:
    SignalT *m_signal;
};

template<typename Handler, typename... Args>
    requires std::invocable<Handler, Args...>
class Slot : public SlotBase<Args...>
{
public:
    explicit Slot(Signal<Args...> *signal, const Handler &handler)
        : SlotBase<Args...>(signal)
        , m_handler(handler)
    {
    }

    void invoke(Args... args) override { m_handler(args...); }

private:
    Handler m_handler;
};

template<typename... Args>
class Signal
{
public:
    template<typename Handler>
        requires std::invocable<Handler, Args...>
    Connection connect(const Handler &handler)
    {
        using Slot = Slot<std::decay_t<Handler>, Args...>;
        auto slot = std::make_shared<Slot>(this, handler);
        Connection c(slot);
        m_slots.push_back(std::move(slot));
        return c;
    }

    void disconnect(Disconnectable *d)
    {
        std::erase_if(m_slots, [d](auto &slot) { return slot.get() == d; });
    }

    template<typename... Ts>
    void operator()(Ts &&...args)
    {
        auto it = m_slots.begin();
        while (it != m_slots.end())
        {
            auto next = std::next(it);
            (*it)->invoke(std::forward<Ts>(args)...);
            it = next;
        }
    }

private:
    std::list<std::shared_ptr<SlotBase<Args...>>> m_slots;
};

} // namespace muslots
