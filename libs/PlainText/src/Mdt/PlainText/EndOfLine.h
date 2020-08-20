/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef MDT_PLAIN_TEXT_END_OF_LINE_H
#define MDT_PLAIN_TEXT_END_OF_LINE_H

namespace Mdt{ namespace PlainText{

  /*! \brief End of line
   */
  enum class EndOfLine
  {
    Native, /*!< Use the native end-of-line.
                   A file writer will open in text mode
                   which will append the platform native end-of-line terminators */
    Lf,     /*!< LF, \\n in C/C++, used on Unix (Linux, mac OS-X, etc) */
    CrLf,   /*!< CR LF, \\r\\n in C/C++, used mainly on MS-DOS and Microsoft Windows */
    Cr      /*!< CR, \\r in C/C++, used mainly on mac OS prior to OS-X */
  };

  /*! \brief Get the native end of line
   */
  inline
  constexpr EndOfLine nativeEndOfLine() noexcept
  {
#if defined MDT_PLAIN_TEXT_OS_UNIX
    return EndOfLine::Lf;
#elif defined MDT_PLAIN_TEXT_OS_WINDOWS
    return EndOfLine::CrLf;
#else
    return EndOfLine::Cr;
#endif
  }

}} // namespace Mdt{ namespace PlainText{

#endif // #ifndef MDT_PLAIN_TEXT_END_OF_LINE_H
