# gstreamerUnityPluginAndroid
This repository is forked from: https://github.com/mrayy/mrayGStreamerUnity with the updated steps on how to build the original mrayGstreamerUnity c++ plugins for Unity Android builds.
 
There are in total 3 plugins (.so files) that need to be manually rebuilt for all the plugins to work together. 

1. Build the 1.14.5 [libgstreamer_android.so](https://github.com/keli95566/MRTunnelingPico/blob/main/MRTunnelingPico/Assets/Plugins/Android/libgstreamer_android.so) gstreamer plugin using ```Android.mk``` configuration under ``` \GstreamerUnityAndroidBranch\Plugin\Android\GStreamer ``` (This is the original gstreamer android plugin.)

2. Build the [libGStreamerUnityPlugin.so] (https://github.com/keli95566/MRTunnelingPico/blob/main/MRTunnelingPico/Assets/Plugins/Android/libGStreamerUnityPlugin.so) plugin by creating a custom ```Android.mk``` configuration under ```\GstreamerUnityAndroidBranch_ARM64\Plugin\Android```.
(```libGStreamerUnityPlugin.so``` contains all the core c++ scripts that create and write to shared OpenGL Unity texture pointers, etc. )

3. Build the [libRenderUnityPlugin.so](https://github.com/keli95566/MRTunnelingPico/blob/main/MRTunnelingPico/Assets/Plugins/Android/libRenderUnityPlugin.so) Unity renderer plugin  using the ```Android.mk``` configuration under ```\GstreamerUnityAndroidBranch_ARM64\Plugin\Android\Renderer```. (```libRenderUnityPlugin.so``` is the plugin that implements the [Unity native rendering interfaces](https://docs.unity3d.com/Manual/NativePlugins.html) provided by Unity.

For building the plugins, I used the following NDK/gstreamer versions: 
1. Use NDK r16b
2. Compile Gstreamer 1.14.5, higher versions do not work for some reason.
3. I only tried to build targeting arm64 architecture.

Noticed that only Gstreamer 1.14.5 seems to work correctly, and is only tested on Windows 10.These built plugins seem to work fine for all Unity Editors 2020 + .


All the build you could use the following commands after installing the ndk-build library.
```ndk-build NDK_PROJECT_PATH=. NDK_APPLICATION_MK=Application.mk```
