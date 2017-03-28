#include <iostream>
#include <algorithm>
#include <deque>
#include <math.h>

#include <string.h>

using namespace std;

struct node
{
    int _r;
    int _c;
    int _val;
    node(int r, int c) : _r(r), _c(c) {}
};

bool operator==(const node& lhs, const node& rhs)
{
    return (lhs._c == rhs._c) && (lhs._r == rhs._r);
}

const unsigned int ARR_LEN = 10;
int position_visited[ARR_LEN][ARR_LEN];
int arr2[ARR_LEN][ARR_LEN];

int arr[ARR_LEN][ARR_LEN] = {
    { 0, -1,  0,  0,  0,  0, -1,  0,  0,  0 },
    { 0, -1,  0, -1, -1,  0,  0,  0, -1,  0 },
    { 0, -1,  0,  0,  0, -1, -1,  0,  0,  0 },
    { 0, -1, -1, -1,  0,  0,  0, -1, -1,  0 },
    { 0, -1,  0, -1, -1,  0,  0,  0, -1,  0 },
    { 0, -1,  0,  0,  0, -1, -1,  0, -1,  0 },
    { 0, -1,  0, -1,  0,  0, -1,  0, -1,  0 },
    { 0, -1,  0, -1,  0,  0,  0,  0, -1,  0 },
    { 0, -1,  0, -1,  0,  0, -1, -1, -1,  0 },
    { 0,  0,  0, -1,  0,  0, -1,  0,  0,  0 }
};


void add_node(deque<node>& dq, const node& nd);
void print_arr(const int p_arr[][ARR_LEN]);
void print_path(deque<node>& res);
void print_node(const node& n);
bool is_position_valid(int r, int c);
node find_next_node(deque<node>& res, node nd);


int main(int argc, char *argv[])
{
    memset(position_visited, 0, (ARR_LEN * ARR_LEN * sizeof(int)));
    memset(arr2, 0, (ARR_LEN * ARR_LEN * sizeof(int)));

    deque<node> dq;
    deque<node> res;
    node n0 (0, 0);
    n0._val = 0;
    dq.push_back(n0);
    position_visited[0][0] = 1;

    // wavefront algorithm
    while(!dq.empty())
    {
        node nd = dq.front();
        res.push_back(nd);
        if (nd._r + 1 == ARR_LEN && nd._c + 1 == ARR_LEN)
            break;


        node right_node (nd._r, nd._c + 1);
        right_node._val = nd._val + 1;
        add_node(dq, right_node);

        node left_node (nd._r, nd._c - 1);
        left_node._val = nd._val + 1;
        add_node(dq, left_node);

        node bittom_node (nd._r + 1, nd._c);
        bittom_node._val = nd._val + 1;
        add_node(dq, bittom_node);

        node top_node (nd._r - 1, nd._c);
        top_node._val = nd._val + 1;
        add_node(dq, top_node);

        dq.pop_front();
    }

    print_path(res);
    print_arr(arr2);

    return 0;
}


void print_arr(const int p_arr[][ARR_LEN])
{
    for (int r = 0; r < ARR_LEN; ++r)
    {
        for (int c = 0; c < ARR_LEN; ++c)
        {
            (p_arr[r][c]) ? printf(" 1 ") : printf(" - ");
        }

        printf("\n");
    }

    printf("\n");
}


node find_next_node(deque<node>& res, node nd)
{
    node n1 = res.back();
    for (int i = res.size() - 1; i >= 0; --i)
    {
        node n1 = res[i];

        int diff_row = abs(n1._r - nd._r);
        int diff_col = abs(n1._c - nd._c);

        if (diff_row > 1)
            continue;

        if (diff_col > 1)
            continue;

        return n1;
    }
}

// printing the path.. from back to front
void print_path(deque<node>& dq)
{
    node nd = dq.back();
    while (nd._c != 0 || nd._r != 0)
    {
        printf("Row: %d, Col: %d, Val: %d\n", nd._r, nd._c, nd._val);

        arr2[nd._r][nd._c] = 1;

        dq.erase(find_if(dq.begin(), dq.end(), [nd](node n){ return n._val == nd._val; }), dq.end());
        nd = find_next_node(dq, nd);
    }

    printf("Row: %d, Col: %d, Val: %d\n", nd._r, nd._c, nd._val);
    printf("\n");
}

// if row and col are not valid for the matrix - return false!
bool is_position_valid(int r, int c)
{
    if (r >= ARR_LEN)
        return false;

    if (r < 0)
        return false;

    if (c >= ARR_LEN)
        return false;

    if (c < 0)
        return false;

    return true;
}


void add_node(deque<node>& dq, const node& nd)
{
    // if position is not valid for the matrix - return
    if (!is_position_valid(nd._r, nd._c))
        return;


    // check the cell - can we step on it?
    if (arr[nd._r][nd._c] == -1)
        return;


    // check if the node is already added once to the deque
    // this use the operator==(const node& lhs, const node& rhs)
    if(find(dq.begin(), dq.end(), nd) != dq.end())
        return;


    // check if the cell was visited before.
    if(position_visited[nd._r][nd._c] == 1)
        return;


    // add the node
    dq.push_back(nd);


    // mark position as visited
    position_visited[nd._r][nd._c] = 1;
}

void print_node(const node& n)
{
    printf("Node.. _r: %d, _c: %d, _val: %d\n", n._r, n._c, n._val);
}
