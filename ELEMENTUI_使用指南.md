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

