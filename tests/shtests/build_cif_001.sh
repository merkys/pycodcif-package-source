#!/usr/bin/python
# -*- coding: utf-8 -*-
#------------------------------------------------------------------------------
#$Author: andrius $
#$Revision: 5815 $
#$URL: svn://www.crystallography.net/cod-tools/branches/experiment/andrius-codcif-CRUD-API/src/components/pycodcif/tests/shtests/build_cif_001.sh $
#$Date: 2017-11-15 10:29:28 +0200 (Wed, 15 Nov 2017) $
#$Id: build_cif_001.sh 5815 2017-11-15 08:29:28Z andrius $
#------------------------------------------------------------------------------
#*
#  Test driver for pycodcif module.
#**
import sys
from pycodcif import new_cif, cif_start_datablock, datablock_insert_cifvalue, cif_datablock_list, CifFile

def test():
    cif = new_cif( None )
    cif_start_datablock( cif, "first", None )

    datablock_insert_cifvalue( cif_datablock_list( cif ), "_number",  12.3456789, None )
    datablock_insert_cifvalue( cif_datablock_list( cif ), "_string",  "Someone Else", None )
    datablock_insert_cifvalue( cif_datablock_list( cif ), "_unknown", None, None )

    cif_object = CifFile()
    cif_object._cif = cif
    print cif_object

if __name__ == '__main__':
    test()
