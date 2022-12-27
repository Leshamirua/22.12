#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <codecvt>
#pragma comment(lib, "urlmon.lib")
using namespace std;

void FindPrintJSON(const string& sours, const string& find) {
    int pos = -1;
    while (true) {
        pos = sours.find(find, pos + 1);
        if (pos == string::npos) break;

        for (auto i = sours.begin() + pos + find.length(); i != sours.end(); ++i) {
            if (*i == ',') break;
            cout << *i;
        }
        cout << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    const char* FileName = "Privat24.txt";

    const char* srcURL = "https://api.privatbank.ua/p24api/pubinfo?exchange&coursid=5";
    if (S_OK == URLDownloadToFileA(NULL, srcURL, FileName, 0, NULL)) {
        cout << "Saved to: " << FileName;
    }

    ifstream file(FileName, ios::in);
    file.imbue(locale(std::locale::empty(), new codecvt_utf8<wchar_t>));

    if (file.is_open())
    {
        string buff;

        while (!file.eof())
        {
            getline(file, buff, '\n');

            FindPrintJSON(buff, "ccy\":");
            FindPrintJSON(buff, "base_ccy\":");
            FindPrintJSON(buff, "buy\":");
            FindPrintJSON(buff, "sale\":");
        }

        file.close();
    }
}
