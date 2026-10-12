
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>

using namespace std;

#define N 5

enum State {
    THINKING,
    HUNGRY,
    EATING
};

class DiningPhilosophers {
private:
    State state[N];
    mutex mtx;
    condition_variable self[N];

public:
    DiningPhilosophers() {
        for (int i = 0; i < N; i++) {
            state[i] = THINKING;
        }
    }

    void test(int i) {
        if (state[i] == HUNGRY &&
            state[(i + 1) % N] != EATING &&
            state[(i + N - 1) % N] != EATING) {

            state[i] = EATING;
            self[i].notify_one();
        }
    }

    void pickup(int i) {
        unique_lock<mutex> lock(mtx);

        state[i] = HUNGRY;
        cout << "\nPhilosopher " << i << " is HUNGRY";

        test(i);

        while (state[i] != EATING) {
            self[i].wait(lock);
        }
    }

    void putdown(int i) {
        unique_lock<mutex> lock(mtx);

        state[i] = THINKING;
        cout << "\nPhilosopher " << i
             << " finished eating and is THINKING";

        test((i + N - 1) % N);
        test((i + 1) % N);
    }
};

void philosopher(DiningPhilosophers &d, int i) {
    for (int count = 0; count < 3; count++) {
        cout << "\nPhilosopher " << i << " is THINKING";
        sleep(1);

        d.pickup(i);
        cout << "\nPhilosopher " << i << " is EATING";
        sleep(1);

        d.putdown(i);
    }
}

int main() {
    DiningPhilosophers d;
    thread phil[N];

    for (int i = 0; i < N; i++) {
        phil[i] = thread(philosopher, ref(d), i);
    }

    for (int i = 0; i < N; i++) {
        phil[i].join();
    }

    return 0;
}
