
<div>
<style>
  /* Tab按钮容器样式 */
  .tab-nav {
    display: flex;
    gap: 4px;
    margin: 16px 0;
    padding: 0;
    list-style: none;
  }
  /* Tab按钮基础样式 */
  .tab-nav a {
    display: inline-block;
    padding: 8px 16px;
    background: #f6f8fa;
    border: 1px solid #d0d7de;
    border-radius: 6px 6px 0 0;
    color: #24292f;
    text-decoration: none;
    font-size: 14px;
    font-weight: 500;
    cursor: pointer;
  }
  /* Tab按钮悬浮/点击反馈 */
  .tab-nav a:hover, .tab-nav a:active {
    background: #f0f2f5;
    border-color: #b9c2ce;
  }
  /* 内容容器样式：默认隐藏，点击后显示 */
  .tab-content {
    padding: 20px;
    border: 1px solid #d0d7de;
    border-radius: 0 6px 6px 6px;
    background: #ffffff;
    display: none;
  }
  /* 锚点定位时自动显示对应内容（核心） */
  .tab-content:target {
    display: block;
  }
  /* 默认显示中文内容（可改为英文：#en-content） */
  #zh-content {
    display: block;
  }
</style>
</div>

<!-- Tab按钮：中文/英文 -->
<ul class="tab-nav">
  <li><a href="#zh-content">Readme</a></li>
  <li><a href="#en-content">组件使用说明</a></li>
  <li><a href="#fr-content">导入项目指南</a></li>
</ul>

<div class="tab-content" id="zh-content">
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

</div>

<div class="tab-content" id="en-content">
  ## ElementUI(Qt Widgets) 组件库使用文档

### 1. 引入与基础约定

#### 1.1 头文件与命名

本库为一套 **Element UI 风格的 Qt Widgets 组件集合**，使用 C++ / Qt Widgets 实现。

- **命名规则**
  - 所有组件类名统一以 `F` 前缀，例如：`FButton`、`FInputLine`
  - 通用工具类在 `private/utils.h` 中，例如：`QSSHelper`、`FontHelper`、`ScaleHelper`、`Log`

---

## 2. 快速上手示例

### 2.1 Button + Message

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

### 2.2 Notification

```cpp
#include "include/notification.h"

auto* n = new FNotification(this);
n->setTitle("操作成功")
 .setContent("数据已更新")
 .setType(FNotification::Type::Success)
 .setShowClose(true)
 .setDuration(3000)
 .setPosition(FNotification::Position::TopRight)
 .show();
```

---

## 3. 图标与基础支撑

### 3.1 FIcon（图标系统）

**头文件**：`include/icon.h`

**用途**：统一从资源中加载 SVG 图标，并根据 `currentColor` 动态上色，支持输出 `QIcon` / `QPixmap` / `QByteArray` / `QSvgRenderer*`。

**关键点：**

- 图标 SVG 存放在 `resources/icons/`，资源路径为 `:/icons/<name>.svg`
- 推荐在 SVG 中使用 `fill="currentColor"`，由程序替换为实际颜色

**常用接口（示意）：**

```cpp
QIcon FIcon::getIcon(FIcon::Name name,
                     const QString& color,
                     int size);

QPixmap FIcon::getPixmap(FIcon::Name name,
                         const QString& color,
                         int size);

QByteArray FIcon::getCodeArray(FIcon::Name name,
                               const QString& color);

QSvgRenderer* FIcon::getRenderer(FIcon::Name name,
                                 const QString& color,
                                 QObject* parent);
```

**示例：**

```cpp
#include "include/icon.h"
#include "include/color.h"

// 给按钮设置图标
auto* btn = new FButton("搜索", this);
btn->setIcon(FIcon::Search, FButton::IconPosition::Left);

// 直接使用 QPixmap
QPixmap pix = FIcon::instance().getPixmap(
    FIcon::Close,
    FColor::secondaryText(),
    16
);
label->setPixmap(pix);
```

---

### 3.2 FColor（颜色）

**头文件**：`include/color.h`  
**用途**：提供一整套 Element 风格的主题颜色。

典型接口（示例）：

```cpp
QString FColor::primary();       // 主色
QString FColor::success();
QString FColor::warning();
QString FColor::danger();
QString FColor::info();
QString FColor::primaryText();
QString FColor::secondaryText();
// ...
```

在组件中多用于生成 QSS 颜色值，或传入 `FIcon` 进行着色。

---

### 3.3 FShadowEf（阴影效果）

**头文件**：`include/shadow.h`  
**用途**：为组件添加阴影特效，多用于 `FCard` 等容器组件。

使用方式（示意）：

```cpp
#include "include/shadow.h"

auto* card = new FCard("标题", nullptr, this);
auto* shadow = new FShadowEf(card);
shadow->setBlurRadius(20);
shadow->setOffset(0, 4);
shadow->setColor(QColor(0, 0, 0, 50));
```

---

### 3.4 FScrollBar（滚动条样式）

**头文件**：`include/scrollbar.h`  
**用途**：自带 Element UI 风格的 `QScrollBar`，可设置到 `QScrollArea` / `QListView` 等组件上。

示例：

```cpp
#include "include/scrollbar.h"

auto* area = new QScrollArea(this);
auto* sbV = new FScrollBar(Qt::Vertical, area);
auto* sbH = new FScrollBar(Qt::Horizontal, area);

area->setVerticalScrollBar(sbV);
area->setHorizontalScrollBar(sbH);
```

---

## 4. 输入与表单组件

### 4.1 FInputLine（单行输入框）

**头文件**：`include/inputline.h`

**用途**：Element 风格输入框，支持前后缀图标、清空按钮、密码显隐、最大长度提示等。

**核心 API：**

- 文本/占位：
  - `setPlaceholder(const QString&)`
  - `setText(const QString&)` / `text()`
- 尺寸与状态：
  - `setWidth(int)`
  - `setSize(Size)`：`Large / Default / Small`
  - `setDisabled(bool)`、`setReadOnly(bool)`
- 图标：
  - `setPrefixIcon(FIcon::Name, std::function<void()> onClick = {})`
  - `setSuffixIcon(FIcon::Name, std::function<void()> onClick = {})`
- 功能：
  - `setMaxLength(int)`（可显示 “当前/最大” 长度）
  - `setClearable(bool)`：右侧显示清空图标
  - `setShowPassword(bool)`：密码框显示/隐藏切换

**示例：**

```cpp
#include "include/inputline.h"
#include "include/icon.h"

auto* input = new FInputLine(this);
input->setPlaceholder("请输入用户名")
     .setSize(FInputLine::Size::Default)
     .setClearable(true)
     .setPrefixIcon(FIcon::User);
```

---

### 4.2 FInputNumber（数字输入）

**头文件**：`include/inputnumber.h`

**用途**：数值输入框，带加减按钮。

**常见能力（根据头文件）：**

- `setMinimum(int)` / `setMaximum(int)`
- `setStep(int)`
- `setValue(int)` / `value()`
- `setDisabled(bool)`

**示例：**

```cpp
#include "include/inputnumber.h"

auto* num = new FInputNumber(this);
num->setMinimum(0);
num->setMaximum(100);
num->setStep(5);
num->setValue(20);
```

---

### 4.3 FSelect（下拉选择框）

**头文件**：`include/select.h`

**用途**：基于 `FInputLine` 的下拉选择组件，支持列表选项、位置、宽度等。

**核心 API（示意）：**

- `setOptions(const QStringList&)`
- `addItem(const QString&)` / `addItems(const QStringList&)`
- `setPlacement(Placement)`：`Top / Bottom`
- `setWidth(int)`
- 文本改变信号复用 `QLineEdit::textChanged(const QString&)`

**示例：**

```cpp
#include "include/select.h"

auto* sel = new FSelect(this);
sel->setOptions({"北京", "上海", "广州"})
   .setPlacement(FSelect::Placement::Bottom)
   .setWidth(200);

connect(sel, &QLineEdit::textChanged, this, [](const QString& v){
    qDebug() << "selected:" << v;
});
```

---

### 4.4 FCheckbox / FCheckboxGroup（复选框）

**头文件**：`include/checkbox.h`

**用途**：自绘风格复选框和复选框组，支持多选、禁用、半选、边框等。

**FCheckbox 常用 API：**

- 值与文本：
  - `setValue(const QVariant&)` / `value()`
  - `setText(const QString&)` / `text()`
- 状态：
  - `setChecked(bool)` / `isChecked()`
  - `setDisabled(bool)` / `isDisabled()`
  - `setIndeterminate(bool)` / `isIndeterminate()`
  - `setBorder(bool)` / `hasBorder()`
- 尺寸：
  - `setSize(Size)` / `size()`

**FCheckboxGroup 常用 API：**

- `addCheckbox(FCheckbox*)`
- `setTitle(const QString&)`
- `setSize(Size)`
- `setMin(int)` / `setMax(int)`（选择数量约束）
- `setDisabled(bool)`

**示例：**

```cpp
#include "include/checkbox.h"

auto* group = new FCheckboxGroup(this);
group->setTitle("兴趣爱好")
     .setMin(1)
     .setMax(3);

auto* c1 = new FCheckbox("唱", group);
c1->setValue("sing");
auto* c2 = new FCheckbox("跳", group);
c2->setValue("dance");
auto* c3 = new FCheckbox("rap", group);
c3->setValue("rap");

group->addCheckbox(c1);
group->addCheckbox(c2);
group->addCheckbox(c3);
```

---

### 4.5 FRadio / FRadioGroup（单选框）

**头文件**：`include/radio.h`

**用途**：Element 风格的单选与单选组。

**FRadio 常用 API：**

- `setValue(const QVariant&)` / `value()`
- `setText(const QString&)` / `text()`
- `setChecked(bool)` / `isChecked()`
- `setDisabled(bool)` / `isDisabled()`
- `setSize(Size)` / `size()`
- `setBorder(bool)` / `hasBorder()`

**FRadioGroup 常用 API：**

- `addRadio(FRadio*)`
- `setTitle(const QString&)`
- `setSize(Size)`
- `setDisabled(bool)`

**示例：**

```cpp
#include "include/radio.h"

auto* g = new FRadioGroup(this);
g->setTitle("性别");

auto* r1 = new FRadio("男", g);
r1->setValue("male");
auto* r2 = new FRadio("女", g);
r2->setValue("female");

g->addRadio(r1);
g->addRadio(r2);
```

---

### 4.6 FForm（表单容器）

**头文件**：`include/form.h`  

**用途**：为一系列输入组件提供统一布局与校验（具体 API 以头文件为准）。

常见用法（示意）：

```cpp
#include "include/form.h"
#include "include/inputline.h"
#include "include/inputnumber.h"

auto* form = new FForm(this);
auto* name = new FInputLine(form);
auto* age  = new FInputNumber(form);

form->addRow("姓名", name);
form->addRow("年龄", age);

// 可扩展：校验规则、错误提示等
```

---

## 5. 操作与弹层组件

### 5.1 FButton（按钮）

**头文件**：`include/button.h`

**用途**：Element 风格按钮，支持 type/style/size，loading 与图标。

**核心 API（来自 README + 头文件）：**

- 外观：
  - `setStyle(Style)`：`Default / Plain / Round / Circle / Link / Text`
  - `setType(Type)`：`Default / Primary / Success / Info / Warning / Danger`
  - `setSize(Size)`：`Large / Default / Small`
- 状态：
  - `setDisabled(bool)`
  - `setLoading(bool)`
- 图标：
  - `setIcon(FIcon::Name, IconPosition)`：`Only / Left / Right`
- 文本：
  - `setText(const QString&)`

**示例：**

```cpp
#include "include/button.h"
#include "include/icon.h"

auto* b = new FButton("新增", this);
b->setType(FButton::Type::Primary)
 .setStyle(FButton::Style::Round)
 .setSize(FButton::Size::Default)
 .setIcon(FIcon::Plus, FButton::IconPosition::Left);
```

---

### 5.2 FLink（文字链接）

**头文件**：`include/link.h`

**用途**：超链接样式的文字组件，支持不同颜色类型、下划线策略、禁用。

**核心 API：**

- `setType(Type)`：`Default/Primary/Success/Info/Warning/Danger`
- `setUnderline(Underline)`：`Default/Always/Hover/Never`
- `setDisabled(bool)`
- `setText(const QString&)`

**示例：**

```cpp
#include "include/link.h"

auto* link = new FLink("查看详情", this);
link->setType(FLink::Type::Primary)
    .setUnderline(FLink::Underline::Hover);

connect(link, &FLink::clicked, this, []{
    qDebug() << "link clicked";
});
```

---

### 5.3 FTooltip（文字提示）

**头文件**：`include/tooltip.h`

**用途**：悬浮/点击等方式触发的提示气泡，带箭头、位置、主题、延迟等。

**核心 API：**

- 行为与样式：
  - `setPlacement(Placement)`：顶部/底部/左右 + Start/End
  - `setEffect(Effect)`：`Dark / Light`
  - `setTrigger(Trigger)`：`Hover / Click / Focus / ContextMenu`
  - `setText(const QString&)`
- 交互：
  - `setDisabled(bool)`
  - `setOffset(int)`
  - `setShowAfter(int)` / `setHideAfter(int)`
  - `setShowArrow(bool)`
  - `setAutoClose(int)`
  - `setEnterable(bool)`（鼠标移入 tooltip 不立即关闭）
  - `setMoveable(bool)` / `setPosition(const QPoint&)`

**示例：**

```cpp
#include "include/tooltip.h"
#include "include/button.h"

auto* btn = new FButton("Hover me", this);
auto* tip = new FTooltip(btn);
tip->setText("这是一段提示")
   .setEffect(FTooltip::Effect::Dark)
   .setTrigger(FTooltip::Trigger::Hover)
   .setPlacement(FTooltip::Placement::Top);
```

---

### 5.4 FDialog（对话框）

**头文件**：`include/dialog.h`

**用途**：带标题和正文的简单对话框，含确定/取消按钮。

**核心 API：**

- `setTitle(const QString&)`
- `setContent(const QString&)`
- `int show()`：同步显示，对用户操作（确定/取消）返回结果

**示例：**

```cpp
#include "include/dialog.h"

auto* dlg = new FDialog(this);
dlg->setTitle("删除确认")
   .setContent("确定要删除当前记录吗？");

int ret = dlg->show();
if (ret == QDialog::Accepted) {
    // 确认
} else {
    // 取消
}
```

---

### 5.5 FDrawer（抽屉）

**头文件**：`include/drawer.h`

**用途**：从窗口边缘滑出的抽屉，常用于设置/详情等。

**核心 API：**

- 行为：
  - `setModal(bool)`：是否阻塞背景
  - `setDirection(Direction)`：
    - `RightToLeft / LeftToRight / TopToBottom / BottomToTop`
  - `setSize(int percent)`：宽/高占父窗口百分比
- UI：
  - `setShowClose(bool)`
  - `setWithHeader(bool)` / `setWithFooter(bool)`
  - `setTitle(const QString&)`
  - `setBody(QWidget*)`
- 信号：
  - `confirm()`：确认按钮点击

**示例：**

```cpp
#include "include/drawer.h"
#include "include/button.h"

auto* content = new QLabel("抽屉内容", this);
auto* drawer = new FDrawer(this);
drawer->setTitle("设置")
      .setDirection(FDrawer::Direction::RightToLeft)
      .setSize(30)
      .setBody(content)
      .setShowClose(true)
      .setModal(true);

connect(buttonOpen, &QPushButton::clicked, drawer, &FDrawer::show);
```

---

### 5.6 FMask / FMaskEf（遮罩）

**头文件**：`include/mask.h`

**用途**：用于覆盖某个区域、实现 “点击空白关闭” 等效果，Drawer / Dialog 常用。

**核心 API：**

- `FMaskEf::setMask(QWidget* partner, QWidget* covered)`：创建并挂载遮罩
- `FMask::clicked()`：点击遮罩区域的信号

**示例：**

```cpp
#include "include/mask.h"

auto* dlg = new FDialog(this);
auto* mask = FMaskEf::setMask(this, dlg);

connect(mask, &FMask::clicked, dlg, &QWidget::close);
dlg->show();
```

---

### 5.7 FMessage（消息提示）

**头文件**：`include/message.h`

**用途**：顶部/底部堆叠的轻量提示条。

**核心 API：**

- 文本与类型：
  - `setMessage(const QString&)`
  - `setType(Type)`：`Primary/Success/Warning/Info/Error`
  - `setPlain(bool)`：朴素样式
- 行为：
  - `setShowClose(bool showClose, bool autoClose = true)`
  - `setPlacement(Placement)`：
    - `Top / TopLeft / TopRight / Bottom / BottomLeft / BottomRight`
  - `setDuration(int msec)`
  - `show()`

**示例：**

```cpp
#include "include/message.h"

auto* msg = new FMessage(this);
msg->setMessage("操作成功")
   .setType(FMessage::Type::Success)
   .setPlain(false)
   .setShowClose(true)
   .setPlacement(FMessage::Placement::TopRight)
   .setDuration(2000)
   .show();
```

---

### 5.8 FNotification（通知）

**头文件**：`include/notification.h`

**用途**：四角弹出的通知消息，支持标题、内容、图标、自动关闭。

**核心 API：**

- `setTitle(const QString&)`
- `setContent(const QString&)`
- `setType(Type)`：`Default/Primary/Success/Warning/Info/Error`
- `setShowClose(bool showClose = true, bool autoClose = true)`
- `setPosition(Position)`：`TopRight / TopLeft / BottomRight / BottomLeft`
- `setDuration(int msec)`
- `show()`

**示例：**

```cpp
#include "include/notification.h"

auto* n = new FNotification(this);
n->setTitle("更新完成")
 .setContent("所有文件已同步至服务器")
 .setType(FNotification::Type::Info)
 .setPosition(FNotification::Position::BottomRight)
 .setDuration(4000)
 .show();
```

---

### 5.9 FBacktop（回到顶部）

**头文件**：`include/backtop.h`

**用途**：绑定滚动区域，超过一定高度出现“回到顶部”按钮。

**核心 API：**

- `setTarget(QScrollArea*)`
- `setVisibilityHeight(int)`：何时显示
- `setRight(int)` / `setBottom(int)`：按钮位置
- `setShape(Shape)`：`Circle/Square`
- `setSize(Size)`：`Large/Default/Small`
- `setType(Type)`：`Icon/Text`

**示例：**

```cpp
#include "include/backtop.h"

auto* area = new QScrollArea(this);
// ... setup area ...

auto* bt = new FBacktop(this);
bt->setTarget(area)
  .setVisibilityHeight(300)
  .setRight(50)
  .setBottom(50)
  .setShape(FBacktop::Shape::Circle)
  .setType(FBacktop::Type::Icon);
```

---

## 6. 展示与容器组件

### 6.1 FText（文本）

**头文件**：`include/text.h`

**用途**：带类型/字号/标签语义的文本组件，可点击/悬停。

**核心 API：**

- 样式：
  - `setType(Type)`：`Default/Primary/Success/Info/Warning/Danger`
  - `setSize(Size)`：`Large/Default/Small`
  - `setTag(Tag)`：如 `Paragraph/Bold/Italic/...`
  - `setTruncated(bool)`：超出宽度时截断
- 外观：
  - `setColor(const QString&)`
  - `setFontSize(int)`
- 信号：
  - `clicked()`
  - `rightClicked()`
  - `hovered(bool)`

**示例：**

```cpp
#include "include/text.h"

auto* t = new FText("可点击文字", this);
t->setType(FText::Type::Primary)
 .setSize(FText::Size::Default)
 .setTruncated(true);

connect(t, &FText::clicked, this, []{
    qDebug() << "text clicked";
});
```

---

### 6.2 FTag（标签）

**头文件**：`include/tag.h`

**用途**：标签组件，可配置类型、尺寸、主题和关闭按钮。

**核心 API：**

- `setEffect(Effect)`：`Dark/Light/Plain`
- `setType(Type)`：`Primary/Success/Info/Warning/Danger`
- `setSize(Size)`：`Large/Default/Small`
- `setCloseable(bool)`
- `setRound(bool)`
- `setText(const QString&)`

**示例：**

```cpp
#include "include/tag.h"

auto* tag = new FTag("标签", this);
tag->setType(FTag::Type::Success)
   .setEffect(FTag::Effect::Light)
   .setSize(FTag::Size::Small)
   .setCloseable(true);
```

---

### 6.3 FBadge（角标）

**头文件**：`include/badge.h`

**用途**：数字/文字徽标，附着在其他组件上。

**核心 API：**

- `setType(Type)`
- `setIsDot(bool)`：仅显示小圆点
- `setValue(int 或 QString)`
- `setMax(int)`：超过该值显示“max+”

**示例：**

```cpp
#include "include/badge.h"
#include "include/button.h"

auto* btn = new FButton("消息", this);
auto* badge = new FBadge(btn);
badge->setValue(12)
     .setMax(99);
```

---

### 6.4 FProgress（进度条）

**头文件**：`include/progress.h`

**用途**：线形、圆形、仪表盘进度条，支持自定义颜色和文本。

**核心 API：**

- 进度：
  - `setPercentage(int)`（0~100）
  - `setType(Type)`：`Line/Circle/Dashboard`
  - `setStrokeWidth(int)`
- 行为：
  - `setTextInside(bool)`
  - `setStatus(Status)`：`None/Success/Exception/Warning`
  - `setIndeterminate(bool)`
  - `setDuration(int)`：动画时长
- 自定义：
  - `setColor(std::function<QString(int)>)`
  - `setShowText(bool)`
  - `setStrokeLinecap(StrokeLinecap)`
  - `setFormat(std::function<QString(int)>)`

**示例：**

```cpp
#include "include/progress.h"

auto* p = new FProgress(this);
p->setType(FProgress::Type::Line)
 .setPercentage(70)
 .setTextInside(true)
 .setShowText(true)
 .setStatus(FProgress::Status::Success);
```

---

### 6.5 FCard（卡片）

**头文件**：`include/card.h`

**用途**：容器卡片，支持 header/footer/body 与阴影策略。

**核心 API：**

- `setHeader(const QString&)`
- `setFooter(const QString&)`
- `setBody(QWidget*)`
- `setShadow(Shadow)`：`Always/Hover/Never`

**示例：**

```cpp
#include "include/card.h"

auto* content = new QLabel("卡片内容", this);
auto* c = new FCard("标题", content, this);
c->setShadow(FCard::Shadow::Hover);
```

---

### 6.6 FTable（表格）

**头文件**：`include/table.h`

**用途**：封装带斑马纹、边框、高亮行的表格。

**核心 API：**

- `setWidth(const QList<int>& widths = {})`：设置列宽
- `setStripe(bool)`：斑马纹
- `setBorder(bool)`：外边框
- `setHightlight(int row, Highlight type)`：
  - `Primary/Success/Info/Warning/Danger`

**示例：**

```cpp
#include "include/table.h"

auto* t = new FTable(this);
t->setStripe(true)
 .setBorder(true)
 .setWidth({100, 200, 150});

t->setHightlight(1, FTable::Highlight::Warning);
```

---

### 6.7 FTabs / FTabBar（标签页）

**头文件**：`include/tabs.h`

**用途**：多页签组件，支持卡片风格、位置切换、可关闭/可新增。

**FTabs 核心 API：**

- `setType(Type)`：`Default/Card/BorderCard`
- `setTabPosition(QTabWidget::TabPosition)`：`Top/Bottom/Left/Right`
- `setCloseable(bool)`
- `setAddable(bool)`
- `setEditable(bool)`
- `setStretch(bool)`
- `getTabWidths()`：返回每个 tab 宽度

**示例：**

```cpp
#include "include/tabs.h"

auto* tabs = new FTabs(this);
tabs->setType(FTabs::Type::Card)
    .setTabPosition(QTabWidget::North)
    .setCloseable(true)
    .setAddable(true);

tabs->addTab(new QLabel("内容1"), "标签1");
tabs->addTab(new QLabel("内容2"), "标签2");
```

---

### 6.8 FCollapse / FCollapseItem（折叠面板）

**头文件**：`include/collapse.h`

**用途**：手风琴 / 折叠面板。

**FCollapseItem 核心 API：**

- 图标与状态：
  - `setIconPosition(IconPosition)`：`Left/Right`
  - `setIcon(FIcon::Name collapsedIcon, FIcon::Name expandIcon)`
  - `setAllowCollapse(bool)`
  - `setCollapse()` / `setExpand()` / `toggleStatus()`
- 内容：
  - `setTitle(const QString&)`
  - `setContent(const QString&)`
  - `setWidth(int)`
  - `setLast(bool)`

**FCollapse 核心 API：**

- `setAccordion(bool)`：手风琴模式
- `setIcon(...)` / `setIconPosition(...)`
- `setCollapse(int index)` / `setExpand(int index)` / `toggleStatus(int index)`
- `addItem(FCollapseItem*)`
- `delItem(int index)`
- `setWidth(int)`

**示例：**

```cpp
#include "include/collapse.h"

auto* col = new FCollapse(this);
col->setAccordion(true);

auto* item1 = new FCollapseItem("面板1", "内容1", col);
auto* item2 = new FCollapseItem("面板2", "内容2", col);

col->addItem(item1);
col->addItem(item2);
```

---

### 6.9 FCarousel（走马灯）

**头文件**：`include/carousel.h`

**用途**：轮播图/走马灯，支持自动播放、卡片模式、方向等。

**核心 API：**

- 触发与指示器：
  - `setTigger(Trigger)`：`Hover/Click`（注意拼写为 `setTigger`）
  - `setIndicatorPos(IndicatorPos)`：`Inside/Outside/None`
  - `setArrow(Arrow)`：`Always/Hover/Never`
- 播放控制：
  - `setAutoplay(bool)`
  - `setInterval(int msec)`
  - `setPauseOnHover(bool)`
  - `setLoop(bool)`
- 模式：
  - `setType(Type)`：`Default/Card`
  - `setCardScale(double)`
  - `setDirection(Direction)`：`Horizontal/Vertical`
- 数据：
  - `addImage(const QPixmap&)`

**示例：**

```cpp
#include "include/carousel.h"

auto* c = new FCarousel(this);
c->setAutoplay(true)
 .setInterval(3000)
 .setType(FCarousel::Type::Card);

// 添加图片
c->addImage(QPixmap(":/images/1.png"));
c->addImage(QPixmap(":/images/2.png"));
c->addImage(QPixmap(":/images/3.png"));
```

---

### 6.10 FAvatar（头像）

**头文件**：`include/avatar.h`

**用途**：头像展示，支持 Icon / 图片 / 文本三种模式，圆形或方形。

**核心 API：**

- 模式：
  - `setIcon(FIcon::Name = FIcon::UserFilled)`
  - `setImage(const QImage& = QImage(":/icons/other/example-avatar.png"))`
  - `setText(const QString& = "user")`
- 外观：
  - `setSize(Size)`：`Large/Default/Small`
  - `setShape(Shape)`：`Circle/Square`

**示例：**

```cpp
#include "include/avatar.h"

auto* a1 = new FAvatar(this);
a1->setIcon(FIcon::UserFilled)
   .setSize(FAvatar::Size::Large)
   .setShape(FAvatar::Shape::Circle);

auto* a2 = new FAvatar(this);
a2->setText("AB")
   .setSize(FAvatar::Size::Small)
   .setShape(FAvatar::Shape::Square);
```

---

### 6.11 FImage（图片）

**头文件**：`include/image.h`

**用途**：带 `object-fit` 风格的图片展示控件。

**核心 API：**

- `setFit(Fit)`：
  - `Fill/Contain/Cover/None/ScaleDown`
- 数据：
  - `setImage(const QImage&)`
  - `setPixmap(const QPixmap&)`

**示例：**

```cpp
#include "include/image.h"

auto* img = new FImage(this);
img->setFit(FImage::Fit::Cover);
img->setPixmap(QPixmap(":/images/banner.png"));
```

---

### 6.12 FRate（评分）

**头文件**：`include/rate.h`

**用途**：星级评分组件。

**核心 API：**

- 分值：
  - `setScore(qreal)`：当前得分
  - `setMax(int)`：最大分（需为 5 的倍数）
- 样式：
  - `setSize(Size)`：`Large/Default/Small`
  - `setAllowHalf(bool)`
  - `setClearable(bool)`
  - `setDisabled(bool)`
- 文本与颜色：
  - `setLowThreshold(int)` / `setHighThreshold(int)`
  - `setShowText(bool)` / `setShowScore(bool)`
  - `setColors(...)`：低/中/高三段颜色
  - `setTexts(...)`：每个等级对应文本

**示例：**

```cpp
#include "include/rate.h"

auto* r = new FRate(this);
r->setMax(50)        // 5 * 10
 .setScore(35)       // 3.5 星
 .setAllowHalf(true)
 .setShowScore(true);
```

---

## 7. 当前为占位空壳的组件（尚未可用）

以下组件的头文件目前仅有类声明，没有完整的属性/方法实现，**暂时不建议在业务中直接使用**。如需可用，需要先补齐对应 `*.h/*.cpp` 实现，然后再扩展本文档。

- `FAlert`
- `FSpace`
- `FBreadcrumb`
- `FSteps`
- `FTimeline`
- `FDescriptions`
- `FStatistic`
- `FPagination`
- `FSkeleton`
- `FEmpty`
- `FCalendar`
- `FResult`
- `FMessageBox`
- `FPopConfirm`
- `FPopOver`

---


</div>

<div class="tab-content" id="fr-content">
## Element UI Qt 组件库使用指南

本指南面向「在其他 Qt 项目中使用 elementui 组件库」的场景，假设你已经拿到一份发布好的目录，例如：

```text
D:/3rdparty/elementui-qt/
  include/    # 头文件（含 elementui.h）
  lib/        # 库文件（.lib / .a）
  bin/        # 动态库 .dll（如有）
  resources/  # 可选：icons.qrc 与 SVG 资源
```

---

### 1. 目录结构说明

- **`include/`**
  - `elementui.h`：统一入口头文件（推荐外部项目只 include 这个）
  - 各组件头文件：`button.h`, `inputline.h`, `select.h`, `table.h`, `tabs.h`, `collapse.h`, `carousel.h`, `avatar.h`, `image.h`, `progress.h`, `rate.h`, `backtop.h`, `message.h`, `notification.h`, `tooltip.h`, `link.h`, `text.h`, `tag.h`, `badge.h`, `color.h`, `icon.h`, `constants.h` 等。
- **`lib/`**
  - `elementui.lib` / `libelementui.a`：链接用（导入库或静态库）。
- **`bin/`**（仅动态库时存在）
  - `elementui.dll`：运行时加载的动态库。
- **`resources/`**（可选对外）
  - `icons.qrc` 与 `icons/*.svg`：`FIcon` 使用的 SVG 资源。

> 注意：使用方工程的 **Qt 版本 + 编译器** 必须与编译 elementui 库时一致（例如都为 Qt 5.15.2 + MinGW 64-bit）。

---

### 2. 在 qmake 项目中集成

假设发布目录为：`D:/3rdparty/elementui-qt`。

#### 2.1 修改 `.pro` 文件

```qmake
# 头文件路径
INCLUDEPATH += D:/3rdparty/elementui-qt/include

# 链接库
LIBS += -LD:/3rdparty/elementui-qt/lib -lelementui

# 需要的 Qt 模块
QT += widgets svg
```

如果 **资源不内置在 elementui 库**，而是由外部项目负责加载，还需要：

```qmake
RESOURCES += D:/3rdparty/elementui-qt/resources/icons.qrc
```

#### 2.2 DLL 放置（动态库时）

- 将 `elementui.dll` 拷贝到你的可执行文件所在目录（例如 `build/bin/`），或
- 把 `D:/3rdparty/elementui-qt/bin` 加入系统 PATH。

---

### 3. 在 CMake 项目中集成（可选）

示例（假设 MinGW + Qt 5）：

```cmake
set(ELEMENTUI_ROOT "D:/3rdparty/elementui-qt")

include_directories(${ELEMENTUI_ROOT}/include)
link_directories(${ELEMENTUI_ROOT}/lib)

find_package(Qt5 COMPONENTS Widgets Svg REQUIRED)

add_executable(MyApp main.cpp ...)

target_link_libraries(MyApp
    PRIVATE
        Qt5::Widgets
        Qt5::Svg
        elementui
)
```

DLL 运行时查找方式同 qmake 场景。

---

### 4. 代码使用示例

#### 4.1 基本用法：按钮 + 顶部消息

```cpp
#include <QApplication>
#include <QWidget>
#include "elementui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget w;
    w.resize(400, 200);

    auto* btn = new FButton("保存", &w);
    btn->move(50, 50);
    btn->setType(FButton::Type::Primary);

    QObject::connect(btn, &QPushButton::clicked, &w, [&]() {
        (new FMessage("保存成功", FMessage::Type::Success))
            ->setShowClose(true)
            .setPlacement(FMessage::Place::TopRight)
            .setDuration(2000)
            .show();
    });

    w.show();
    return a.exec();
}
```

#### 4.2 输入框 + 选择框

```cpp
#include "elementui.h"

// 在你的窗口构造函数内：
auto* input = new FInputLine("请输入关键字", this);
input->move(50, 30);
input->setPrefixIcon(FIcon::Search).setClearable(true);

auto* select = new FSelect(this);
select->move(50, 80);
select->setOptions({"选项A", "选项B", "选项C"});

connect(select, &QLineEdit::textChanged, this, [](const QString& v){
    qDebug() << "选择了:" << v;
});
```

#### 4.3 通知 + Tooltip

```cpp
#include "elementui.h"

auto* btn = new FButton("通知", this);
btn->move(50, 130);

auto* tip = new FTooltip("这是一个提示", btn);
tip->setPlacement(FTooltip::Placement::Top)
   .setEffect(FTooltip::Effect::Dark)
   .setTrigger(FTooltip::Trigger::Hover);

connect(btn, &QPushButton::clicked, this, [=] {
    (new FNotification("警告", "网络不稳定", FNotification::Type::Warning))
        ->setPosition(FNotification::Position::BottomRight)
        .setDuration(3000)
        .show();
});
```

---

### 5. 常见问题（FAQ）

**Q1：链接时报 `unresolved external symbol FButton::...`？**  
**A：** 通常是 `.pro` / CMake 没有正确链接 `elementui` 库，或 `-L` 路径指错。确认：

- qmake：`LIBS += -LD:/3rdparty/elementui-qt/lib -lelementui`
- CMake：`link_directories` 与 `target_link_libraries` 正确。

---

**Q2：程序运行时提示找不到 `elementui.dll`？**  
**A：** 把 `elementui.dll` 放到可执行文件同一目录，或者把 `bin` 目录加入 PATH。

---

**Q3：图标不显示 / 日志提示找不到 SVG 文件？**  
**A：**

- 若资源打包在 elementui 库内：确认你链接的是包含 `icons.qrc` 的正确版本；
- 若由外部项目加载：检查 `.pro` 或 CMake 是否加入了 `icons.qrc`，并确认 `icons/*.svg` 文件存在。

---

**Q4：使用方能否自行扩展图标？**  
**A：**

- 简单做法：在自己的项目中增加新的 qrc 资源文件，自行管理路径；
- 如果希望通过 `FIcon` 统一管理，需要在 elementui 源码侧扩展 `FIcon::Name` 枚举与 `_iconList` 映射，这属于修改库源码的范畴。

---

如需发布多套构建（例如：MinGW 版与 MSVC 版），推荐在说明书中注明对应的：

- Qt 版本（如：Qt 5.15.2）
- 编译器及架构（如：MSVC 2019 64-bit / MinGW 8.1 64-bit）

使用方需选择与自己工程完全匹配的一套库文件。


</div>
