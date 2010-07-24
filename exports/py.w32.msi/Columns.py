#!/usr/env/python

from ColumnNames import *
from ColumnTypes import *

def Columns ( view ):
    names = ColumnNames(view)
    types = ColumnTypes(view)
    for i in range(len(names)):
        yield (names[i],types[i])
