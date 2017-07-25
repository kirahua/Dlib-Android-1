package com.orange.opencv;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import org.opencv.android.Utils;
import org.opencv.core.CvType;
import org.opencv.core.Mat;

public class MainActivity extends AppCompatActivity {

    String TAG = "MainActivity";

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = (TextView) findViewById(R.id.sample_text);
        ImageView iv = (ImageView) findViewById(R.id.iv);
        long start = System.currentTimeMillis();

        Bitmap bitmap = BitmapFactory.decodeResource(this.getResources(), R.drawable.lena);
        Mat mat = new Mat(bitmap.getWidth(), bitmap.getHeight(), CvType.CV_8UC1);
        Utils.bitmapToMat(bitmap, mat);
        loadJpeg(mat.nativeObj);
        Utils.matToBitmap(mat, bitmap);
        iv.setImageBitmap(bitmap);

        Log.w(TAG, "SPEND :" + (System.currentTimeMillis() - start));
        tv.setText(stringFromJNI());
    }

    public native String stringFromJNI();

    public native void loadJpeg(long nativeObj);
}
