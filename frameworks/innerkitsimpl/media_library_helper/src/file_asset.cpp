/*
 * Copyright (C) 2021-2023 Huawei Device Co., Ltd.
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
#define MLOG_TAG "FileAsset"

#include "file_asset.h"

#include <fcntl.h>
#include <fstream>
#include <unistd.h>

#include "datashare_business_error.h"
#include "datashare_predicates.h"
#include "datashare_result_set.h"
#include "directory_ex.h"
#include "media_column.h"
#include "media_file_utils.h"
#include "media_log.h"
#include "medialibrary_db_const.h"
#include "medialibrary_helper_container.h"
#include "medialibrary_errno.h"
#include "medialibrary_type_const.h"
#include "uri.h"
#include "values_bucket.h"

using namespace std;

namespace OHOS {
namespace Media {
static constexpr int MAP_INT_MAX = 50;
FileAsset::FileAsset()
    : albumUri_(DEFAULT_MEDIA_ALBUM_URI), typeMask_(DEFAULT_TYPE_MASK), resultNapiType_(ResultNapiType::TYPE_NAPI_MAX)
{
    member_.reserve(MAP_INT_MAX);
}

int32_t FileAsset::GetId() const
{
    return GetInt32Member(MEDIA_DATA_DB_ID);
}

void FileAsset::SetId(int32_t id)
{
    member_[MEDIA_DATA_DB_ID] = id;
}

int32_t FileAsset::GetCount() const
{
    return count_;
}

void FileAsset::SetCount(int32_t count)
{
    count_ = count;
}

const string &FileAsset::GetUri() const
{
    return GetStrMember(MEDIA_DATA_DB_URI);
}

void FileAsset::SetUri(const string &uri)
{
    member_[MEDIA_DATA_DB_URI] = uri;
}

const string &FileAsset::GetPath() const
{
    return GetStrMember(MEDIA_DATA_DB_FILE_PATH);
}

void FileAsset::SetPath(const string &path)
{
    member_[MEDIA_DATA_DB_FILE_PATH] = path;
}

const string &FileAsset::GetRelativePath() const
{
    return GetStrMember(MEDIA_DATA_DB_RELATIVE_PATH);
}

void FileAsset::SetRelativePath(const string &relativePath)
{
    member_[MEDIA_DATA_DB_RELATIVE_PATH] = relativePath;
}

const string &FileAsset::GetMimeType() const
{
    return GetStrMember(MEDIA_DATA_DB_MIME_TYPE);
}

void FileAsset::SetMimeType(const string &mimeType)
{
    member_[MEDIA_DATA_DB_MIME_TYPE] = mimeType;
}

MediaType FileAsset::GetMediaType() const
{
    return static_cast<Media::MediaType>(GetInt32Member(MEDIA_DATA_DB_MEDIA_TYPE));
}

void FileAsset::SetMediaType(MediaType mediaType)
{
    member_[MEDIA_DATA_DB_MEDIA_TYPE] = mediaType;
}

const string &FileAsset::GetDisplayName() const
{
    return GetStrMember(MEDIA_DATA_DB_NAME);
}

void FileAsset::SetDisplayName(const string &displayName)
{
    member_[MEDIA_DATA_DB_NAME] = displayName;
}

int64_t FileAsset::GetSize() const
{
    return GetInt64Member(MEDIA_DATA_DB_SIZE);
}

void FileAsset::SetSize(int64_t size)
{
    member_[MEDIA_DATA_DB_SIZE] = size;
}

int64_t FileAsset::GetDateAdded() const
{
    return GetInt64Member(MEDIA_DATA_DB_DATE_ADDED);
}

void FileAsset::SetDateAdded(int64_t dateAdded)
{
    member_[MEDIA_DATA_DB_DATE_ADDED] = dateAdded;
}

int64_t FileAsset::GetDateModified() const
{
    return GetInt64Member(MEDIA_DATA_DB_DATE_MODIFIED);
}

void FileAsset::SetDateModified(int64_t dateModified)
{
    member_[MEDIA_DATA_DB_DATE_MODIFIED] = dateModified;
}

const string &FileAsset::GetTitle() const
{
    return GetStrMember(MEDIA_DATA_DB_TITLE);
}

void FileAsset::SetTitle(const string &title)
{
    member_[MEDIA_DATA_DB_TITLE] = title;
}

const string &FileAsset::GetArtist() const
{
    return GetStrMember(MEDIA_DATA_DB_ARTIST);
}

void FileAsset::SetArtist(const string &artist)
{
    member_[MEDIA_DATA_DB_ARTIST] = artist;
}

const string &FileAsset::GetAlbum() const
{
    return GetStrMember(MEDIA_DATA_DB_ALBUM);
}

void FileAsset::SetAlbum(const string &album)
{
    member_[MEDIA_DATA_DB_ALBUM] = album;
}

int32_t FileAsset::GetPosition() const
{
    return GetInt32Member(MEDIA_DATA_DB_POSITION);
}

void FileAsset::SetPosition(int32_t position)
{
    member_[MEDIA_DATA_DB_POSITION] = position;
}

int32_t FileAsset::GetWidth() const
{
    return GetInt32Member(MEDIA_DATA_DB_WIDTH);
}

void FileAsset::SetWidth(int32_t width)
{
    member_[MEDIA_DATA_DB_WIDTH] = width;
}

int32_t FileAsset::GetHeight() const
{
    return GetInt32Member(MEDIA_DATA_DB_HEIGHT);
}

void FileAsset::SetHeight(int32_t height)
{
    member_[MEDIA_DATA_DB_HEIGHT] = height;
}

int32_t FileAsset::GetDuration() const
{
    return GetInt32Member(MEDIA_DATA_DB_DURATION);
}

void FileAsset::SetDuration(int32_t duration)
{
    member_[MEDIA_DATA_DB_DURATION] = duration;
}

int32_t FileAsset::GetOrientation() const
{
    return GetInt32Member(MEDIA_DATA_DB_ORIENTATION);
}

void FileAsset::SetOrientation(int32_t orientation)
{
    member_[MEDIA_DATA_DB_ORIENTATION] = orientation;
}

int32_t FileAsset::GetAlbumId() const
{
    return GetInt32Member(MEDIA_DATA_DB_BUCKET_ID);
}

void FileAsset::SetAlbumId(int32_t albumId)
{
    member_[MEDIA_DATA_DB_BUCKET_ID] = albumId;
}

const string &FileAsset::GetAlbumName() const
{
    return GetStrMember(MEDIA_DATA_DB_BUCKET_NAME);
}

void FileAsset::SetAlbumName(const string &albumName)
{
    member_[MEDIA_DATA_DB_BUCKET_NAME] = albumName;
}

int32_t FileAsset::GetParent() const
{
    return GetInt32Member(MEDIA_DATA_DB_PARENT_ID);
}

void FileAsset::SetParent(int32_t parent)
{
    member_[MEDIA_DATA_DB_PARENT_ID] = parent;
}

const string &FileAsset::GetAlbumUri() const
{
    return albumUri_;
}

void FileAsset::SetAlbumUri(const string &albumUri)
{
    albumUri_ = albumUri;
}

const string &FileAsset::GetTypeMask() const
{
    return typeMask_;
}

void FileAsset::SetTypeMask(const string &typeMask)
{
    typeMask_ = typeMask;
}

int64_t FileAsset::GetDateTaken() const
{
    return GetInt64Member(MEDIA_DATA_DB_DATE_TAKEN);
}

void FileAsset::SetDateTaken(int64_t dateTaken)
{
    member_[MEDIA_DATA_DB_DATE_TAKEN] = dateTaken;
}

int64_t FileAsset::GetTimePending() const
{
    return GetInt64Member(MEDIA_DATA_DB_TIME_PENDING);
}

void FileAsset::SetTimePending(int64_t timePending)
{
    member_[MEDIA_DATA_DB_TIME_PENDING] = timePending;
}

bool FileAsset::IsFavorite() const
{
    return GetInt32Member(MEDIA_DATA_DB_IS_FAV);
}

void FileAsset::SetFavorite(bool isFavorite)
{
    member_[MEDIA_DATA_DB_IS_FAV] = isFavorite;
}

int64_t FileAsset::GetDateTrashed() const
{
    return GetInt64Member(MEDIA_DATA_DB_DATE_TRASHED);
}

void FileAsset::SetDateTrashed(int64_t dateTrashed)
{
    member_[MEDIA_DATA_DB_DATE_TRASHED] = dateTrashed;
}

const string &FileAsset::GetSelfId() const
{
    return GetStrMember(MEDIA_DATA_DB_SELF_ID);
}

void FileAsset::SetSelfId(const string &selfId)
{
    member_[MEDIA_DATA_DB_SELF_ID] = selfId;
}

int32_t FileAsset::GetIsTrash() const
{
    if (resultNapiType_ == ResultNapiType::TYPE_USERFILE_MGR ||
        resultNapiType_ == ResultNapiType::TYPE_PHOTOACCESS_HELPER) {
        return static_cast<int32_t>(GetInt64Member(MediaColumn::MEDIA_DATE_TRASHED));
    }

    return GetInt32Member(MEDIA_DATA_DB_IS_TRASH);
}

void FileAsset::SetIsTrash(int32_t isTrash)
{
    member_[MEDIA_DATA_DB_IS_TRASH] = isTrash;
}

const string &FileAsset::GetRecyclePath() const
{
    return GetStrMember(MEDIA_DATA_DB_RECYCLE_PATH);
}

void FileAsset::SetRecyclePath(const string &recyclePath)
{
    member_[MEDIA_DATA_DB_RECYCLE_PATH] = recyclePath;
}

const string FileAsset::GetOwnerPackage() const
{
    return GetStrMember(MEDIA_DATA_DB_OWNER_PACKAGE);
}

void FileAsset::SetOwnerPackage(const string &packageName)
{
    member_[MEDIA_DATA_DB_OWNER_PACKAGE] = packageName;
}

ResultNapiType FileAsset::GetResultNapiType() const
{
    return resultNapiType_;
}

void FileAsset::SetResultNapiType(const ResultNapiType type)
{
    resultNapiType_ = type;
}

int32_t FileAsset::GetPhotoSubType() const
{
    return GetInt32Member(PhotoColumn::PHOTO_SUBTYPE);
}

void FileAsset::SetPhotoSubType(int32_t photoSubType)
{
    member_[PhotoColumn::PHOTO_SUBTYPE] = photoSubType;
}

bool FileAsset::IsHidden() const
{
    return GetInt32Member(MediaColumn::MEDIA_HIDDEN);
}

void FileAsset::SetHidden(bool isHidden)
{
    member_[MediaColumn::MEDIA_HIDDEN] = isHidden;
}

void FileAsset::SetOpenStatus(int32_t fd, int32_t openStatus)
{
    lock_guard<mutex> lock(openStatusMapMutex_);
    if (openStatusMap_ == nullptr) {
        openStatusMap_ = make_shared<unordered_map<int32_t, int32_t>>();
    }
    openStatusMap_->insert({fd, openStatus});
}

void FileAsset::RemoveOpenStatus(int32_t fd)
{
    lock_guard<mutex> lock(openStatusMapMutex_);
    if (openStatusMap_ == nullptr) {
        return;
    }
    openStatusMap_->erase(fd);
}

int32_t FileAsset::GetOpenStatus(int32_t fd)
{
    lock_guard<mutex> lock(openStatusMapMutex_);
    if (openStatusMap_ == nullptr) {
        return E_INVALID_VALUES;
    }
    if (openStatusMap_->find(fd) != openStatusMap_->end()) {
        return openStatusMap_->at(fd);
    } else {
        MEDIA_ERR_LOG("can not find this fd: [%{public}d]", fd);
        return E_INVALID_VALUES;
    }
}

unordered_map<string, variant<int32_t, int64_t, string>> &FileAsset::GetMemberMap()
{
    return member_;
}

variant<int32_t, int64_t, string> &FileAsset::GetMemberValue(const string &name)
{
    return member_[name];
}

const string &FileAsset::GetStrMember(const string &name) const
{
    return (member_.count(name) > 0) ? get<string>(member_.at(name)) : DEFAULT_STR;
}

int32_t FileAsset::GetInt32Member(const string &name) const
{
    return (member_.count(name) > 0) ? get<int32_t>(member_.at(name)) : DEFAULT_INT32;
}

int64_t FileAsset::GetInt64Member(const string &name) const
{
    return (member_.count(name) > 0) ? get<int64_t>(member_.at(name)) : DEFAULT_INT64;
}

void FileAsset::CommitModify()
{
    if (!MediaFileUtils::CheckDisplayName(GetStrMember(MEDIA_DATA_DB_NAME))) {
        MEDIA_ERR_LOG("CommitModify CheckDisplayName fail, fileUri=%{private}s", GetUri().c_str());
        return;
    }

    shared_ptr<DataShare::DataShareHelper> dataShareHelper =
        MediaLibraryHelperContainer::GetInstance()->GetDataShareHelper();
    if (dataShareHelper == nullptr) {
        MEDIA_ERR_LOG("Get DataShareHelper fail, fileUri=%{private}s", GetUri().c_str());
        return;
    }

    string uri = MEDIALIBRARY_DATA_URI + "/" + Media::MEDIA_FILEOPRN + "/" + Media::MEDIA_FILEOPRN_MODIFYASSET;
    MediaFileUtils::UriAddFragmentTypeMask(uri, typeMask_);
    Uri updateAssetUri(uri);
    // use it in api10
    string notifyUri = MediaFileUtils::GetMediaTypeUriV10(
        static_cast<Media::MediaType>(GetInt32Member(MEDIA_DATA_DB_MEDIA_TYPE)));
    DataShare::DataSharePredicates predicates;
    DataShare::DataShareValuesBucket valuesBucket;
    valuesBucket.Put(MEDIA_DATA_DB_DATE_ADDED, GetInt64Member(MEDIA_DATA_DB_DATE_ADDED));
    valuesBucket.Put(MEDIA_DATA_DB_DATE_MODIFIED, GetInt64Member(MEDIA_DATA_DB_DATE_MODIFIED));
    predicates.SetWhereClause(MEDIA_DATA_DB_ID + " = ? ");
    predicates.SetWhereArgs({to_string(GetInt32Member(MEDIA_DATA_DB_ID))});
    int32_t changedRows = dataShareHelper->Update(updateAssetUri, predicates, valuesBucket);
    if (changedRows < 0) {
        MEDIA_ERR_LOG("File asset modification failed, err: %{public}d", changedRows);
    } else {
        Uri modifyNotify(notifyUri);
        dataShareHelper->NotifyChange(modifyNotify);
    }
}

bool FileAsset::IsDirectory()
{
    int32_t mediaType = -1;
#ifdef MEDIALIBRARY_COMPATIBILITY
    if ((GetMediaType() == MediaType::MEDIA_TYPE_AUDIO) ||
        (GetMediaType() == MediaType::MEDIA_TYPE_IMAGE) ||
        (GetMediaType() == MediaType::MEDIA_TYPE_VIDEO)) {
        return false;
    }
    int64_t virtualId = MediaFileUtils::GetVirtualIdByType(GetId(), MediaType::MEDIA_TYPE_FILE);
    vector<string> selectionArgs = { to_string(virtualId)};
#else
    vector<string> selectionArgs = { to_string(GetId())};
#endif
    shared_ptr<DataShare::DataShareHelper> dataShareHelper =
        MediaLibraryHelperContainer::GetInstance()->GetDataShareHelper();
    if (dataShareHelper == nullptr) {
        MEDIA_ERR_LOG("Get DataShareHelper fail");
        return false;
    }
    vector<string> columns = { MEDIA_DATA_DB_MEDIA_TYPE };
    DataShare::DataSharePredicates predicates;
    predicates.SetWhereClause(MEDIA_DATA_DB_ID + " = ?");
    predicates.SetWhereArgs(selectionArgs);
    string queryUri = MEDIALIBRARY_DATA_URI;
    Uri uri(queryUri);
    DataShare::DatashareBusinessError businessError;
    shared_ptr<DataShare::DataShareResultSet> resultSet = dataShareHelper->Query(uri,
        predicates, columns, &businessError);
    if (resultSet == nullptr || resultSet->GoToFirstRow() != ERR_OK) {
        MEDIA_ERR_LOG("Query IsDirectory failed");
        return false;
    }
    int32_t index = 0;
    if (resultSet->GetColumnIndex(MEDIA_DATA_DB_MEDIA_TYPE, index) != ERR_OK) {
        MEDIA_ERR_LOG("Query Directory failed");
        return false;
    }
    if (resultSet->GetInt(index, mediaType) != ERR_OK) {
        MEDIA_ERR_LOG("Can not get file path");
        return false;
    }
    return mediaType == static_cast<int>(MediaType::MEDIA_TYPE_ALBUM);
}
}  // namespace Media
}  // namespace OHOS
