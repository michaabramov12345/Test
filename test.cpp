#include "TXLib.h"

struct Answer
{
    int x1;
    int y1;
    int x2;
    int y2;
    const char* text;
};

void drawAnswer(Answer ans)
{
    txRectangle(ans.x1, ans.y1, ans.x2, ans.y2);
    txDrawText(ans.x1, ans.y1, ans.x2, ans.y2, ans.text);
}

struct Question
{
    const char* text;
    Answer ans1;
    Answer ans2;
    Answer ans3;
};

void drawQuestion(Question que)
{
    txSetFillColor(TX_RED);
    txRectangle(100, 0, 800, 100);
    txDrawText(100, 0, 800, 100, que.text);
    drawAnswer(que.ans1);
    drawAnswer(que.ans2);
    drawAnswer(que.ans3);
}

int main()
{
    txCreateWindow(900, 600);

    //Текст вопроса
    txSetFillColor(TX_BLACK);
    txClear();
    Question que1 = {"Это вопрос",
        {100, 250, 300, 350, "Это ответ1"},
        {600, 250, 800, 350, "Это ответ2"},
        {400, 350, 600, 450, "Это ответ3"}
    };
    drawQuestion(que1);
    txSleep(3000);

    txSetFillColor(TX_BLACK);
    txClear();
    Question que2 = {"Это вопрос2",
        {100, 250, 300, 350, "Это ответ1"},
        {600, 250, 800, 350, "Это ответ2"}
    };
    drawQuestion(que2);
    txSleep(3000);

    return 0;
}
