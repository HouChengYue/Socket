package com.hcy.soket.socket;

/**
 * Created by 侯程月  2018年09月12日.
 * QQ 437286343
 */
public class Watcher {
    static {
        System.loadLibrary("native-lib");
    }
//创建监听
    public native void creatWatcher(String userId);
// 连接服务端
    public native void connectMonitor();
}
