#include "cmake-build-debug/class.h"

int main()
{
    MinesweeperBoard x(9, 7, HARD);
    x.debug_display();
    std::cout<<x.getFieldInfo(0,1);
    std::cout<<"git commit";
    return 0;
}
