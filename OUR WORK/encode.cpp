/*
 * Copyright (C) Pedram Pourang (aka Tsu Jan) 2014-2024 <tsujan2000@gmail.com>
 *
 * FeatherPad is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * FeatherPad is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @license GPL-2.0+ <https://spdx.org/licenses/GPL-2.0+.html>
 */

#include "encoding.h"

namespace FeatherPad {

/* In the GTK+ version, I used g_utf8_validate().
   This function validates UTF-8 directly and fast. */
bool validateUTF8 (const QByteArray byteArray)
{
    const char *string = byteArray.constData();
    if (!string) return true;

    const unsigned char *bytes = (const unsigned char*)string;
    unsigned int cp; // code point
    int bn; // bytes number

    while (*bytes != 0x00)
    {
        /* assuming that UTF-8 maps a sequence of 1-4 bytes,
           we find the code point and the number of bytes */
        if ((*bytes & 0x80) == 0x00)
        { // 0xxxxxxx, all ASCII characters (0-127)
            cp = (*bytes & 0x7F);
            bn = 1;
        }
        else if ((*bytes & 0xE0) == 0xC0)
        { // 110xxxxx 10xxxxxx
            cp = (*bytes & 0x1F);
            bn = 2;
        }
        else if ((*bytes & 0xF0) == 0xE0)
        { // 1110xxxx 10xxxxxx 10xxxxxx
            cp = (*bytes & 0x0F);
            bn = 3;
        }
        else if ((*bytes & 0xF8) == 0xF0)
        { // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
            cp = (*bytes & 0x07);
            bn = 4;
        }
        else
            return false;

        bytes += 1;
        for (int i = 1; i < bn; ++i)
        {
            /* all the other bytes should be of the form 10xxxxxx */
            if ((*bytes & 0xC0) != 0x80)
                return false;
            cp = (cp << 6) | (*bytes & 0x3F);
            bytes += 1;
        }

        if (cp > 0x10FFFF // max code point by definition
            /* the range from 0xd800 to 0xdfff is reserved
               for use with UTF-16 and excluded from UTF-8 */
            || (cp >= 0xD800 && cp <= 0xDFFF)
            /* logically impossible situations */
            || (cp <= 0x007F && bn != 1)
            || (cp >= 0x0080 && cp <= 0x07FF && bn != 2)
            || (cp >= 0x0800 && cp <= 0xFFFF && bn != 3)
            || (cp >= 0x10000 && cp <= 0x1FFFFF && bn != 4))
        {
            return false;
        }
    }

    return true;
}
/*************************/
const QString detectCharset (const QByteArray& byteArray)
{
    if (validateUTF8 (byteArray))
        return QStringLiteral ("UTF-8");
    /* legacy encodings aren't supported by Qt >= Qt6 */
    return QStringLiteral ("ISO-8859-1");
}

}
