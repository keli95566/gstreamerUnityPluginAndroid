
#include "GraphicsInclude.h"
#include "PixelUtil.h"
#include "ImageInfo.h"
#include "RendererHelpers.h"

#include <vector>
#include <memory.h>

using namespace mray;
using namespace video;

struct MultiNetRenderRequest
{
	void* p;
	void* _TextureNativePtr;
	int _UnityTextureWidth;
	int _UnityTextureHeight;
	int index;
};
std::vector<MultiNetRenderRequest> __multiNetRequests;

//for GL.IssuePluginEvent
static void __stdcall mray_gst_customPlayerBlitImageNativeEvent(int eventID)
{
	//LogMessage("mray_gst_customPlayerBlitImageNativeEvent()", ELL_INFO);
	for (int i = 0; i < __multiNetRequests.size(); ++i)
	{
		MultiNetRenderRequest r = __multiNetRequests[i];
		if(r.p)
			BlitImage((video::ImageInfo*)r.p, r._TextureNativePtr, r._UnityTextureWidth, r._UnityTextureHeight);
	}
	__multiNetRequests.clear();
}

extern "C" UNITY_INTERFACE_EXPORT UnityRenderNative mray_gst_BlitImageNativeGLCall(video::ImageInfo* p, void* _TextureNativePtr, int _UnityTextureWidth, int _UnityTextureHeight,int index)
{
	//LogMessage("mray_gst_BlitImageNativeGLCall()", ELL_INFO);
	MultiNetRenderRequest r;
	r.p = p;
	r._TextureNativePtr = _TextureNativePtr;
	r._UnityTextureWidth = _UnityTextureWidth;
	r._UnityTextureHeight = _UnityTextureHeight;
	r.index = index;
	__multiNetRequests.push_back(r);
	return mray_gst_customPlayerBlitImageNativeEvent;
}


struct ImageBlitData
{
	video::ImageInfo* ifo;
	void* _TextureNativePtr;
};

std::vector<ImageBlitData> _data;

extern "C" UNITY_INTERFACE_EXPORT void mray_ImageInfoBlitImageDataInfo(video::ImageInfo* ifo, void* _TextureNativePtr)
{

	if (ifo == NULL || !_TextureNativePtr)
		return;

	if (ifo)
	{
		BlitImage(ifo, _TextureNativePtr, ifo->Size.x, ifo->Size.y);
	}

}
static void  __stdcall mray_gst_ImageInfoBlitImageNativeEvent(int eventID)
{
	if (_data.size() == 0)
		return;
	for (int i = 0; i < _data.size(); ++i)
	{
		ImageBlitData& r = _data[i];
		mray_ImageInfoBlitImageDataInfo(r.ifo, r._TextureNativePtr);
	}
	_data.clear();
}
extern "C" UNITY_INTERFACE_EXPORT UnityRenderNative mray_gst_ImageInfoBlitImageNativeGLCall(video::ImageInfo* ifo, void* _TextureNativePtr)
{
	//LogMessage("mray_gst_ImageInfoBlitImageNativeGLCall()", ELL_INFO);
	ImageBlitData r;
	r.ifo = ifo;
	r._TextureNativePtr = _TextureNativePtr;
	_data.push_back(r);
	return mray_gst_ImageInfoBlitImageNativeEvent;
}

void g_SetPluginName(const char* name);
extern "C" UNITY_INTERFACE_EXPORT  void mray_SetDebugFunction(FuncPtr f);
extern "C" UNITY_INTERFACE_EXPORT void mray_Renderer_SetDebugFunction(FuncPtr f)
{
	g_SetPluginName("Renderer");
	mray_SetDebugFunction(f);
}