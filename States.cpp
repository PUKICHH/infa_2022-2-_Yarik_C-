#include <set>
#include <random>
#include <iostream>

using namespace std;

struct State {
    virtual bool contains(int) const = 0;
};

class DiscreteState : public State {
private:
    const int state;

public:
    DiscreteState(int state) : state(state) {}

    bool contains(int s) const override {
        return state == s;
    }
};

class SegmentState : public State {
private:
    const int begin, end;

public:
    SegmentState(int begin, int end) : begin(begin), end(end) {}

    bool contains(int s) const override {
        return begin <= s && s <= end;
    }
};

class SetState : public State {
private:
    set<int> states;
public:
    SetState(const set<int> &states) : states(states) {}  //& - могу работать со всеми дочерними классами класса set

    void input_DS(int state) {
        states.insert(state);
    }

    void input_SS(int begin, int end) {
        for (int i = begin; i <= end; i++) {
            states.insert(i);
        }
    }

    bool contains(int s) const override {
        return states.count(s) > 0;
    }

};


class Union : public State {
private:
    const SetState state1;
    const SetState state2;
public:
    Union(SetState state1, SetState state2) : state1(state1), state2(state2) {}

    bool contains(int s) const override {
        return state1.contains(s) || state2.contains(s);
    }
};

class Intersection : public State {
private:
    const SetState state1;
    const SetState state2;
public:
    Intersection(SetState state1, SetState state2) : state1(state1), state2(state2) {}

    bool contains(int s) const override {
        return state1.contains(s) && state2.contains(s);
    }
};


class ProbabilityTest {
private:
    unsigned seed;
    int E_min = -1000, E_max = 1000;
    unsigned test_count;
public:
    ProbabilityTest(unsigned seed, unsigned test_count) :
            seed(seed), test_count(test_count) {}

    float operator()(const State &s) const {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(E_min, E_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;
        return static_cast<float>(good) / static_cast<float>(test_count);
    }
};

int main() {
    DiscreteState d(1);
    SegmentState s(0, 9);

    SetState D({});
    SetState S({});
    D.input_DS(1);
    S.input_SS(0, 9);

    SetState ss1({1, 3, 5, 7, 23, 48, 57, 60, 90, 99});
    SetState ss2({1, 3, 5, 7, 23, 48, 57, 60, 90, 87});


    Union un(ss1, ss2);
    Intersection in(ss1, ss2);
    ProbabilityTest pt(time(0), 100000);
    cout << pt(D) << endl;

    cout << pt(S) << endl;

    cout << pt(ss1) << endl;
    cout << pt(un) << endl;
    cout << pt(in) << endl;

    return 0;
}
