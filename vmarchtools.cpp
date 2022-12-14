/* AUTHOR: TIAN_SHENG, DATE: 2022/7/27 */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wvarargs"

#include "vmarchtools.h"
#include <cstdio>
#include <cstdarg>
#include <algorithm>
#include <thread>

namespace vmarchtools {

    std::string vfmt(const std::string &__fmt, va_list __va)
    {
        char *buf;
        int len;
        len = vasprintf(&buf, __fmt.c_str(), __va);
        std::string __fmtret(buf, len);
        free(buf);

        return __fmtret;
    }

    std::string fmt(const std::string &__fmt, ...)
    {
        va_list va;
        va_start(va, __fmt);
        std::string __fmtret = vfmt(__fmt, va);
        va_end(va);

        return __fmtret;
    }

    void verror(const std::string &__fmt, ...)
    {
        va_list va;
        va_start(va, __fmt);
        vfprintf(stderr, (__fmt + "\n").c_str(), va);
        va_end(va);
        exit(EXIT_SUCCESS);
    }

    bool is_number(const std::string &str)
    {
        if (str.empty())
            return false;

        return std::all_of(str.begin(), str.end(), [](char ch) {
            return isdigit(ch);
        });
    }

    void fread_all(const std::string &path, std::string *p_buf)
    {
        FILE *fp;
        size_t fsz;

        fp = fopen(path.c_str(), "r");

        fseek(fp, 0, SEEK_END);
        fsz = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        char buf[fsz];
        fread(buf, fsz, 1, fp);

        fclose(fp);
        p_buf->assign(buf);
    }

    std::vector<std::string> split(const std::string &str, const std::string &delim)
    {
        std::vector<std::string> ret;
        size_t pos = 0;
        while (true) {
            size_t next = str.find(delim, pos);
            if (next == std::string::npos) {
                ret.push_back(str.substr(pos));
                break;
            }
            ret.push_back(str.substr(pos, next - pos));
            pos = next + delim.size();
        }

        if (!ret.empty() && ret[ret.size() - 1].empty())
            ret.pop_back();

        return ret;
    }

    void sleep(unsigned int milliseconds)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

}

#pragma clang diagnostic pop