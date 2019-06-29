#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
using namespace std;
struct Option {
    int strike_price;       // 履約價
    double call_price;      // 買權成交價
    double call_buy;        // 買權買價
    double call_sell;       // 買權賣價
    double put_price;       // 賣權成交價
    double put_buy;         // 賣權買價
    double put_sell;        // 賣權賣價
};
double taiex_buy;           // 台指買價
double taiex_sell;          // 台指賣價
double taiex_future_buy;    // 台指期買價
double taiex_future_sell;   // 台指期賣價
double rate;                // 利率
double pv;                  // 折現比例
vector<Option> options;
double strtod(string s) {
    stringstream ss; double res;
    ss << s; ss >> res;
    return res;
}
void init(char **argv) {
    options.clear();
    rate                = strtod(string(argv[2])) * 0.01 / 12;
    pv                  = exp(-rate);
    taiex_buy           = strtod(string(argv[3]));
    taiex_sell          = strtod(string(argv[4]));
    taiex_future_buy    = strtod(string(argv[5]));
    taiex_future_sell   = strtod(string(argv[6]));
    ifstream fin(argv[1]); string input;
    while (fin >> input) {
        for (auto &c : input)
            if (c == ',')
                c = ' ';
        stringstream ss; ss << input;
        Option opt;
        ss >> opt.strike_price;
        ss >> opt.call_price;
        ss >> opt.call_buy;
        ss >> opt.call_sell;
        ss >> opt.put_price;
        ss >> opt.put_buy;
        ss >> opt.put_sell;
        options.push_back(opt);
    }
}
/* check begin */
void put_call_parity(Option &opt) {

}
void put_call_future_parity() {

}
void Theorem_3() {

}
void Theorem_4() {

}
void Theorem_6() {

}
/* check  end  */
void solve() {
    for (auto &opt : options) {
        cout << "**********************************\n";
        cout << "履約價: " << opt.strike_price << '\n';
        put_call_parity(opt);
        put_call_future_parity();
        Theorem_3();
        Theorem_4();
        Theorem_6();
    }
    cout << "**********************************\n";
}
int main(int argc, char **argv) {
    if (argc != 7) {
        cout << "Usage: " << argv[0] << " <選擇權csv檔案> <利率(%)> <台指買價> <台指賣價> <台指期買價> <台指期賣價>\n";
        return 0;
    }
    init(argv);
    solve();
}
