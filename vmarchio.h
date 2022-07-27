/* AUTHOR: TIAN_SHENG, DATE: 2022/7/26 */
#ifndef VMARCH_VMARCHIO_H
#define VMARCH_VMARCHIO_H

#include <string>
#include <vector>

std::string getpcwd();
std::vector<std::string> find_file(const std::string &path, const std::string &pattern); /* find_file("/opt", ".txt") */
std::string getparent(const std::string &path);

#endif /* VMARCH_VMARCHIO_H */
