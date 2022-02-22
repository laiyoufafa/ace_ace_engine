/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_JAVASCRIPT_EXECUTE_CALLBACK_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_JAVASCRIPT_EXECUTE_CALLBACK_H

#include <string>

#include "value_callback.h"

namespace OHOS::Ace {
using namespace OHOS::WebView;
class WebJavaScriptExecuteCallBack : public OHOS::WebView::ValueCallback<std::string> {
public:
    void OnReceiveValue(std::string result) override
    {
        if (callback_) {
            callback_(result);
        }
    }
    void SetCallBack(const std::function<void(std::string)>&& callback)
    {
        callback_ = callback;
    }
    std::function<void(std::string)> callback_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_JAVASCRIPT_EXECUTE_CALLBACK_H