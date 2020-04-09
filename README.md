# Immediate Files in Minix OS

This lab assignment was done in a pair as a part of CS 314 Operating Systems Lab course during the Spring Semester of 2019-20.<br>
The repository contains a script run.sh along with the changed files, which is supposed to be run in the system running Minix OS. It copies these files to the appropriate places in /usr/src/ directory containing the source code for Minix OS and then builds the system.<br>

<b> Modified Files </b> <br>
Following files have been modified to implement immediate files: <br>
/minix/include/minix/const.h <br>
/minix/fs/mfs/link.c <br>
/minix/fs/mfs/misc.c <br>
/minix/fs/mfs/read.c <br>
/minix/fs/mfs/write.c <br>
/minix/fs/mfs/table.c <br>
/minix/fs/mfs/proto.h <br>
/minix/servers/vfs/link.c <br>
/minix/servers/vfs/open.c <br>
/minix/lib/libc/gen/fslib.c <br>

Please refer to the <a href="https://github.com/ksanu1998/immediate_fs_minix_os/blob/master/170030035_170030038_Lab7_Report.pdf">report</a> for getting an overview of the changes made.
