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
#ifndef MDT_PLAIN_TEXT_BOOST_SPIRIT_KARMA_QSTRING_UNICODE_VIEW_H
#define MDT_PLAIN_TEXT_BOOST_SPIRIT_KARMA_QSTRING_UNICODE_VIEW_H

#include "QStringUnicodeView.h"
#include <boost/spirit/include/karma.hpp>

namespace boost { namespace spirit { namespace traits{

  /*! \internal
   */
  template <>
  struct is_container<const Mdt::PlainText::QStringUnicodeView> : mpl::true_ {};

//   /*! \internal
//    */
//   template <>
//   struct extract_from_attribute<uint32_t, const Mdt::PlainText::BoostSpiritKarmaQStringContainer>
//   {
//     template <typename Context>
//     static
//     uint32_t call(const Mdt::PlainText::BoostSpiritKarmaQStringContainer & c, Context&)
//     {
//     }
//   };

//   /*! \internal
//    */
//   template <>
//   struct extract_from_container<uint32_t, const Mdt::PlainText::BoostSpiritKarmaQStringContainer>
//   {
//     template <typename Context>
//     static
//     uint32_t call(const Mdt::PlainText::BoostSpiritKarmaQStringContainer & c, Context&)
//     {
//     }
//   };

  /*! \internal
   */
  template <>
  struct container_iterator<const Mdt::PlainText::QStringUnicodeView>
  {
    using type = Mdt::PlainText::QStringUnicodeView::const_iterator;
  };

  /*! \internal Define how to stream a BoostSpiritKarmaQStringContainer (required for debug)
   */
  template<typename Out, typename Enable>
  struct print_attribute_debug<Out, Mdt::PlainText::QStringUnicodeView, Enable>
  {
    static void call(Out & out, const Mdt::PlainText::QStringUnicodeView & c)
    {
      out << c.toQString().toStdString();
    }
  };

}}} // namespace boost { namespace spirit { namespace traits{

#endif // #ifndef MDT_PLAIN_TEXT_BOOST_SPIRIT_KARMA_QSTRING_UNICODE_VIEW_H
