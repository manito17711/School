#include <iostream>
#include <stack>
#include <sstream>

using namespace  std;

class tower
{
private:
    int stepsTacken;
    stack<int> source, destination, spare;

    void move_disc(int bottomDisk, stack<int>& source, stack<int>& destination, stack<int>& spare);
    void step_taken(int disc);
    void print_rods();
    string build_string(const stack<int>& st);

public:
    tower(int initValue, int count);

    void move_discs();
};

int main()
{
    // value of the bottom disc
    int initValue = 5;

    // count of the discs
    int count = 5;


    tower t (initValue, count);
    t.move_discs();

    return 0;
}

tower::tower(int initValue, int count) : stepsTacken(0)
{
    for (int i = 0; i < count; ++i)
    {
        source.push(initValue);
        --initValue;
    }
}

void tower::move_discs()
{
    this->print_rods();
    this->move_disc(this->source.size(), this->source, this->destination, this->spare);
}

void tower::move_disc(int bottomDisk, stack<int>& source, stack<int>& destination, stack<int>& spare)
{
    if (bottomDisk == 1)
    {
        int disk = source.top();
        destination.push(disk);
        source.pop();
        this->step_taken(bottomDisk);
    }
    else
    {
        this->move_disc(bottomDisk - 1, source, spare, destination);
        int disc = source.top();
        destination.push(disc);
        source.pop();
        this->step_taken(bottomDisk);
        this->move_disc(bottomDisk - 1, spare, destination, source);
    }
}

void tower::step_taken(int disc)
{
    ++this->stepsTacken;
    printf("Step %d: Moved disk {%d}\n", this->stepsTacken, disc);
    print_rods();
    printf("\n");
}

void tower::print_rods()
{
    string line;

    line = this->build_string(this->source);
    printf("Source: %s\n", line.c_str());


    line = this->build_string(this->destination);
    printf("Destination: %s\n", line.c_str());


    line = this->build_string(this->spare);
    printf("Spare: %s\n", line.c_str());

    printf("\n");
}

string tower::build_string(const stack<int>& st)
{
    stringstream ss;
    stack<int> src = st;
    while (!src.empty())
    {
        ss << src.top();
        ss << " ";
        src.pop();
    }

    return ss.str();
}
