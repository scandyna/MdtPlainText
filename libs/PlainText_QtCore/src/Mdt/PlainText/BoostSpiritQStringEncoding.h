/****************************************************************************
 **
 ** MdtPlainText - A C++ library to read and write simple plain text
 ** using the boost Spirit library.
 **
 ** Copyright (C) 2020-2020 Philippe Steinmann.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with this program.  If not, see <https://www.gnu.org/licenses/>.
 **
 ** This code is inspired from the this post:
 ** http://boost.2283326.n4.nabble.com/QString-and-QChar-support-in-qi-td3555736.html
 **
 ** and from the Spirit documentation:
 ** https://www.boost.org/doc/libs/1_73_0/libs/spirit/doc/html/spirit/qi/reference/basics.html
 **
 ****************************************************************************/
#ifndef MDT_PLAIN_TEXT_BOOST_SPIRIT_QSTRING_ENCODING_H
#define MDT_PLAIN_TEXT_BOOST_SPIRIT_QSTRING_ENCODING_H

#include <QChar>
// #include <QString>
#include <boost/spirit/include/qi.hpp>
#include <cctype>

namespace boost { namespace spirit { namespace char_encoding{

  struct qchar
  {
    using char_type = QChar;

    // isascii_

    static
    bool ischar(const QChar &) noexcept
    {
      return true;
    }

    static
    bool isalnum(const QChar & ch) noexcept
    {
      return ch.isLetterOrNumber();
    }

    static
    bool isalpha(const QChar & ch) noexcept
    {
      return ch.isLetter();
    }

    static
    bool isblank(const QChar & ch) noexcept
    {
      return (ch.toLatin1() == ' ' || ch.toLatin1() == '\t');
    }

    static
    bool isspace(const QChar & ch) noexcept
    {
      return ch.isSpace();
    }

    static
    bool iscntrl(const QChar & ch) noexcept
    {
      return ch.category() == QChar::Other_Control;
    }

    static
    bool isdigit(const QChar & ch) noexcept
    {
      return ch.isDigit();
    }

    static
    bool isxdigit(const QChar & ch) noexcept
    {
      if( ch.isDigit() ){
        return true;
      }
      const char c = ch.toLower().toLatin1();
      if( (c >= 'a') && (c <= 'f') ){
        return true;
      }
      return false;
    }

    static
    bool isgraph(const QChar & ch) noexcept
    {
      return ch.isPrint() && !ch.isSpace();
    }

    static
    bool islower(const QChar & ch) noexcept
    {
      return ch.isLower();
    }

    static
    bool isupper(const QChar & ch) noexcept
    {
      return ch.isUpper();
    }

    static
    bool isprint(const QChar & ch) noexcept
    {
      return ch.isPrint();
    }

    static
    bool ispunct(const QChar & ch) noexcept
    {
      return ch.isPunct();
    }

    // isxdigit
    // ...

    // 
  };

}}} // namespace boost { namespace spirit { namespace char_encoding{
BOOST_SPIRIT_DEFINE_CHAR_CODES(qchar)

namespace boost { namespace spirit { namespace traits{

  /*! \internal Tell Qi to recognize QChar as char type
   */
  template<>
  struct is_char<QChar> : mpl::true_ {};

  /*! \internal Tell Qi to recognize QString as a string
   */
  template<>
  struct is_string<QString> : mpl::true_ {};

  /*! \internal Tell Qi that underlying char type of a QString
   */
  template<>
  struct char_type_of<QString> : mpl::identity<QChar> {};

}}} // namespace boost { namespace spirit { namespace traits{

namespace boost { namespace spirit { namespace char_class{

  /*! \internal Test characters for classification
   */
  template<>
  struct classify<boost::spirit::char_encoding::qchar>
  {
    using char_type = boost::spirit::char_encoding::qchar::char_type;

#define BOOST_SPIRIT_CLASSIFY(name, isname)                                                           \
        template <typename Char>                                                                      \
        static                                                                                        \
        bool is(tag::name, Char ch)                                                                   \
        {                                                                                             \
            return boost::spirit::char_encoding::qchar::isname BOOST_PREVENT_MACRO_SUBSTITUTION (ch); \
        }

    BOOST_SPIRIT_CLASSIFY(char_, ischar)
    BOOST_SPIRIT_CLASSIFY(alnum, isalnum)
    BOOST_SPIRIT_CLASSIFY(alpha, isalpha)
    BOOST_SPIRIT_CLASSIFY(blank, isblank)
    BOOST_SPIRIT_CLASSIFY(space, isspace)
    BOOST_SPIRIT_CLASSIFY(cntrl, iscntrl)
    BOOST_SPIRIT_CLASSIFY(digit, isdigit)
    BOOST_SPIRIT_CLASSIFY(xdigit, isxdigit)
    BOOST_SPIRIT_CLASSIFY(graph, isgraph)
    BOOST_SPIRIT_CLASSIFY(lower, islower)
    BOOST_SPIRIT_CLASSIFY(upper, isupper)
    BOOST_SPIRIT_CLASSIFY(print, isprint)
    BOOST_SPIRIT_CLASSIFY(punct, ispunct)

#undef BOOST_SPIRIT_CLASSIFY
  };

}}} // namespace boost { namespace spirit { namespace char_class{

namespace boost { namespace spirit { namespace qi{

  /*! \internal
   *
   * Hoist the char classification namespaces into qi sub-namespaces
   * of the same name
   */
  namespace qchar { using namespace boost::spirit::qchar; }

}}} // namespace boost { namespace spirit { namespace qi{

#endif // #ifndef MDT_PLAIN_TEXT_BOOST_SPIRIT_QSTRING_ENCODING_H
