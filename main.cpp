// C++ termProjectBingo
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h> // Sleep 함수
using namespace std;

class Bingo // 빙고틀
{
protected:
    int line;
    int bingo[25];
public:
    Bingo() {};
    int lineCheck()
    {
        line = 0;
        for (int i = 0; i < 5; i++) // 가로줄
        {
            if (bingo[i*5+0] == 0 && bingo[i * 5 + 1] == 0 && bingo[i * 5 + 2] == 0 && bingo[i * 5 + 3] == 0 && bingo[i * 5 + 4] == 0) { line +=1; }
        }
        for (int i = 0; i < 5; i++) // 세로줄
        {
            if (bingo[0 * 5 + i] == 0 && bingo[1 * 5 + i] == 0 && bingo[2 * 5 + i] == 0 && bingo[3 * 5 + i] == 0 && bingo[4 * 5 + i] == 0) { line +=1; }
        }
        if (bingo[0]==0 && bingo[6]==0 && bingo[12]==0 && bingo[18]==0 && bingo[24] == 0) { line+=1; } // ＼줄
        if (bingo[4]==0 && bingo[8]==0 && bingo[12]==0 && bingo[16]==0 && bingo[20] == 0) { line+=1; } // / 줄
        return line;
    }
    int show(int i, int j) { return this->bingo[i * 5 + j]; } // 빙고숫자확인
    void numberChange(int number) // 빙고 바꾸기
    {
        for (int i = 0; i < 25; i++)
        {
            if (bingo[i] == number) { bingo[i] = 0; }
        }
    }
};
class PlayerBingo : public Bingo
{
public:
    PlayerBingo()
    {
        for (int i = 0; i < 25; i++) { bingo[i] = i + 1; } // 1-25 넣기
        srand((unsigned)time(NULL));
        for (int i = 0; i < rand(); i++) // 빙고판 섞기
        {
            int save;
            int random1 = rand() % 25;
            int random2 = rand() % 25;
            save = bingo[random1];
            bingo[random1] = bingo[random2];
            bingo[random2] = save;
        }
        line = 0;
    }
    bool numberCheck(int number) // 빙고 확인
    {
        for (int i = 0; i < 25; i++)
        {
            if (number == bingo[i] && number != 0) return true;
        }
        return false;
    }
};

class ComputerBingo : public Bingo
{
public:
    ComputerBingo()
    {
        for (int i = 0; i < 25; i++) { bingo[i] = i + 1; } // 1-25 넣기
        for (int i = 0; i < rand(); i++) // 빙고판 섞기
        {
            int save;
            int random1 = rand() % 25;
            int random2 = rand() % 25;
            save = bingo[random1];
            bingo[random1] = bingo[random2];
            bingo[random2] = save;
        }
        line = 0;
    }
    int getRandomNumber() // 컴퓨터 랜덤 숫자
    {
        while (true)
        {
            int random1 = rand() % 25;
            if (this->bingo[random1] != 0) { return bingo[random1]; }
        }
    }
};

int main()
{
    while (true)
    {
        PlayerBingo playerBingo;
        ComputerBingo computerBingo;
        int finish = 0;
        while (true)
        {
        FINISH:
            system("cls");
            cout << "18114875 김장현\n\n";
            cout << "   <사용자>                 <컴퓨터>\n";
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    cout.width(2);
                    cout << playerBingo.show(i, j) << " ";
                }
                cout << "          ";
                for (int j = 0; j < 5; j++)
                {
                    cout.width(2);
                    cout << computerBingo.show(i, j) << " ";
                }
                cout << endl;
            }
            cout << "현재 당신은 " << playerBingo.lineCheck() << "줄 빙고 입니다.\n";
            cout << "현재 컴퓨터는 " << computerBingo.lineCheck() << "줄 빙고 입니다.\n";
            if (finish != 0) break;

            int answer = 0;
        RE:
            cout << "빙고 숫자를 입력하세요 >> ";
            cin >> answer;

            if (playerBingo.numberCheck(answer))
            {
                playerBingo.numberChange(answer);
                if (playerBingo.lineCheck() >= 5) { finish = 1; goto FINISH; }
                computerBingo.numberChange(answer);
                if (computerBingo.lineCheck() >= 5) { finish = 2; goto FINISH; }
            }
            else { goto RE; }

            int randomNumber = computerBingo.getRandomNumber();
            cout << "컴퓨터의 빙고 숫자 >> " << randomNumber << endl;
            Sleep(1000);
            computerBingo.numberChange(randomNumber);
            if (computerBingo.lineCheck() >= 5) { finish = 2; goto FINISH; }
            playerBingo.numberChange(randomNumber);
            if (playerBingo.lineCheck() >= 5) { finish = 1; goto FINISH; }
        }
        cout << "다시 하시려면 0을 입력하여 주세요. >> ";
        cin >> finish;
        if (finish != 0) break;
    }
}