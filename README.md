## ElementUI (Qt Widgets) 组件库

本仓库是在 `https://github.com/yyx-dev/qt-element-ui` 基础上的二次开发版本，对原项目做了适配与整理，提供一套 **Element UI 风格** 的 Qt Widgets 组件集合（C++ / Qt Widgets）。

- **组件命名**：全部以 `F` 前缀命名，例如：`FButton`、`FInputLine`、`FTable` 等
- **风格统一**：按钮、输入框、弹窗、通知、表格、标签等组件均参考 Element UI 设计规范
- **链式调用**：大部分 `setXxx()` 接口返回引用，支持链式（Fluent）配置
- **完整中文文档**：详细组件说明见根目录下 `组件使用说明.md` / `ELEMENTUI_使用指南.md` 与 `widgets/README.md`

---

## 1. 适用场景

- **桌面端 Qt 项目**，希望具备类似 Element UI 的界面风格
- 需要统一的按钮、输入框、弹窗、通知、表单、表格等基础组件
- 希望通过链式 API 快速构建一致风格的业务界面

---

## 2. 快速上手

### 2.1 引入工程

1. 将本仓库以子模块或源码形式引入你的 Qt 工程目录  
2. 在 `.pro` 中加入：

```pro
include(elementui-lib.pro)
```

或直接把 `include/`、`widgets/`、`resources/` 中相关文件加入你的 `.pro`：

```pro
HEADERS += \
    include/elementui.h \
    include/button.h \
    include/message.h \
    include/icon.h \
    # ...

SOURCES += \
    widgets/button.cpp \
    widgets/message.cpp \
    widgets/icon.cpp \
    # ...

RESOURCES += \
    resources/icons.qrc \
    resources/fonts.qrc
```

> 以上仅为示意，具体以你项目的路径与需要启用的组件为准。

### 2.2 基础使用示例

```cpp
#include "include/button.h"
#include "include/message.h"
#include "include/icon.h"

auto* btn = new FButton("保存", this);
btn->setType(FButton::Type::Primary)
   .setStyle(FButton::Style::Round)
   .setIcon(FIcon::Check, FButton::IconPosition::Left);

connect(btn, &QPushButton::clicked, this, [=]{
    auto* msg = new FMessage(this);
    msg->setMessage("已保存")
       .setType(FMessage::Type::Success)
       .setShowClose(true)
       .setDuration(2000)
       .setPlacement(FMessage::Placement::TopRight)
       .show();
});
```

更多示例与详细 API 说明，请查看 `组件使用说明.md` 与 `widgets/README.md`。

---

## 3. 目录结构简要说明

- `include/`：对外暴露的组件头文件（`FButton`、`FInputLine`、`FTable` 等）
- `widgets/`：组件具体实现及内部工具
- `resources/`：图标（SVG）、字体等资源文件以及对应 `.qrc`
- `build/`：本地构建输出（例如 `elementui.dll` / `libelementui.a`）
- `ELEMENTUI_使用指南.md` / `组件使用说明.md`：中文使用手册与示例

---

## 4. 与上游项目的主要差异

基于上游仓库 `qt-element-ui`，本仓库做了以下调整（不完全列举）：

- 统一类命名为 `F*` 前缀，去掉原有命名空间
- 调整/整理部分组件 API，使其更接近桌面端常用场景
- 增加或修订中文文档，补充更多示例与用法说明

> 具体实现与细节以当前仓库源码和中文文档为准。

---

## 5. 版权与协议

本项目基于上游 `qt-element-ui` 进行修改与扩展，版权与开源协议请参考原项目声明；如需在商业项目中使用，请自行评估并遵守相关开源协议要求。
