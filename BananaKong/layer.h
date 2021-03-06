/*!
 * \file layer.h
 * \date 2015/05/29 19:12
 *
 * \author Lincifer
 * Contact: linlihao159@gmail.com
 *
 * \brief 该头文件包含Layer类的声明
 *
 *Layer类不负责具体的绘制和交互
 *是所有其他图层类的基类
 *高级别的Layer覆盖在低级别的上
 *
*/

#ifndef CLASS_LAYER_H

#define CLASS_LAYER_H

#include <windows.h>
#include "commom.h"

class Layer
{
public:
	//构造函数,通过初始可见性和级别构造图层
	Layer(bool visible,int level);

	//外部接口,确认是否显示
	bool isVisible();

	//该接口用于修改图层可见性
	void SetVisible(bool visible);

	//该接口用于修改图层显示级别
	void SetLevel(int level);

	//纯虚函数,负责图层的绘制刷新,具体实现依赖于派生类
	virtual void Draw(HDC hdc,RECT rect)=0;

	//纯虚函数,用于图层对消息的响应,返回true表示消息响应截止,返回false表示无响应或继续响应
	//参数与主函数中的WndProc()以及Container中的DispatchMSG()保持一致
	virtual bool Response(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)=0;
	
	//纯虚函数,用于使类对象状态更新到下一状态(由外部按时触发)
	virtual void GetNext()=0;

	//用于比较图层优先级的函数
	//由于Layer是抽象类,所以传入派生类指针进行比较
	friend bool LayerCmp(Layer * a,Layer * b);

	//纯虚函数,执行图层析构时的资源释放
	virtual ~Layer();
private:
	//表示图层的可见性,值为false时不再进行绘制,直到其值为true
	bool m_visible;

	//表示图层显示级别,高级别图层覆盖在低级别图层上方
	int m_level;
};



#endif