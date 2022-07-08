/*
 * Copyright (C) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef OHOS_MEDIALIBRARY_COMMON_UTILS_H
#define OHOS_MEDIALIBRARY_COMMON_UTILS_H

#include <climits>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace OHOS {
namespace Media {
const static size_t HASH_INPUT_MAX_LENGTH = LONG_MAX;

class MediaLibraryCommonUtils {
public:
    static int32_t GenKeySHA256(const std::vector<uint8_t> &input, std::string &key);
    static int32_t GenKeySHA256(const std::string &input, std::string &key);
private:
    MediaLibraryCommonUtils() {};
    ~MediaLibraryCommonUtils() {};

    static void Char2Hex(const unsigned char *data, const size_t len, std::string &hexStr);
    static int32_t GenKey(const unsigned char *data, const size_t len, std::string &key);

    static const std::string CHAR2HEX_TABLE[UCHAR_MAX + 1];
};
} // namespace Media
} // namespace OHOS
#endif // OHOS_MEDIALIBRARY_COMMON_UTILS_H