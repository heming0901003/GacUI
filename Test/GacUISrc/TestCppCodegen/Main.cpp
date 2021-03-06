#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "Source/DemoIncludes.h"
#include <Windows.h>

using namespace vl;
using namespace vl::collections;
using namespace vl::stream;
using namespace vl::reflection::description;
using namespace vl::presentation;
using namespace vl::presentation::controls;
using namespace demo;

namespace demo
{
	class MyViewModel : public Object, public IViewModel
	{
	public:
		list::ObservableList<Ptr<MyTextItem>> textItems;

		Ptr<IValueObservableList> GetTextItems()override
		{
			return textItems.GetWrapper();
		}

		void AddTextItem(Ptr<MyTextItem> item)override
		{
			textItems.Add(item);
		}

		void RemoveTextItem(vint32_t index)override
		{
			textItems.RemoveAt(index);
		}

		void ClearTextItems()override
		{
			textItems.Clear();
		}
	};

	Ptr<IViewModel> CreateViewModel()
	{
		return new MyViewModel;
	}
}

void GuiMain()
{
	{
		FileStream fileStream(L"UI.bin", FileStream::ReadOnly);
		auto resource = GuiResource::LoadPrecompiledBinary(fileStream);
		GetResourceManager()->SetResource(L"Resource", resource, GuiResourceUsage::DataOnly);
	}

	LoadDemoTypes();
	demo::MainWindow window;
	window.ForceCalculateSizeImmediately();
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}

//#define GUI_GRAPHICS_RENDERER_GDI
#define GUI_GRAPHICS_RENDERER_DIRECT2D

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int CmdShow)
{
#ifdef GUI_GRAPHICS_RENDERER_GDI
	int result = SetupWindowsGDIRenderer();
#endif
#ifdef GUI_GRAPHICS_RENDERER_DIRECT2D
	int result = SetupWindowsDirect2DRenderer();
#endif

#if VCZH_CHECK_MEMORY_LEAKS
	_CrtDumpMemoryLeaks();
#endif
	return result;
}