#!/usr/bin/python
# -*- coding: utf-8 -*-
#------------------------------------------------------------------------------
#$Author: andrius $
#$Revision: 5815 $
#$URL: svn://www.crystallography.net/cod-tools/branches/experiment/andrius-codcif-CRUD-API/src/components/pycodcif/tests/shtests/tag_index_002.sh $
#$Date: 2017-11-15 10:29:28 +0200 (Wed, 15 Nov 2017) $
#$Id: tag_index_002.sh 5815 2017-11-15 08:29:28Z andrius $
#------------------------------------------------------------------------------
#*
#  Test driver for pycodcif module.
#**
import sys
from pycodcif import CifFile, CifDatablock

def test():
    datablock = CifDatablock("new")
    datablock['_tag'] = 10

    print datablock['_tag']

    cif = CifFile()
    cif.append( datablock )
    print cif

    print cif['new']['_tag']
    print cif[0]['_tag']
    print cif[0].keys()

if __name__ == '__main__':
    test()
