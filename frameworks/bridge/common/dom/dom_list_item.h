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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_DOM_DOM_LIST_ITEM_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_DOM_DOM_LIST_ITEM_H

#include "core/components/list/list_item_component.h"
#include "core/components/theme/card_theme.h"
#include "frameworks/bridge/common/dom/dom_node.h"
#include "frameworks/bridge/common/dom/dom_type.h"

namespace OHOS::Ace::Framework {

class DOMListItem : public DOMNode {
    DECLARE_ACE_TYPE(DOMListItem, DOMNode);

public:
    DOMListItem(NodeId nodeId, const std::string& nodeName, int32_t forIndex);
    ~DOMListItem() override = default;

    RefPtr<Component> GetSpecializedComponent() override;

    virtual int32_t GetItemIndex() const
    {
        return itemIndex_;
    }

    const std::string& GetItemKey() const
    {
        return indexKey_;
    }

    const RefPtr<ListItemComponent>& GetListItemComponent() const
    {
        return listItemComponent_;
    }

    static RefPtr<DOMListItem> GetDOMListItem(const RefPtr<DOMNode>& node)
    {
        RefPtr<DOMNode> domNode = node;
        while (domNode) {
            auto listItem = AceType::DynamicCast<DOMListItem>(domNode);
            if (listItem) {
                return listItem;
            }
            if (domNode->GetChildList().empty()) {
                return nullptr;
            }
            domNode = domNode->GetChildList().front();
        }
        return nullptr;
    }

    virtual NodeId GetDirtyNodeId() const override;

protected:
    bool SetSpecializedAttr(const std::pair<std::string, std::string>& attr) override;
    bool SetSpecializedStyle(const std::pair<std::string, std::string>& style) override;
    bool AddSpecializedEvent(int32_t pageId, const std::string& event) override;
    void OnChildNodeAdded(const RefPtr<DOMNode>& child, int32_t slot) override;
    void OnChildNodeRemoved(const RefPtr<DOMNode>& child) override;
    void OnMounted(const RefPtr<DOMNode>& parentNode) override;
    void PrepareSpecializedComponent() override;
    RefPtr<Component> CompositeSpecializedComponent(const std::vector<RefPtr<SingleChild>>& components) override;
    void ResetInitializedStyle() override;

    bool IsSubscriptEnable() const override
    {
        if (declaration_) {
            declaration_->SetIsSubscriptEnable(true);
        }
        return true;
    }

    std::string type_;
    Radius topLeftRadius_;
    Radius topRightRadius_;
    Radius bottomLeftRadius_;
    Radius bottomRightRadius_;
    StickyMode stickyMode_ = StickyMode::NONE;

private:
    void AddListItem(const RefPtr<DOMNode>& node, int32_t slot);
    void RemoveListItem(const RefPtr<DOMNode>& node);
    void SetCardThemeAttrs();
    void SetDividerStyle(const RefPtr<DOMNode>& parentNode);
    void SetCardTransitionEffect();

    // common variables
    int32_t columnSpan_ = DEFAULT_COLUMN_SPAN;
    // If the item is generated by for loop, its index would be increased from 0.
    int32_t itemIndex_ = -1;
    std::string indexKey_;
    int32_t key_ = -1;

    // list-item's variables
    Alignment alignment_ { Alignment::TOP_LEFT };
    FlexDirection flexDirection_ { FlexDirection::ROW };
    FlexAlign flexMainAlign_ { FlexAlign::FLEX_START };
    FlexAlign flexCrossAlign_ { FlexAlign::FLEX_START };
    FlexAlign alignSelf_ { FlexAlign::AUTO };
    RefPtr<ListItemComponent> listItemComponent_;
    RefPtr<FlexComponent> flexComponent_;
    RefPtr<DisplayComponent> displayComponent_;
    bool sticky_ = false;
    bool isTitle_ = false;
    Dimension stickyRadius_;
    bool clickEffect_ = true;
    bool primary_ = false;
    bool isActive_ = false;
    Color clickColor_ = Color::TRANSPARENT;

    EventMarker clickEventId_;
    EventMarker stickyEventId_;
    RefPtr<CardTheme> cardTheme_;
    bool isCardBlur_ = false;
    bool isCard_ = false;
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_DOM_DOM_LIST_ITEM_H
