#ifndef _w32_gdi_PixelFormat_hpp__
#define _w32_gdi_PixelFormat_hpp__

// Copyright(c) Andre Caron, 2009-2010
//
// This document is covered by the Artistic License 2.0 (Open Source Initiative
// approved license). A copy of the license should have been provided alongside
// this software package (see "license.rtf"). If not, the license is available
// online at "http://www.opensource.org/licenses/artistic-license-2.0.php".

#include "__configure__.hpp"
#include <w32/NotCopyable.hpp>
#include <w32.gdi/DeviceContext.hpp>

namespace w32 { namespace gdi {

        /*!
         * @brief Describes the pixel format for a device context.
         *
         * The pixel format is mainly used for OpenGL enabled DCs.
         */
    class PixelFormat :
        private w32::NotCopyable
    {
        /* nested types. */
    public:
        class Color;
        class Buffering;
        class Implementation;
        class Layer;
        class Channels;
        class Description;
        class Search;

        /* data. */
    private:
        const DeviceContext& myDevice;
        int myId;

        /* construction. */
    public:
            /*!
             * Gets the current pixel format for a device.
             */
        PixelFormat ( const DeviceContext& device );

            /*!
             * @brief Chooses a pixel format that satisfies the given criterion.
             */
        PixelFormat ( const DeviceContext& device, const Search& search );

        /* methods. */
    public:
            /*!
             * @brief Obtains the device context the pixel format is used for.
             */
        const DeviceContext& device () const {
            return (myDevice);
        }

            /*!
             * @brief Obtains the pixel format's identifier.
             *
             * Note: this value only means something for the device used to
             * compute the ID; using it for another device yields unpredictable
             * results.
             */
        const int& id () const {
            return (myId);
        }
    };

    class PixelFormat::Color
    {
        /* class data. */
    public:
        static const Color rgba;
        static const Color indexed;

        /* data. */
    private:
        int myValue;

        /* construction. */
    private:
        Color ( int value )
            : myValue(value)
        {}

        /* methods. */
    public:
        int get () const {
            return (myValue);
        }
    };

    class PixelFormat::Buffering
    {
        /* class data. */
    public:
            // Default.
        static const Buffering single;
        static const Buffering doubled;
        static const Buffering any;

        /* data. */
    private:
        ::DWORD myFlag;

        /* construction. */
    private:
        Buffering ( ::DWORD flag )
            : myFlag(flag)
        {}

        /* methods. */
    public:
        ::DWORD get () const {
            return (myFlag);
        }
    };

    class PixelFormat::Implementation
    {
        /* class data. */
    public:
        static const Implementation software;
        static const Implementation hardware;

        /* data. */
    private:
        ::DWORD myFlag;

        /* construction. */
    private:
        Implementation ( ::DWORD flag )
            : myFlag(flag)
        {}

        /* methods. */
    public:
        ::DWORD get () const {
            return (myFlag);
        }
    };

    class PixelFormat::Layer
    {
        /* class data. */
    public:
        static const Layer underlay;
        static const Layer main;
        static const Layer overlay;

        /* data. */
    private:
        int myValue;

        /* construction. */
    private:
        Layer ( int value )
            : myValue(value)
        {}

        /* methods. */
    public:
        int get () const {
            return (myValue);
        }
    };

    class PixelFormat::Channels
    {
        /* class data. */
    public:
            // Default.
        static const Channels mono;
        static const Channels stereo;
        static const Channels any;

        /* data. */
    private:
        ::DWORD myFlag;

        /* construction. */
    private:
        Channels ( ::DWORD flag )
            : myFlag(flag)
        {}

        /* methods. */
    public:
        ::DWORD get () const {
            return (myFlag);
        }
    };

        /*!
         * @brief Description for an existing pixel format.
         */
    class PixelFormat::Description :
        private w32::NotCopyable
    {
        /* data. */
    private:
        ::PIXELFORMATDESCRIPTOR myData;

        /* construction. */
    public:
        Description ( const PixelFormat& format );

        /* methods. */
    public:
        const ::PIXELFORMATDESCRIPTOR & get () const {
            return (myData);
        }

        ::BYTE color () const {
            return (myData.cColorBits);
        }

        ::BYTE depth () const {
            return (myData.cDepthBits);
        }

        bool window () const {
            return ((myData.dwFlags & PFD_DRAW_TO_WINDOW) != 0);
        }

        bool bitmap () const {
            return ((myData.dwFlags & PFD_DRAW_TO_BITMAP) != 0);
        }

        bool gdi () const {
            return ((myData.dwFlags & PFD_SUPPORT_GDI) != 0);
        }

        bool openGL () const {
            return ((myData.dwFlags & PFD_SUPPORT_OPENGL) != 0);
        }

        bool hardware () const {
            return ((myData.dwFlags & PFD_GENERIC_ACCELERATED) != 0);
        }

        bool software () const {
            return ((myData.dwFlags & PFD_GENERIC_FORMAT) != 0);
        }

        bool doubled () const {
            return ((myData.dwFlags & PFD_DOUBLEBUFFER) != 0);
        }

        bool stereo () const {
            return ((myData.dwFlags & PFD_STEREO) != 0);
        }

        bool rgba () const {
            return ((myData.iPixelType == PFD_TYPE_RGBA) != 0);
        }

        bool indexed () const {
            return ((myData.iPixelType == PFD_TYPE_COLORINDEX) != 0);
        }
    };

        /*!
         * @brief Hints on what we would like to have as a pixel format.
         */
    class PixelFormat::Search :
        private w32::NotCopyable
    {
        /* data. */
    private:
        ::PIXELFORMATDESCRIPTOR myCriterion;

        /* construction. */
    public:
        Search ()
        {
            ::ZeroMemory(&myCriterion,sizeof(myCriterion));
            myCriterion.nSize = sizeof(myCriterion);
            myCriterion.nVersion = 1;
        }

        /* methods. */
    public:
        const ::PIXELFORMATDESCRIPTOR & criterion () const {
            return (myCriterion);
        }

        void color ( const Color & color )
        {
            static ::DWORD clear =
                PFD_TYPE_RGBA | PFD_TYPE_COLORINDEX;
            myCriterion.dwFlags &= ~clear;
            myCriterion.dwFlags |= color.get();
        }

        void implementation ( const Implementation & implementation )
        {
            static ::DWORD clear =
                PFD_GENERIC_ACCELERATED | PFD_GENERIC_FORMAT;
            myCriterion.dwFlags &= ~clear;
            myCriterion.dwFlags |= implementation.get();
        }

        void buffering ( const Buffering & buffering )
        {
            static ::DWORD clear = PFD_DOUBLEBUFFER | PFD_DOUBLEBUFFER_DONTCARE;
            myCriterion.dwFlags &= ~clear;
            myCriterion.dwFlags |= buffering.get();
        }

        void layer ( const Layer & layer )
        {
            myCriterion.iLayerType = layer.get();
        }

        void channels ( const Channels & channels )
        {
            static ::DWORD clear = PFD_STEREO | PFD_STEREO_DONTCARE;
            myCriterion.dwFlags &= ~clear;
            myCriterion.dwFlags |= channels.get();
        }
    };

} }

#endif /* _w32_gdi_PixelFormat_hpp__ */
