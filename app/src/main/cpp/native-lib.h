//
// Created by 侯程月 on 2018/9/12.
//

#ifndef SOCKET_NATIVE_LIB_H
#define SOCKET_NATIVE_LIB_H

#endif //SOCKET_NATIVE_LIB_H

#include <sys/select.h>
#include <unistd.h>
#include <sys/socket.h>
#include <pthread.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/un.h>
#include <errno.h>
#include <stdlib.h>
#include <linux/signal.h>
#include <android/log.h>

#define LOG_TAG "tuch"
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

void child_do_work();
void child_listen_msg();
int chid_crate_channel();