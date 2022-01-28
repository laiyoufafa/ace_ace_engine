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

#include "core/components/side_bar/side_bar_container_component.h"

#include "base/geometry/dimension.h"
#include "core/components/box/box_component.h"
#include "core/components/display/display_component.h"
#include "core/components/gesture_listener/gesture_listener_component.h"
#include "core/components/image/image_component.h"
#include "core/components/side_bar/render_side_bar_container.h"
#include "core/components/side_bar/side_bar_container_element.h"
#include "core/components/split_container/row_split_component.h"
#include "core/gestures/tap_gesture.h"
#include "core/pipeline/base/component.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace {

SideBarContainerComponent::SideBarContainerComponent(const std::list<RefPtr<Component>>& children)
    : StackComponent(Alignment::CENTER_LEFT, StackFit::KEEP, Overflow::SCROLL, children)
{
    declaration_ = AceType::MakeRefPtr<SideBarDeclaration>();
    declaration_->Init();

    BuildButton();
}

RefPtr<RenderNode> SideBarContainerComponent::CreateRenderNode()
{
    return RenderSideBarContainer::Create();
}

RefPtr<Element> SideBarContainerComponent::CreateElement()
{
    return AceType::MakeRefPtr<SideBarContainerElement>();
}

void SideBarContainerComponent::BuildButton()
{
    RefPtr<ImageComponent> imageComponent = AceType::MakeRefPtr<OHOS::Ace::ImageComponent>();
    if (sideStatus_ == SideStatus::SHOW) {
        if (GetShowIcon().empty()) {
            imageComponent->SetSrc(GetShowIcon());
        } else {
            imageComponent->SetResourceId(InternalResource::ResourceId::SIDE_BAR);
        }
    } else {
        if (!GetHiddenIcon().empty()) {
            imageComponent->SetSrc(GetHiddenIcon());
        } else {
            imageComponent->SetResourceId(InternalResource::ResourceId::SIDE_BAR);
        }
    }
    imageComponent->SetUseSkiaSvg(false);
    imageComponent->SetImageFit(ImageFit::FILL);
    exRegionComponent_ = imageComponent;
}

void SideBarContainerComponent::Build()
{
    if (!declaration_) {
        return;
    }

    auto children = GetChildren();
    RefPtr<BoxComponent> barbox = AceType::MakeRefPtr<BoxComponent>();

    RefPtr<Component>& sidebar = children.front();
    barbox->SetChild(sidebar);

    RefPtr<BoxComponent> contentbox = AceType::MakeRefPtr<BoxComponent>();
    RefPtr<Component>& content = children.back();
    contentbox->SetChild(content);

    auto tapGesture = AceType::MakeRefPtr<TapGesture>();
    tapGesture->SetOnActionId([weak = WeakClaim(this)](GestureEvent& info) {
        auto component = weak.Upgrade();
        if (component && component->buttonClick_) {
            component->buttonClick_();
        }
    });

    RefPtr<BoxComponent> btnbox = AceType::MakeRefPtr<BoxComponent>();
    btnbox->SetOnClick(tapGesture);
    btnbox->SetChild(exRegionComponent_);
    btnbox->SetWidth(Dimension(declaration_->GetImageWidth(), DimensionUnit::VP));
    btnbox->SetHeight(Dimension(declaration_->GetImageHeight(), DimensionUnit::VP));
    btnbox->SetLeft(Dimension(declaration_->GetLeft(), DimensionUnit::VP));
    btnbox->SetTop(Dimension(declaration_->GetTop(), DimensionUnit::VP));
    btnbox->SetPositionType(PositionType::ABSOLUTE);
    btnbox->SetFlex(BoxFlex::FLEX_XY);
    RefPtr<DisplayComponent> display = AceType::MakeRefPtr<DisplayComponent>(btnbox);
    if (!GetShowControlButton()) {
        display->SetVisible(VisibleType::GONE);
    } else {
        display->SetVisible(VisibleType::VISIBLE);
    }

    ClearChildren();

    AppendChild(contentbox);
    AppendChild(barbox);
    AppendChild(btnbox);
}

void SideBarContainerComponent::SetButtonWidth(double width)
{
    declaration_->SetImageWidth(width);
}

void SideBarContainerComponent::SetButtonHeight(double height)
{
    declaration_->SetImageHeight(height);
}

double SideBarContainerComponent::GetButtonWidth() const
{
    return declaration_->GetImageWidth();
}

double SideBarContainerComponent::GetButtonHeight() const
{
    return declaration_->GetImageHeight();
}

double SideBarContainerComponent::GetButtonTop() const
{
    return declaration_->GetTop();
}

double SideBarContainerComponent::GetButtonLeft() const
{
    return declaration_->GetLeft();
}

void SideBarContainerComponent::SetShowIcon(const std::string& path)
{
    declaration_->SetShowIcon(path);
}

std::string& SideBarContainerComponent::GetShowIcon() const
{
    return declaration_->GetShowIcon();
}

void SideBarContainerComponent::SetHiddenIcon(const std::string& path)
{
    declaration_->SetHiddenIcon(path);
}

std::string& SideBarContainerComponent::GetHiddenIcon() const
{
    return declaration_->GetHiddenIcon();
}

void SideBarContainerComponent::SetSwitchIcon(const std::string& path)
{
    declaration_->SetSwitchIcon(path);
}

std::string& SideBarContainerComponent::GetSwitchIcon() const
{
    return declaration_->GetSwitchIcon();
}

void SideBarContainerComponent::SetButtonLeft(double left)
{
    declaration_->SetLeft(left);
}

void SideBarContainerComponent::SetButtonTop(double top)
{
    declaration_->SetTop(top);
}

void SideBarContainerComponent::SetClickedFunction(std::function<void()>&& clickCallback)
{
    buttonClick_ = std::move(clickCallback);
}
}