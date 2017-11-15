#!/usr/bin/python
# -*- coding: utf-8 -*-
#------------------------------------------------------------------------------
#$Author: andrius $
#$Revision: 5815 $
#$URL: svn://www.crystallography.net/cod-tools/branches/experiment/andrius-codcif-CRUD-API/src/components/pycodcif/tests/shtests/build_cif_002.sh $
#$Date: 2017-11-15 10:29:28 +0200 (Wed, 15 Nov 2017) $
#$Id: build_cif_002.sh 5815 2017-11-15 08:29:28Z andrius $
#------------------------------------------------------------------------------
#*
#  Test driver for pycodcif module.
#**
import sys
from pycodcif import CifFile, CifDatablock

def test():
    datablock = CifDatablock("new")

    datablock.add_loop( [ '_a', '_b' ], [[1, 2], [3, 4]] )
    datablock.add_loop( [ '_c', '_d', '_e' ], [[1, 2, 3], [3, 4, 4], ['c', 'd', 'e']] )

    cif = CifFile()
    cif.append( datablock )
    print cif

    # This should cause an error
    try:
        datablock.add_loop( [ '_a', '_f' ], [[ 1, 1 ]] )
    except KeyError as e:
        print e

    datablock['_overwritten'] = 'first'
    print cif

    datablock['_overwritten'] = 'second'
    print cif

    del datablock['_c']
    del datablock['_overwritten']
    datablock['_simple_loop'] = [ 10, 12, 13 ]
    print cif

    del datablock['_e']
    print cif

    del datablock['_d']
    del datablock['_simple_loop']
    print cif

if __name__ == '__main__':
    test()
