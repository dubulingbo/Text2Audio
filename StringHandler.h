#ifndef _STRING_HANDLER_H_
#define _STRING_HANDLER_H_
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include<algorithm>

/*
        ���������ࣺ
                ��һ�������ַ���ת��Ϊvector
        �������£�
                ������ת��Ϊ��Ӧ��Ƶ�ļ���������ÿ���ļ����������vector������
*/
class StringHandler {
  public:
    StringHandler(std::string &s) { // s�����ֻ��һ��С����
    
        auto len = s.size();
        auto point = s.find(".");
        if (point == std::string::npos) { //û��С����
            long_p = handle_Long_p(s);
            float_p = "";
            have_point = false; //��û��С���㣬��Ȼ��Ч
        } else {
            long_p = handle_Long_p(s.substr(0, point)); //ȡС����ǰ����ַ���
            float_p =
                handle_Float_p(s.substr(point + 1)); //ȡС���������ַ���
            if (float_p == "") //�����С���㣬�����Ч
                have_point = false;
            else //С������Ч
                have_point = true;
        }
    }

    StringHandler() {} // Ĭ�Ϲ��캯��

    /*
            �������������ַ�����������Ƶ�ļ���
    */
    std::vector<std::string> prase() {
        ////////////////// ����С������沿�� /////////////////////
        if (float_p != "")
            for (auto i = float_p.rbegin(); i != float_p.rend(); ++i)
                targetVector.push_back(std::string(1, *i));

        ////////////////// ����С���㲿�� /////////////////////
        if (have_point)
            targetVector.push_back("#");

        ////////////////// ����С����ǰ�沿�� /////////////////////

        if (long_p == "0") { //ֻ����
            targetVector.push_back(posTable[0]);
        } else { // ���ַ���ת��Ϊһ����������ת�������Ķ��������磺123,1231,0094,2320
                 // : �Ӻ���ǰÿ��λ����һ��������λ����
            // std::vector<std::string> tvec;  // �ݴ�����������
            auto len = long_p.size();
            auto k = len % 4 != 0 ? len / 4 + 1 : len / 4;
            for (decltype(len) i = 1; i <= k; ++i) {
                std::string t = len >= i * 4
                                    ? long_p.substr(len - i * 4, 4)
                                    : long_p.substr(0, len - 4 * (i - 1));

                auto len_t = t.size();
                bool is_zero = false; //��ǵ�ǰ��λ��ʮλ����λΪ��

                //�� "��" ���� "��"
                //������������һ����λ֮�⣬����ÿ��λ֮����һ�� ���� �� ���ڡ�
                //�ķ���
                if (i > 1) {
                    targetVector.push_back((i - 1) % 2 == 0 ? posTable[14]
                                                            : posTable[13]);
                }

                //��λ
                if (len_t >= 1) {
                    //�и�λ��Ϊ�㣬�����������򣬷���
                    if (t[len_t - 1] != '0')
                        targetVector.push_back(
                            posTable
                                [t[len_t - 1] -
                                 '0']); //�����ַ�ת��Ϊ�ַ��������üӺţ����������
                    else
                        is_zero = true;
                }

                //ʮλ
                if (len_t >= 2) {              //��ʮλ
                    if (t[len_t - 2] != '0') { //��Ϊ�㣬ʮλ����
                        targetVector.push_back(posTable[10]);
                        targetVector.push_back(posTable[t[len_t - 2] - '0']);
                    } else {          //Ϊ��
                        if (!is_zero) //��λ��Ϊ��
                            targetVector.push_back(
                                posTable[t[len_t - 2] - '0']);
                        is_zero = true;
                    }
                }
                //��λ
                if (len_t >= 3) {              //�а�λ
                    if (t[len_t - 3] != '0') { //��Ϊ�㣬��λ����
                        targetVector.push_back(posTable[11]);
                        targetVector.push_back(posTable[t[len_t - 3] - '0']);
                    } else {
                        if (!is_zero) //ʮλ��Ϊ��
                            targetVector.push_back(
                                posTable[t[len_t - 3] - '0']);
                        is_zero = true;
                    }
                }

                //ǧλ
                if (len_t >= 4) { //��ǧλ
                    if (t[len_t - 4] != '0') { //��Ϊ�㣬ǧλ������Ϊ�㣬������
                        targetVector.push_back(posTable[12]);
                        targetVector.push_back(posTable[t[len_t - 4] - '0']);
                    }
                }
            }
            // targetVector.insert(targetVector.end(), tvec.begin(),
            // tvec.end());
        }
        return targetVector;
    }

    std::string zh_read() {
        zh_read_ = "";
        for (auto it = targetVector.rbegin(); it != targetVector.rend(); ++it)
            zh_read_.append(keyTable.at(*it));
        return zh_read_;
    }

    static std::vector<std::string> prase(std::string &source) {
        std::vector<std::string> vec;
        if (source.size() == 0) {
            std::cout << "empty string!" << std::endl;
        } else {
            for (auto it = source.rbegin(); it != source.rend(); ++it)
                if (*it == '.')
                    vec.push_back("#");
                else
                    vec.push_back(std::string(1, *it));
        }
        return vec;
    }

  private:
    /*
            ����С����ǰ����ַ���
    */
    std::string handle_Long_p(std::string pre) {
        //ֻ��������14���ڵ��ַ���
        if (pre.size() < 14) {
            auto pos = pre.find_first_not_of("0");
            if (pos == std::string::npos) //ȫ�������ַ���,ֱ�Ӹ� "0"
                pre = "0";
            else
                pre = pre.substr(pos); //ȥ��ǰ��������
        }
        return pre;
    }

    /*
            ����С���������ַ���
    */
    std::string handle_Float_p(std::string suf) {
        //����С������沿��,ȥ���ַ���β���������
        auto pos = suf.find_last_not_of("0");
        if (pos == std::string::npos) //ȫ�����մ���ֱ���ÿ�
            suf = "";
        else
            suf = suf.substr(0, pos + 1);
        return suf;
    }

    // std::string sourceString;               // ��Ҫ�������ַ���
    bool have_point;                       // ���С�����Ƿ���Ч
    std::string long_p;                    // С����ǰ����ַ���
    std::string float_p;                   // С���������ַ���
    std::vector<std::string> targetVector; // Ŀ����������Ž����������

    //��ŷ����ļ����ļ���
    std::string posTable[30] = {
        "0",        // �� �ķ���
        "1",        // һ �ķ���
        "2",        // �� �ķ���
        "3",        // �� �ķ���
        "4",        // �� �ķ���
        "5",        // �� �ķ���
        "6",        // �� �ķ���
        "7",        // �� �ķ���
        "8",        // �� �ķ���
        "9",        // �� �ķ���
        "10",       // ʮ �ķ���
        "100",      // �� �ķ���
        "1000",     // ǧ �ķ���
        "10000",    // �� �ķ���
        "100000000" // �� �ķ���
    };

    std::string zh_read_; //��������ַ��������Ķ���
    
	std::map<std::string, std::string> keyTable = {
        {"#", "��"},   {"0", "��"},    {"1", "һ"},     {"2", "��"},
        {"3", "��"},   {"4", "��"},    {"5", "��"},     {"6", "��"},
        {"7", "��"},   {"8", "��"},    {"9", "��"},     {"10", "ʮ"},
        {"100", "��"}, {"1000", "ǧ"}, {"10000", "��"}, {"100000000", "��"}};
};

#endif // !_STRING_HANDLER_H_
