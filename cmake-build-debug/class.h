#ifndef SAPER_CLASS_H
#define SAPER_CLASS_H
#include <iostream>

enum GameMode  { DEBUG, EASY, NORMAL, HARD };
enum GameState { RUNNING, FINISHED_WIN, FINISHED_LOSS };

struct Field
{
    bool hasMine;
    bool hasFlag;
    bool isRevealed;
};

class MinesweeperBoard
{
    int height;
    int width;
    int mine_count;
    GameState state;
    Field board[100][100];
public:
    MinesweeperBoard(int width, int height, GameMode mode);
    void debug_display() const;
    int getBoardWidth() const;
    int getBoardHeight() const;
    int getMineCount() const;
    int countMines(int x, int y) const;
    bool hasFlag(int x, int y) const;
    void toggleFlag(int x, int y);
    void revealField(int x, int y);
    bool isRevealed(int x, int y) const;
    GameState getGameState() const;
    char getFieldInfo(int x, int y) const;
    bool isOutside(int x, int y) const;
};

MinesweeperBoard::MinesweeperBoard(int width, int height, GameMode mode)
{
    state=RUNNING;
    this->width = width;
    this->height= height;
    float percent=0;

    if (mode==EASY)
    {
        percent=0.1;
    }
    else if (mode==NORMAL)
    {
        percent=0.2;
    }
    else if (mode==HARD)
    {
        percent=0.3;
    }
    for(int i=0; i<width; i++)
    {
        for (int j=0; j<height; j++)
        {
            board[i][j].hasFlag= false;
            board[i][j].hasMine= false;
            board[j][i].isRevealed = false;
        }
    }
    if (mode==DEBUG)
        for (int i=0; i<width;i++)
        {
            board[0][i].hasMine = true;
            for (int j=0; j<height; j++)
            {
                if (j==i)
                    board[j][i].hasMine = true;
                board[2*j][0].hasMine = true;
            }
        }
    mine_count=width*height*percent;
    int mine_amount=mine_count;
    while (mine_amount>0)
    {
        int a = rand()%height;
        int b = rand()%width;
        if (!board[a][b].hasMine)
        {
            board[a][b].hasMine = rand() % 2;
            if (board[a][b].hasMine)
                mine_amount--;
        }
    }
}

void display_Field(Field field)
{
    std::cout<<"[";
    if (field.hasMine)
    {
        std::cout<<"M";
    }else
    {
        std::cout<<".";
    }
    if (field.isRevealed)
    {
        std::cout<<"o";
    } else
    {
        std::cout<<".";
    }
    if (field.hasFlag)
    {
        std::cout<<"f";
    }else
    {
        std::cout<<".";
    }
    std::cout<<"]";
}

void MinesweeperBoard::debug_display() const
{
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            display_Field(board[i][j]);
        }
        std::cout<<std::endl;
    }
}

int MinesweeperBoard::getBoardWidth() const
{
    return MinesweeperBoard::width;
}

int MinesweeperBoard::getBoardHeight() const
{
    return MinesweeperBoard::height;
}

int MinesweeperBoard::getMineCount() const
{
    return MinesweeperBoard::mine_count;
}

int MinesweeperBoard::countMines(int x, int y) const
{
    int mines=0;
    if ((!MinesweeperBoard::board[y][x].isRevealed)||!isOutside(x, y))
        return -1;
    else
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j<2; j++)
            {
                if (MinesweeperBoard::board[x - 1 + i][y + j - 1].hasMine)
                    mines++;
            }
        }
    return mines;
}

bool MinesweeperBoard::hasFlag(int x, int y) const
{
    if ((MinesweeperBoard::board[y][x].isRevealed)||isOutside(x,y)||(!MinesweeperBoard::board[y][x].hasFlag))
        return false;
    else if (MinesweeperBoard::board[y][x].hasFlag)
        return true;
}

void MinesweeperBoard::toggleFlag(int x, int y)
{
    if (isOutside(x,y)||isRevealed(x,y)||state==(FINISHED_WIN||FINISHED_LOSS))
        return;
    else if (!isRevealed(x,y)&&hasFlag(x,y))
        MinesweeperBoard::board[y][x].hasFlag = false;
    else if (!isRevealed(x,y)&&!hasFlag(x,y))
        MinesweeperBoard::board[y][x].hasFlag = true;
}

void MinesweeperBoard::revealField(int x, int y)
{
    if (isRevealed(x,y))
        return;
    else if (!isRevealed(x,y))
    {
        for (int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                if (isRevealed(j,i));
                else
                    if (MinesweeperBoard::board[y][x].hasMine)
                        {
                        MinesweeperBoard::board[y][x].hasMine= false;
                        for (int j=0; j>0;)
                            {
                            int a = rand()%height;
                            int b = rand()%width;
                            if (!board[a][b].hasMine)
                                {
                                    board[a][b].hasMine = true;
                                    j++;
                                }
                                return;
                            }
                        }
            }
        }
        if (MinesweeperBoard::board[y][x].hasMine)
        {
            MinesweeperBoard::state=FINISHED_LOSS;
        }
    }
}

bool MinesweeperBoard::isRevealed(int x, int y) const
{
    if (MinesweeperBoard::board[y][x].isRevealed)
        return true;
    else
        return false;
}

GameState MinesweeperBoard::getGameState() const
{
    GameState state;
    int mines1=mine_count;
    int mines2=mine_count;
    for (int i=0; i<getBoardHeight(); i++)
    {
        for (int j=0; j<getBoardWidth(); j++)
        {
            if (MinesweeperBoard::board[i][j].hasMine&&isRevealed(j, i))
                return state=FINISHED_LOSS;
            else if (MinesweeperBoard::board[i][j].hasMine&&hasFlag(j, i))
            {
                if (!MinesweeperBoard::board[i][j].hasMine&&hasFlag(j, i))
                    mines1++;
                mines1--;
                if (mines1==0)
                    return state=FINISHED_WIN;
            }
            else if (!isRevealed(j, i)&&MinesweeperBoard::board[i][j].hasMine)
            {
                mines2--;
                if (mines2==0)
                {
                    return  state=FINISHED_WIN;
                }
            }
            else
                return state=RUNNING;
        }
    }
}

bool MinesweeperBoard::isOutside(int x, int y) const
{
    if (x>width||y>height)
        {
        std::cout<<width;
        return true;
        }
    else
        return false;
}

char MinesweeperBoard::getFieldInfo(int x, int y) const
{
    if (isOutside(x,y))
        return '#';
    else if (!isRevealed(x,y)&&hasFlag(x,y))
        return 'F';
    else if (!isRevealed(x,y)&&!hasFlag(x,y))
        return '_';
    else if (isRevealed(x,y)&&MinesweeperBoard::board[y][x].hasMine)
        return 'x';
    else if (isRevealed(x,y)&&countMines(x,y)==0)
        return ' ';
    else if (isRevealed(x,y)&&countMines(x,y)!=0)
        return countMines(x,y);
    else
        return '?';
}

#endif //SAPER_CLASS_H