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
#ifndef FRAMEWORKS_MEDIATOOLS_COMMAND_COMMAND_H_
#define FRAMEWORKS_MEDIATOOLS_COMMAND_COMMAND_H_
#include <memory>
#include <vector>

#include "exec_env.h"
#include "userfile_manager_types.h"

namespace OHOS {
namespace Media {
namespace MediaTool {
class Command {
public:
    Command() = default;
    virtual ~Command() = default;
    Command(const Command &command) = delete;
    Command(Command&& command) = delete;
    Command& operator=(const Command &command) = delete;
    Command& operator=(Command&& command) = delete;
    static std::unique_ptr<Command> Create(const ExecEnv &env);
    virtual int32_t Start(const ExecEnv &env) = 0;
protected:
    static const std::vector<MediaType> &GetSupportTypes();
};
} // namespace MediaTool
} // namespace Media
} // namespace OHOS
#endif // FRAMEWORKS_MEDIATOOLS_COMMAND_COMMAND_H_