/* AUTHOR: TIAN_SHENG, DATE: 2022/7/26 */
#include "vmarchcmd.h"
#include "vmarchtools.h"

int main(int argc, char **argv)
{
    vmarchtools::printf_to_stdout("%d\n", vmarchtools::value_of<int>("123"));
    vmarchtools::printf_to_stdout("%f\n", vmarchtools::value_of<float>("3.1415926"));
//    vmarchcmd_main(argc, argv);
    return 0;
}
