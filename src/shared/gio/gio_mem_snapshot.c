/*
 * Copyright (c) 2012 The Native Client Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/*
 * NaCl Generic I/O interface implementation: in-memory snapshot of a file.
 */

#include "native_client/src/include/portability.h"
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "native_client/src/shared/gio/gio.h"

struct GioVtbl const  kGioMemoryFileSnapshotVtbl = {
  GioMemoryFileSnapshotDtor,
  GioMemoryFileRead,
  GioMemoryFileWrite,
  GioMemoryFileSeek,
  GioMemoryFileFlush,
  GioMemoryFileClose,
};


int   GioMemoryFileSnapshotCtor(struct GioMemoryFileSnapshot  *self,
                                char                          *fn) {
  FILE            *iop;
  //FIXME from sdk header
  struct stat {
      dev_t     st_dev;     /* ID of device containing file */
      ino_t     st_ino;     /* inode number */
      mode_t    st_mode;    /* protection */
      nlink_t   st_nlink;   /* number of hard links */
      uid_t     st_uid;     /* user ID of owner */
      gid_t     st_gid;     /* group ID of owner */
      dev_t     st_rdev;    /* device ID (if special file) */
      off_t     st_size;    /* total size, in bytes */
      blksize_t st_blksize; /* blocksize for file system I/O */
      blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
      time_t    st_atime;   /* time of last access */
      time_t    st_mtime;   /* time of last modification */
      time_t    st_ctime;   /* time of last status change */
  };
  struct stat stbuf;
  char            *buffer;

  ((struct Gio *) self)->vtbl = (struct GioVtbl *) NULL;
  if (0 == (iop = fopen(fn, "rb"))) {
    return 0;
  }
  if (fstat(fileno(iop), &stbuf) == -1) {
 abort0:
    fclose(iop);
    return 0;
  }
  if (0 == (buffer = malloc(stbuf.st_size))) {
    goto abort0;
  }
  if (fread(buffer, 1, stbuf.st_size, iop) != (size_t) stbuf.st_size) {
 abort1:
    free(buffer);
    goto abort0;
  }
  if (GioMemoryFileCtor(&self->base, buffer, stbuf.st_size) == 0) {
    goto abort1;
  }
  (void) fclose(iop);

  ((struct Gio *) self)->vtbl = &kGioMemoryFileSnapshotVtbl;
  return 1;
}


void GioMemoryFileSnapshotDtor(struct Gio                     *vself) {
  struct GioMemoryFileSnapshot  *self = (struct GioMemoryFileSnapshot *)
      vself;
  free(self->base.buffer);
  GioMemoryFileDtor(vself);
}
