#include "IEOpenedTabParser.h"
#include <utf.h>

#include <cstdio>
#include <cstdlib>
#include <clocale>
#include <cstring>
#include <algorithm>
#include <stdint.h>
#include <wchar.h>
#include <string>
#include <memory>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("please give a path\n");
        return 1;
    }

    FILE* fp = fopen(argv[1], "rb");
    if (fp == NULL)
    {
        perror("read file error\n");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    size_t len = ftell(fp);
    unsigned char* buffer = new unsigned char[len];
    fseek(fp, 0, SEEK_SET);
    
    len = fread(buffer, 1, len, fp);
    printf("file length: %lu\n", len);

    OPENED_TAB_INFO info;
    if (!OpenedTabFileParser::GetOpenedTabInfo(buffer, len, &info))
    {
        printf("cannot find the property set\n");
        return 1;
    }

    printf("url: %s\ntitle: %s\nfavicon url: %s\n",
           WstringToUTF8(info.url.c_str()).c_str(),
           WstringToUTF8(info.title.c_str()).c_str(),
           WstringToUTF8(info.faviconUrl.c_str()).c_str());
    
    return 0;
}
