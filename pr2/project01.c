#include "types.h"
#include "stat.h"
#include "user.h"

int 
main(int argc, char *argv[])
{
    char* st_id = "2020090791";
    int pid, gpid;
    pid = getpid();
    gpid = getgpid();
    printf(1,"My student id is %s\n",st_id);
    printf(1,"My pid is %x\n",pid);
    printf(1,"My gpid is %x\n",gpid);
    exit();
}