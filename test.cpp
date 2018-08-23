#include "TXLib.h"

#include "answer.cpp"
#include <fstream>
#include <iostream>
using namespace std;


int main()
{
    txCreateWindow(900, 600);

    Question que[100];
    int count_questions = 0;
    int kolichestvo_pravilnyh = 0;
    char stroka_dlya_kolichestvo_pravilnyh[100];

    //Заполняем вопросы нормально

    char stroka_iz_faila[100];                          // буфер промежуточного хранения считываемого из файла текста
    ifstream question_file;                             // открыли файл для чтения
    question_file.open("Вопросы.txt");

    while (question_file.good())                        // если файл открыт
    {
        question_file.getline(stroka_iz_faila, 100);    // считали строку из файла

        //Если stroka_iz_faila == Vopros
        if (strcmp(stroka_iz_faila, "Vopros") == 0)
        {
            question_file.getline(stroka_iz_faila, 100);    // считали строку из файла

            //ПРиходится заводить переменную, чтобы тексты вопросов были уникальными
            char* text = new char[100];
            strcpy(text, stroka_iz_faila);

            que[count_questions++] = {text,
                {{"1", true},
                {"2", false}
                }
            };
        }

    }

    question_file.close();                          // закрываем файл


    /*{
    que[count_questions++] = {"Выберите число",
        {{"1", true},
         {"Курица", false},
         {"g", false},
         {"456", false},
         {"dfg", false}}
    };
    que[count_questions++] = {"Это невопрос. Все ответы правильные",
        {{"Это ответ1", true},
         {"Это ответ2", true},
         {"Это ответ3", true}}
    };
    que[count_questions++] = {"Выберите число",
        {{"2", true},
         {"Вася", false},
         {"Вася", false},
         {"15", true}}
    };
    que[count_questions++] = {"Выберите число",
        {{"2", true},
         {"15", true}}
    };
    }   */


    //Считаем количество ответов и расставляем их
    for (int nomer = 0; nomer < count_questions; nomer++)
    {
        for (int otvet = 0; otvet < 100; otvet++)
        {
            if (que[nomer].ans[otvet].text == nullptr)
            {
                que[nomer].count_answers = otvet;
                break;
            }
        }

        for (int otvet = 0; otvet < que[nomer].count_answers; otvet++)
        {
            //900 - ширина экрана
            int shirina_otveta = 900 / que[nomer].count_answers;

            que[nomer].ans[otvet].x1 = 10 + otvet * shirina_otveta;
            que[nomer].ans[otvet].x2 = que[nomer].ans[otvet].x1 + shirina_otveta - 20;

            que[nomer].ans[otvet].y1 = 300;
            que[nomer].ans[otvet].y2 = 400;
        }
    }

    //Рисуем вопросы
    int nomer_voprosa = 0;
    while (nomer_voprosa < count_questions)
    {
        txBegin();
        txSetFillColor(TX_BLACK);
        txClear();
        drawQuestion(que[nomer_voprosa]);

        sprintf(stroka_dlya_kolichestvo_pravilnyh,
            "Количество правильных ответов %d из %d",
            kolichestvo_pravilnyh,
            nomer_voprosa);
        txTextOut(30, 100, stroka_dlya_kolichestvo_pravilnyh);

        for (int nomer = 0; nomer < que[nomer_voprosa].count_answers; nomer++)
        {
            if (
                txMouseX() >= que[nomer_voprosa].ans[nomer].x1 and
                txMouseX() <= que[nomer_voprosa].ans[nomer].x2 and
                txMouseY() >= que[nomer_voprosa].ans[nomer].y1 and
                txMouseY() <= que[nomer_voprosa].ans[nomer].y2
            )
            {
                txSetFillColor(TX_YELLOW);
                txFloodFill(que[nomer_voprosa].ans[nomer].x1 + 10,
                            que[nomer_voprosa].ans[nomer].y1 + 10);
                txSleep(10);

                if (txMouseButtons() & 1)
                {
                    if (que[nomer_voprosa].ans[nomer].pravilnyi)
                    {
                        kolichestvo_pravilnyh = kolichestvo_pravilnyh + 1;
                    }
                    nomer_voprosa = nomer_voprosa + 1;
                    txSleep(1000);
                }
            }
        }

        txSleep(3);
        txEnd();
    }

    //Результат
    {
    txSetFillColor(TX_BLACK);
    txClear();
    sprintf(stroka_dlya_kolichestvo_pravilnyh,
        "Количество правильных ответов %d из %d",
        kolichestvo_pravilnyh,
        nomer_voprosa);
    txTextOut(30, 100, stroka_dlya_kolichestvo_pravilnyh);

    /*if ((100 * kolichestvo_pravilnyh) / nomer_voprosa > 80)
    {
        txTextOut(30, 400, "Вы гений");
    }
    else
    {
        txTextOut(30, 400, "Вы идиот");
    }    */
    }

    return 0;
}
