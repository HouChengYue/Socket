package com.hcy.soket.socket;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;


/**
 * ndk 双线程守护核心服务 Demo
 * java socket 步骤
 * 1、创建 ServerSocket 对象并绑定监听
 * 2、通过accept()方法监听客户端的请求
 * 3、建立连接后，通过载入输入输流读取客户端发送的请求信息
 * 4、通过输出流向客户端发送请求信息
 * 5.关闭相关资源
 * <p>
 * ServerSocket lServerSocket=new ServerSocket(5209);
 * lServerSocket=server.accpt();
 * BufferedReader in=new BufferedReader(new InputStreamReader(socket.getInputStream()));
 * line=br.readLine();
 * lServerSocket.close();
 * server.close;
 * //客户端
 * Socket lSocket=new Socket("192.168.1.115",5209);
 * 获取输入流，并获取服务端的响应信息
 * BufferedReader in=new BufferedReader(new InputStreamReader(lSocket.getInputStream()));
 * 关闭Scoket
 * lSocket.close();
 *
 *
 * Linux
 *第一步 等待连接
 * 第二步 读取消息
 *
 *
 *
 *adb shell
 * adb kill -server
 * adb start -server
 * ps
 * kill -9  &pid
 */
public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Intent lIntent=new Intent(this,ProcessService.class);
        startService(lIntent);
    }


}
