#include <iostream>
#include <string>
#include <cstdlib>
#include <ifaddrs.h>    // 新增头文件
#include <arpa/inet.h> 
#include "Logger.h"
#include "ftxui/dom/elements.hpp"  // FTXUI 头文件
#include "ftxui/screen/screen.hpp" // FTXUI 头文件

using namespace std;
using namespace frames::include;
using namespace ftxui;

// 新增 IP 获取函数
string get_local_ip() {
    struct ifaddrs *addrs = nullptr;
    getifaddrs(&addrs);
    
    string ip = "unknown";
    for (auto ifa = addrs; ifa; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr || ifa->ifa_addr->sa_family != AF_INET)
            continue;
        if (string(ifa->ifa_name).find("lo") != string::npos)
            continue;
            
        void *tmp = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
        char buffer[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, tmp, buffer, INET_ADDRSTRLEN);
        ip = buffer;
        break;
    }
    freeifaddrs(addrs);
    return ip;
}

int main()
{
    // 初始化日志对象
    Logger::instance()->open("./Logging.log");
    
    const char* username = getenv("USER");
    string ip = get_local_ip();  // 获取 IP 地址
    
    // 修改后的日志格式
    debug("name=%s ip=%s", username ? username : "unknown", ip.c_str());

    // FTXUI 示例代码
    auto screen = Screen::Create(Dimension::Full(), Dimension::Full());
    auto document = vbox({
        text("Welcome to Easy_Log!"),
        text("Username: " + string(username ? username : "unknown")),
        text("IP Address: " + ip)
    });

    Render(screen, document);
    screen.Print();

    return 0;
}