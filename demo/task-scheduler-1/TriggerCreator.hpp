#ifndef _TriggerCreator_hpp__
#define _TriggerCreator_hpp__

// Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <w32.hpp>
#include <w32.ts-1.hpp>
#include <iostream>
#include <sstream>
#include <string>

        /*!
         * @brief Create a new trigger for an exising task.
         */
    class TriggerCreator
    {
        /* data. */
    private:
        w32::com::Library myContext;
        w32::ts::Scheduler myScheduler;
        w32::ts::Task myTask;
        w32::ts::Editor myTaskEditor;
        w32::ts::Trigger myTrigger;
        w32::ts::Trigger::Editor myEditor;

        /* construction. */
    public:
            /*!
             * @brief Create a trigger for a task, using it's name.
             */
        TriggerCreator ( const w32::string& task )
            : myContext(), myScheduler(), myTask(myScheduler, task),
              myTaskEditor(myTask), myTrigger(myTask), myEditor(myTrigger)
        {}

        /* methods. */
    private:
        static bool specifies (
            const w32::string& property, const w32::string& model
            )
        {
            return (::wcsncmp(property.data(),model.data(),model.size()) == 0);
        }

        /* operators. */
    public:
            /*!
             * @brief Set one of the trigger's property, using a string.
             */
        void operator() ( const w32::string& property )
        {
            static const w32::string begin(L"-begin=");
            static const w32::string daily(L"-daily=");
            if ( specifies(property,begin) ) {
                std::wstringstream parser;
                parser << property.substr(begin.length());
                int year = 0, month = 0, day = 0;
                if ( parser.str() == L"today" ) {
                    w32::Time time;
                    year = time.year(), month = time.month(), day = time.day();
                }
                else {
                    if ( !(parser >> year) || (year < 2008) ) {
                        std::cerr << "Invalid year." << std::endl;
                    }
                    if ( parser.get() != int('/') ) {
                        std::cerr << "Invalid trigger format." << std::endl;
                    }
                    if ( !(parser >> month) || (month < 1) || (month > 12) ) {
                        std::cerr << "Invalid month." << std::endl;
                    }
                    if ( parser.get() != int('/') ) {
                        std::cerr << "Invalid trigger format." << std::endl;
                    }
                    if ( !(parser >> day) || (day < 1) || (day > 31) ) {
                        std::cerr << "Invalid day." << std::endl;
                    }
                }
                myEditor.start(year,month,day);
            }
            else if ( specifies(property,daily) ) {
                std::wstringstream parser;
                parser << property.substr(daily.length());
                int interval = 0;
                if ( !(parser >> interval) || (interval < 0) ) {
                    std::cerr << "Invalid interval." << std::endl;
                }
                if ( parser.get() != int(',') ) {
                    std::cerr << "Invalid trigger format." << std::endl;
                }
                int hour = 0;
                if ( !(parser >> hour) || (hour < 0) || (hour > 23) ) {
                    std::cerr << "Invalid hour." << std::endl;
                }
                if ( parser.get() != int(':') ) {
                    std::cerr << "Invalid trigger format." << std::endl;
                }
                int minute = 0;
                if ( !(parser >> minute) || (minute < 0) || (minute > 59) ) {
                    std::cerr << "Invalid minute." << std::endl;
                }
                myEditor.daily(interval,hour,minute);
            }
        }

            /*!
             * @brief Save the trigger (and the task).
             */
        void operator() ()
        {
            myEditor.commit();
            myTaskEditor.commit();
        }
    };

#endif /* _TriggerCreator_hpp__ */
