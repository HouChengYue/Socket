#include <jni.h>
#include <string>
#include <unistd.h>
#include "native-lib.h"

int chid_crate_channel();

void child_listen_msg();

int m_child;

const char *PAHT = "/data/data/com.hcy.soket.socket/my.sock";

extern "C" JNIEXPORT jstring
JNICALL
Java_com_hcy_soket_socket_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

void child_do_work() {
// 开启socket 服务端
    if (chid_crate_channel()) {
        child_listen_msg();
    }
}

/**
 * 读取服务端的信息
 *
 */
void child_listen_msg() {
    fd_set rfds;
    while (true) {
        FD_ZERO(&rfds);
        read()

    }
}

/*
 *  创建服务端scoket
 * 跨进程 文件  读写 服务
 *socket()
 * bind()
 */
int chid_crate_channel() {
    int listenid = socket(AF_LOCAL, SOCK_STREAM, 0);
//    addr->内存 区域
    struct sockaddr_un addr;
//    清空该区域内存
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_LOCAL;//和上一个指定的协议必须相同
    strcpy(addr.sun_path, PAHT);//只能通过内存拷贝的方式进行赋值
    int ret2 = bind(listenid, reinterpret_cast<const sockaddr *>(&addr), sizeof(sockaddr_un));
//    ret2<0代表错误
    if (ret2 < 0) {
        LOGE("绑定错误");
        return 0;
    }
    listen(listenid, 5);// socket 和最大客户端数
//    保证宿主进程连接成功
    int connfd = 0;
    while (1) {
//  返回客户端的地址  阻塞式函数
        if (accept(listenid, NULL, NULL) < 0) {
//                连接
            if (errno = EINTR) {
                continue;
            } else {
                LOGE("读取错误！");
                return 0;
            }
        }
        m_child = connfd;
        LOGE("apk父进程连接上了 %d", m_child);
        break;
    }
    return 1;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_hcy_soket_socket_Watcher_creatWatcher(JNIEnv *env, jobject instance, jstring userId_) {
    const char *userId = env->GetStringUTFChars(userId_, 0);
//开双进程
//1. fork 函数 开进程 返回0 开进程失败， =0  子进程，>0开的是父进程
    pid_t pid = fork();
    if (pid < 0) {
//    fork() 失败
    } else if (pid == 0) {
//    开的是子进程   守护进程
        child_do_work();
    } else if (pid > 0) {
//    父进程
    }


    env->ReleaseStringUTFChars(userId_, userId);
}