#!/usr/env/python

    # Import native C++ wrappers.
from _msi import *

def Records ( view ):
    """Generates all records returned by executing the view.
    """
    view.execute()
    try:
        while True:
            yield Record(view)
    except:
        pass

def Fields ( record ):
    """Returns all fields in the record.
    """
    for i in range(len(record)):
        yield record[i]
