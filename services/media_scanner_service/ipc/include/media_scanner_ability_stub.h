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

#ifndef MEDIA_SCANNER_ABILITY_STUB_H
#define MEDIA_SCANNER_ABILITY_STUB_H

#include "iremote_broker.h"
#include "iremote_stub.h"
#include "imedia_scanner_ability.h"

namespace OHOS {
namespace Media {
class MediaScannerAbilityStub : public IRemoteStub<IMediaScannerAbility> {
public:
    virtual int32_t OnRemoteRequest(uint32_t code, MessageParcel &data, MessageParcel &reply,
            MessageOption &option) override;

private:
    int32_t HandleScanDir(MessageParcel& data, MessageParcel &reply);
    int32_t HandleScanFile(MessageParcel& data, MessageParcel &reply);
    int32_t HandleMediaScannerAbilitySetCallback(MessageParcel& data);
    int32_t HandleGetScanStatus(MessageParcel& data, MessageParcel& reply);
};
} // namespace Media
} // namespace OHOS
#endif // MEDIA_SCANNER_ABILITY_STUB_H
