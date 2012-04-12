#ifndef _TaskCreator_hpp__
#define _TaskCreator_hpp__

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

#include <w32.ts-1.hpp>
#include <iostream>
#include <string>

        /*!
         * @brief Create a new task, providing parameters using strings.
         */
    class TaskCreator
    {
        /* data. */
    private:
        w32::com::Library myContext;
        w32::ts::Scheduler myScheduler;
        w32::ts::Task myTask;
        w32::ts::Editor myEditor;

        /* construction. */
    public:
        TaskCreator ( const w32::string& name )
            : myContext(), myScheduler(),
              myTask(w32::ts::Task::create(myScheduler,name)),
              myEditor(myTask)
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
             * @brief Set one of the tasks's properties.
             */
        void operator() ( const w32::string& property )
        {
            static const w32::string application(L"-application=");
            static const w32::string arguments(L"-arguments=");
            static const w32::string creator(L"-creator=");
            static const w32::string account(L"-account=");
            if ( specifies(property,application) ) {
                w32::string value = property.substr(application.length());
                myEditor.application(value);
            }
            else if ( specifies(property,arguments) ) {
                w32::string value = property.substr(arguments.length());
                myEditor.arguments(value);
            }
            else if ( specifies(property,account) ) {
                w32::string value = property.substr(account.length());
                myEditor.account(value);
            }
            else if ( specifies(property,creator) ) {
                w32::string value = property.substr(creator.length());
                myEditor.creator(value);
            }
            else {
                // Invalid argument.
                std::wcerr << L"Invalid proprety: " << property << std::endl;
            }
        }

            /*!
             * @brief Save the task.
             */
        void operator() () {
            myEditor.commit();
        }
    };

#endif /* _TaskCreator_hpp__ */
