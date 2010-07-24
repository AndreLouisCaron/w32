
import msi

def TableNames ( database ):
    view = msi.View(database,u'select `Name` from `_Tables`')
    view.execute()
    for record in view:
        yield record[0]

def TableInformation ( database, table ):
    print u'%s:' % table
    view = msi.View(database,u'select * from `%s`' % table)
    for (name,type) in msi.Columns(view):
        print '    ' + name + ':' + type
    print

def DescribeTables ( database ):
    for table in TableNames(database):
        TableInformation(database,table)

def ExecuteUpdate ( database, statement ):
    """Executes an update query from which we expect no results.
    """
    view = msi.View(database,statement)
    view.execute()
    view.close()

def AddProperty ( database, key, value ):
    """Adds a property into the property table.
    """
    query = u'insert into `Properties` values (`%s`,`%s`)'
    ExecuteStatement(database,query % (key,value))

def ExecuteQuery ( database, query ):
    """Executes a query and reads all records.
    """
    view = msi.View(database,query)
    view.execute()
    for record in msi.Records(view):
        print record[0]
    print

def ListTableNames ( database ):
    ExecuteQuery(database,u'select `Name` from `_Tables`')

def ListTableFields ( database, table ):
    view = msi.View(database,u'select * from `%s`' % table)
    information = msi.View.ColumnInformation(view,msi.View.Column.Names)
    for column in msi.Fields(information):
        print column
    print

def main ( arguments ):
    database = msi.Database(u'Schema.Msi',msi.Database.Mode.ReadOnly)
    #AddProperty(database,u'MyProperty',u'Fubar!')
    #ListTableNames(database)
    #ListTableFields(database,u'ServiceInstall')
    InstallService(
        database, component='fubar', name='Fubar service.',
        arguments=['foo','bar']
        )

def InstallService (
    database, component, name, display=None, process=None,
    start=None, loadorder=None, dependencies=None, user=None, password=None,
    arguments=None
    ):
    query = u'insert into `ServiceInstall` (%s) values (%s)'
    fields = u'Component_,Name'
    values = u'%s,%s' % (component,name)
    if not display is None:
        fields += u',DisplayName'
        values += u',%s' % display
    if not process is None:
        fields += u',ServiceType'
        values += u',%s' % process
    if not start is None:
        fields += u',StartType'
        values += u',%s' % start
    if not user is None:
        fields += u',StartName'
        values += u',%s' % user
    if not password is None:
        fields += u',Password'
        values += u',%s' % password
    if not arguments is None:
        fields += u',Arguments'
        value = arguments[0]
        for i in range(1,len(arguments)):
            value += '~%s' % arguments[i]
        values += u',%s' % value
    print query % (fields,values)

import sys

if __name__ == '__main__':
    main(sys.argv)
