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
 ** This code is inspired from the Boost Spirit custom string example
 ** https://www.boost.org/doc/libs/1_73_0/libs/spirit/example/qi/custom_string.cpp
 **
 ****************************************************************************/
#ifndef MDT_PLAIN_TEXT_BOOST_SPIRIT_QSTRING_CONTAINER_H
#define MDT_PLAIN_TEXT_BOOST_SPIRIT_QSTRING_CONTAINER_H

#include <boost/spirit/include/qi.hpp>

#include <boost/spirit/home/qi/detail/assign_to.hpp>

// #include <boost/spirit/home/support/attributes.hpp>

#include <QChar>
#include <QString>

namespace boost { namespace spirit { namespace traits{

  /*! \internal
   *
   * Prototype:
   * \code
   * template <typename Attrib, typename T, typename Enable>
   * struct assign_to_attribute_from_value
   * {
   * };
   * \endcode
   */
  template<>
  struct assign_to_attribute_from_value<QChar, char>
  {
    static void call(const char & val, QChar & attr)
    {
      attr = QChar::fromLatin1(val);
    }
  };

  /*! \internal Make Qi recognize QString as a container
   */
  template<>
  struct is_container<QString> : mpl::true_ {};

  /*! \internal Expose the container's (QString's) value_type
   */
  template<>
  struct container_value<QString> : mpl::identity<QChar> {};

  /*! \internal Define how to insert a new element at the end of the container (QString)
   */
  template<>
  struct push_back_container<QString, QChar>
  {
    static bool call(QString& c, const QChar & val)
    {
        c.append(val);
        return true;
    }
  };

  /*! \internal Test if a QString is empty (required for debug)
   */
  template<>
  struct is_empty_container<QString>
  {
    static bool call(const QString & c)
    {
        return c.isEmpty();
    }
  };

  /*! \internal Define how to stream a QString (required for debug)
   */
  template<typename Out, typename Enable>
  struct print_attribute_debug<Out, QString, Enable>
  {
    static void call(Out & out, const QString & val)
    {
        out << val.toStdString();
    }
  };

}}} // namespace boost { namespace spirit { namespace traits{

#endif // #ifndef MDT_PLAIN_TEXT_BOOST_SPIRIT_QSTRING_CONTAINER_H
