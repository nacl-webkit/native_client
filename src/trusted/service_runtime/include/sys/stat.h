/*
 * Copyright 2008 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can
 * be found in the LICENSE file.
 */

/*
 * NaCl kernel / service run-time system call ABI.  stat/fstat.
 */

#ifndef NATIVE_CLIENT_SRC_TRUSTED_SERVICE_RUNTIME_INCLUDE_SYS_STAT_H_
#define NATIVE_CLIENT_SRC_TRUSTED_SERVICE_RUNTIME_INCLUDE_SYS_STAT_H_

#ifdef __native_client__
#include <sys/types.h>
#else
#include "native_client/src/trusted/service_runtime/include/machine/_types.h"
#endif
#include "native_client/src/trusted/service_runtime/include/bits/stat.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Linux <bit/stat.h> uses preprocessor to define st_atime to
 * st_atim.tv_sec etc to widen the ABI to use a struct timespec rather
 * than just have a time_t access/modification/inode-change times.
 * this is unfortunate, since that symbol cannot be used as a struct
 * member elsewhere (!).
 *
 * just like with type name conflicts, we avoid it by using nacl_abi_
 * as a prefix for struct members too.  sigh.
 */

struct nacl_abi_stat {  /* must be renamed when ABI is exported */
  nacl_abi_dev_t     nacl_abi_st_dev;       /* not implemented */
  nacl_abi_ino_t     nacl_abi_st_ino;       /* not implemented */
  nacl_abi_mode_t    nacl_abi_st_mode;      /* partially implemented. */
  nacl_abi_nlink_t   nacl_abi_st_nlink;     /* link count */
  nacl_abi_uid_t     nacl_abi_st_uid;       /* not implemented */
  nacl_abi_gid_t     nacl_abi_st_gid;       /* not implemented */
  nacl_abi_dev_t     nacl_abi_st_rdev;      /* not implemented */
  nacl_abi_off_t     nacl_abi_st_size;      /* object size */
  nacl_abi_blksize_t nacl_abi_st_blksize;   /* not implemented */
  nacl_abi_blkcnt_t  nacl_abi_st_blocks;    /* not implemented */
  nacl_abi_time_t    nacl_abi_st_atime;     /* access time */
  int64_t            nacl_abi_st_atimensec; /* possibly just pad */
  nacl_abi_time_t    nacl_abi_st_mtime;     /* modification time */
  int64_t            nacl_abi_st_mtimensec; /* possibly just pad */
  nacl_abi_time_t    nacl_abi_st_ctime;     /* inode change time */
  int64_t            nacl_abi_st_ctimensec; /* possibly just pad */
};

#ifdef __native_client__
extern int stat(char const *path, struct nacl_abi_stat *stbuf);
extern int fstat(int d, struct nacl_abi_stat *stbuf);
extern int mkdir(const char *path, nacl_abi_mode_t mode);
#endif

//FIXME: from toolchain/linux_x86_newlib/x86_64-nacl/include/bits/stat.h
#ifndef S_IFMT
#define S_IFMT        0000370000  /* for now */
#define S_IFSHM_SYSV  0000300000  /* must map all-or-nothing */
#define S_IFSEMA      0000270000
#define S_IFCOND      0000260000
#define S_IFMUTEX     0000250000
#define S_IFSHM       0000240000
#define S_IFBOUNDSOCK 0000230000  /* bound socket*/
#define S_IFSOCKADDR  0000220000  /* socket address */
#define S_IFDSOCK     0000210000  /* data-only, transferable socket*/

#define S_IFSOCK      0000140000  /* data-and-descriptor socket*/
#define S_IFLNK       0000120000  /* symbolic link */
#define S_IFREG       0000100000  /* regular file */
#define S_IFBLK       0000060000  /* block device */
#define S_IFDIR       0000040000  /* directory */
#define S_IFCHR       0000020000  /* character device */
#define S_IFIFO       0000010000  /* fifo */

#define S_UNSUP       0000370000  /* unsupported file type */
#endif

#ifndef S_ISUID
#define S_ISUID      0004000
#define S_ISGID      0002000
#define S_ISVTX      0001000

#define S_IREAD      0400
#define S_IWRITE     0200
#define S_IEXEC      0100

#define S_IRWXU  (S_IREAD|S_IWRITE|S_IEXEC)
#define S_IRUSR  (S_IREAD)
#define S_IWUSR  (S_IWRITE)
#define S_IXUSR  (S_IEXEC)

#define S_IRWXG  (S_IRWXU >> 3)
#define S_IRGRP  (S_IREAD >> 3)
#define S_IWGRP  (S_IWRITE >> 3)
#define S_IXGRP  (S_IEXEC >> 3)

#define S_IRWXO  (S_IRWXU >> 6)
#define S_IROTH  (S_IREAD >> 6)
#define S_IWOTH  (S_IWRITE >> 6)
#define S_IXOTH  (S_IEXEC >> 6)
#endif
/*
 * only user access bits are supported; the rest are cleared when set
 * (effectively, umask of 077) and cleared when read.
 */

#ifndef S_ISSOCK
#define S_ISSOCK(m)  (0)
#define S_ISLNK(m)   (0)
#define S_ISREG(m)   (((m) & S_IFMT) == S_IFREG)
#define S_ISBLK(m)   (0)
#define S_ISDIR(m)   (((m) & S_IFMT) == S_IFDIR)
#define S_ISSOCKADDR(m) \
                              (((m) & S_IFMT) == S_IFSOCKADDR)
#define S_ISCHR(m)   (0)
#define S_ISFIFO(m)  (0)
#endif

#ifndef __S_IFMT
#define __S_IFMT    0170000 /* These bits determine file type.  */

/* File types.  */
#define __S_IFDIR   0040000 /* Directory.  */
#define __S_IFCHR   0020000 /* Character device.  */
#define __S_IFBLK   0060000 /* Block device.  */
#define __S_IFREG   0100000 /* Regular file.  */
#define __S_IFIFO   0010000 /* FIFO.  */
#define __S_IFLNK   0120000 /* Symbolic link.  */
#define __S_IFSOCK  0140000 /* Socket.  */

#define __S_ISUID   04000   /* Set user ID on execution.  */
#define __S_ISGID   02000   /* Set group ID on execution.  */
#define __S_ISVTX   01000   /* Save swapped text after use (sticky).  */
#define __S_IREAD   0400    /* Read by owner.  */
#define __S_IWRITE  0200    /* Write by owner.  */
#define __S_IEXEC   0100    /* Execute by owner.  */
#endif

// end of FIXME

#ifdef __cplusplus
}
#endif

#endif
