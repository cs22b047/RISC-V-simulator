#include <iostream>
#include <bitset>
int main()
{
    int x1 = 0;
    std::bitset<7> bt;
    bt = -100;
    x1=(int)bt.to_ulong();
    std::cout << bt;
}