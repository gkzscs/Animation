# Animation
使用Qt制作动画，包含多种效果，如表盘、加载圈、电池、链式图片等

# 编译运行方法
1. 使用Qt5及以上版本，打开`Animation.pro`文件；
2. 直接qmake后，构建即可。

# 错误及解决办法
若出现未定义的标识符`Ui::Loading`，可使用如下办法解决：
1. 打开`ui_loading.h`头文件；
2. 将代码中的`Ui_Widget`改成`Ui_Loading`，将`Widget`改成`Loading`；
3. 保存文件，重新编译即可。

修改后的`ui_loading.h`文件内容如下：

```c++
/********************************************************************************
** Form generated from reading UI file 'loading.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADING_H
#define UI_LOADING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Loading
{
public:

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Loading"));
        Widget->resize(800, 600);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Loading", "Loading", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Loading: public Ui_Loading {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADING_H
```
