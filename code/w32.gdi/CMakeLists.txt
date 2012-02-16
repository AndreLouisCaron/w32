# Copyright (c) 2009-2012, Andre Caron (andre.l.caron@gmail.com)
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

file(GLOB ${module}_headers
  __configure__.hpp
  __module__.hpp
  Animation.hpp
  Application.hpp
  Atom.hpp
  AtomProperty.hpp
  Bitmap.hpp
  Blend.hpp
  Brush.hpp
  Button.hpp
  Calendar.hpp
  callback.hpp
  capture.hpp
  ChooseColorDialog.hpp
  ChooseFontDialog.hpp
  Class.hpp
  Color.hpp
  ComboBox.hpp
  console.hpp
  Control.hpp
  Cursor.hpp
  DateTimePicker.hpp
  desktop.hpp
  Device.hpp
  DeviceCompatibleBitmap.hpp
  DeviceContext.hpp
  DeviceIndependantBitmap.hpp
  Dialog.hpp
  Dispatcher.hpp
  Edit.hpp
  enable_common_controls.hpp
  EnhancedMetafile.hpp
  Event.hpp
  EventQueue.hpp
  Focus.hpp
  Font.hpp
  fonts.hpp
  Foreground.hpp
  GainedKeyboardFocus.hpp
  Group.hpp
  Header.hpp
  Icon.hpp
  image.hpp
  ImageList.hpp
  IpAddress.hpp
  Key.hpp
  KeyboardFocus.hpp
  KeyboardNotification.hpp
  KeyPressed.hpp
  KeyReleased.hpp
  LeftButtonDoubleClick.hpp
  LeftButtonDown.hpp
  LeftButtonUp.hpp
  ListBox.hpp
  ListView.hpp
  loop.hpp
  LosingKeyboardFocus.hpp
  LosingMouseCapture.hpp
  MappingMode.hpp
  Menu.hpp
  Message.hpp
  MessageBox.hpp
  Metafile.hpp
  Monitor.hpp
  MouseCapture.hpp
  MouseHover.hpp
  MouseLeave.hpp
  MouseMove.hpp
  MouseNotification.hpp
  NamedProperty.hpp
  Notification.hpp
  OpenFileDialog.hpp
  OpenGLContext.hpp
  PaintContext.hpp
  Pen.hpp
  PixelFormat.hpp
  Point.hpp
  post.hpp
  ProgressBar.hpp
  Property.hpp
  PropertySearch.hpp
  PropertySheet.hpp
  Quit.hpp
  Rectangle.hpp
  Region.hpp
  ResourceDialog.hpp
  RightButtonDown.hpp
  SaveFileDialog.hpp
  ScrollBar.hpp
  Size.hpp
  Splash.hpp
  Static.hpp
  StatusBar.hpp
  SystemColor.hpp
  TabControl.hpp
  TextMetrics.hpp
  ThreadEvents.hpp
  ThreadWindowsEvents.hpp
  Timer.hpp
  Tooltip.hpp
  TrackBar.hpp
  TreeView.hpp
  UpDown.hpp
  Window.Handler.hpp
  Window.hpp
  WindowEvents.hpp
)
file(GLOB ${module}_sources
  Animation.cpp
  Atom.cpp
  Bitmap.cpp
  Blend.cpp
  Brush.cpp
  Button.cpp
  Calendar.cpp
  capture.cpp
  Class.cpp
  ComboBox.cpp
  console.cpp
  Cursor.cpp
  DateTimePicker.cpp
  desktop.cpp
  Device.cpp
  DeviceCompatibleBitmap.cpp
  DeviceContext.cpp
  DeviceIndependantBitmap.cpp
  Dialog.cpp
  Edit.cpp
  enable_common_controls.cpp
  EnhancedMetafile.cpp
  EventQueue.cpp
  Focus.cpp
  Font.cpp
  fonts.cpp
  Foreground.cpp
  Group.cpp
  Header.cpp
  Icon.cpp
  ImageList.cpp
  IpAddress.cpp
  Key.cpp
  KeyboardFocus.cpp
  LeftButtonDoubleClick.cpp
  LeftButtonDown.cpp
  LeftButtonUp.cpp
  ListBox.cpp
  ListView.cpp
  loop.cpp
  MappingMode.cpp
  Menu.cpp
  Message.cpp
  MessageBox.cpp
  Metafile.cpp
  Monitor.cpp
  MouseCapture.cpp
  MouseHover.cpp
  MouseLeave.cpp
  MouseMove.cpp
  OpenGLContext.cpp
  PaintContext.cpp
  Pen.cpp
  PixelFormat.cpp
  post.cpp
  ProgressBar.cpp
  PropertySearch.cpp
  PropertySheet.cpp
  Quit.cpp
  Region.cpp
  RightButtonDown.cpp
  ScrollBar.cpp
  Splash.cpp
  Static.cpp
  StatusBar.cpp
  SystemColor.cpp
  TabControl.cpp
  TextMetrics.cpp
  ThreadEvents.cpp
  ThreadWindowsEvents.cpp
  Timer.cpp
  Tooltip.cpp
  TrackBar.cpp
  TreeView.cpp
  UpDown.cpp
  window-procedure.cpp
  Window.cpp
  WindowEvents.cpp
)
set(${module}_libraries
  ComCtl32.lib
)
set(${module}_dependencies
  w32
)

add_library(${module}
  STATIC
  ${${module}_headers}
  ${${module}_sources}
)
target_link_libraries(${module} ${${module}_libraries})
add_dependencies(${module} ${${module}_dependencies})
