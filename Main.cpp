#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <algorithm>
#include "StringHandler.h"
#include "TextPlayer.h"

using namespace std;

void setWindowsStyle() {
    system("title Text to Audio");
    system("color f0");
    system("mode con cols=68 lines=20");
}
void menu2() {
    while (true) {
        system("mode con cols=100 lines=15");
        system("cls");
        cout << endl << endl;
        cout << "\t\t+==================+ 数字朗读 +==================+" << endl;
        cout << "\t\t|                                                |" << endl;
        cout << "\t\t| 文本输入规则:                                  |" << endl;
        cout << "\t\t|  1.字符范围在[1234567890]                      |" << endl;
        cout << "\t\t|  2.长度在尽量在一百以内                        |" << endl;
        cout << "\t\t|                                                |" << endl;
        cout << "\t\t|                                  返回请输入quit|" << endl;
        cout << "\t\t+============== Designed by DubLBo ==============+" << endl;

        string temp;
        cout << "\t请输入 : ";
        cin >> temp;

        if (temp == "quit")
            break;

        else if (temp.find_first_not_of("1234567890") <  temp.size()) { //含有非数字字符
            cout << "\t目前只能接受纯数字！";
            system("pause");
        } else if (temp.size() > 100) {
            cout << "\t输入过长！";
            system("pause");
        } else {
            //处理输入的字符串
            vector<string> vec = StringHandler::prase(temp);
            system("color f4");
            cout << "\t正在发音..." << endl << "\t";
            TextPlayer::play(vec);
            system("color f0");
            system("pause");
        }
    }
}

void menu1() {
    while (true) {
        system("cls");

        cout << endl << endl;
        cout << "\t+================+ 中文读数朗读 +================+" << endl;
        cout << "\t|                                                |" << endl;
        cout << "\t| 文本输入规则:                                  |" << endl;
        cout << "\t|  1.字符范围在[1234567890.]                     |" << endl;
        cout << "\t|  2.至多输入一个 \".\"                            |" << endl;
        cout << "\t|  3.中文读数整数部分长度尽量控制在17位          |" << endl;
        cout << "\t|    以内（不含），否则可能会失真!               |" << endl;
        cout << "\t|                                                |" << endl;
        cout << "\t|                                  返回请输入quit|" << endl;
        cout << "\t+============== Designed by DubLBo ==============+" << endl;

        string temp;
        cout << "\t请输入 : ";
        cin >> temp;

        if (temp == "quit")
            break;

        else if (temp.find_first_not_of("1234567890.") < temp.size()) { //含有非数字字符
            cout << "\t目前只能接受纯数字和小数点！";
            system("pause");
        } else if (count(temp.begin(), temp.end(), '.') > 1) {
            cout << "\t输入不合法！";
            system("pause");
        } else if (temp.size() > 17) {
            cout << "\t长度不能超过17！";
            system("pause");
        } else {
            //处理输入的字符串
            StringHandler sh(temp);
            vector<string> vec = sh.prase();
            if (vec.size() == 0) { //没有数据处理
                cout << "\t无数据处理！";
                system("pause");
            } else {
                system("color f4");
                cout << "\t正在发音 : " << sh.zh_read() << endl << "\t";
                TextPlayer::play(vec);
                system("color f0");
                system("pause");
            }
        }
    }
}

void choice() {

    string select = "2333";
    do {
        setWindowsStyle();
        cout << endl << endl;
        cout << "\t+================+文本转语音程序+================+" << endl
             << endl;
        cout << "\t\t》 1. 中文读数朗读" << endl;
        cout << "\t\t》 2. 数字朗读" << endl;
        cout << "\t\t》 0. 退出程序" << endl;
        cout << "\n\t+============== Designed by DubLBo ==============+"
             << endl;

        cout << "\t输入选项序号 : ";
        cin >> select;
        if (select == "0")
            break;
        else if (select == "1") {
            menu1();
        } else if (select == "2") {
            menu2();
        } else {
            cout << "\t输入有误！";
            system("pause");
        }

        system("cls");
    } while (select != "0");
}

int main() {
    choice();
    return 0;
}