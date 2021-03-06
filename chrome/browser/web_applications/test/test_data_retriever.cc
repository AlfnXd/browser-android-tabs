// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/web_applications/test/test_data_retriever.h"

#include "base/logging.h"
#include "chrome/common/web_application_info.h"

namespace web_app {

TestDataRetriever::TestDataRetriever(
    std::unique_ptr<WebApplicationInfo> web_app_info)
    : web_app_info_(std::move(web_app_info)) {}

TestDataRetriever::~TestDataRetriever() = default;

void TestDataRetriever::GetWebApplicationInfo(
    content::WebContents* web_contents,
    GetWebApplicationInfoCallback callback) {
  DCHECK(web_contents);
  base::ThreadTaskRunnerHandle::Get()->PostTask(
      FROM_HERE, base::BindOnce(std::move(callback), std::move(web_app_info_)));
}

void TestDataRetriever::GetIcons(content::WebContents* web_contents,
                                 const std::vector<GURL>& icon_urls,
                                 bool skip_page_fav_icons,
                                 GetIconsCallback callback) {
  base::ThreadTaskRunnerHandle::Get()->PostTask(
      FROM_HERE, base::BindOnce(std::move(callback), std::move(icons_map_)));
  icons_map_.clear();
}

void TestDataRetriever::SetIcons(IconsMap icons_map) {
  icons_map_ = std::move(icons_map);
}

}  // namespace web_app
