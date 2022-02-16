/*
 * Copyright (C) 2021 Huawei Device Co., Ltd.
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

#ifndef OHOS_MEDIA_LOG_H
#define OHOS_MEDIA_LOG_H

#include <stdio.h>
#include "hilog/log.h"

#undef LOG_DOMAIN
#undef LOG_TAG
#define LOG_DOMAIN 0xD002B00
#define LOG_TAG "MultiMedia:MediaLibrary"

#define __FILENAME__ (__builtin_strrchr(__FILE__, '/') ? __builtin_strrchr(__FILE__, '/') + 1 : __FILE__)

#ifndef OHOS_DEBUG
#define DECORATOR_HILOG(op, fmt, args...) \
    do {                                  \
        op(LOG_CORE, "{%s()} " fmt, __FUNCTION__, ##args);        \
    } while (0)
#else
#define DECORATOR_HILOG(op, fmt, args...)                                                \
    do {                                                                                 \
        op(LOG_CORE, "{%s()-%s:%d} " fmt, __FUNCTION__, __FILENAME__, __LINE__, ##args); \
    } while (0)
#endif

#define CHECK_AND_RETURN_RET_LOG(cond, ret, fmt, ...)  \
    do {                                               \
        if (!(cond)) {                                 \
            MEDIA_ERR_LOG(fmt, ##__VA_ARGS__);         \
            return ret;                                \
        }                                              \
    } while (0)

#define CHECK_AND_RETURN_LOG(cond, fmt, ...)           \
    do {                                               \
        if (!(cond)) {                                 \
            MEDIA_ERR_LOG(fmt, ##__VA_ARGS__);         \
            return;                                    \
        }                                              \
    } while (0)

#define CHECK_AND_PRINT_LOG(cond, fmt, ...)            \
    do {                                               \
        if (!(cond)) {                                 \
            MEDIA_ERR_LOG(fmt, ##__VA_ARGS__);         \
        }                                              \
    } while (0)

#define MEDIA_DEBUG_LOG(fmt, ...) DECORATOR_HILOG(HILOG_DEBUG, fmt, ##__VA_ARGS__)
#define MEDIA_ERR_LOG(fmt, ...) DECORATOR_HILOG(HILOG_ERROR, fmt, ##__VA_ARGS__)
#define MEDIA_WARNING_LOG(fmt, ...) DECORATOR_HILOG(HILOG_WARN, fmt, ##__VA_ARGS__)
#define MEDIA_INFO_LOG(fmt, ...) DECORATOR_HILOG(HILOG_INFO, fmt, ##__VA_ARGS__)
#define MEDIA_FATAL_LOG(fmt, ...) DECORATOR_HILOG(HILOG_FATAL, fmt, ##__VA_ARGS__)

#define MEDIA_OK 0
#define MEDIA_INVALID_PARAM (-1)
#define MEDIA_INIT_FAIL (-2)
#define MEDIA_ERR (-3)
#define MEDIA_PERMISSION_DENIED (-4)

#endif // OHOS_MEDIA_LOG_H
