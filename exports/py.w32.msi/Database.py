#!/usr/env/python

import pymsi

class Database:
    """Allows manipulation of MSI files as miniature databases.
    """

    ReadOnly = pymsi.DatabaseMode.ReadOnly
    ReadWrite = pymsi.DatabaseMode.Transaction

    def __init__ ( self, path, mode = ReadWrite ):
        """Opens the database using a given mode.
        """
        self.backend = pymsi.Database(path,mode)
        return
