#!python

"""~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
w32/tests/run.py --- Unit-test framework for Python bindings.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
"""

import glob
import os
import sys

  # Put python extension modules on search path.
__tests__ = os.path.dirname(os.path.join(os.getcwd(), __file__))
__build__ = os.path.join(__tests__, '..', '.build', 'opt')
sys.path.append(__build__)

def fail ( command ):
    print '  (( Unkown command: "%s". ))' % command
    sys.exit(1)

def find ():
    '''Glob for tests.'''
    return glob.glob('test.*.py')

def usage ():
    '''Show usage and list unit test names.'''
    print __doc__
    print 'Available tests:'
    print
    names = map(lambda name: '  * ' + name[5:-3], find())
    for name in names:
        print name
    print
    sys.exit(1)

def one ( name ):
    '''Run a specific test.'''
    print '(( Running: "%s" ))' % name
    execfile(name)
    print

def all ():
    '''Glob for unit tests and Invoke 'one()' repeatedly.'''
    for test in find():
        one(test)

  # For automated command line processing.
def noop ( *arguments ):
    return arguments
__commands__ = (
    ('-?', '--help', 0, usage, noop  ),
    ('-*', '--all',  0,   all, noop  ),
    ('-1', '--one',  1,   one,
      lambda n: ('test.%s.py'%n,) ))

  # Dispatch to handler functions.
def main ( arguments ):
      # Process multiple commands.
    while len(arguments) > 0:
        command = arguments[0]
        effect = fail
        values = (command,)
        for candidate in __commands__:
              # Match either of short or long names.
            if (command == candidate[0]) or (command == candidate[1]):
                  # Grab required number of arguments and handler.
                validate = candidate[4]
                values = arguments[1:candidate[2]+1]
                values = validate(*values)
                effect = candidate[3]
                arguments = arguments[candidate[2]+1:]
                break
        effect(*values)

  # Act as a both a library and a script.
if __name__ == '__main__':
    main(sys.argv[1:])
