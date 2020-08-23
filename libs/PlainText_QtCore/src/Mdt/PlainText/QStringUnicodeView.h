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
#ifndef MDT_PLAIN_TEXT_QSTRING_UNICODE_VIEW_H
#define MDT_PLAIN_TEXT_QSTRING_UNICODE_VIEW_H

#include "QStringConstIterator.h"
#include <QString>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <iterator>

namespace Mdt{ namespace PlainText{

  /*! \brief QStringUnicodeView is a view on a QString to access its elements as unicode code points
   *
   */
  class QStringUnicodeView
  {
   public:

    /*! \brief STL const_iterator
     */
    using const_iterator = QStringConstIterator;

    /*! \brief STL value_type
     */
    using value_type = uint32_t;

    /*! \brief STL size_type
     */
    using size_type = int;

    QStringUnicodeView() = default;

    /*! \brief Construct a view from \a str
     */
    explicit QStringUnicodeView(const QString & str) noexcept
     : mBegin( str.cbegin(), str.cend() ),
       mEnd( str.cend(), str.cend() )
    {
    }

    /*! \brief Assign \a str to this view
     */
    QStringUnicodeView & operator=(const QString & str) noexcept
    {
      mBegin = QStringConstIterator( str.cbegin(), str.cend() );
      mEnd = QStringConstIterator( str.cend(), str.cend() );

      return *this;
    }

    /*! \brief Copy construct a view from \a other
     */
    QStringUnicodeView(const QStringUnicodeView & other) noexcept = default;

    /*! \brief Copy assign \a other to this view
     */
    QStringUnicodeView & operator=(const QStringUnicodeView & other) noexcept = default;

    /*! \brief Move construct a view from \a other
     */
    QStringUnicodeView(QStringUnicodeView && other) noexcept = default;

    /*! \brief Move assign \a other to this view
     */
    QStringUnicodeView & operator=(QStringUnicodeView && other) noexcept = default;

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

    /*! \brief Return a QString from this view
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

#endif // #ifndef MDT_PLAIN_TEXT_QSTRING_UNICODE_VIEW_H
