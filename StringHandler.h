#ifndef _STRING_HANDLER_H_
#define _STRING_HANDLER_H_
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include<algorithm>

/*
        解析数字类：
                将一串数字字符串转化为vector
        规则如下：
                将数字转化为对应音频文件名，并将每个文件名按序存入vector容器中
*/
class StringHandler {
  public:
    StringHandler(std::string &s) { // s中最多只有一个小数点
    
        auto len = s.size();
        auto point = s.find(".");
        if (point == std::string::npos) { //没有小数点
            long_p = handle_Long_p(s);
            float_p = "";
            have_point = false; //都没有小数点，自然无效
        } else {
            long_p = handle_Long_p(s.substr(0, point)); //取小数点前面的字符串
            float_p =
                handle_Float_p(s.substr(point + 1)); //取小数点后面的字符串
            if (float_p == "") //多余的小数点，标记无效
                have_point = false;
            else //小数点有效
                have_point = true;
        }
    }

    StringHandler() {} // 默认构造函数

    /*
            解析函数：将字符串解析成音频文件名
    */
    std::vector<std::string> prase() {
        ////////////////// 解析小数点后面部分 /////////////////////
        if (float_p != "")
            for (auto i = float_p.rbegin(); i != float_p.rend(); ++i)
                targetVector.push_back(std::string(1, *i));

        ////////////////// 解析小数点部分 /////////////////////
        if (have_point)
            targetVector.push_back("#");

        ////////////////// 解析小数点前面部分 /////////////////////

        if (long_p == "0") { //只有零
            targetVector.push_back(posTable[0]);
        } else { // 将字符串转化为一个长整数（转化成中文读数）例如：123,1231,0094,2320
                 // : 从后往前每四位看成一个发音单位处理
            // std::vector<std::string> tvec;  // 暂存解析后的内容
            auto len = long_p.size();
            auto k = len % 4 != 0 ? len / 4 + 1 : len / 4;
            for (decltype(len) i = 1; i <= k; ++i) {
                std::string t = len >= i * 4
                                    ? long_p.substr(len - i * 4, 4)
                                    : long_p.substr(0, len - 4 * (i - 1));

                auto len_t = t.size();
                bool is_zero = false; //标记当前个位，十位，百位为零

                //发 "万" 或者 "亿"
                //的音，即除第一个四位之外，其它每四位之后有一个 “万” 或 “亿”
                //的发音
                if (i > 1) {
                    targetVector.push_back((i - 1) % 2 == 0 ? posTable[14]
                                                            : posTable[13]);
                }

                //个位
                if (len_t >= 1) {
                    //有个位；为零，不发音；否则，发音
                    if (t[len_t - 1] != '0')
                        targetVector.push_back(
                            posTable
                                [t[len_t - 1] -
                                 '0']); //单个字符转化为字符串不能用加号，会出现乱码
                    else
                        is_zero = true;
                }

                //十位
                if (len_t >= 2) {              //有十位
                    if (t[len_t - 2] != '0') { //不为零，十位发音
                        targetVector.push_back(posTable[10]);
                        targetVector.push_back(posTable[t[len_t - 2] - '0']);
                    } else {          //为零
                        if (!is_zero) //个位不为零
                            targetVector.push_back(
                                posTable[t[len_t - 2] - '0']);
                        is_zero = true;
                    }
                }
                //百位
                if (len_t >= 3) {              //有百位
                    if (t[len_t - 3] != '0') { //不为零，百位发音
                        targetVector.push_back(posTable[11]);
                        targetVector.push_back(posTable[t[len_t - 3] - '0']);
                    } else {
                        if (!is_zero) //十位不为零
                            targetVector.push_back(
                                posTable[t[len_t - 3] - '0']);
                        is_zero = true;
                    }
                }

                //千位
                if (len_t >= 4) { //有千位
                    if (t[len_t - 4] != '0') { //不为零，千位发音，为零，不发音
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
            处理小数点前面的字符串
    */
    std::string handle_Long_p(std::string pre) {
        //只处理长度在14以内的字符串
        if (pre.size() < 14) {
            auto pos = pre.find_first_not_of("0");
            if (pos == std::string::npos) //全是零或空字符串,直接赋 "0"
                pre = "0";
            else
                pre = pre.substr(pos); //去掉前面多余的零
        }
        return pre;
    }

    /*
            处理小数点后面的字符串
    */
    std::string handle_Float_p(std::string suf) {
        //处理小数点后面部分,去点字符串尾部多余的零
        auto pos = suf.find_last_not_of("0");
        if (pos == std::string::npos) //全是零或空串，直接置空
            suf = "";
        else
            suf = suf.substr(0, pos + 1);
        return suf;
    }

    // std::string sourceString;               // 需要解析的字符串
    bool have_point;                       // 标记小数点是否有效
    std::string long_p;                    // 小数点前面的字符串
    std::string float_p;                   // 小数点后面的字符串
    std::vector<std::string> targetVector; // 目标容器，存放解析后的内容

    //存放发音文件的文件名
    std::string posTable[30] = {
        "0",        // 零 的发音
        "1",        // 一 的发音
        "2",        // 二 的发音
        "3",        // 三 的发音
        "4",        // 四 的发音
        "5",        // 五 的发音
        "6",        // 六 的发音
        "7",        // 七 的发音
        "8",        // 八 的发音
        "9",        // 九 的发音
        "10",       // 十 的发音
        "100",      // 百 的发音
        "1000",     // 千 的发音
        "10000",    // 万 的发音
        "100000000" // 亿 的发音
    };

    std::string zh_read_; //存放数字字符串的中文读数
    
	std::map<std::string, std::string> keyTable = {
        {"#", "点"},   {"0", "零"},    {"1", "一"},     {"2", "二"},
        {"3", "三"},   {"4", "四"},    {"5", "五"},     {"6", "六"},
        {"7", "七"},   {"8", "八"},    {"9", "九"},     {"10", "十"},
        {"100", "百"}, {"1000", "千"}, {"10000", "万"}, {"100000000", "亿"}};
};

#endif // !_STRING_HANDLER_H_
