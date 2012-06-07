#!/usr/bin/python
# Copyright (c) 2012 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
#
# IMPORTANT NOTE: If you make local mods to this file, you must run:
#   %  pnacl/build.sh driver
# in order for them to take effect in the scons build.  This command
# updates the copy in the toolchain/ tree.
#

from driver_tools import Run
from driver_env import env
from driver_log import Log

def main(argv):
  if len(argv) == 0:
    print get_help(argv)
    return 1
  env.set('ARGS', *argv)
  Run('"${RANLIB}" --plugin=LLVMgold ${ARGS}')
  # only reached in case of no errors
  return 0

def get_help(unused_argv):
  return """
Usage: %s [options] archive
 Generate an index to speed access to archives
 The options are:
  @<file>                      Read options from <file>
  -t                           Update the archive's symbol map timestamp
  -h --help                    Print this help message
  -v --version                 Print version information
""" % env.getone('SCRIPT_NAME')
