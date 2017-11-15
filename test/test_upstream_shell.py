from os import path, listdir
import imp, sys

def test_upstream():
    for f in listdir('tests/shtests'):
        if f.endswith('.sh'):
            base = path.splitext(f)[0]
            yield check_parse, 'tests/shtests/{}'.format(f), 'tests/shoutputs/{}.out'.format(base)

def check_parse(sh_file, out_file):
    module = imp.load_source( 'module', sh_file )
    sys.argv[0] = 'tests/scripts/cif_parser_test'
    with open(out_file, 'r') as f:
        output_old = f.read()
    with capture() as output_new:
        module.test()
    assert output_old == output_new[0]

import contextlib

@contextlib.contextmanager
def capture():
    import sys
    from cStringIO import StringIO
    oldout,olderr = sys.stdout, sys.stderr
    try:
        out=[StringIO(), StringIO()]
        sys.stdout,sys.stderr = out
        yield out
    finally:
        sys.stdout,sys.stderr = oldout, olderr
        out[0] = out[0].getvalue()
        out[1] = out[1].getvalue()
