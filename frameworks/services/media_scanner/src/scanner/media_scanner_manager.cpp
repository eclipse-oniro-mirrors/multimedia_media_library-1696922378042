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

#define MLOG_TAG "Scanner"

#include "media_scanner_manager.h"

#include "media_log.h"
#include "medialibrary_errno.h"

namespace OHOS {
namespace Media {
std::shared_ptr<MediaScannerManager> MediaScannerManager::instance_ = nullptr;
std::mutex MediaScannerManager::instanceMutex_;

std::shared_ptr<MediaScannerManager> MediaScannerManager::GetInstance()
{
    if (instance_ == nullptr) {
        std::lock_guard<std::mutex> guard(instanceMutex_);
        instance_ = std::shared_ptr<MediaScannerManager>(new MediaScannerManager());
    }

    return instance_;
}

int32_t MediaScannerManager::ScanFile(std::string &path, const std::shared_ptr<IMediaScannerCallback> &callback)
{
    MEDIA_DEBUG_LOG("scan file %{private}s", path.c_str());

    if (path.empty()) {
        MEDIA_ERR_LOG("path is empty");
        return E_INVALID_PATH;
    }

    if (ScannerUtils::GetRealPath(path) != ERR_SUCCESS) {
        MEDIA_ERR_LOG("invalid path %{private}s", path.c_str());
        return E_INVALID_PATH;
    }

    if (ScannerUtils::IsDirectory(path)) {
        MEDIA_ERR_LOG("path %{private}s is a dir", path.c_str());
        return E_INVALID_PATH;
    }

    std::unique_ptr<MediaScannerObj> scanner = std::make_unique<MediaScannerObj>(path, callback, false);
    executor_.Commit(move(scanner));

    return E_OK;
}

int32_t MediaScannerManager::ScanDir(std::string &path, const std::shared_ptr<IMediaScannerCallback> &callback)
{
    MEDIA_DEBUG_LOG("scan dir %{private}s", path.c_str());

    if (path.empty()) {
        MEDIA_ERR_LOG("path is empty");
        return E_INVALID_PATH;
    }

    if (ScannerUtils::GetRealPath(path) != ERR_SUCCESS) {
        MEDIA_ERR_LOG("invalid path %{private}s", path.c_str());
        return E_INVALID_PATH;
    }

    if (!ScannerUtils::IsDirectory(path)) {
        MEDIA_ERR_LOG("path %{private}s isn't a dir", path.c_str());
        return E_INVALID_PATH;
    }

    std::unique_ptr<MediaScannerObj> scanner = std::make_unique<MediaScannerObj>(path, callback, true);
    executor_.Commit(move(scanner));

    return E_OK;
}
} // namespace Media
} // namespace OHOS