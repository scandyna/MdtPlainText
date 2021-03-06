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
 ****************************************************************************/
#ifndef MDT_PLAIN_TEXT_BOOST_SPIRIT_KARMA_QSTRING_SUPPORT_H
#define MDT_PLAIN_TEXT_BOOST_SPIRIT_KARMA_QSTRING_SUPPORT_H

#include "QStringUnicodeView.h"
#include "QStringContainerUnicodeView.h"
#include "Mdt/PlainText/ContainerAliasView.h"
#include <boost/spirit/include/karma.hpp>

namespace boost { namespace spirit { namespace traits{

  /*! \internal Define how to stream a QStringUnicodeView (required for debug)
   */
  template<typename Out, typename Enable>
  struct print_attribute_debug<Out, Mdt::PlainText::QStringUnicodeView, Enable>
  {
    static void call(Out & out, const Mdt::PlainText::QStringUnicodeView & c)
    {
      out << c.toQString().toStdString();
    }
  };

  /*! \internal Define how to stream a QStringContainerUnicodeView (required for debug)
   */
  template<typename Container, typename Out, typename Enable>
  struct print_attribute_debug<Out, Mdt::PlainText::QStringContainerUnicodeView<Container>, Enable>
  {
    static void call(Out & out, const Mdt::PlainText::QStringContainerUnicodeView<Container> & container)
    {
      auto first = container.cbegin();
      const auto last = container.cend();

      out << '[';
      if(first != last){
        const Mdt::PlainText::QStringUnicodeView str = *first;
        out << str.toQString().toStdString();
        ++first;
      }
      while(first != last){
        const Mdt::PlainText::QStringUnicodeView str = *first;
        out << ',' << str.toQString().toStdString();
        ++first;
      }
      out << ']';
    }
  };

  /*! \internal Define how to stream a ContainerAliasView of QStringContainerUnicodeView (required for debug)
   */
  template<typename List, typename Container, typename Out, typename Enable>
  struct print_attribute_debug<Out, Mdt::PlainText::ContainerAliasView< List, Mdt::PlainText::QStringContainerUnicodeView<Container> >, Enable>
  {
    static void call(Out & out, const Mdt::PlainText::ContainerAliasView< List, Mdt::PlainText::QStringContainerUnicodeView<Container> > & list)
    {
      using Printer = print_attribute_debug<Out, Mdt::PlainText::QStringContainerUnicodeView<Container>, Enable>;

      auto first = list.cbegin();
      const auto last = list.cend();

      out << '[';
      if(first != last){
        Printer::call(out, *first);
        ++first;
      }
      while(first != last){
        out << ',';
        Printer::call(out, *first);
        ++first;
      }
      out << ']';
    }
  };

}}} // namespace boost { namespace spirit { namespace traits{

#endif // #ifndef MDT_PLAIN_TEXT_BOOST_SPIRIT_KARMA_QSTRING_SUPPORT_H
