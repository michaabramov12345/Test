#include "TXLib.h"
#include <locale.h>

#include "answer.cpp"
#include <fstream>
#include <iostream>
using namespace std;


int main()
{
    setlocale (LC_ALL,"Rus");
    setlocale(LC_CTYPE, "");
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
            question_file.getline(stroka_iz_faila, 100);    // считали текст вопроса

            //ПРиходится заводить переменную, чтобы тексты вопросов были уникальными
            char* text_voprosa = new char[100];
            strcpy(text_voprosa, stroka_iz_faila);

            //Записываем текст вопроса
            que[count_questions] = {text_voprosa};


            question_file.getline(stroka_iz_faila, 100);    // считали слово "Answers"

            if (strcmp(stroka_iz_faila, "Answers") == 0)
            {
                int nomer_otveta = 0;
                while (1)
                {
                    question_file.getline(stroka_iz_faila, 100);    // считали текст ответа

                    //ПРиходится заводить переменную, чтобы тексты вопросов были уникальными
                    char* text_otveta = new char[100];
                    strcpy(text_otveta, stroka_iz_faila);

                    if (strcmp(stroka_iz_faila, "Answers end") == 0)
                    {
                        break;
                    }


                    question_file.getline(stroka_iz_faila, 100);    // считали правильность ответа
                    bool pravilnyi = (strcmp(stroka_iz_faila, "true") == 0);

                    if (strcmp(stroka_iz_faila, "Answers end") == 0)
                    {
                        break;
                    }

                    que[count_questions].ans[nomer_otveta] = {text_otveta, pravilnyi};

                    nomer_otveta++;
                }
            }

            //Считаем количество вопросов
            count_questions++;
        }

    }

    question_file.close();                          // закрываем файл




    //Считаем количество ответов и расставляем их
    for (int nomer = 0; nomer < count_questions; nomer++)
    {
        //КОличество ответов
        for (int otvet = 0; otvet < 100; otvet++)
        {
            if (que[nomer].ans[otvet].text == nullptr)
            {
                que[nomer].count_answers = otvet;
                break;
            }
        }

        //ширина и расстановка
        for (int nomer_otvet = 0; nomer_otvet < que[nomer_otvet].count_answers; nomer_otvet++)
        {
            //900 - ширина экрана
            int shirina_otveta = 900 / que[nomer].count_answers;

            que[nomer].ans[nomer_otvet].x1 = 10 + nomer_otvet * shirina_otveta;
            que[nomer].ans[nomer_otvet].x2 = que[nomer].ans[nomer_otvet].x1 + shirina_otveta - 20;

            que[nomer].ans[nomer_otvet].y1 = 300;
            que[nomer].ans[nomer_otvet].y2 = 400;
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
                    //Считаем количество правильных ответов
                    if (que[nomer_voprosa].ans[nomer].pravilnyi)
                    {
                        kolichestvo_pravilnyh = kolichestvo_pravilnyh + 1;
                    }

                    //номер текущего вопроса
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

    if ((100 * kolichestvo_pravilnyh) / nomer_voprosa > 80)
    {
        txTextOut(30, 400, "Вы гений");
    }
    else
    {
        txTextOut(30, 400, "Вы идиот");
    }
    }

    return 0;
}
