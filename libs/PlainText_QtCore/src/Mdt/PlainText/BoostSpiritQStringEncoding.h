/*
 * Copyright Philippe Steinmann 2020 - 2020.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE.txt or copy at
 * https://www.boost.org/LICENSE_1_0.txt)
 *
 * This code is inspired from the this post:
 * http://boost.2283326.n4.nabble.com/QString-and-QChar-support-in-qi-td3555736.html
 *
 * and from the Spirit documentation:
 * https://www.boost.org/doc/libs/1_73_0/libs/spirit/doc/html/spirit/qi/reference/basics.html
 */
#ifndef MDT_PLAIN_TEXT_BOOST_SPIRIT_QSTRING_ENCODING_H
#define MDT_PLAIN_TEXT_BOOST_SPIRIT_QSTRING_ENCODING_H

#include <QChar>
// #include <QString>
#include <boost/spirit/include/qi.hpp>

namespace boost { namespace spirit { namespace char_encoding{

  struct qchar
  {
    using char_type = QChar;

    // isascii_

    static
    bool ischar(const QChar &)
    {
      return true;
    }

    // isalnum
    // isalpha
    // isdigit
    // isxdigit
    // iscntrl
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
