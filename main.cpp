#include "cmake-build-debug/class.h"

int main()
{
    srand(time(NULL));
    MinesweeperBoard x(9, 7, DEBUG);
    x.debug_display();
    std::cout<<x.getFieldInfo(0,1);
    /// awgrnevge
    return 0;
}
