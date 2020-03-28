/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef __StrlUtil_h
#define __StrlUtil_h

class StrlUtil
{
public:
    static size_t strlcpy(char *dst, const char *src, size_t siz);
    static size_t strlcat(char *dst, const char *src, size_t siz);

};

#endif // __StrlUtil_h
