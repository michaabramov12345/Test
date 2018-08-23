
struct Answer
{
    //Обязательные
    const char* text;
    bool pravilnyi;
    //Необязательные
    HDC pic;
    int x1;
    int y1;
    int x2;
    int y2;
};

void drawAnswer(Answer ans)
{
    txRectangle(ans.x1, ans.y1, ans.x2, ans.y2);
    if (ans.pic != nullptr)
    {
        txBitBlt (txDC(), ans.x1, ans.y1, ans.x2 - ans.x1, ans.y2 - ans.y1, ans.pic, 130, 150);
    }
    txDrawText(ans.x1, ans.y1, ans.x2, ans.y2, ans.text);
}

struct Question
{
    //Обязательные
    const char* text;
    Answer ans[100];
    //Необязательные
    int count_answers;
};

void drawQuestion(Question que)
{
    txSetFillColor(TX_RED);
    txRectangle(100, 0, 800, 100);
    txDrawText(100, 0, 800, 100, que.text);

    for (int nomer = 0; nomer < que.count_answers; nomer++)
    {
        drawAnswer(que.ans[nomer]);
    }
}
