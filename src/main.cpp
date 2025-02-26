/*#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#include "include/Logger.h"
using namespace frames::include;
*/

/*int main()
{
    // 初始化日志对象
    Logger::instance()->open("./Logging.log");

    debug("name=%s age=%d", "jack", 18);

    return 0;
}*/

/*int main(){

    Logger::instance()->open("./Logging.log");

    const char *username=getenv("USER");

    debug("name=%s age=%d",username ? username : "unknown",18);

    return 0;
}
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ifaddrs.h>    // 新增头文件
#include <arpa/inet.h> 
#include "Logger.h"

using namespace std;
using namespace frames::include;


// 新增IP获取函数
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
    string ip = get_local_ip();  // 获取IP地址
    
    // 修改后的日志格式
    debug("name=%s ip=%s", username ? username : "unknown", ip.c_str());

    return 0;
}