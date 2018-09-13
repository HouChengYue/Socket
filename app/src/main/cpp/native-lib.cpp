#include <jni.h>
#include <string>
#include <unistd.h>
#include "native-lib.h"

int chid_crate_channel();

void child_listen_msg();

int m_child;
const char *userId;

const char *PAHT = "/data/data/com.hcy.soket.socket/my.sock";


void child_do_work() {
// 开启socket 服务端
    LOGE("开启服务端");
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
    struct timeval timeout = {3, 0};
    while (true) {
//清空内容
        FD_ZERO(&rfds);
        FD_SET(m_child, &rfds);
        int r = select(m_child + 1, &rfds, NULL, NULL, &timeout);
        if (r > 0) {
//            定义一个缓冲区
            char pkg[256] = {0};
//            保证是来自我们需要的apk客户来的
            if (FD_ISSET(m_child, &rfds)) {
                int result = read(m_child, pkg, sizeof(pkg));
//                开启服务
                LOGE("userId %s", userId);
                execlp("am", "am", "satartservice", "--user", userId,
                       "com.hcy.soket.socket/com.hcy.soket.socket.ProccessService", (char *) NULL);
                break;
            }
        }
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
//    将可能存在的之前的连接清空
    unlink(PAHT);
//    addr->内存 区域
    struct sockaddr_un addr;
//    清空该区域内存
    memset(&addr, 0, sizeof(sockaddr_un));
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
        LOGE("apk父进程绑定成功 %d", m_child);
        break;
    }
    return 1;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_hcy_soket_socket_Watcher_creatWatcher(JNIEnv *env, jobject instance, jstring userId_) {
    userId = env->GetStringUTFChars(userId_, 0);
//开双进程
//1. fork 函数 开进程 返回0 开进程失败， =0  子进程，>0开的是父进程

    pid_t pid = fork();
    if (pid < 0) {
//    fork() 失败
        LOGE("fork 失败 ");
    } else if (pid == 0) {
//    开的是子进程   守护进程
        LOGE("fork守护子线程开启 ");
        child_do_work();
    } else if (pid > 0) {
        LOGE("fork 进入到父线程 ");
//    父进程
    }
    env->ReleaseStringUTFChars(userId_, userId);
}extern "C"
JNIEXPORT void JNICALL
Java_com_hcy_soket_socket_Watcher_connectMonitor(JNIEnv *env, jobject instance) {
//    客户端进程
    int socked;
    struct sockaddr_un addr;
    while (true) {
        LOGE("父进程开始连接");
        socked = socket(AF_LOCAL, SOCK_STREAM, 0);
        if (socked < 0) {
            LOGE("连接失败");
            return;
        }
//        和上面部分一样
        memset(&addr, 0, sizeof(sockaddr_un));
        addr.sun_family = AF_LOCAL;
        strcpy(addr.sun_path, PAHT);
//开始连接
        if (connect(socked, reinterpret_cast<const sockaddr *>(&addr), sizeof(sockaddr_un))) {
//            连接失败，重新连接
            LOGE("连接失败");
            close(socked);
//            休眠一秒 再来尝试一次连接直到保证成功
            sleep(1);
            continue;
        }
        LOGE("连接成功！");
        break;
    }

}