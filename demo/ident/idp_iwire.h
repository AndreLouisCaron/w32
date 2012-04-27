#ifndef _idp_iwire_h__
#define _idp_iwire_h__

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

/*!
 * @file idp_iwire.h
 * @brief Ident service query parser.
 */

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief Enumeration of wire protocol parser errros.
 */
enum idp_iwire_error
{
    /*! @brief No error. */
    idp_iwire_good,

    /*!
     * @internal
     * @brief Parser temporarily paused, not an error.
     */
    idp_iwire_pause,

    /*! @brief Invalid input request. */
    idp_iwire_invalid_syntax,

    /*! @brief Server port not a number in [1,65536). */
    idp_iwire_invalid_server_port,

    /*! @brief Client port not a number in [1,65536). */
    idp_iwire_invalid_client_port,
};

/*!
 * @brief Ident service query parser.
 */
typedef struct idp_iwire
{
    /*!
     * @public
     * @brief Data pointer reserver for use by the application.
     *
     * You may use this pointer for any application purpose.  It is not used or
     * interpreted in any way by the parser.  The default value is 0.
     */
    void * baton;

    /*!
     * @public
     * @brief Indicates that a fully specified and valid query was received.
     * @return 0 to continue processing, non-zero to force a parser pause.
     *  Pausing the parser causes @c idp_iwire_feed() to return after calling
     *  this callback instead of processing any other pipelined requests.
     *
     * It is expected that ident response handling will occur within this
     * callback.  The parser automatically resets immediately after invoking
     * this function (regardless of pausing).  If you plan to delay the
     * response, you should save the @c server_port and @c client_port fields.
     */
    int(*query)(struct idp_iwire*);

    /*!
     * @public
     * @readonly
     * @brief Counts the number of valid queries processed so far.
     */
    int queries;

    /*!
     * @public
     * @readonly
     * @brief Within @c query(), contains the query's server port field.
     *
     * The server port field is the port number of the host running the ident
     * service.  It designates a @e local port.
     *
     * @note Accessing this parameter outside the @c query() callback yields
     *  an unspecified value.
     */
    int server_port;

    /*!
     * @public
     * @readonly
     * @brief Within @c query(), contains the query's client port field.
     *
     * The client port field is the port number of the peer sending a query to
     * the ident service.  It designates a @e remote port.
     *
     * @note Accessing this parameter outside the @c query() callback yields
     *  an unspecified value.
     */
    int client_port;

    /*!
     * @public
     * @readonly
     * @brief Contains the parser error, if any.
     *
     * You should check this field after every call to @c idp_iwire_feed().
     */
    enum idp_iwire_error error;

    /*!
     * @private
     * @internal
     * @brief Current state machine callback.
     * @param stream Current parser state.
     * @param data Buffer of @a size bytes to consume.
     * @param size Number of bytes, starting at @a data, to consume.
     * @return The number of consumed bytes.
     *
     * This field is changed by callbacks to perform a state transfer.  Each
     * state transfer is followed by a return from the state callback so that
     * the next state may start consume the data.
     */
    int(*state)(struct idp_iwire* stream, const char* data, int size);

} idp_iwire;

/*!
 * @brief Initialize the ident wire protocol parser.
 * @param stream The parser to initialize.
 *
 * This function zero-initializes the stream's @c baton and all callbacks.  You
 * must assign the @c baton and the callbacks after initializing the parser.
 */
void idp_iwire_init (idp_iwire * stream);

/*!
 * @brief Consume input data received from the peer.
 * @param stream Current parser state.
 * @param data Buffer of @a size bytes to consume.
 * @param size Number of bytes, starting at @a data, to consume.
 * @return The number of bytes consumed by the parser.  Unless the @c query()
 *  callback requests a parser pause or an error occurs, this should be equal
 *  to @a size.  Note that this value being equal to @a size is not a reliable
 *  test for errors.  Consult @c stream->error after each call to this
 *  function.
 *
 * @todo Handle the boundary case where input stops after the last client port
 *  digit and there is no trailing whitespace.
 */
int idp_iwire_feed (idp_iwire * stream, const void * data, int size);

#ifdef __cplusplus
}
#endif

#endif /* _idp_iwire_h__ */
