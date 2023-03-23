/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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

#ifndef INTERFACES_INNERKITS_NATIVE_INCLUDE_PHOTO_ALBUM_ASSET_H_
#define INTERFACES_INNERKITS_NATIVE_INCLUDE_PHOTO_ALBUM_ASSET_H_

#include "userfile_manager_types.h"

namespace OHOS {
namespace Media {
class PhotoAlbumAsset {
public:
    PhotoAlbumAsset();
    virtual ~PhotoAlbumAsset();

    void SetAlbumId(const int32_t photoAlbumId);
    int32_t GetAlbumId() const;

    void SetPhotoAlbumType(const PhotoAlbumType type);
    PhotoAlbumType GetPhotoAlbumType() const;

    void SetPhotoAlbumSubType(const PhotoAlbumSubType subType);
    PhotoAlbumSubType GetPhotoAlbumSubType() const;

    void SetAlbumUri(const std::string &uri);
    const std::string& GetAlbumUri() const;

    void SetAlbumName(const std::string &photoAlbumName);
    const std::string& GetAlbumName() const;

    void SetCoverUri(const std::string &coverUri);
    const std::string& GetCoverUri() const;

    void SetCount(const int32_t count);
    int32_t GetCount() const;

    void SetRelativePath(const std::string &logicalRelativePath);
    const std::string& GetRelativePath() const;

    void SetTypeMask(const std::string &typeMask);
    const std::string& GetTypeMask() const;

    void SetResultNapiType(const ResultNapiType resultNapiType);
    ResultNapiType GetResultNapiType() const;

private:
    int32_t albumId_;
    PhotoAlbumType type_;
    PhotoAlbumSubType subType_;
    std::string uri_;
    std::string albumName_;
    std::string coverUri_;
    int32_t count_;
    std::string relativePath_;

    std::string typeMask_;
    ResultNapiType resultNapiType_;
};
} // namespace Media
} // namespace OHOS

#endif  // INTERFACES_INNERKITS_NATIVE_INCLUDE_PHOTO_ALBUM_ASSET_H_