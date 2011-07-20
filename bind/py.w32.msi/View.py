#!/usr/env/python

import pymsi
from Record import *

class View:
    """Executes an SQL query in the installer and yields all records(rows).
    """

    def __init__ ( self, database, query ):
        """Executes the SQL query in the database.
        """
        self.backend = pymsi.View(database.backend,query)
        self.backend.execute()
        return

    def __iter__ ( self ):
        return self

    def next ( self ):
        """Yields the next record(row).
        """
        return Record(self.backend)
