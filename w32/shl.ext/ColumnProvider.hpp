#ifndef _w32_shl_ext_ColumnProvider_hpp__
#define _w32_shl_ext_ColumnProvider_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>

namespace w32 { namespace shl { namespace ext {

    class ColumnProvider;

        /*!
         * @brief Describes a column we wish to export to the Windows Explorer's
         *    list view.
         */
    class W32_SHL_EXT_EXPORT Column :
        private NotCopyable
    {
    friend class ColumnProvider;

        /* nested types. */
    public:
        class Alignment; class Flags;

        /* data. */
    private:
        ::SHCOLUMNINFO * myData;

        /* construction. */
    private:
            // For use by class ColumnProvider only.
        explicit Column ( ::SHCOLUMNINFO * data );

        /* methods. */
    public:
            /*!
             * @brief Sets the unique identifier for the column.
             *
             * This identifier is used to identify the different exported
             * columns (you can export more than one per COM server) and is
             * provided to you when data for a column is queried.
             *
             * @param class_ Globally unique identifier for the column, this is
             *    usually the GUID of the COM server that exports the column.
             * @param index Index of the exported column. This framework
             *    only provides you with this index when it queries for column
             *    data.
             */
        void identifier ( const com::Guid& class_, ::DWORD index );

            /*!
             * @brief Type of value the system is to expect when querying column
             *    values.
             */
        void type ( const Variant::Type& type );

            /*!
             * @brief Alignment of the values in the column (not the title).
             */
        void alignment ( const Alignment& value );

            /*!
             * @brief Expected width, in number of characters, for the values.
             */
        void width ( uint characters );

            /*!
             * @brief Miscellaneous options.
             */
        void flags ( const Flags& values );

            /*!
             * @brief Title for the column.
             *
             * This is normally a one word description of the values that will
             * appear in the column.
             */
        void title ( const string& value );

            /*!
             * @brief Description of the column values.
             */
        void description ( const string& value );
    };

        /*!
         * @brief Indicates alignment of the values in the column.
         */
    class W32_SHL_EXT_EXPORT Column::Alignment
    {
        /* nested types. */
    public:
        typedef dword Value;

        /* class data. */
    public:
        static const Alignment left ();
        static const Alignment right ();
        static const Alignment center ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    private:
        Alignment ( Value value );

        /* methods. */
    public:
        Value value () const;
    };

        /*!
         * @brief Enables/disables different options for the column.
         */
    class W32_SHL_EXT_EXPORT Column::Flags
    {
        /* nested types. */
    public:
        typedef dword Value;

        /* class data. */
    public:
            /*!
             * @brief Indicates the values are slow to compute.
             *
             * For slow computation data (i.e. you need to open each file
             * to fetch values), this tells the explorer to run the queries
             * in a background thread so the files are displayed immediately
             * and this column's values are displayed as they are computed.
             */
        static const Flags slow ();

            /*!
             * @brief Indicates the column is added to every list view
             *    without the user enabling it.
             *
             * There is no way to specify this on a per-folder basis, it is
             * all folders by default or none of them. In any case, the
             * column can be added/removed on a per-folder bases.
             */
        static const Flags onbydefault ();

            // Not clear what these are...
        static const Flags date ();
        static const Flags integer ();
        static const Flags string ();

        /* data. */
    private:
        Value myValue;

        /* construction. */
    public:
            /*!
             * @brief Creates an empty flag set (nothing is enabled).
             */
        Flags ();

    private:
            // For internal use only.
        Flags ( Value value );

        /* methods. */
    public:
            /*!
             * @brief Obtains the native representation of the flags.
             */
        Value value () const;

        /* operators. */
    public:
        Flags& operator|= ( const Flags& other );
        Flags operator| ( const Flags& other ) const;
        Flags& operator&= ( const Flags& other );
        Flags operator& ( const Flags& other ) const;
    };

        /*!
         * @brief Identifies a file in the given folder for which the explorer
         *    will query for values.
         */
    class W32_SHL_EXT_EXPORT EntryData :
        private NotCopyable
    {
    friend class ColumnProvider;

        /* data. */
    private:
        const ::SHCOLUMNDATA * myData;

        /* construction. */
    private:
            // For use by ColumnProvider only.
        explicit EntryData ( const ::SHCOLUMNDATA * data );

        /* methods. */
    public:
            // Not sure.
        dword flags () const;

            /*!
             * @brief Pre-computed file attributes for the entry.
             *
             * This is mainly useful for checking if the entry is a directory.
             */
        w32::fs::Attributes attributes () const;

            /*!
             * @brief Fully qualified path to the file.
             */
        string path () const;

            /*!
             * @brief Pointer to the start of the file's extension.
             *
             * Displayed properties often depend on they type of file
             * considered. Since the type of file is commonly associated to a
             * particular extension, this provides a quick means to check the
             * extension.
             */
        string extension () const;
    };

        /*!
         * @brief Implements columns for the details view in the explorer.
         *
         * Objects of this class are requested to describe what information they
         * want to insert in the new columns and to fetch it for each requested
         * item displayed in the explorer.
         */
    class W32_SHL_EXT_EXPORT ColumnProvider :
        public ::IColumnProvider
    {
        /* data. */
    private:
            // The path to the folder is passed at the Initialize() function.
            // Store it to avoid the need for derived classes to store it
            // themselves.
        string myFolder;

        /* methods. */
    public:
            /*!
             * @brief Obtains the path to the target folder.
             */
        const string& folder () const {
            return (myFolder);
        }

        virtual ::DWORD columns () const = 0;

        virtual com::Result describe (
            ::DWORD index, Column& column
            ) = 0;

        virtual com::Result fill (
            ::DWORD column, const EntryData& entry, w32::Variant& data
            ) = 0;

        /* overrides. */
    public:
        virtual ::HRESULT __stdcall Initialize ( ::LPCSHCOLUMNINIT column );

        virtual ::HRESULT __stdcall GetColumnInfo (
            ::DWORD index, ::SHCOLUMNINFO * column
            );

        virtual ::HRESULT __stdcall GetItemData (
            const ::SHCOLUMNID * identifier,
            const ::SHCOLUMNDATA * data, ::VARIANT * more
            );
    };

} } }

#endif /* _w32_shl_ext_ColumnProvider_hpp__ */
