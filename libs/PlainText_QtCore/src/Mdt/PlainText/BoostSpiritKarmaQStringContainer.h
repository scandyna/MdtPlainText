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
#ifndef MDT_PLAIN_TEXT_BOOST_SPIRIT_KARMA_QSTRING_CONTAINER_H
#define MDT_PLAIN_TEXT_BOOST_SPIRIT_KARMA_QSTRING_CONTAINER_H

#include "QStringConstIterator.h"
#include <QString>
#include <boost/spirit/include/karma.hpp>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <iterator>

namespace Mdt{ namespace PlainText{

  /*! \brief QStringUnicodeView is a view on a QString to access its elements as unicode code points
   *
   *
   */
  class BoostSpiritKarmaQStringContainer
  {
   public:

    /// \todo typdefs should refer to underlaying types..

    /*! \brief STL const_iterator
     */
    using const_iterator = QStringConstIterator;

    /*! \brief STL value_type
     */
    using value_type = uint32_t;

    /*! \brief STL size_type
     */
    using size_type = int;

    BoostSpiritKarmaQStringContainer() = delete;

    /*! \brief Construct a view from \a str
     */
    explicit BoostSpiritKarmaQStringContainer(const QString & str) noexcept
     : mBegin( str.cbegin(), str.cend() ),
       mEnd( str.cend(), str.cend() )
    {
    }

    /*! \brief Copy construct a container from \a other
     */
    BoostSpiritKarmaQStringContainer(const BoostSpiritKarmaQStringContainer & other) noexcept = default;

    /*! \brief Copy assign \a other to this container
     */
    BoostSpiritKarmaQStringContainer & operator=(const BoostSpiritKarmaQStringContainer & other) noexcept = default;

    /*! \brief Move construct a container from \a other
     */
    BoostSpiritKarmaQStringContainer(BoostSpiritKarmaQStringContainer && other) noexcept = default;

    /*! \brief Move assign \a other to this container
     */
    BoostSpiritKarmaQStringContainer & operator=(BoostSpiritKarmaQStringContainer && other) noexcept = default;

    /*! \brief Get a iterator to the beginning
     */
    const_iterator begin() const noexcept
    {
      return mBegin;
    }

    /*! \brief Get a iterator to the end
     */
    const_iterator end() const noexcept
    {
      return mEnd;
    }

    /*! \brief Return a QString from this container
     *
     * \note This can be useful for debug,
     * but can be slow
     */
    QString toQString() const
    {
      if( mBegin == mEnd ){
        return QString();
      }
      std::vector<uint32_t> unicodeBuffer;
      std::copy( mBegin, mEnd, std::back_inserter(unicodeBuffer) );

      return QString::fromUcs4( unicodeBuffer.data(), unicodeBuffer.size() );
    }

   private:

    QStringConstIterator mBegin;
    QStringConstIterator mEnd;
  };

}} // namespace Mdt{ namespace PlainText{

namespace boost { namespace spirit { namespace traits{

  /*! \internal
   */
  template <>
  struct is_container<const Mdt::PlainText::BoostSpiritKarmaQStringContainer> : mpl::true_ {};

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
  struct container_iterator<const Mdt::PlainText::BoostSpiritKarmaQStringContainer>
  {
    using type = Mdt::PlainText::BoostSpiritKarmaQStringContainer::const_iterator;
  };

  /*! \internal Define how to stream a BoostSpiritKarmaQStringContainer (required for debug)
   */
  template<typename Out, typename Enable>
  struct print_attribute_debug<Out, Mdt::PlainText::BoostSpiritKarmaQStringContainer, Enable>
  {
    static void call(Out & out, const Mdt::PlainText::BoostSpiritKarmaQStringContainer & c)
    {
      out << c.toQString().toStdString();
    }
  };

}}} // namespace boost { namespace spirit { namespace traits{

#endif // #ifndef MDT_PLAIN_TEXT_BOOST_SPIRIT_KARMA_QSTRING_CONTAINER_H
