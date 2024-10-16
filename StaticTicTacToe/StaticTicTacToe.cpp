// TicTacToe game with Bot
// I am not familiar with creating artificial intelligence so Bot is placing symbols randomly
// Also there is a problem with borders of field. I tried to fix it but unsuccessful

#include <iostream>
#include <ctime>
#include <vector>
#include <conio.h>

#define Width 3
#define Height 3


char Bot_Symbol = 'E';
char Human_Symbol = 'E';

char Field[Width][Height];

void Create_Field() { // Create a field for the game
    for (int i = 0; i < Width; i++) {
        for (int j = 0; j < Height; j++) {
            Field[i][j] = '-';
        }
    }
}

bool Look_For_Space() // Trying to find if there is any free cell
{
    for (int i = 0; i < Width; i++) {
        for (int j = 0; j < Height; j++) {
            if (Field[i][j] == '-') return true;
            
        }
    }
    return false;
}

void Field_Draw(int X_Pos, int Y_Pos) //Just draw the field and do nothing with it 
{ 
    for (int i = 0; i < Width; i++) {
        for (int j = 0; j < Height; j++) {
            if (i == X_Pos && Y_Pos == j) std::cout << "H" << " ";
            else std::cout << Field[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

class Player
{
public:
    char Symbol = 'E'; //E is Empty
    std::string Player_Type;
    int Player_Row = 0;
    int Player_Column = 0;

    void Place_Player_Symbol() // Moving and placing Human's 'X' or 'O'
    {
        Player_Row = 0;
        Player_Column = 0;
       bool Redeem = false;
        while (!Redeem && Player_Type != "Bot")
        {
            if (_kbhit())
            {
                switch (_getch())
                {
                case 72: // Arrow Up
                        Player_Row--; 
                        break;
                case 80: // Arrow Down
                        Player_Row++; 
                        break;
                case 75: // Arrow Left
                        Player_Column--;
                        break;
                case 77: // Arrow Right
                        Player_Column++;
                        break;
                case 32: // Space
                    if (Player_Row >= 0 && Player_Row < Width && Player_Column >= 0 && Player_Column < Height &&
                        Field[Player_Row][Player_Column] == '-')
                    {
                        Field[Player_Row][Player_Column] = Symbol;
                        Redeem = true;
                    }
                    break;
                }

                // Redraw the field every time a key is pressed
                system("cls"); // Clear the screen
                std::cout << "Human => " << Human_Symbol << "   Bot => " << Bot_Symbol << "\n";
                Field_Draw(Player_Row, Player_Column);
                std::cout << "Coord:" << Player_Row << ":" << Player_Column;
            }
        }

        if (Player_Type == "Bot")
        {
            if (Look_For_Space())
            {
                do
                {
                    Player_Row = rand() % Width; // Random row index
                    Player_Column = rand() % Height; // Random column index
                } while (Field[Player_Row][Player_Column] != '-');
                Field[Player_Row][Player_Column] = Symbol;
            }
            else return;
        }
    }

    char Symbol_Choose(Player Another_Team_Player)
    {
        if (Another_Team_Player.Symbol == 'E') // E - Empty. If Symbol is Empty then set it randomly
            Symbol = ((1 + std::rand() % 3) == 1) ? 'O' : 'X';
        else
            Symbol = (Another_Team_Player.Symbol == 'O') ? 'X' : 'O';
        return Symbol;
    }
};

bool Check_For_Win(char Symbol) // Checks for 3 same symbols in a "row"
{ 
    for (int i = 0; i < Width; i++) {
        bool Win_Row = true;
        for (int j = 0; j < Height; j++) {
            if (Field[i][j] != Symbol) {
                Win_Row = false;
                break;
            }
        }
        if (Win_Row) return true;
    }
    for (int j = 0; j < Height; j++) {
        bool Win_Column = true;
        for (int i = 0; i < Width; i++) {
            if (Field[i][j] != Symbol) {
                Win_Column = false;
                break;
            }
        }
        if (Win_Column) return true;
    }
    bool Win_Main_Diagonal = true;
    for (int i = 0; i < Width; i++) {
        if (Field[i][i] != Symbol) {
            Win_Main_Diagonal = false;
            break;
        }
    }
    if (Win_Main_Diagonal) return true;
    bool Win_Anti_Diagonal = true;
    for (int i = 0; i < Width; i++) {
        if (Field[i][Width - 1 - i] != Symbol) {
            Win_Anti_Diagonal = false;
            break;
        }
    }
    if (Win_Anti_Diagonal) return true;
    return false;
}

int static Menu() // Starting screen
{
    int Menu_Return;
    do {
        std::cout << "\nWhat would you like to choose?\n1 - Start the game\n2 - Leave the game\nYour choise => ";
        std::cin >> Menu_Return;
    } while (Menu_Return != 1 && Menu_Return != 2);
    return Menu_Return;
}

void Game_Process() { // Logic of the game
    Player Human;
    Player Bot;
    bool Game_End = false;

    Bot.Player_Type = "Bot";

    while (Menu() == 1)
    {
        Human_Symbol = Human.Symbol_Choose(Bot);
        Bot_Symbol = Bot.Symbol_Choose(Human);
        std::cout << "Human => " << Human_Symbol << "\nBot => " << Bot_Symbol << "\n";
        Create_Field();
        Game_End = false;
        while (!Game_End) {
            system("cls");
            std::cout << "Human => " << Human_Symbol << "   Bot => " << Bot_Symbol << "\n";
            Field_Draw(0, 0);
            std::cout << "Coord:" << Human.Player_Row << ":" << Human.Player_Column;
            Human.Place_Player_Symbol();
            Bot.Place_Player_Symbol();
            system("cls");
            if (Check_For_Win(Human_Symbol))
            {
                Human.Symbol = 'E';
                Bot.Symbol = 'E';
                Field_Draw(-1, -1);
                std::cout << "Human wins";
                Game_End = true;
            }
            else if (Check_For_Win(Bot_Symbol))
            {
                Human.Symbol = 'E';
                Bot.Symbol = 'E';
                Field_Draw(-1, -1);
                std::cout << "Bot wins";
                Game_End = true;
            }
            else if (!Look_For_Space())
            {
                Human.Symbol = 'E';
                Bot.Symbol = 'E';
                Field_Draw(-1, -1);
                std::cout << "No more space";
                Game_End = true;
            }
        }
    }
}

int main() 
{
    std::srand(std::time(0));
    Game_Process();
}
