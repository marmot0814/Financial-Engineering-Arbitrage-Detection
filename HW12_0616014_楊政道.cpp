/*
 * The following link is the report about this project.
 * report: https://github.com/marmot0814/Financial-Engineering-Arbitrage-Detection/blob/master/HW12_0616014_%E6%A5%8A%E6%94%BF%E9%81%93.pdf
 * The whole project can be found at github.
 * github: https://github.com/marmot0814/Financial-Engineering-Arbitrage-Detection
 */

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
    ifstream fin(argv[1]); string input; fin >> input;
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
void output(double sum) {
    if (sum < 0) 
        cout << "------No Arbitrage.\n";
    else 
        cout << "------\033[41;36m Arbitrage: " << sum << "\033[0m\n";
}
/* check begin */
void put_call_parity(Option &opt) {
    double sum;
    cout << "--Put Call Parity\n";
    if (opt.put_price == 0)
        return cout << "----No Price\n", void();
    cout << "----Sell a put, Sell a Taiex, Buy a call.\n";
    sum = opt.put_buy + taiex_buy - opt.call_sell - opt.strike_price - 3;
    output(sum);
    cout << "----Buy a put, Buy a Taiex, Sell a call.\n";
    sum = - opt.put_sell - taiex_sell + opt.call_buy + opt.strike_price - 3;
    output(sum);
}
void put_call_future_parity(Option &opt) {
    double sum;
    cout << "--Put Call Future Parity\n";
    if (opt.put_price == 0)
        return cout << "----No Price\n", void();
    cout << "----Sell a put, Sell a future, Buy a call.\n";
    sum = opt.put_buy + taiex_future_buy - opt.call_sell - opt.strike_price - 3;
    output(sum);
    cout << "----Buy a put, Buy a future, Sell a call.\n";
    sum = - opt.put_sell - taiex_future_sell + opt.call_buy + opt.strike_price - 3;
    output(sum);
}
void Theorem_3(Option &opt) {
    double sum;
    cout << "--Theorem 3\n";
    cout << "----Sell a call, Buy a stock.\n";
    sum = opt.call_buy - taiex_sell - 2;
    output(sum);
    cout << "----Sell a put.\n";
    if (opt.put_price == 0)
        return cout << "------No Price\n", void();
    sum = opt.put_buy - opt.strike_price * pv - 1;
    output(sum);
}
void Theorem_4(Option &opt) {
    double sum;
    cout << "--Theorem 4\n";
    cout << "----Buy a call, Sell a stock, Lend PV(X) money.\n";
    sum = - opt.call_sell + max(taiex_buy - opt.strike_price * pv, (double)0) - 2;
    output(sum);
}
void Theorem_6(Option &opt) {
    double sum;
    cout << "--Theorem 6\n";
    if (opt.put_price == 0)
        return cout << "----No Price\n", void();
    cout << "----Buy a put, Buy a stock, Borrow PV(X) money.\n";
    sum = - opt.put_sell + max(opt.strike_price * pv - taiex_sell, (double)0) - 2;
}
/* check  end  */
void solve() {
    for (auto &opt : options) {
        cout << "**********************************\n";
        cout << "Strike Price: " << opt.strike_price << '\n';
        put_call_parity(opt);
        put_call_future_parity(opt);
        Theorem_3(opt);
        Theorem_4(opt);
        Theorem_6(opt);
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
