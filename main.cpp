// C++ termProjectBingo
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h> // Sleep �Լ�
using namespace std;

class Bingo // ����Ʋ
{
protected:
    int line;
    int bingo[25];
public:
    Bingo() {};
    int lineCheck()
    {
        line = 0;
        for (int i = 0; i < 5; i++) // ������
        {
            if (bingo[i*5+0] == 0 && bingo[i * 5 + 1] == 0 && bingo[i * 5 + 2] == 0 && bingo[i * 5 + 3] == 0 && bingo[i * 5 + 4] == 0) { line +=1; }
        }
        for (int i = 0; i < 5; i++) // ������
        {
            if (bingo[0 * 5 + i] == 0 && bingo[1 * 5 + i] == 0 && bingo[2 * 5 + i] == 0 && bingo[3 * 5 + i] == 0 && bingo[4 * 5 + i] == 0) { line +=1; }
        }
        if (bingo[0]==0 && bingo[6]==0 && bingo[12]==0 && bingo[18]==0 && bingo[24] == 0) { line+=1; } // ����
        if (bingo[4]==0 && bingo[8]==0 && bingo[12]==0 && bingo[16]==0 && bingo[20] == 0) { line+=1; } // / ��
        return line;
    }
    int show(int i, int j) { return this->bingo[i * 5 + j]; } // �������Ȯ��
    void numberChange(int number) // ���� �ٲٱ�
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
        for (int i = 0; i < 25; i++) { bingo[i] = i + 1; } // 1-25 �ֱ�
        srand((unsigned)time(NULL));
        for (int i = 0; i < rand(); i++) // ������ ����
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
    bool numberCheck(int number) // ���� Ȯ��
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
        for (int i = 0; i < 25; i++) { bingo[i] = i + 1; } // 1-25 �ֱ�
        for (int i = 0; i < rand(); i++) // ������ ����
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
    int getRandomNumber() // ��ǻ�� ���� ����
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
            cout << "18114875 ������\n\n";
            cout << "   <�����>                 <��ǻ��>\n";
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
            cout << "���� ����� " << playerBingo.lineCheck() << "�� ���� �Դϴ�.\n";
            cout << "���� ��ǻ�ʹ� " << computerBingo.lineCheck() << "�� ���� �Դϴ�.\n";
            if (finish != 0) break;

            int answer = 0;
        RE:
            cout << "���� ���ڸ� �Է��ϼ��� >> ";
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
            cout << "��ǻ���� ���� ���� >> " << randomNumber << endl;
            Sleep(1000);
            computerBingo.numberChange(randomNumber);
            if (computerBingo.lineCheck() >= 5) { finish = 2; goto FINISH; }
            playerBingo.numberChange(randomNumber);
            if (playerBingo.lineCheck() >= 5) { finish = 1; goto FINISH; }
        }
        cout << "�ٽ� �Ͻ÷��� 0�� �Է��Ͽ� �ּ���. >> ";
        cin >> finish;
        if (finish != 0) break;
    }
}