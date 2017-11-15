#!/usr/bin/python
# -*- coding: utf-8 -*-
#------------------------------------------------------------------------------
#$Author: andrius $
#$Revision: 5815 $
#$URL: svn://www.crystallography.net/cod-tools/branches/experiment/andrius-codcif-CRUD-API/src/components/pycodcif/tests/shtests/build_cif_003.sh $
#$Date: 2017-11-15 10:29:28 +0200 (Wed, 15 Nov 2017) $
#$Id: build_cif_003.sh 5815 2017-11-15 08:29:28Z andrius $
#------------------------------------------------------------------------------
#*
#  Test driver for pycodcif module.
#**
import sys
from pycodcif import CifFile

def test():
    cif = CifFile( file = "tests/inputs/1YGG.cif" )
    print cif

if __name__ == '__main__':
    test()
