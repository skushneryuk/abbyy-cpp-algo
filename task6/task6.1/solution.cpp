#include <coroutine>
#include <iostream>

using namespace std;

struct ReturnObject {
    struct promise_type {
        ReturnObject get_return_object() {
            return {
                .h_ = std::coroutine_handle<promise_type>::from_promise(*this)
            };
        }

        std::suspend_never initial_suspend() {
            return {};
        }

        std::suspend_never final_suspend() noexcept {
            return {};
        }

        void unhandled_exception() {}
        void return_void() {}
    };

    std::coroutine_handle<promise_type> h_;
};


struct Awaiter {
    std::coroutine_handle<> *hp_;

    constexpr bool await_ready() const noexcept {
        return false;
    }

    void await_suspend(std::coroutine_handle<> h) {
        *hp_ = h;
    }

    constexpr void await_resume() const noexcept {}
};


ReturnObject FriendlyCoroutine(std::coroutine_handle<> *continuation_out) {
    Awaiter a{continuation_out};
    co_await a;
        
    std::cout << "Hello World!" << endl;
    co_await a;

    std::cout << "I am Coroutine!" << endl;
    co_await a;

    std::cout << "Nice to meet you!" << endl;
    co_await a;

    std::cout << "Goodbye" << endl;
    
    co_await a;
}

ReturnObject counter(std::coroutine_handle<> *continuation_out) {
    Awaiter a{continuation_out};
    for (unsigned i = 0;; ++i) {
        co_await a;
        std::cout << "counter: " << i << std::endl;
    }
}


int main() {
    std::coroutine_handle<> h;

    FriendlyCoroutine(&h);
    cout << "------------------\nClick ENTER for start\n------------------" << endl;
    cin.get();
    h.resume();

    cout << "----------------\nClick ENTER for next info\n----------------" << endl;
    cin.get();
    h.resume();

    cout << "----------------\nClick ENTER for next info\n----------------" << endl;
    cin.get();
    h.resume();

    cout << "----------------\nClick ENTER for next info\n----------------" << endl;
    cin.get();
    h.resume();

    cout << "--------------\nClick ENTER to kill coroutine\n--------------" << endl;
    cin.get();
    h.destroy();
    cout << "Coroutine is destroyed (ಥ⌣ಥ)" << endl;
}