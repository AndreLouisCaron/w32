#ifndef _windows_ShellLink_HPP__
#define _windows_ShellLink_HPP__

#include <win32com/Object.hpp>
#include <shlobj.h>

namespace windows {

    class ShellLink : public win32com::Object<::IShellLinkA>
    {
        /* construction. */
    protected:
        ShellLink ( ::IShellLinkA* object )
            : win32com::Object<::IShellLinkA>(object)
        {}
    };

    class NewShellLink : public ShellLink
    {
        /* class methods. */
    private:
        static ::IShellLinkA* create ()
        {
            ::IShellLinkA* value = 0;
            const win32com::Result result = ::CoCreateInstance(
                CLSID_ShellLink, 0, CLSCTX_INPROC_SERVER,
                IID_IShellLink, (void**)&value
                );
            if ( result.bad() ) {
                throw (std::exception("Could not create shell link."));
            }
            return (value);
        }

        /* construction. */
    public:
        NewShellLink ( const win32com::Context& )
            : ShellLink(create())
        {}

    public:
        void target ( const char * path )
        {
            get().SetPath(path);
        }

        void arguments ( const char * value )
        {
            get().SetArguments(value);
        }

        void description ( const char * value )
        {
            get().SetDescription(value);
        }

        void icon ( const char * path )
        {
            get().SetIconLocation(path,0);
        }
    };

}

#endif /* _windows_ShellLink_HPP__ */
