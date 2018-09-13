package com.hcy.soket.socket;

import android.app.Service;
import static android.content.ContentValues.TAG;
import android.content.Intent;
import android.os.IBinder;
import android.os.Process;
import android.support.annotation.Nullable;
import android.util.Log;
import java.util.Timer;
import java.util.TimerTask;

/**
 * Created by 侯程月  2018年09月12日.
 * QQ 437286343
 * 被守护的服务
 */
public class ProcessService extends Service {
    private Integer i = 0;

    @Nullable
    @Override
    public IBinder onBind(Intent pIntent) {
        return null;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        Watcher lWatcher = new Watcher();
        String UID = String.valueOf(Process.myUid());
        Log.e(TAG, "onCreate: UID"+UID);
        lWatcher.creatWatcher(UID);
        lWatcher.connectMonitor();
        Timer timer = new Timer();
//        定时器

        timer.scheduleAtFixedRate(new TimerTask() {
            @Override
            public void run() {
                Log.i(TAG, "run: " + i);
                i++;

            }
        }, 0, 1000 * 1);
    }
}
