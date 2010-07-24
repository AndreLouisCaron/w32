#!/usr/env/python

import pymsi

class ColumnNames:
    """Array of fields returned by executing an SQL query through a view.
    """

    class Iterator:
        """Iterates through all fields(columns) in a record.
        """
        def __init__ ( self, record ):
            self.record = record
            self.index = 0
            self.last = len(self.record)
            return

        def next ( self ):
            self.index += 1
            if self.index > self.last:
                raise StopIteration
            return self.record[self.index]

    def __init__ ( self, view ):
        """Fetches the next record(row) for a query.
        """
        self.backend = pymsi.ColumnInformation(
            view.backend, pymsi.ViewColumn.Names
            )
        return

    def __len__ ( self ):
        """Obtains the number of fields(columns)x in the record.
        """
        return int(self.backend.fields())

    def __getitem__ ( self, index ):
        """Obtains the field in the i-th column.
        """
        return self.backend.field(index+1)[:-1]

    def __iter__ ( self ):
        """Returns an iterator to the fields for each column.
        """
        return ColumnNames.Iterator(self)
