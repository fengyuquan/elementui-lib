#pragma once

#include <QtGlobal>

/**
* @file constants.h
* @brief Element UI 组件常量定义
* 
* 集中管理所有组件的硬编码参数，方便后期修改和维护
*/

namespace FConstants
{
    // ==================== Select 组件常量 ====================
    namespace FSelect
    {
        // 选项列表项高度
        constexpr int ItemHeight = 35;
        
        // 选项列表最大高度
        constexpr int MaxHeight = 300;
        
        // 选项列表内边距
        constexpr int Padding = 15;
        
        // 选项列表默认宽度
        constexpr int DefaultWidth = 300;
        
        // 选项列表项字体大小（像素）
        constexpr int ItemFontSize = 16;
        
        // 选项列表项左侧内边距（像素）
        constexpr int ItemPaddingLeft = 15;
        
        // 选项列表与输入框的间距
        constexpr int InputSpacing = 15;
        
        // 选项列表边框圆角
        constexpr int BorderRadius = 4;
        
        // 选项列表边框宽度（用于高度计算）
        constexpr int BorderWidth = 2;
    }
    
    // ==================== InputLine 组件常量 ====================
    namespace FInputLine
    {
        // 默认最小宽度（缩放后）
        constexpr int DefaultMinWidth = 240;
        
        // 大尺寸高度（缩放后）
        constexpr int LargeHeight = 40;
        
        // 默认尺寸高度（缩放后）
        constexpr int DefaultHeight = 32;
        
        // 小尺寸高度（缩放后）
        constexpr int SmallHeight = 24;
        
        // 大尺寸字体大小
        constexpr int LargeFontSize = 16;
        
        // 默认尺寸字体大小
        constexpr int DefaultFontSize = 16;
        
        // 小尺寸字体大小
        constexpr int SmallFontSize = 14;
        
        // 边框圆角
        constexpr int BorderRadius = 4;
        
        // 内边距（垂直 水平）
        constexpr int PaddingVertical = 1;
        constexpr int PaddingHorizontal = 11;
        
        // 图标大小
        constexpr int IconSize = 20;
        
        // 最大长度标签右边距
        constexpr int MaxLengthLabelRightMargin = 15;
        
        // 最大长度标签额外宽度
        constexpr int MaxLengthLabelExtraWidth = 10;
        
        // 最大长度提示字符串预留大小
        constexpr int MaxLengthTipReserve = 16;
        
        // 图标区域边距
        constexpr int IconAreaMargin = 2;
        
        // 图标区域边距（从高度计算）
        constexpr int IconAreaMarginFromHeight = 4;
    }
    
    // ==================== Icon 组件常量 ====================
    namespace FIcon
    {
        // 箭头图标线条宽度
        constexpr int ArrowLineWidth = 2;
        
        // 箭头大小相对于图标大小的比例（1/3）
        constexpr double ArrowSizeRatio = 1.0 / 3.0;
        
        // 箭头偏移比例（1/3）
        constexpr double ArrowOffsetRatio = 1.0 / 3.0;
        
        // 图标中心点计算（除以2）
        constexpr double CenterRatio = 0.5;
    }
    
    // ==================== ScrollBar 组件常量 ====================
    namespace FScrollBar
    {
        // 滚动条宽度（垂直）
        constexpr int VerticalWidth = 0;
        
        // 滚动条高度（水平）
        constexpr int HorizontalHeight = 10;
        
        // 滚动条手柄圆角
        constexpr int HandleBorderRadius = 5;
        
        // 滚动条手柄背景色（RGBA）
        constexpr int HandleBackgroundAlpha = 77;  // 0.3 * 255
        constexpr int HandleHoverAlpha = 128;      // 0.5 * 255
        
        // 滚动时间窗口（毫秒）
        constexpr qint64 ScrollTimeWindow = 500;
        
        // 滚动加速比例阈值
        constexpr int ScrollAccelerationThreshold = 15;
        constexpr double ScrollAccelerationRatio = 2.5;
        
        // 平滑滚动总步数
        constexpr int SmoothScrollTotalSteps = 24;  // 60 * 400 / 1000
        
        // 平滑滚动帧率（FPS）
        constexpr int SmoothScrollFPS = 60;
        
        // ALT 键加速倍数
        constexpr double AltKeyMultiplier = 5.0;
        
        // 平滑滚动计算中的除数（用于余弦函数）
        constexpr double SmoothScrollDivisor = 2.0;
    }
    
    // ==================== Shadow 组件常量 ====================
    namespace FShadow
    {
        // Basic 类型
        constexpr int BasicBlurRadius = 32;
        constexpr int BasicOffsetX = 0;
        constexpr int BasicOffsetY = 12;
        constexpr double BasicColorAlpha = 0.04;
        
        // Light 类型
        constexpr int LightBlurRadius = 12;
        constexpr int LightOffsetX = 0;
        constexpr int LightOffsetY = 0;
        constexpr double LightColorAlpha = 0.12;
        
        // Lighter 类型
        constexpr int LighterBlurRadius = 6;
        constexpr int LighterOffsetX = 0;
        constexpr int LighterOffsetY = 0;
        constexpr double LighterColorAlpha = 0.12;
        
        // Dark 类型
        constexpr int DarkBlurRadius = 48;
        constexpr int DarkOffsetX = 0;
        constexpr int DarkOffsetY = 16;
        constexpr double DarkColorAlpha = 0.08;
    }
    
    // ==================== Button 组件常量 ====================
    namespace FButton
    {
        // 默认内边距（垂直 水平）
        constexpr int DefaultPaddingVertical = 4;
        constexpr int DefaultPaddingHorizontal = 12;
        
        // 默认字体大小
        constexpr int DefaultFontSize = 12;
        
        // 默认边框圆角
        constexpr int DefaultBorderRadius = 4;
        
        // Round/Circle 样式边框圆角
        constexpr int RoundBorderRadius = 20;
        
        // Circle 样式内边距
        constexpr int CirclePadding = 8;
        
        // Circle 样式尺寸（宽高）
        constexpr int CircleSize = 40;
        
        // Large 尺寸内边距（垂直 水平）
        constexpr int LargePaddingVertical = 12;
        constexpr int LargePaddingHorizontal = 19;
        
        // Large 尺寸高度（缩放后）
        constexpr int LargeHeight = 40;
        
        // Small 尺寸边框圆角
        constexpr int SmallBorderRadius = 2;
        
        // Small 尺寸内边距（垂直 水平）
        constexpr int SmallPaddingVertical = 5;
        constexpr int SmallPaddingHorizontal = 11;
        
        // Small 尺寸字体大小
        constexpr int SmallFontSize = 14;
        
        // Small 尺寸高度（缩放后）
        constexpr int SmallHeight = 24;
        
        // Default 尺寸高度（缩放后）
        constexpr int DefaultHeight = 32;
        
        // 默认图标大小
        constexpr int DefaultIconSize = 18;
        
        // 小尺寸图标大小
        constexpr int SmallIconSize = 16;
    }
    
    // ==================== Checkbox 组件常量 ====================
    namespace FCheckbox
    {
        // 默认字体大小
        constexpr int DefaultFontSize = 16;
        
        // 小尺寸字体大小
        constexpr int SmallFontSize = 14;
        
        // 文本与指示器间距
        constexpr int Spacing = 10;
        
        // 小尺寸指示器大小
        constexpr int SmallIndicatorSize = 14;
        
        // 默认/大尺寸指示器大小
        constexpr int DefaultIndicatorSize = 16;
        
        // 指示器边框圆角
        constexpr int IndicatorBorderRadius = 2;
        
        // 大尺寸高度
        constexpr int LargeHeight = 50;
        
        // 默认尺寸高度
        constexpr int DefaultHeight = 40;
        
        // 小尺寸高度
        constexpr int SmallHeight = 30;
        
        // 大尺寸边框内边距（右 左）
        constexpr int LargeBorderPaddingRight = 20;
        constexpr int LargeBorderPaddingLeft = 15;
        
        // 默认尺寸边框内边距（右 左）
        constexpr int DefaultBorderPaddingRight = 18;
        constexpr int DefaultBorderPaddingLeft = 12;
        
        // 小尺寸边框内边距（右 左）
        constexpr int SmallBorderPaddingRight = 15;
        constexpr int SmallBorderPaddingLeft = 10;
        
        // 边框圆角
        constexpr int BorderRadius = 4;
        
        // 对勾绘制宽度比例（1/3）
        constexpr double CheckmarkWidthRatio = 1.0 / 3.0;
        
        // 对勾绘制高度比例（1/4）
        constexpr double CheckmarkHeightRatio = 1.0 / 4.0;
        
        // 横线绘制起始位置比例（1/4）
        constexpr double IndeterminateStartRatio = 1.0 / 4.0;
        
        // 横线绘制宽度比例（1/2）
        constexpr double IndeterminateWidthRatio = 1.0 / 2.0;
        
        // 标记线条宽度
        constexpr int MarkLineWidth = 2;
        
        // 组布局边距（左 上 右 下）
        constexpr int GroupMarginLeft = 15;
        constexpr int GroupMarginTop = 5;
        constexpr int GroupMarginRight = 15;
        constexpr int GroupMarginBottom = 5;
        
        // 组布局间距
        constexpr int GroupSpacing = 20;
    }
    
    // ==================== InputNumber 组件常量 ====================
    namespace FInputNumber
    {
        // 大尺寸字体大小
        constexpr int LargeFontSize = 16;
        
        // 默认尺寸字体大小
        constexpr int DefaultFontSize = 14;
        
        // 小尺寸字体大小
        constexpr int SmallFontSize = 12;
        
        // 大尺寸宽度
        constexpr int LargeWidth = 220;
        
        // 大尺寸高度
        constexpr int LargeHeight = 42;
        
        // 大尺寸按钮宽度
        constexpr int LargeButtonWidth = 42;
        
        // 大尺寸按钮高度
        constexpr int LargeButtonHeight = 40;
        
        // 默认尺寸宽度
        constexpr int DefaultWidth = 200;
        
        // 默认尺寸高度
        constexpr int DefaultHeight = 32;
        
        // 默认尺寸按钮宽度
        constexpr int DefaultButtonWidth = 32;
        
        // 默认尺寸按钮高度
        constexpr int DefaultButtonHeight = 30;
        
        // 小尺寸宽度
        constexpr int SmallWidth = 100;
        
        // 小尺寸高度
        constexpr int SmallHeight = 24;
        
        // 小尺寸按钮宽度
        constexpr int SmallButtonWidth = 22;
        
        // 小尺寸按钮高度
        constexpr int SmallButtonHeight = 20;
        
        // 边框圆角
        constexpr int BorderRadius = 4;
        
        // 按钮位置偏移（左/右）
        constexpr int ButtonPositionOffset = 1;
        
        // 大/默认尺寸图标大小
        constexpr int LargeDefaultIconSize = 20;
        
        // 小尺寸图标大小
        constexpr int SmallIconSize = 16;
    }
    
    // ==================== Radio 组件常量 ====================
    namespace FRadio
    {
        // 默认字体大小
        constexpr int DefaultFontSize = 16;
        
        // 小尺寸字体大小
        constexpr int SmallFontSize = 14;
        
        // 文本与指示器间距
        constexpr int Spacing = 10;
        
        // 小尺寸指示器大小
        constexpr int SmallIndicatorSize = 14;
        
        // 默认/大尺寸指示器大小
        constexpr int DefaultIndicatorSize = 16;
        
        // 小尺寸指示器边框圆角
        constexpr int SmallIndicatorBorderRadius = 8;
        
        // 默认/大尺寸指示器边框圆角
        constexpr int DefaultIndicatorBorderRadius = 9;
        
        // 大尺寸高度
        constexpr int LargeHeight = 50;
        
        // 默认尺寸高度
        constexpr int DefaultHeight = 40;
        
        // 小尺寸高度
        constexpr int SmallHeight = 30;
        
        // 大尺寸边框内边距（右 左）
        constexpr int LargeBorderPaddingRight = 20;
        constexpr int LargeBorderPaddingLeft = 15;
        
        // 默认尺寸边框内边距（右 左）
        constexpr int DefaultBorderPaddingRight = 18;
        constexpr int DefaultBorderPaddingLeft = 12;
        
        // 小尺寸边框内边距（右 左）
        constexpr int SmallBorderPaddingRight = 15;
        constexpr int SmallBorderPaddingLeft = 10;
        
        // 边框圆角
        constexpr int BorderRadius = 4;
        
        // 圆点半径比例（1/4）
        constexpr double DotRadiusRatio = 1.0 / 4.0;
        
        // 组布局边距（左 上 右 下）
        constexpr int GroupMarginLeft = 15;
        constexpr int GroupMarginTop = 5;
        constexpr int GroupMarginRight = 15;
        constexpr int GroupMarginBottom = 5;
        
        // 组布局间距
        constexpr int GroupSpacing = 20;
    }
    
    // ==================== Progress 组件常量 ====================
    namespace FProgress
    {
        // 默认字体大小
        constexpr int DefaultFontSize = 8;
        
        // 默认描边宽度
        constexpr int DefaultStrokeWidth = 6;
        
        // 圆形最小尺寸
        constexpr int CircleMinSize = 50;
        
        // 仪表盘最小宽度
        constexpr int DashboardMinWidth = 50;
        
        // 仪表盘最小高度
        constexpr int DashboardMinHeight = 40;
        
        // 文本间距
        constexpr int TextSpacing = 10;
        
        // 图标大小
        constexpr int IconSize = 16;
        
        // 圆形起始角度
        constexpr int CircleStartAngle = 90;
        
        // 圆形跨度角度
        constexpr int CircleSpanAngle = 360;
        
        // 仪表盘起始角度
        constexpr int DashboardStartAngle = 227;
        
        // 仪表盘跨度角度
        constexpr int DashboardSpanAngle = 274;
        
        // 仪表盘宽度比例
        constexpr double DashboardWidthRatio = 1.15;
    }
    
    // ==================== Card 组件常量 ====================
    namespace FCard
    {
        // 最小宽度
        constexpr int MinWidth = 300;
        
        // 最小高度
        constexpr int MinHeight = 240;
        
        // 最大宽度
        constexpr int MaxWidth = 380;
        
        // 最大高度
        constexpr int MaxHeight = 280;
        
        // 内边距（水平 垂直）
        constexpr int PaddingHorizontal = 8;
        constexpr int PaddingVertical = 12;
        
        // 主体边距（左 右 下）
        constexpr int BodyMarginLeft = 1;
        constexpr int BodyMarginRight = 1;
        constexpr int BodyMarginBottom = 1;
        
        // 边框圆角
        constexpr int BorderRadius = 4;
    }
    
    // ==================== Notification 组件常量 ====================
    namespace FNotification
    {
        // 最小尺寸
        constexpr int MinWidth = 250;
        constexpr int MinHeight = 100;
        
        // 边距（水平 上 下）
        constexpr int MarginHorizontal = 20;
        constexpr int MarginTop = 15;
        constexpr int MarginBottom = 15;
        
        // 间距
        constexpr int Spacing = 10;
        
        // 内容左侧间距
        constexpr int ContentLeftSpacing = 34;
        
        // 内容右侧间距
        constexpr int ContentRightSpacing = 30;
        
        // 关闭图标大小
        constexpr int CloseIconSize = 16;
        
        // 图标大小
        constexpr int IconSize = 24;
        
        // 位置偏移
        constexpr int PositionOffset = 15;
        
        // 偏移量
        constexpr int Offset = 10;
        
        // 边框调整
        constexpr int BorderAdjust = 1;
        
        // 边框圆角
        constexpr int BorderRadius = 8;
        
        // 默认持续时间（毫秒）
        constexpr int DefaultDuration = 4500;
    }
    
    // ==================== Message 组件常量 ====================
    namespace FMessage
    {
        // 边距
        constexpr int Margin = 10;
        
        // 间距
        constexpr int Spacing = 10;
        
        // 偏移量
        constexpr int Offset = 10;
        
        // 图标大小
        constexpr int IconSize = 20;
        
        // 边框圆角
        constexpr int BorderRadius = 4;
        
        // 边框宽度
        constexpr int BorderWidth = 2;
        
        // 参数颜色
        constexpr const char* ParameterColor = "#008080";
        
        // 默认持续时间（毫秒）
        constexpr int DefaultDuration = 3000;
    }
    
    // ==================== Tooltip 组件常量 ====================
    namespace FTooltip
    {
        // 箭头宽度（水平方向）
        constexpr int ArrowWidth = 16;
        
        // 箭头高度（垂直方向）
        constexpr int ArrowHeight = 8;
        
        // 箭头边框宽度
        constexpr int ArrowBorderWidth = 1;
        
        // 内边距（垂直 水平）
        constexpr int PaddingVertical = 7;
        constexpr int PaddingHorizontal = 11;
        
        // 边框圆角
        constexpr int BorderRadius = 4;
        
        // 边框宽度
        constexpr int BorderWidth = 1;
        
        // 空白线偏移
        constexpr int BlankLineOffset = 2;
        
        // 空白线宽度
        constexpr int BlankLineWidth = 2;
        
        // 默认偏移
        constexpr int DefaultOffset = 15;
        
        // 默认隐藏延迟（毫秒）
        constexpr int DefaultHideAfter = 200;
    }
    
    // ==================== Drawer 组件常量 ====================
    namespace FDrawer
    {
        // 表头字体大小
        constexpr int HeaderFontSize = 12;
        
        // 关闭图标大小
        constexpr int CloseIconSize = 20;
        
        // 表头边距
        constexpr int HeaderMargin = 20;
        
        // 主体边距
        constexpr int BodyMargin = 20;
        
        // 页脚边距（水平 上 下）
        constexpr int FooterMarginHorizontal = 20;
        constexpr int FooterMarginTop = 10;
        constexpr int FooterMarginBottom = 20;
        
        // 页脚按钮间距
        constexpr int FooterButtonSpacing = 10;
        
        // 默认宽度比例
        constexpr double DefaultWidthRatio = 0.3;
    }
    
    // ==================== Mask 组件常量 ====================
    namespace FMask
    {
        // 遮罩透明度（0-255）
        constexpr int Alpha = 77;  // 0.3 * 255
    }
    
    // ==================== Dialog 组件常量 ====================
    namespace FDialog
    {
        // 宽度
        constexpr int Width = 500;
        
        // 高度
        constexpr int Height = 175;
        
        // 边距
        constexpr int Margin = 20;
        
        // 间距
        constexpr int Spacing = 20;
        
        // 按钮间距
        constexpr int ButtonSpacing = 10;
        
        // 位置比例（相对于父窗口高度的比例）
        constexpr double PositionRatio = 0.18;
    }
    
    // ==================== Tabs 组件常量 ====================
    namespace FTabs
    {
        // 标签高度
        constexpr int TabHeight = 50;
        
        // 标签字体大小
        constexpr int TabFontSize = 10;
        
        // 标签最小宽度
        constexpr int MinTabWidth = 50;
        
        // 标签内边距（水平）
        constexpr int TabPaddingHorizontal = 20;
        
        // 分割线高度
        constexpr int DividerHeight = 2;
        
        // 选中线偏移
        constexpr int SelectedLineOffset = 40;
        
        // 卡片边框高度
        constexpr int CardBorderHeight = 1;
        
        // 卡片边框圆角
        constexpr int CardBorderRadius = 6;
        
        // 垂直标签文本偏移
        constexpr int VerticalTabTextOffset = 30;
    }
    
    // ==================== Table 组件常量 ====================
    namespace FTable
    {
        // 行高度
        constexpr int RowHeight = 50;
        
        // 表头高度
        constexpr int HeaderHeight = 50;
        
        // 表头字体大小
        constexpr int HeaderFontSize = 9;
        
        // 表头内边距（垂直 水平）
        constexpr int HeaderPaddingVertical = 0;
        constexpr int HeaderPaddingHorizontal = 12;
        
        // 单元格内边距（垂直 水平）
        constexpr int ItemPaddingVertical = 0;
        constexpr int ItemPaddingHorizontal = 12;
        
        // 边框宽度
        constexpr int BorderWidth = 1;
    }
    
    // ==================== Carousel 组件常量 ====================
    namespace FCarousel
    {
        // 箭头直径
        constexpr int ArrowDiameter = 36;
        
        // 箭头边距
        constexpr int ArrowMargin = 20;
        
        // 箭头图标大小
        constexpr int ArrowIconSize = 12;
        
        // 指示器宽度
        constexpr int IndicatorWidth = 30;
        
        // 指示器高度
        constexpr int IndicatorHeight = 2;
        
        // 指示器间距
        constexpr int IndicatorSpacing = 10;
        
        // 指示器底部边距
        constexpr int IndicatorBottomMargin = 25;
        
        // 默认自动播放间隔（毫秒）
        constexpr int DefaultInterval = 3000;
        
        // 卡片缩放比例
        constexpr double DefaultCardScale = 0.83;
    }
    
    // ==================== Collapse 组件常量 ====================
    namespace FCollapse
    {
        // 标题字体大小
        constexpr int TitleFontSize = 9;
        
        // 内容字体大小
        constexpr int ContentFontSize = 9;
        
        // 标题高度
        constexpr int TitleHeight = 60;
        
        // 图标大小
        constexpr int IconSize = 12;
        
        // 图标间距
        constexpr int IconSpacing = 10;
        
        // 展开时底部边距
        constexpr int ExpandMarginBottom = 20;
        
        // 默认宽度
        constexpr int DefaultWidth = 800;
    }
    
    // ==================== Avatar 组件常量 ====================
    namespace FAvatar
    {
        // 默认尺寸
        constexpr int DefaultSize = 50;
        
        // 小尺寸
        constexpr int SmallSize = 30;
        
        // 大尺寸
        constexpr int LargeSize = 60;
        
        // 方形边框圆角
        constexpr int SquareBorderRadius = 4;
        
        // 默认尺寸图标位置和大小
        constexpr int DefaultIconX = 13;
        constexpr int DefaultIconY = 12;
        constexpr int DefaultIconSize = 25;
        
        // 大尺寸图标位置和大小
        constexpr int LargeIconX = 15;
        constexpr int LargeIconY = 15;
        constexpr int LargeIconSize = 30;
        
        // 小尺寸图标位置和大小
        constexpr int SmallIconX = 6;
        constexpr int SmallIconY = 5;
        constexpr int SmallIconSize = 18;
    }
    
    // ==================== Rate 组件常量 ====================
    namespace FRate
    {
        // 星星数量
        constexpr int StarCount = 5;
        
        // 布局边距（垂直）
        constexpr int LayoutMarginVertical = 8;
        
        // 布局间距
        constexpr int LayoutSpacing = 10;
        
        // 默认图标大小
        constexpr int DefaultIconSize = 22;
        
        // 大尺寸图标大小
        constexpr int LargeIconSize = 22;
        
        // 小尺寸图标大小
        constexpr int SmallIconSize = 18;
        
        // 默认尺寸高度
        constexpr int DefaultHeight = 38;
        
        // 大尺寸高度
        constexpr int LargeHeight = 38;
        
        // 小尺寸高度
        constexpr int SmallHeight = 34;
    }
    
    // ==================== Backtop 组件常量 ====================
    namespace FBacktop
    {
        // 默认可见高度
        constexpr int DefaultVisibilityHeight = 200;
        
        // 默认右边距
        constexpr int DefaultRight = 40;
        
        // 默认底边距
        constexpr int DefaultBottom = 40;
        
        // 默认尺寸
        constexpr int DefaultSize = 60;
        
        // 大尺寸
        constexpr int LargeSize = 80;
        
        // 小尺寸
        constexpr int SmallSize = 40;
        
        // 方形边框圆角
        constexpr int SquareBorderRadius = 4;
        
        // 默认尺寸图标位置和大小
        constexpr int DefaultIconX = 18;
        constexpr int DefaultIconY = 18;
        constexpr int DefaultIconSize = 25;
        
        // 大尺寸图标位置和大小
        constexpr int LargeIconX = 25;
        constexpr int LargeIconY = 25;
        constexpr int LargeIconSize = 30;
        
        // 小尺寸图标位置和大小
        constexpr int SmallIconX = 11;
        constexpr int SmallIconY = 10;
        constexpr int SmallIconSize = 18;
        
        // 大文本字体大小
        constexpr int LargeTextFontSize = 14;
    }
    
    // ==================== Badge 组件常量 ====================
    namespace FBadge
    {
        // 高度
        constexpr int Height = 20;
        
        // 最大宽度
        constexpr int MaxWidth = 100;
        
        // 边框圆角
        constexpr int BorderRadius = 10;
        
        // 内边距（上 水平 下）
        constexpr int PaddingTop = 0;
        constexpr int PaddingHorizontal = 6;
        constexpr int PaddingBottom = 2;
    }
    
    // ==================== Tag 组件常量 ====================
    namespace FTag
    {
        // 文本字体大小
        constexpr int TextFontSize = 9;
        
        // 关闭图标大小
        constexpr int CloseIconSize = 16;
        
        // 布局间距
        constexpr int LayoutSpacing = 4;
        
        // 边框圆角
        constexpr int BorderRadius = 4;
        
        // 圆角样式边框圆角
        constexpr int RoundBorderRadius = 15;
        
        // 内边距（垂直 水平）
        constexpr int PaddingVertical = 0;
        constexpr int PaddingHorizontal = 9;
        
        // 默认尺寸高度
        constexpr int DefaultHeight = 30;
        
        // 默认尺寸最小宽度
        constexpr int DefaultMinWidth = 60;
        
        // 大尺寸高度
        constexpr int LargeHeight = 40;
        
        // 大尺寸最小宽度
        constexpr int LargeMinWidth = 70;
        
        // 小尺寸高度
        constexpr int SmallHeight = 25;
        
        // 小尺寸最小宽度
        constexpr int SmallMinWidth = 50;
    }
    
    // ==================== 通用常量 ====================
    namespace FCommon
    {
        // 布局边距和间距
        constexpr int LayoutMargin = 0;
        constexpr int LayoutSpacing = 0;
        
        // 默认 DPI（用于计算缩放因子）
        constexpr int DefaultDPI = 96;
        
        // 颜色透明度最大值
        constexpr int ColorAlphaMax = 255;
        
        // 最大长度标签格式化字符串前缀
        constexpr const char* MaxLengthLabelPrefix = "0 / ";
        
        // 垂直居中计算除数
        constexpr double VerticalCenterDivisor = 2.0;
    }
}
