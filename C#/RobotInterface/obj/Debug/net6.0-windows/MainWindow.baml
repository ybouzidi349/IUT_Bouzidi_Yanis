   M S B A M L   `   `   `  ����I  ERobotInterface, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null/clr-namespace:RobotInterfaceRobotInterface  5   	       RobotInterface.MainWindow   5   	   W SPresentationCore, Version=6.0.2.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=6.0.2.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35e aSystem.Windows.Controls.Ribbon, Version=6.0.2.0, Culture=neutral, PublicKeyToken=b77a5c561934e089R NWindowsBase, Version=6.0.2.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35F 9http://schemas.microsoft.com/winfx/2006/xaml/presentation     5   	   R NSystem.Xaml, Version=6.0.2.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   .localclr-namespace:RobotInterface     5   	     � Title$  
MainWindow��5   	   $	��450��6   $	��800��6)   .��5	      �  � RowDefinitions 5
   
   �� 5      $��1* �6   �� 5      $��50 �6    � ColumnDefinitions 5   
   �� 5      $��1* �6   �� 5      $��1* �6   .+�5   
   �� -   5         ��Name$ groupBox��5      $��Emission��6%   $��10q�67   ���	#FFDDDDDD
���   �$��0��6n   $��0��6~   .��5      �� -   5         ��Name$ textBoxEmission��5       �� AcceptsReturn$
 True��6\   ��6/   Z� ��6F   Z� 6q   5      �� 5   
   -   5        $ 	groupBox1��5      $��
Réception��6&   $��10q�69   ���	#FFDDDDDD
���   �$��1��6p   $��0��6�   .��5      �� -   5        $ textBoxReception��5       �� 
IsReadOnly$
 True��6]   ��60   Z� ��6F   Z� 6]   5      �� 5   
    �� Orientation$ 
Horizontal=�6   $��1��6.   $��2��6;   $��Center=�6O   .+�5      �� -   5         ��Name$ buttonEnvoyer��5      $��1��6,   $
��Send��6<   $	��100��6K   $��5q�6W   6b   �� 5      -   5        $ buttonClear��5      $��1��6*   $��Clear��6:   $	��100��6J   $��5q�6V   6a   �� 5      -   5        $ 
buttonTest��5      $��1��6)   $
��Test��69   $	��100��6H   $��5q�6T   6_   5      5!      5"      