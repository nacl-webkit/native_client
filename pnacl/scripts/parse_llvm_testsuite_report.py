#!/usr/bin/python
# Copyright (c) 2011 The Native Client Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

"""Parse the report output of the llvm test suite,
   filter out known failures, and check for new failures

pnacl/scripts/parse_llvm_testsuite_report.py [options]+ reportfile

"""

import csv
import optparse
import os
import sys

# exclude these tests
EXCLUDES = {}

def ParseCommandLine(argv):
  parser = optparse.OptionParser()
  parser.add_option('-x', '--exclude', action='append', dest='excludes',
                    default=[],
                    help='Add list of excluded tests (expected fails)')
  parser.add_option('-c', '--check-excludes', action='store_true',
                    default=False, dest='check_excludes',
                    help='Report tests which unexpectedly pass')
  parser.add_option('-v', '--verbose', action='store_true',
                    default=False, dest='verbose',
                    help='Print compilation/run logs of failing tests')
  parser.add_option('-p', '--build-path', dest='buildpath',
                    help='Path to test-suite build directory')

  options, args = parser.parse_args(argv)
  return options, args

def Fatal(text):
  print >> sys.stderr, text
  sys.exit(1)

def IsFullname(name):
  return name.find('/') != -1

def GetShortname(fullname):
  return fullname.split('/')[-1]

def ParseCSV(filename):
  ''' Parse a CSV file with a record for each test.
      returns 2 dictionaries:
      1) a mapping from the short name of the test (without the path) to
       a list of full pathnames that match it. It contains all the tests.
      2) a mapping of all test failures, mapping full test path to the type
       of failure (compile or exec)
  '''
  alltests = {}
  failures = {}
  reader = csv.DictReader(open(filename, 'rb'))

  testcount = 0
  for row in reader:
    testcount += 1
    fullname = row['Program']
    shortname = GetShortname(fullname)
    fullnames = alltests.get(shortname, [])
    fullnames.append(fullname)
    alltests[shortname] = fullnames

    if row['CC'] == '*':
      failures[fullname] = 'compile'
    elif row['Exec'] == '*':
      failures[fullname] = 'exec'

  print testcount, 'tests,', len(failures), ' failures'
  return alltests, failures

def ParseExcludeFile(filename, alltests):
  ''' Parse a list of excludes (known test failures). Excludes can be specified
      by shortname (e.g. fbench) or by full path
      (e.g. SingleSource/Benchmarks/Misc/fbench) but if there is more than
      one test with the same shortname, the full name must be given.
      Errors are reported if an exclude does not match exactly one test
      in alltests, or if there are duplicate excludes.
  '''
  f = open(filename)
  for line in f:
    line = line.strip()
    if not line: continue
    if line.startswith('#'): continue
    if line in EXCLUDES:
      Fatal('ERROR: duplicate exclude: ' + line)
    if IsFullname(line):
      shortname = GetShortname(line)
      if shortname not in alltests or line not in alltests[shortname]:
        Fatal('ERROR: exclude ' + line + ' not found in list of tests')
      fullname = line
    else:
      # short name is specified
      shortname = line
      if shortname not in alltests:
        Fatal('ERROR: exclude ' + shortname + ' not found in list of tests')
      if len(alltests[shortname]) > 1:
        Fatal('ERROR: exclude ' + shortname + ' matches more than one test: ' +
              str(alltests[shortname]) + '. Specify full name in exclude file.')
      fullname = alltests[shortname][0]

    if fullname in EXCLUDES:
      Fatal('ERROR: duplicate exclude ' + fullname)

    EXCLUDES[fullname] = filename
  f.close()
  print 'parsed', filename + ': now', len(EXCLUDES), 'total excludes'

def DumpFileContents(name):
  print name
  print open(name, 'rb').read()

def PrintCompilationResult(path, test):
  ''' Print the compilation and run results for the specified test.
      These results are left in several different log files by the testsuite
      driver, and are different for MultiSource/SingleSource tests
  '''
  print 'RESULTS for', test
  testpath = os.path.join(path, test)
  testdir, testname = os.path.split(testpath)
  outputdir = os.path.join(testdir, 'Output')

  print 'COMPILE phase'
  print 'OBJECT file phase'
  if test.startswith('MultiSource'):
    for f in os.listdir(outputdir):
      if f.endswith('llvm.o.compile'):
        DumpFileContents(os.path.join(outputdir, f))
  elif test.startswith('SingleSource'):
    DumpFileContents(os.path.join(outputdir, testname + '.llvm.o.compile'))
  else:
    Fatal('ERROR: unrecognized test type ' + test)

  print 'PEXE generation phase'
  DumpFileContents(os.path.join(outputdir, testname + '.pexe.compile'))

  print 'TRANSLATION phase'
  DumpFileContents(os.path.join(outputdir, testname + '.nexe.translate'))

  print 'EXECUTION phase'
  print 'native output:'
  DumpFileContents(os.path.join(outputdir, testname + '.out-nat'))
  print 'pnacl output:'
  DumpFileContents(os.path.join(outputdir, testname + '.out-pnacl'))

def main(argv):
  options, args = ParseCommandLine(argv[1:])

  if len(args) != 1:
    Fatal('Must specify filename to parse')
  if options.verbose:
    if options.buildpath is None:
      Fatal('ERROR: must specify build path if verbose output is desired')

  filename = args[0]
  failures = {}
  # get the set of tests and failures
  if filename.endswith('csv'):
    alltests, failures = ParseCSV(filename)
  else:
    Fatal('Only csv files currently supported')

  # get the set of excludes
  for f in options.excludes:
    ParseExcludeFile(f, alltests)

  # intersect them and check for unexpected fails/passes
  unexpected_failures = 0
  unexpected_passes = 0
  for tests in alltests.itervalues():
    for test in tests:
      if test in failures:
        if test not in EXCLUDES:
          unexpected_failures += 1
          print test + ': ' + failures[test] + ' failure'
          if options.verbose:
            PrintCompilationResult(options.buildpath, test)
      elif test in EXCLUDES and options.check_excludes:
        unexpected_passes += 1
        print test + ': ' + ' unexpected success'

  print unexpected_failures, 'unexpected failures',
  print unexpected_passes, 'unexpected pases'
  return unexpected_failures + unexpected_passes

if __name__ == '__main__':
  sys.exit(main(sys.argv))