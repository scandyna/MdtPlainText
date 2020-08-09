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

namespace Mdt{ namespace PlainText{

  /*! \brief QString wrapper to be passed as attribute to a boost Spirit Karma generator
   */
  class BoostSpiritKarmaQStringContainer
  {
   public:

    using const_iterator = QStringConstIterator;

    using value_type = uint32_t;

    BoostSpiritKarmaQStringContainer() = delete;

    /*! \brief Construct a container from \a str
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

  /*! \internal
   */
  template <>
  struct container_iterator<const Mdt::PlainText::BoostSpiritKarmaQStringContainer>
  {
    using type = Mdt::PlainText::BoostSpiritKarmaQStringContainer::const_iterator;
  };

}}} // namespace boost { namespace spirit { namespace traits{

#endif // #ifndef MDT_PLAIN_TEXT_BOOST_SPIRIT_KARMA_QSTRING_CONTAINER_H
