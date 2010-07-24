#ifndef _windows_ShellFolder_HPP__
#define _windows_ShellFolder_HPP__

#include <win32com/Object.hpp>
#include <shlobj.h>

namespace windows {

    class ShellFolder : public win32com::Object<::IShellFolder>
    {
        /* construction. */
    protected:
        ShellFolder ( ::IShellFolder* object )
            : win32com::Object<::IShellFolder>(object)
        {}
    };

    class NewShellFolder : public ShellFolder
    {
        /* class methods. */
    private:
        static ::IShellFolder* create ()
        {
            ::IShellFolder* value = 0;
            const win32com::Result result = ::CoCreateInstance(
                CLSID_FolderShortcut, 0, CLSCTX_INPROC_SERVER,
                IID_IShellFolder, (void**)&value
                );
            if ( result.bad() ) {
                throw (std::exception("Could not create shell folder."));
            }
            return (value);
        }

        /* construction. */
    public:
        NewShellFolder ( const win32com::Context& )
            : ShellFolder(create())
        {}

    public:
    };

}

#endif /* _windows_ShellFolder_HPP__ */
