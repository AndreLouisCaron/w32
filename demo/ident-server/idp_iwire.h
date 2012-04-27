#ifndef _idp_iwire_h__
#define _idp_iwire_h__

/*
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
*/

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

enum idp_iwire_mode
{
    idp_iwire_query,
    idp_iwire_reply,
};

#define IDP_MAX_ERROR 64
#define IDP_MAX_TOKEN 512

struct idp_iwire;

/*!
 * @private
 * @internal
 * @brief State machine callback.
 * @param stream Current parser state.
 * @param data Buffer of @a size bytes to consume.
 * @param size Number of bytes, starting at @a data, to consume.
 * @return The number of consumed bytes.
 */
typedef int(*idp_iwire_state)
    (struct idp_iwire* stream, const char* data, int size);

/*!
 * @brief Ident service query parser.
 */
typedef struct idp_iwire
{
    enum idp_iwire_mode mode;

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
    int(*accept_query)(struct idp_iwire*);

    /*!
     * @public
     * @brief Called when the server rejects the query.
     *
     * This function may be called one or more times to deliver its payload in
     * parts.  The results of all invocations for a single response should be
     * concatenated.
     *
     * This function normally produces one of the following values:
     * @li "INVALID-PORT": invalid client or server port number;
     * @li "NO-USER": no match for the query;
     * @li "HIDDEN-USER": the request was willfully denied;
     * @li "UNKNOWN-ERROR": there was another error or the server decided to
     *  hide the real failure for security concerns.
     * The specification allows for non-standard error codes prefixed with "X".
     */
    int(*accept_error)(struct idp_iwire*,const char*,int);

    /*!
     * @public
     * @brief Called to provide the operating system name.
     *
     * This function may be called one or more times to deliver its payload in
     * parts.  The results of all invocations for a single response should be
     * concatenated.
     *
     * This should be an IANA-registered operating system name.
     * @see http://www.iana.org/assignments/operating-system-names/operating-system-names.xml
     */
    int(*accept_opsys)(struct idp_iwire*,const char*,int);

    /*!
     * @public
     * @brief Called to provide the character encoding name.
     *
     * The character encoding only applies to the octet stream retrieved by @c
     * accept_token().  All other fields are in US-ASCII.  This callback is @e
     * always invoked to provide a character encoding name.  When none is
     * present, this library emits the "US-ASCII" value as required by the
     * specification.  Note that an ident server might not return use US-ASCII
     * as its default encoding and still leave the character encoding
     * unspecified.
     *
     * This function may be called one or more times to deliver its payload in
     * parts.  The results of all invocations for a single response should be
     * concatenated.
     *
     * The payload should be an IANA-registered character encoding name.
     *
     * @see http://www.iana.org/assignments/character-sets
     */
    int(*accept_codec)(struct idp_iwire*,const char*,int);

    /*!
     * @public
     * @brief Called to provide the unique user identifier.
     *
     * The character identifier octet stream is encoded using the character
     * encoding retrieved by @c accept_codec().
     *
     * This function may be called one or more times to deliver its payload in
     * parts.  The results of all invocations for a single response should be
     * concatenated.
     *
     * The ident protocol specification recommends that you display the token
     * using the "<codec>,<raw-hex-encoded-token>" format if you do not
     * understand the character encoding name.
     */
    int(*accept_token)(struct idp_iwire*,const char*,int);

    /*!
     * @public
     * @brief Indicates that the response has been completely parsed.
     *
     * This callback is where you would normally process the response.  After
     * this callback finishes, the parser will be reset.
     */
    int(*accept_reply)(struct idp_iwire*);

    /*!
     * @private
     * @internal
     * @brief Offset in current pattern to match.
     *
     * @see text
     */
    int base;

    /*!
     * @private
     * @internal
     * @brief Current pattern to match.
     *
     * The @c text and @c base members are used to perform pattern matching
     * against string literals in the protocol (e.g. error code names like
     * "NO-USER").  The idea is that before entering the pattern matching
     * state, the @c text member is set to the pattern to match and @c base is
     * set to 0.  As input characters match, the @c base member is incremented
     * until a mismatch occurs or @c text[base]=='\0'.
     *
     * @see base
     */
    const char * text;

    /*!
     * @public
     * @readonly
     * @brief Counts the number of valid queries processed so far.
     */
    int messages;

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
     * @brief Current position in the state machine callback stack.
     *
     * @see stack
     */
    int level;

    /*!
     * @private
     * @internal
     * @brief Current state machine callback stack.
     *
     * This field is changed by callbacks to perform a state transfer.  Each
     * state transfer is followed by a return from the state callback so that
     * the next state may start consume the data.
     *
     * The callback are arranged in a stack so that common parsing states can
     * be composed.  For example, parsing optional whitespace is handled by
     * setting the next actual state at position 0 and then adding a whitespace
     * auxiliary state at position 1, then setting @c level to 1.  When the
     * auxliary state finishes, it pops itself off the stack by decreasing
     * @c level.  Up to 3 auxiliary states may be pushed onto the stack.
     *
     * @see level
     */
    idp_iwire_state stack[4];

} idp_iwire;

/*!
 * @brief Initialize the ident wire protocol parser.
 * @param stream The parser to initialize.
 * @param mode Parser mode.
 *
 * This function zero-initializes the stream's @c baton and all callbacks.  You
 * must assign the @c baton and the callbacks after initializing the parser.
 */
void idp_iwire_init (idp_iwire * stream, enum idp_iwire_mode mode);

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
 */
int idp_iwire_feed (idp_iwire * stream, const void * data, int size);

#ifdef __cplusplus
}
#endif

#endif /* _idp_iwire_h__ */
