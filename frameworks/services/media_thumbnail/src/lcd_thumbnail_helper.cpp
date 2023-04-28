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
#define MLOG_TAG "Thumbnail"

#include <fcntl.h>

#include "lcd_thumbnail_helper.h"
#include "medialibrary_errno.h"
#include "media_log.h"
#include "thumbnail_const.h"
#include "thumbnail_utils.h"
#include "thumbnail_utils.h"

using namespace std;
using namespace OHOS::DistributedKv;
using namespace OHOS::NativeRdb;

namespace OHOS {
namespace Media {
int32_t LcdThumbnailHelper::CreateThumbnail(ThumbRdbOpt &opts, bool isSync)
{
    int err = E_ERR;
    ThumbnailData thumbnailData;
    auto rdbSet = QueryThumbnailInfo(opts, thumbnailData, err);
    if (rdbSet == nullptr) {
        MEDIA_ERR_LOG("QueryThumbnailInfo Faild [ %{public}d ]", err);
        return err;
    }
    rdbSet.reset();

    if (!thumbnailData.lcdKey.empty()) {
        ThumbnailData tmpData = thumbnailData;
        ThumbnailUtils::GenLcdKey(tmpData);
        if (tmpData.lcdKey == thumbnailData.lcdKey) {
            MEDIA_DEBUG_LOG("CreateLcd key is same, no need generate");
            return E_OK;
        }
    }

    if (isSync) {
        DoCreateLcd(opts, thumbnailData, true);
    } else {
        IThumbnailHelper::AddAsyncTask(IThumbnailHelper::CreateLcd, opts, thumbnailData, true);
    }
    return E_OK;
}

int32_t LcdThumbnailHelper::GetThumbnailPixelMap(ThumbRdbOpt &opts)
{
    int err;
    ThumbnailWait thumbnailWait(false);
    thumbnailWait.CheckAndWait(opts.row, true);
    ThumbnailData thumbnailData;
    auto rdbSet = QueryThumbnailInfo(opts, thumbnailData, err);
    if (rdbSet == nullptr) {
        MEDIA_ERR_LOG("QueryThumbnailInfo Faild [ %{public}d ]", err);
        return E_ERR;
    }
    rdbSet.reset();

    if (thumbnailData.lcdKey.empty()) {
        if (!opts.networkId.empty()) {
            auto remoteQuery = ThumbnailUtils::QueryRemoteThumbnail(opts, thumbnailData, err);
            if ((!remoteQuery || thumbnailData.lcdKey.empty()) &&
                !IThumbnailHelper::DoThumbnailSync(opts, thumbnailData)) {
                return E_THUMBNAIL_REMOTE_CREATE_FAIL;
            }
        } else if (!DoCreateLcd(opts, thumbnailData)) {
            MEDIA_ERR_LOG("DoCreateLcd Faild");
            return E_THUMBNAIL_LOCAL_CREATE_FAIL;
        }
    }

    string fileName = ThumbnailUtils::GetThumbPath(thumbnailData.path, thumbnailData.lcdKey);
    if (access(fileName.c_str(), F_OK) != 0) {
        MEDIA_ERR_LOG("image not exist, key [%{public}s]", thumbnailData.lcdKey.c_str());
        if (!DoCreateLcd(opts, thumbnailData, true)) {
            return E_THUMBNAIL_LOCAL_CREATE_FAIL;
        }
    }
    auto fd = open(fileName.c_str(), O_RDONLY);
    if (fd >= 0) {
        ThumbnailUtils::UpdateVisitTime(opts, thumbnailData, err);
        return fd;
    }
    return -errno;
}
} // namespace Media
} // namespace OHOS
