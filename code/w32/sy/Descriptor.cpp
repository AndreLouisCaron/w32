/*!
 * @file w32/sct/Descriptor.cpp
 * @author Andre Caron
 */

#include <w32/sct/Descriptor.hpp>
#include <w32/dbg/UncheckedError.hpp>

namespace w32 {
    namespace sct {

        Descriptor::Descriptor ()
        {
            const ::BOOL result = ::InitializeSecurityDescriptor(
                                      &myData, SECURITY_DESCRIPTOR_REVISION
                                  );
            if ( result == 0 ) {
                const ::DWORD error = ::GetLastError();
                UNCHECKED_WIN32C_ERROR(InitializeSecurityDescriptor,error);
            }
        }

        Descriptor::Data& Descriptor::get ()
        {
            return (myData);
        }

        const Descriptor::Data& Descriptor::get () const
        {
            return (myData);
        }

        dword Descriptor::length () const
        {
            return (::GetSecurityDescriptorLength(
                        &const_cast<::SECURITY_DESCRIPTOR&>(myData)
                    ));
        }

        bool Descriptor::valid () const
        {
            return (::IsValidSecurityDescriptor(
                        &const_cast<::SECURITY_DESCRIPTOR&>(myData)
                    ) != FALSE);
        }

    }
}
