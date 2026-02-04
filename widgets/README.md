# Element UI（Qt Widgets）组件库说明书

本项目是一套「Element UI 风格」的 Qt Widgets 组件集合（C++），从外部项目移植并按本项目约定整理：

- **去掉原命名空间**：直接使用全局类名（如 `FButton`）
- **类名统一加 `F` 前缀**
- **硬编码参数统一收敛到** `constants.h`（命名空间 `FConstants::F<组件名>`）
- **图标统一由** `FIcon` **管理**（SVG 读取、`currentColor` 颜色替换、缓存）

> 本文档强调“以当前代码为准”。某些组件头文件目前仍是**占位空壳**（只有 `Q_OBJECT` 但无公开 API），这类会在组件章节里明确标注，避免误用。

---

## 1. 快速开始（推荐写法）

### 1.1 基本用法（Button + Message）

```cpp
#include "widgets/elementui/button.h"
#include "widgets/elementui/message.h"

auto* btn = new FButton("保存", this);
btn->setType(FButton::Type::Primary)
   .setIcon(FIcon::Check, FButton::IconPosition::Left);

connect(btn, &QPushButton::clicked, this, [=]{
    (new FMessage("已保存", FMessage::Type::Success))
        ->setShowClose(true)
        .show();
});
```

### 1.2 链式（Fluent）API 约定

多数组件的 `setXxx()` 会返回 `&`，可链式调用：

```cpp
(new FNotification("完成", "数据已更新", FNotification::Type::Success))
    ->setDuration(2500)
    .setShowClose(true)
    .show();
```

---

## 2. 目录结构与核心基建

### 2.1 目录结构

- **组件本体**：各 `*.h/*.cpp`（如 `button.h/.cpp`）
- **常量表**：`constants.h`
- **颜色体系**：`color.h/.cpp`（`FColor::*()` 返回颜色字符串）
- **图标体系**：`icon.h/.cpp`（`FIcon`：SVG 读取/上色/缓存）
- **阴影效果**：`shadow.h/.cpp`（`FShadowEf`）
- **通用工具**：`private/utils.h/.cpp`
  - `QSSHelper`：按“样式组/属性”管理与生成 QSS
  - `FontHelper`：字体、字号辅助
  - `ScaleHelper` + `sc(...)`：缩放（高 DPI/不同缩放因子）
  - `Log`：简单日志（带级别）

### 2.2 常量（FConstants）使用规则

所有组件的尺寸/间距/圆角/动画参数等硬编码值应集中在：

- `gui/widgets/elementui/constants.h`
- 命名空间：`FConstants::F<组件名>::<常量名>`

示例：

```cpp
// 图标尺寸
FConstants::FInputLine::IconSize

// Select 的选项高度
FConstants::FSelect::ItemHeight
```

### 2.3 缩放（sc）

组件内部大量使用 `sc(...)` 做缩放。新写组件/新加常量时建议：

- 常量本身保存“设计像素值”
- 使用时用 `sc(...)` 转为实际像素（尤其是高度、边距、图标尺寸）

---

## 3. 图标系统（FIcon）——非常重要

### 3.1 图标资源在哪里？

`FIcon` 从 Qt Resource 读取：

- **资源路径**：`:/icons/<name>.svg`
- **资源清单**：`gui/resources/icons.qrc`

只要 `icons.qrc` 被加入 `.pro` 的 `RESOURCES` 并编译进资源，`FIcon` 就能工作。

### 3.2 `currentColor` 上色机制

`FIcon` 读取 SVG 文本后会把其中的 `currentColor` 替换为你传入的颜色字符串（如 `FColor::primaryText()`）。因此 SVG 推荐使用 `fill="currentColor"` 等写法。

### 3.3 常用 API（按使用场景）

- **给 `QAction/QPushButton` 等用 `QIcon`**
  - `FIcon::instance().getIcon(FIcon::Search, FColor::regularText(), 20)`
- **给 `QLabel::setPixmap` 用 `QPixmap`**
  - `FIcon::instance().getPixmap(FIcon::Close, FColor::secondaryText(), 16)`
- **给 `QSvgWidget::load` 用 SVG 字节**
  - `FIcon::instance().getCodeArray(FIcon::StarFilled, FColor::warning())`
- **自己在 `paintEvent` 渲染用 `QSvgRenderer*`**
  - `FIcon::instance().getRenderer(FIcon::CaretTop, FColor::primaryText(), this)`

### 3.4 新增/补齐图标（避免“Name 不存在/资源找不到”）

新增 icon 需要三处同步（顺序不能乱）：

1. `gui/resources/icons.qrc`：加入 `icons/<file>.svg`
2. `gui/widgets/elementui/icon.cpp`：`_iconList` 追加 `<file>`（不带 `.svg`）
3. `gui/widgets/elementui/icon.h`：`enum Name` 追加枚举项，并确保与 `_iconList` **索引顺序一致**

> 典型报错：
> - 运行时报 `Icon file not found`：多半是 qrc 缺文件或资源没编译进去
> - 编译时报 `'XXX' is not a member of 'FIcon'`：多半是枚举没补齐

---

## 4. 组件清单（按当前目录文件）

### 4.1 基础/支撑

- `FColor`（`color.h/.cpp`）
- `FIcon`（`icon.h/.cpp`）
- `FShadowEf`（`shadow.h/.cpp`）
- `FScrollBar`（`scrollbar.h/.cpp`）
- `QSSHelper / FontHelper / ScaleHelper / Log`（`private/utils.h/.cpp`）

### 4.2 输入与表单

- `FInputLine`
- `FInputNumber`
- `FSelect`（含 `FOptionList/FOptionListItemWidget`）
- `FCheckbox / FCheckboxGroup`
- `FRadio / FRadioGroup`
- `FForm`

### 4.3 操作与弹层

- `FButton`
- `FLink`
- `FTooltip`（含 `FArrow`）
- `FPopOver`
- `FPopConfirm`
- `FDialog`
- `FDrawer`
- `FMask / FMaskEf`

### 4.4 反馈与提示

- `FMessage`
- `FNotification`
- `FMessageBox`

### 4.5 展示与容器

- `FTable`
- `FTabs / FTabBar`
- `FCollapse / FCollapseItem`
- `FCarousel`
- `FCard`
- `FBacktop`
- `FProgress`
- `FRate`
- `FAvatar`
- `FBadge`
- `FTag`
- `FText`
- `FDivider`
- `FImage`
- `FLink`

### 4.6 目前为“占位空壳”的组件（头文件无公开 API）

以下头文件目前只有类声明，没有公开方法/属性，暂无法按“可用组件”去调用：

- `FAlert`（`alert.h`）
- `FSpace`（`space.h`）
- `FBreadcrumb`（`breadcrumb.h`）
- `FSteps`（`steps.h`）
- `FTimeline`（`timeline.h`）
- `FDescriptions`（`descriptions.h`）
- `FStatistic`（`statistic.h`）
- `FPagination`（`pagination.h`）
- `FSkeleton`（`skeleton.h`）
- `FEmpty`（`empty.h`）
- `FCalendar`（`calendar.h`）
- `FResult`（`result.h`）
- `FMessageBox`（`messagebox.h`）
- `FPopConfirm`（`popconfirm.h`）
- `FPopOver`（`popover.h`）

> 这些组件如果你希望“也要详细说明 + 能直接用”，需要先把它们的 `*.h/*.cpp` **补齐实现**（目前仅靠 README 无法凭空编出真实 API）。

---

## 5. 逐一组件说明（可用组件）

> 说明格式：
> - **用途**
> - **核心 API（来自头文件）**
> - **信号（如有）**
> - **最小示例**
> - **常见坑**

### 5.1 `FButton`（`button.h/.cpp`）

- **用途**：Element 风格按钮，支持 style/type/size、loading、icon（左/右/仅图标）。
- **核心 API**：
  - `setStyle(FButton::Style)`：`Default/Plain/Round/Circle/Link/Text`
  - `setType(FButton::Type)`：`Default/Primary/Success/Info/Warning/Danger`
  - `setSize(FButton::Size)`：`Large/Default/Small`
  - `setDisabled(bool)`、`setLoading(bool)`
  - `setIcon(FIcon::Name, IconPosition)`：`Only/Left/Right`
  - `setText(const QString&)`
- **最小示例**：

```cpp
auto* b = new FButton("新增", this);
b->setType(FButton::Type::Primary)
 .setStyle(FButton::Style::Round)
 .setSize(FButton::Size::Default)
 .setIcon(FIcon::Plus, FButton::IconPosition::Left)
 .setLoading(false);
```

- **常见坑**：
  - `FButton` 内部会根据 type/style 生成 QSS；如果你外部再强行 setStyleSheet 可能覆盖其效果。

### 5.2 `FInputLine`（`inputline.h/.cpp`）

- **用途**：增强版输入框：prefix/suffix 图标、hover 变色、最大长度提示、clearable、showPassword。
- **核心 API**：
  - `setPlaceholder(const QString&)`
  - `setWidth(int)`、`setSize(Size)`（`Large/Default/Small`）
  - `setDisabled(bool)`、`setReadOnly(bool)`、`setAutoFocus()`
  - `setPrefixIcon(FIcon::Name[, callback])`
  - `setSuffixIcon(FIcon::Name[, callback])`
  - `setMaxLength(int)`（额外显示 “当前长度 / 最大长度”）
  - `setClearable(bool)`：启用清空（用 `CircleClose`）
  - `setShowPassword(bool)`：启用密码显示/隐藏（用 `View/Hide`）
- **最小示例**：

```cpp
auto* in = new FInputLine("请输入", this);
in->setPrefixIcon(FIcon::Search);
in->setSuffixIcon(FIcon::Edit);
in->setMaxLength(20);
in->setClearable(true);
```

- **常见坑**：
  - `setClearable(true)` 会占用 suffix icon；如果你同时还想要自定义 suffix，需要自行决定优先级/交互。

### 5.3 `FSelect`（`select.h/.cpp`）

- **用途**：下拉选择框，基于 `FInputLine`，弹出 `FOptionList`。
- **核心 API**：
  - `setOptions(const QStringList&)`
  - `addItem/addItems`
  - `setPlacement(Top/Bottom)`
- **信号**：
  - 复用 `QLineEdit::textChanged` 作为选中项变化通知
  - `FOptionListItemWidget::clicked(const QString&)`（内部用）
  - `FOptionList::itemClicked(const QString&)`（内部/可接）
- **最小示例**：

```cpp
auto* s = new FSelect(this);
s->setOptions({"A", "B", "C"}).setPlacement(FSelect::Placement::Bottom).setWidth(240);
connect(s, &QLineEdit::textChanged, this, [](const QString& v){ qDebug() << v; });
```

### 5.4 `FCheckbox / FCheckboxGroup`（`checkbox.h/.cpp`）

- **用途**：自绘风格复选框与复选框组（min/max 约束）。
- **核心 API（FCheckbox）**：
  - `setValue/getValue`（`QVariant`）
  - `setText/getText`
  - `setDisabled/isDisabled`
  - `setSize/getSize`（`Large/Default/Small`）
  - `setChecked/getChecked`
  - `setBorder/getBorder`
  - `setIndeterminate/getIndeterminate`
- **核心 API（FCheckboxGroup）**：
  - `setSize/getSize`、`setDisabled/isDisabled`
  - `setMin/getMin`、`setMax/getMax`
  - `addCheckbox(FCheckbox*)`、`setTitle(const QString&)`

### 5.5 `FRadio / FRadioGroup`（`radio.h/.cpp`）

- **用途**：自绘风格单选与单选组。
- **核心 API（FRadio）**：
  - `setValue/getValue`（`QVariant`）
  - `setText/getText`
  - `setDisabled/isDisabled`
  - `setSize/getSize`
  - `setChecked/getChecked`
  - `setBorder/getBorder`
- **核心 API（FRadioGroup）**：
  - `setSize/getSize`、`setDisabled/isDisabled`
  - `addRadio(FRadio*)`、`setTitle(const QString&)`

### 5.6 `FText`（`text.h/.cpp`）

- **用途**：带类型/字号/标签语义的文本控件，提供 click/rightClick/hover 信号。
- **核心 API**：
  - `setType/getType`：`Default/Primary/Success/Info/Warning/Danger`
  - `setSize/getSize`：`Large/Default/Small`
  - `setTag/getTag`：`Paragraph/Bold/Italic/...`
  - `setTruncated/getTruncated`：超长截断
  - `setColor(const QString&)`、`setFontSize(int)`
- **信号**：`clicked()`、`rightClicked()`、`hovered(bool)`
- **便捷函数**：`h1/h2/h3/p`（快速生成常用字号）

### 5.7 `FTag`（`tag.h/.cpp`）

- **用途**：标签（可关闭、圆角、不同 type/effect）。
- **核心 API**：
  - `setEffect(Dark/Light/Plain)`
  - `setType(Primary/Success/Info/Warning/Danger)`
  - `setSize(Large/Default/Small)`
  - `setCloseable(bool)`、`setRound(bool)`
  - `setText(const QString&)`

### 5.8 `FBadge`（`badge.h/.cpp`）

- **用途**：角标（数字/文本/dot），附着在 partner 上并自动定位。
- **核心 API**：
  - `setType(...)`、`setIsDot(bool)`
  - `setValue(int / QString)`、`setMax(int)`

### 5.9 `FProgress`（`progress.h/.cpp`）

- **用途**：进度条（线形/圆形/仪表盘），支持 status 图标、文本格式化、自定义颜色函数、动画。
- **核心 API**：
  - `setPercentage(int)`
  - `setType(Line/Circle/Dashboard)`
  - `setStrokeWidth(int)`
  - `setTextInside(bool)`
  - `setStatus(None/Success/Exception/Warning)`
  - `setIndeterminate(bool)`、`setDuration(int)`
  - `setColor(std::function<QString(int)>)`
  - `setShowText(bool)`
  - `setStrokeLinecap(Butt/Round/Square)`
  - `setFormat(std::function<QString(int)>)`

### 5.10 `FBacktop`（`backtop.h/.cpp`）

- **用途**：回到顶部按钮，绑定 `QScrollArea` 的纵向滚动条，超过阈值后显示。
- **核心 API**：
  - `setTarget(QScrollArea*)`
  - `setVisibilityHeight(int)`、`setRight(int)`、`setBottom(int)`
  - `setShape(Circle/Square)`、`setSize(Large/Default/Small)`、`setType(Icon/Text)`
- **图标**：默认使用 `FIcon::CaretTop`（SVG Renderer 绘制）

### 5.11 `FMask / FMaskEf`（`mask.h/.cpp`）

- **用途**：遮罩层（覆盖某个区域/组件），常用于 Drawer/Dialog 等的“点击空白关闭”。
- **核心 API**：
  - `FMaskEf::setMask(QWidget* partner, QWidget* covered)`：创建并挂载遮罩
- **信号**：`FMask::clicked()`

### 5.12 `FTooltip`（`tooltip.h/.cpp`）

- **用途**：提示气泡，支持多方位、深浅主题、触发方式、延迟、箭头、自动关闭等。
- **核心 API**：
  - `setPlacement(...)`（Top/Left/Right/Bottom + Start/End）
  - `setEffect(Dark/Light)`
  - `setTrigger(Hover/Click/Focus/ContextMenu)`
  - `setText(const QString&)`
  - `setDisabled(bool)`、`setOffset(int)`
  - `setShowAfter(int)`、`setHideAfter(int)`
  - `setShowArrow(bool)`
  - `setAutoClose(int)`、`setEnterable(bool)`
  - `setMoveable(bool)`、`setPosition(const QPoint&)`
- **关联类**：`FArrow` 负责箭头绘制与定位

### 5.13 `FDialog`（`dialog.h/.cpp`）

- **用途**：简易对话框（标题/正文/取消/确认）。
- **核心 API**：
  - `setTitle(const QString&)`
  - `setContent(const QString&)`
  - `int show()`（注意：这是类内自定义的 `show()`，不是 `QDialog::show()` 的返回类型）

### 5.14 `FDrawer`（`drawer.h/.cpp`）

- **用途**：抽屉组件（方向、遮罩、头部/底部、关闭按钮）。
- **核心 API**：
  - `setModal(bool)`
  - `setDirection(Direction)`：`RightToLeft/LeftToRight/TopToBottom/BottomToTop`
  - `setShowClose(bool)`
  - `setSize(int percent)`
  - `setTitle(const QString&)`
  - `setWithHeader(bool)`、`setWithFooter(bool)`
  - `setBody(QWidget*)`
- **信号**：`confirm()`

### 5.15 `FMessage`（`message.h/.cpp`）

- **用途**：轻量提示条（多位置堆叠），支持类型/是否朴素/关闭按钮/自动关闭时间。
- **核心 API**：
  - `setMessage/setParamater`
  - `setType(Primary/Success/Warning/Info/Error)`
  - `setPlain(bool)`
  - `setShowClose(bool showClose, bool autoClose=true)`
  - `setPlacement(Top/TopLeft/TopRight/Bottom/BottomLeft/BottomRight)`
  - `setDuration(int msec)`
  - `show()`

### 5.16 `FNotification`（`notification.h/.cpp`）

- **用途**：通知弹窗（四角堆叠），支持标题/内容/类型/关闭按钮/时长/位置。
- **核心 API**：
  - `setTitle/setContent`
  - `setType(Defualt/Primary/Success/Warning/Info/Error)`
  - `setShowClose(bool showClose=true, bool autoClose=true)`
  - `setPosition(TopRight/TopLeft/BottomRight/BottomLeft)`
  - `setDuration(int msec)`
  - `show()`

### 5.17 其他组件
本目录还包含大量组件。若你希望同样按上述模板把它们**逐个写到同等细节**，我建议按优先级分批补齐文档（避免 README 过长且难维护）。

### 5.18 `FCard`（`card.h/.cpp`）

- **用途**：卡片容器，支持 Header/Footer/Body、自定义阴影策略。
- **核心 API**：
  - `setHeader(const QString&)`、`setFooter(const QString&)`
  - `setBody(QWidget*)`
  - `setShadow(Shadow::Always/Hover/Never)`
- **最小示例**：

```cpp
auto* c = new FCard("标题", new QLabel("内容", this), this);
c->setShadow(FCard::Shadow::Hover);
```

### 5.19 `FTable`（`table.h/.cpp`）

- **用途**：带斑马纹/边框/高亮行的表格封装。
- **核心 API**：
  - `setWidth(const QList<int>& widths = {})`：设置各列宽
  - `setStripe(bool)`：斑马纹
  - `setBorder(bool)`：外边框
  - `setHightlight(int row, Highlight type)`：高亮某行（`Primary/Success/Info/Warning/Danger`）
- **事件**：覆写 `eventFilter/paintEvent` 做 hover 高亮。

### 5.20 `FTabs / FTabBar`（`tabs.h/.cpp`）

- **用途**：标签页，支持卡片风格、可关闭/可新增/可编辑、位置切换。
- **核心 API（FTabs）**：
  - `setType(Default/Card/BorderCard)`
  - `setTabPosition(Top/Bottom/Left/Right)`
  - `setCloseable(bool)`、`setAddable(bool)`、`setEditable(bool)`
  - `setStretch(bool)`
  - `getTabWidths()`：返回各 tab 宽度映射
- **核心 API（FTabBar）**：内部用于自绘，不额外开放新方法，构造时注入 type/position。

### 5.21 `FCollapse / FCollapseItem`（`collapse.h/.cpp`）

- **用途**：手风琴/折叠面板，支持图标位置、禁用、宽度设置。
- **核心 API（Item）**：
  - `setIconPosition(Left/Right)`、`setIcon(collapsedIcon, expandIcon)`
  - `setAllowCollapse(bool)`、`setCollapse()`、`setExpand()`、`toggleStatus()`
  - `setTitle(const QString&)`、`setContent(const QString&)`
  - `setWidth(int)`、`setLast(bool)`
- **核心 API（FCollapse）**：
  - `setAccordion(bool)`：手风琴模式
  - `setIcon(...)`、`setIconPosition(...)`
  - `setCollapse/setExpand/toggleStatus(int index)`
  - `addItem(FCollapseItem*)`、`delItem(int)`、`setWidth(int)`
- **默认图标**：收起 `FIcon::ArrowRight`，展开 `FIcon::ArrowDown`。

### 5.22 `FCarousel`（`carousel.h/.cpp`）

- **用途**：走马灯/轮播图，支持触发方式、指示器位置、箭头显示策略、自动播放、卡片模式、水平/垂直。
- **核心 API**：
  - `setTigger(Trigger::Hover/Click)`（注意：函数名为 `setTigger`）
  - `setIndicatorPos(Inside/Outside/None)`
  - `setArrow(Always/Hover/Never)`
  - `setAutoplay(bool)`、`setInterval(int)`、`setPauseOnHover(bool)`
  - `setType(Default/Card)`、`setCardScale(double)`
  - `setLoop(bool)`、`setDirection(Horizontal/Vertical)`
  - `addImage(const QPixmap&)`
- **箭头图标**：默认使用 `FIcon::ArrowLeft/ArrowRight` 对应的 `QSvgRenderer`。

### 5.23 `FAvatar`（`avatar.h/.cpp`）

- **用途**：头像，支持 Icon / Image / Text，圆形或方形，多尺寸。
- **核心 API**：
  - `setIcon(FIcon::Name = FIcon::UserFilled)`
  - `setImage(const QImage& = QImage(":/icons/other/example-avatar.png"))`
  - `setText(const QString& = "user")`
  - `setSize(Large/Default/Small)`、`setShape(Circle/Square)`
- **绘制**：`paintEvent` 内按类型绘制；Icon 使用 `QSvgRenderer`。

### 5.24 `FImage`（`image.h/.cpp`）

- **用途**：图片展示，支持类似 CSS `object-fit` 的模式。
- **核心 API**：
  - `setFit(Fit::Fill/Contain/Cover/None/ScaleDown)`
  - `setImage(const QImage&)`、`setPixmap(const QPixmap&)`
- **绘制**：`paintEvent` 依据 Fit 计算 `_imageRect` 并绘制。

### 5.25 `FLink`（`link.h/.cpp`）

- **用途**：超链接风格文本，支持类型颜色、下划线策略、禁用。
- **核心 API**：
  - `setType(Type::Default/Primary/Success/Info/Warning/Danger)`
  - `setUnderline(Underline::Default/Always/Hover/Never)`
  - `setDisabled(bool)`、`setText(const QString&)`
- **事件**：`enterEvent/leaveEvent` 控制 hover 颜色与下划线。

### 5.26 `FRate`（`rate.h/.cpp`）

- **用途**：评分组件，支持半星、文本/分值展示、自定义颜色与文本。
- **核心 API**：
  - `setScore(qreal)` / `setMax(int)`（必须是 5 的倍数；内部以十分制存储）
  - `setSize(Large/Default/Small)`
  - `setAllowHalf(bool)`、`setClearable(bool)`、`setDisabled(bool)`
  - `setLowThreshold(int)`、`setHighThreshold(int)`（注意：`setHighThreshold` 返回值声明有笔误，实际应为设置）
  - `setShowText(bool)`、`setShowScore(bool)`
  - `setColors(low, mid, high)`、`setTexts(first..fifth)`
- **内部**：使用 `QSvgWidget` 加载 `FIcon::Star / StarFilled` 的 SVG。

### 5.27 目前未实现/需补代码的组件

- `FAlert/FSpace/FBreadcrumb/FSteps/FTimeline/FDescriptions/FStatistic/FPagination/FSkeleton/FEmpty/FCalendar/FResult/FMessageBox/FPopConfirm/FPopOver`（头文件只有声明）


---

## 6. FAQ（常见问题）

### 6.1 图标不显示 / 日志提示 `Icon file not found`

检查：

- `gui/resources/icons.qrc` 是否已加入 `.pro` 的 `RESOURCES`
- `icons/<name>.svg` 是否真实存在
- `FIcon::_iconList` 的文件名是否与 qrc 保持一致（含连字符 `-`）
- SVG 是否使用了 `currentColor`（否则换色无效）

### 6.2 编译错误：`'XXX' is not a member of 'FIcon'`

说明使用了尚未存在的枚举项。处理方式：

- 优先改用已存在的 `FIcon::Name`
- 或按 3.4 的流程补齐：`icons.qrc` + `_iconList` + `enum Name`

### 6.3 组件尺寸在不同 DPI 下不一致

建议：

- 尺寸/边距/图标大小使用 `sc(...)`
- 新常量统一进 `constants.h`


