#include<iostream>
#include<fstream>
#include<string>

using namespace std;

struct WelcomeMessage
{
    string message;
};

struct Player
{
    string name;
    int score;
};

char board[3][3];
char turn;
int row, column;
bool draw;
Player player1, player2;

void reset_board()
{
    char temp[3][3] = { {'1','2','3'},{'4','5','6'},{'7','8','9'} };
    memcpy(board, temp, sizeof(temp));
    turn = 'X';
    draw = false;
}

void display_board()
{
    system("cls");
    cout << "\t\t T I C - T A C - T O E" << endl;
    cout << "\t\t\t" << player1.name << " [X]\n\t\t\t" << player2.name << " [0]\n\n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << board[i][j] << " | ";
        }
        cout << "\n";
    }
}

void player_turn()
{
    int choice;
    cout << "\n\t " << ((turn == 'X') ? player1.name : player2.name) << " turn: ";
    cin >> choice;
    row = (choice - 1) / 3;
    column = (choice - 1) % 3;
    if (board[row][column] != 'X' && board[row][column] != 'O')
    {
        board[row][column] = turn;
        turn = (turn == 'X') ? 'O' : 'X';
    }
    else
    {
        cout << "Box is already filled!\n" << "Try Again.\n";
        player_turn();
    }
    display_board();
}

bool gameover()
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] ||
            board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            return false;
        }
    }
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] ||
        board[0][2] == board[1][1] && board[0][0] == board[2][0])
    {
        return false;
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != 'X' && board[i][j] != 'O')
            {
                return true;
            }
        }
    }
    draw = true;
    return false;
}

void write_high_score(Player* winner)
{
    ofstream file;
    file.open("high_scores.txt", ios::app);
    file << winner->name << ": " << ++winner->score << "\n";
    file.close();
}

void view_high_scores()
{
    ifstream file;
    string line;
    file.open("high_scores.txt");
    while (getline(file, line))
    {
        cout << line << "\n";
    }
    file.close();
}

void play_game()
{
    reset_board();
    while (gameover())
    {
        display_board();
        player_turn();
    }
    if (turn == 'X' && draw == false)
    {
        cout << player2.name << " Wins!! Congratulations\n";
        write_high_score(&player2);
    }
    else if (turn == 'O' && draw == false)
    {
        cout << player1.name << " Wins!! Congratulations\n";
        write_high_score(&player1);
    }
    else
    {
        cout << "Game Draw!\n";
    }
}

int main()
{
    WelcomeMessage welcomeMessage = { "Welcome to Tic Tac Toe!" };
    WelcomeMessage* ptrWelcomeMessage = &welcomeMessage;
    cout << ptrWelcomeMessage->message << endl;
    cout << "Enter name for player 1: ";
    cin >> player1.name;
    player1.score = 0;
    cout << "Enter name for player 2: ";
    cin >> player2.name;
    player2.score = 0;
    int choice;
    do
    {
        cout << "1. Play Game\n";
        cout << "2. View High Scores\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            play_game();
            break;
        case 2:
            view_high_scores();
            break;
        case 3:
            exit(0);
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
    return 0;
}

