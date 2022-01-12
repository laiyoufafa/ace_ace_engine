/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PLUGIN_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PLUGIN_MANAGER_H

#include <mutex>
#include <unordered_map>

#include "adapter/ohos/entrance/ace_ability.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "base/utils/singleton.h"
#include "core/components/plugin/plugin_sub_container.h"
#include "frameworks/bridge/js_frontend/engine/common/js_engine_loader.h"

namespace OHOS::Ace {
class ACE_EXPORT PluginManager final : public Singleton<PluginManager> {
    DECLARE_SINGLETON(PluginManager);

public:
    void AddPluginSubContainer(int64_t pluginId, const RefPtr<PluginSubContainer>& pluginSubContainer);
    void RemovePluginSubContainer(int64_t pluginId);
    void AddNonmatchedContainer(const std::string& pluginKey, const RefPtr<PluginSubContainer>& pluginSubContainer);
    RefPtr<PluginSubContainer> GetPluginSubContainer(int64_t pluginId);
    RefPtr<PluginSubContainer> MatchPluginSubContainerWithPluginId(int64_t pluginId, const std::string& pluginKey);
    int64_t GetPluginSubContainerId();
    void SetJsEngineLoader(Framework::JsEngineLoader* jsEngineLoader)
    {
        jsEngineLoader_ = jsEngineLoader;
    }

    Framework::JsEngineLoader* GetJsEngineLoader()
    {
        return jsEngineLoader_;
    }

    void SetAceAbility(AceAbility* aceAbility)
    {
        aceAbility_ = aceAbility;
    };

    AceAbility* GetAceAbility() const
    {
        return aceAbility_;
    };

private:
    std::mutex mutex_;
    std::map<int64_t, RefPtr<PluginSubContainer>> pluginSubContainerMap_;
    std::mutex nonmatchedContainerMutex_;
    std::unordered_map<std::string, RefPtr<PluginSubContainer>> nonmatchedContainerMap_;
    Framework::JsEngineLoader* jsEngineLoader_ = nullptr;
    AceAbility* aceAbility_ = nullptr;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PLUGIN_MANAGER_H