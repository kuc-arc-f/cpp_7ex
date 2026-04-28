
#include <windows.h>
#include <chrono>
#include <curl/curl.h>
#include <fcntl.h>       // _O_U16TEXT
#include <iostream>
#include <io.h>          // _setmode
#include <string>
#include <map>
#include <stdexcept>
#include <nlohmann/json.hpp> // JSONライブラリ
#include <shellapi.h>    // CommandLineToArgvW

#include "http_client.hpp"

#pragma comment(lib, "shell32.lib")

// JSON用エイリアス
using json = nlohmann::json;

struct QueryReq {
    std::string title;
};
// これ一行で、QueryReq <=> json の変換が魔法のように可能になります
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(QueryReq, title)

std::wstring StringToWString(const std::string& str)
{
    if (str.empty()) return L"";

    int size_needed = MultiByteToWideChar(
        CP_UTF8, 0,
        str.c_str(), (int)str.size(),
        NULL, 0
    );

    std::wstring wstr(size_needed, 0);

    MultiByteToWideChar(
        CP_UTF8, 0,
        str.c_str(), (int)str.size(),
        &wstr[0], size_needed
    );

    return wstr;
}

// std::wstring を UTF-8 の std::string に変換するヘルパー
std::string to_utf8(const std::wstring& wstr) {
    if (wstr.empty()) return std::string();
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

int main()
{
    std::cout << "#start:" << std::endl;
    try{
        // 開始時刻
        auto start = std::chrono::high_resolution_clock::now();

        HttpClient client(30 /*timeout*/, true /*verify_ssl*/);
        //POST
        QueryReq req;
        req.title = "test-1";

        json j = req; // 構造体を代入するだけ！
        std::string json_str = j.dump();
        int i;
        for(i = 0; i < 100; i++) {
            //std::wcout << L"Post " << i+1 << std::endl;
             auto resp = client.post_json("http://localhost:8000/todos", json_str);
            if (!resp.error.empty()) {
                std::wcerr << L"[ERROR] \n";
                return 1;
            }
            //std::cout << "Status : " << resp.status_code << "\n";
        }
        // 終了時刻
        auto end = std::chrono::high_resolution_clock::now();
        // 差分（ミリ秒）
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "time: " << duration.count() << " ms" << std::endl;        

    } catch (const std::exception& e) {
        std::cerr << "\n[ERROR] " << e.what() << std::endl;
        //std::wcout << L"Error , main" << std::endl;
        return 0;
    }   
}
