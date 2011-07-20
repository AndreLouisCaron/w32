#!python

def InstallerProperty ( installer, name ):
    installer = pyw32.string(installer)
    database = pyw32msi.Database(installer, pyw32msi.Database.Mode.ReadOnly)
    #view = pyw32msi.View(
    #    database, 'select Value from Property where Property = \'%s\'' % name
    #    )
    #for record in view:
    #    yield record[0]

for installer in glob.iglob(u'C:\\Windows\\Installer\\*.msi'):
    print installer
    installer = pyw32.string(installer)
    database = pyw32msi.Database(installer, pyw32msi.Database.Mode.ReadOnly)
    #for p in InstallerProperty(installer, 'ProductName'):
    #    print p
    #print
