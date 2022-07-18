/* AUTHOR: TIAN_SHENG, DATE: 2022/7/18 */

void vmarchcmd_exec_stop(const struct vmarch_option_flags *p_optflags);
void vmarchcmd_exec_start(const struct vmarch_option_flags *p_optflags);

void vmarchcmd_exec_restart(const struct vmarch_option_flags *p_optflags)
{
    vmarchcmd_exec_stop(p_optflags);
    vmarchcmd_exec_start(p_optflags);
}