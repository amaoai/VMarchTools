/* AUTHOR: TIAN_SHENG, DATE: 2022/7/27 */
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wvarargs"

#include "vmarchtools.h"
#include <cstdio>
#include <stdexcept>
#include <cstdarg>
#include <algorithm>

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
        throw std::runtime_error(vfmt(__fmt, va));
        va_end(va);
    }

    void printf_to_stdout(const std::string &__fmt, ...)
    {
        va_list va;
        va_start(va, __fmt);
        fprintf(stdout, "%s", vfmt(__fmt, va).c_str());
        va_end(va);
    }

    void printf_to_stderr(const std::string &__fmt, ...)
    {
        va_list va;
        va_start(va, __fmt);
        fprintf(stderr, "%s", vfmt(__fmt, va).c_str());
        va_end(va);
    }

    bool is_number(const std::string &str)
    {
        if (str.empty())
            return false;

        return std::all_of(str.begin(), str.end(), [](char ch) {
            return isdigit(ch);
        });
    }

    bool fread_all(const std::string &path, std::string *p_buf)
    {
        FILE *fp = fopen(path.c_str(), "r");

        if (fp == nullptr)
            return false;

        char buf[1024];
        while (fgets(buf, sizeof(buf), fp) != nullptr)
            p_buf->append(buf);

        fclose(fp);
        return true;
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

}

#pragma clang diagnostic pop