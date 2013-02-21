// -*- compile-command:"csc /target:exe /r:System.dll,System.Windows.Forms.dll,System.Drawing.dll /out:sysinfo.exe SysInfoString.cs SysInfoList.cs  && sysinfo " -*-
using System.Windows.Forms;
using System.Drawing;
using System;

class SysInfoString
{
	static SysInfoString()
	{
		Init();
	}
	protected static void Init()
	{
		Console.WriteLine("SysInfoString::Init()...");

		_Labels = new string[] {
			"ActiveWindowTrackingDelay",
			"ArrangeDirection",
			"ArrangeStartingPosition",
			"BootMode",
			"Border3DSize",
			"BorderMultiplierFactor",
			"BorderSize",
			"CaptionButtonSize",
			"CaptionHeight",
			"CaretBlinkTime",
			"CaretWidth",
			"ComputerName",
			"CursorSize",
			"DbcsEnabled",
			"DebugOS",
			"DoubleClickSize",
			"DoubleClickTime",
			"DragFullWindows",
			"DragSize",
			"FixedFrameBorderSize",
			"FontSmoothingContrast",
			"FontSmoothingType",
			"FrameBorderSize",
			"HighContrast",
			"HorizontalFocusThickness",
			"HorizontalResizeBorderThickness",
			"HorizontalScrollBarArrowWidth",
			"HorizontalScrollBarHeight",
			"HorizontalScrollBarThumbWidth",
			"IconHorizontalSpacing",
			"IconSize",
			"IconSpacingSize",
			"IconVerticalSpacing",
			"IsActiveWindowTrackingEnabled",
			"IsComboBoxAnimationEnabled",
			"IsDropShadowEnabled",
			"IsFlatMenuEnabled",
			"IsFontSmoothingEnabled",
			"IsHotTrackingEnabled",
			"IsIconTitleWrappingEnabled",
			"IsKeyboardPreferred",
			"IsListBoxSmoothScrollingEnabled",
			"IsMenuAnimationEnabled",
			"IsMenuFadeEnabled",
			"IsMinimizeRestoreAnimationEnabled",
			"IsSelectionFadeEnabled",
			"IsSnapToDefaultEnabled",
			"IsTitleBarGradientEnabled",
			"IsToolTipAnimationEnabled",
			"KanjiWindowHeight",
			"KeyboardDelay",
			"KeyboardSpeed",
			"MaxWindowTrackSize",
			"MenuAccessKeysUnderlined",
			"MenuBarButtonSize",
			"MenuButtonSize",
			"MenuCheckSize",
			"MenuFont",
			"MenuHeight",
			"MenuShowDelay",
			"MidEastEnabled",
			"MinimizedWindowSize",
			"MinimizedWindowSpacingSize",
			"MinimumWindowSize",
			"MinWindowTrackSize",
			"MonitorCount",
			"MonitorsSameDisplayFormat",
			"MouseButtons",
			"MouseButtonsSwapped",
			"MouseHoverSize",
			"MouseHoverTime",
			"MousePresent",
			"MouseSpeed",
			"MouseWheelPresent",
			"MouseWheelScrollDelta",
			"MouseWheelScrollLines",
			"NativeMouseWheelSupport",
			"Network",
			"PenWindows",
			"PopupMenuAlignment",
			"PowerStatus",
			"PrimaryMonitorMaximizedWindowSize",
			"PrimaryMonitorSize",
			"RightAlignedMenus",
			"ScreenOrientation",
			"Secure",
			"ShowSounds",
			"SizingBorderWidth",
			"SmallCaptionButtonSize",
			"SmallIconSize",
			"TerminalServerSession",
			"ToolWindowCaptionButtonSize",
			"ToolWindowCaptionHeight",
			"UIEffectsEnabled",
			"UserDomainName",
			"UserInteractive",
			"UserName",
			"VerticalFocusThickness",
			"VerticalResizeBorderThickness",
			"VerticalScrollBarArrowHeight",
			"VerticalScrollBarThumbHeight",
			"VerticalScrollBarWidth",
			"VirtualScreen",
			"WorkingArea",
		};
		_Values = new string[] {
			SystemInformation.ActiveWindowTrackingDelay.ToString(),
			SystemInformation.ArrangeDirection.ToString(),
			SystemInformation.ArrangeStartingPosition.ToString(),
			SystemInformation.BootMode.ToString(),
			SystemInformation.Border3DSize.ToString(),
			SystemInformation.BorderMultiplierFactor.ToString(),
			SystemInformation.BorderSize.ToString(),
			SystemInformation.CaptionButtonSize.ToString(),
			SystemInformation.CaptionHeight.ToString(),
			SystemInformation.CaretBlinkTime.ToString(),
			SystemInformation.CaretWidth.ToString(),
			SystemInformation.ComputerName.ToString(),
			SystemInformation.CursorSize.ToString(),
			SystemInformation.DbcsEnabled.ToString(),
			SystemInformation.DebugOS.ToString(),
			SystemInformation.DoubleClickSize.ToString(),
			SystemInformation.DoubleClickTime.ToString(),
			SystemInformation.DragFullWindows.ToString(),
			SystemInformation.DragSize.ToString(),
			SystemInformation.FixedFrameBorderSize.ToString(),
			SystemInformation.FontSmoothingContrast.ToString(),
			SystemInformation.FontSmoothingType.ToString(),
			SystemInformation.FrameBorderSize.ToString(),
			SystemInformation.HighContrast.ToString(),
			SystemInformation.HorizontalFocusThickness.ToString(),
			SystemInformation.HorizontalResizeBorderThickness.ToString(),
			SystemInformation.HorizontalScrollBarArrowWidth.ToString(),
			SystemInformation.HorizontalScrollBarHeight.ToString(),
			SystemInformation.HorizontalScrollBarThumbWidth.ToString(),
			SystemInformation.IconHorizontalSpacing.ToString(),
			SystemInformation.IconSize.ToString(),
			SystemInformation.IconSpacingSize.ToString(),
			SystemInformation.IconVerticalSpacing.ToString(),
			SystemInformation.IsActiveWindowTrackingEnabled.ToString(),
			SystemInformation.IsComboBoxAnimationEnabled.ToString(),
			SystemInformation.IsDropShadowEnabled.ToString(),
			SystemInformation.IsFlatMenuEnabled.ToString(),
			SystemInformation.IsFontSmoothingEnabled.ToString(),
			SystemInformation.IsHotTrackingEnabled.ToString(),
			SystemInformation.IsIconTitleWrappingEnabled.ToString(),
			SystemInformation.IsKeyboardPreferred.ToString(),
			SystemInformation.IsListBoxSmoothScrollingEnabled.ToString(),
			SystemInformation.IsMenuAnimationEnabled.ToString(),
			SystemInformation.IsMenuFadeEnabled.ToString(),
			SystemInformation.IsMinimizeRestoreAnimationEnabled.ToString(),
			SystemInformation.IsSelectionFadeEnabled.ToString(),
			SystemInformation.IsSnapToDefaultEnabled.ToString(),
			SystemInformation.IsTitleBarGradientEnabled.ToString(),
			SystemInformation.IsToolTipAnimationEnabled.ToString(),
			SystemInformation.KanjiWindowHeight.ToString(),
			SystemInformation.KeyboardDelay.ToString(),
			SystemInformation.KeyboardSpeed.ToString(),
			SystemInformation.MaxWindowTrackSize.ToString(),
			SystemInformation.MenuAccessKeysUnderlined.ToString(),
			SystemInformation.MenuBarButtonSize.ToString(),
			SystemInformation.MenuButtonSize.ToString(),
			SystemInformation.MenuCheckSize.ToString(),
			SystemInformation.MenuFont.ToString(),
			SystemInformation.MenuHeight.ToString(),
			SystemInformation.MenuShowDelay.ToString(),
			SystemInformation.MidEastEnabled.ToString(),
			SystemInformation.MinimizedWindowSize.ToString(),
			SystemInformation.MinimizedWindowSpacingSize.ToString(),
			SystemInformation.MinimumWindowSize.ToString(),
			SystemInformation.MinWindowTrackSize.ToString(),
			SystemInformation.MonitorCount.ToString(),
			SystemInformation.MonitorsSameDisplayFormat.ToString(),
			SystemInformation.MouseButtons.ToString(),
			SystemInformation.MouseButtonsSwapped.ToString(),
			SystemInformation.MouseHoverSize.ToString(),
			SystemInformation.MouseHoverTime.ToString(),
			SystemInformation.MousePresent.ToString(),
			SystemInformation.MouseSpeed.ToString(),
			SystemInformation.MouseWheelPresent.ToString(),
			SystemInformation.MouseWheelScrollDelta.ToString(),
			SystemInformation.MouseWheelScrollLines.ToString(),
			SystemInformation.NativeMouseWheelSupport.ToString(),
			SystemInformation.Network.ToString(),
			SystemInformation.PenWindows.ToString(),
			SystemInformation.PopupMenuAlignment.ToString(),
			SystemInformation.PowerStatus.ToString(),
			SystemInformation.PrimaryMonitorMaximizedWindowSize.ToString(),
			SystemInformation.PrimaryMonitorSize.ToString(),
			SystemInformation.RightAlignedMenus.ToString(),
			SystemInformation.ScreenOrientation.ToString(),
			SystemInformation.Secure.ToString(),
			SystemInformation.ShowSounds.ToString(),
			SystemInformation.SizingBorderWidth.ToString(),
			SystemInformation.SmallCaptionButtonSize.ToString(),
			SystemInformation.SmallIconSize.ToString(),
			SystemInformation.TerminalServerSession.ToString(),
			SystemInformation.ToolWindowCaptionButtonSize.ToString(),
			SystemInformation.ToolWindowCaptionHeight.ToString(),
			SystemInformation.UIEffectsEnabled.ToString(),
			SystemInformation.UserDomainName.ToString(),
			SystemInformation.UserInteractive.ToString(),
			SystemInformation.UserName.ToString(),
			SystemInformation.VerticalFocusThickness.ToString(),
			SystemInformation.VerticalResizeBorderThickness.ToString(),
			SystemInformation.VerticalScrollBarArrowHeight.ToString(),
			SystemInformation.VerticalScrollBarThumbHeight.ToString(),
			SystemInformation.VerticalScrollBarWidth.ToString(),
			SystemInformation.VirtualScreen.ToString(),
			SystemInformation.WorkingArea.ToString(),
		};
	}
	public static string[] Labels
	{
		get
		{
			return Labels;
		}
	}
	public static string[] Values
	{
		get
		{
			return Values;
		}
	}
	public static float MaxLabelWidth(Graphics graphics, Font font)
	{
		return MaxWidth(Labels, graphics, font);
	}
	public static float MaxValueWidth(Graphics graphics, Font font)
	{
		return MaxWidth(Values, graphics, font);
	}
	protected static float MaxWidth(string [] stringList, Graphics graphics, Font font)
	{
		float maxWidth = float.MinValue;
		foreach (string item in stringList)
		{
			maxWidth = Math.Max(maxWidth, graphics.MeasureString(item, font).Width);
		}
		return maxWidth;
	}
	protected static string [] _Labels;
	protected static string [] _Values;
}
