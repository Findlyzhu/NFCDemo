package com.ccore.nfcdemo;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.Toast;

import com.ccore.CCoreNFC;
import com.ccore.SKFJni;
import com.ccore.SKFType;

import java.io.IOError;

public class MainActivity extends AppCompatActivity {
    private CCoreNFC mcoreNFC = null;
    private SKFType  mskftype = null;
    private SKFJni   mskfjni  = null;
    private long     ret      = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mcoreNFC = new CCoreNFC(this);
        mskftype = new SKFType();
        mskfjni  = new SKFJni(mcoreNFC);
    }

    @Override
    protected void onResume() {
        super.onResume();
        mcoreNFC.enableDispatch();
    }

    @Override
    protected void onNewIntent(Intent intent) {
        super.onNewIntent(intent);
        mcoreNFC.recvNewTag(intent);
        if(mcoreNFC.recvIsoDep == true){
            showinfo();
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        mcoreNFC.disableDispatch();
    }

    @Override
    protected void onStart() {
        super.onStart();

        //showinfo();
    }

    public void showinfo() {
        char[] applist = new char[1024];
        Integer applen = new Integer(0);
        Integer hDev   = new Integer(0);
        Integer hApp   = new Integer(0);
        Integer hCtn   = new Integer(0);
        Integer len   = new Integer(0);
        byte[] pdata   = {0x01,0x02,0x03,0x04};
        byte[] puk = new byte[512];
        byte[] pcert = new byte[2048];
        SKFType.ENVELOPEDKEYBLOB ecckey = mskftype.new ENVELOPEDKEYBLOB();
        SKFType.ECCPUBLICKEYBLOB pubkey = mskftype.new ECCPUBLICKEYBLOB();
        SKFType.ECCSIGNATUREBLOB signdata = mskftype.new ECCSIGNATUREBLOB();
        SKFType.ECCCIPHERBLOB ECCCipherBlob = mskftype.new ECCCIPHERBLOB();
        SKFType.DEVINFO devinfo = mskftype.new DEVINFO();
        try {
            ret = mskfjni.SKF_ConnectDev("",hDev);
            if(ret != SKFType.SAR_OK){
                Toast.makeText(this,"连接设备失败",Toast.LENGTH_SHORT).show();
                return;
            }
            ret = mskfjni.SKF_OpenApplication(hDev,"test_appsm2",hApp);
            if(ret != SKFType.SAR_OK){
                Toast.makeText(this,"打开应用失败",Toast.LENGTH_SHORT).show();
                return;
            }
            ret = mskfjni.SKF_OpenContainer(hApp,"test_ctnsm2",hCtn);
            if(ret != SKFType.SAR_OK){
                Toast.makeText(this,"打开容器失败",Toast.LENGTH_SHORT).show();
                return;
            }
            ret = mskfjni.SKF_ECCSignData(hCtn,pdata,pdata.length,signdata);
            if(ret != SKFType.SAR_OK){
                Toast.makeText(this,"签名失败",Toast.LENGTH_SHORT).show();
                return;
            }
            len = 512;
            ret = mskfjni.SKF_ExportPublicKey(hCtn,true,puk,len);
            if(ret != SKFType.SAR_OK){
                Toast.makeText(this,"获取公钥失败",Toast.LENGTH_SHORT).show();
                return;
            }
            pubkey.set_pubkey(puk);
            ret = mskfjni.SKF_ECCVerify(hDev,pubkey,pdata,pdata.length,signdata);
            if(ret != SKFType.SAR_OK){
                Toast.makeText(this,"验签失败",Toast.LENGTH_SHORT).show();
                return;
            }
            ret = mskfjni.SKF_ExportCertificate(hCtn,false,pcert,len);
            if(ret != SKFType.SAR_OK){
                Toast.makeText(this,"获取证书失败",Toast.LENGTH_SHORT).show();
                return;
            }
            ret = mskfjni.SKF_GetDevInfo(hDev,devinfo);
            if(ret != SKFType.SAR_OK){
                Toast.makeText(this,"获取设备信息失败",Toast.LENGTH_SHORT).show();
                return;
            }
            mskfjni.SKF_DisConnect(hDev);
            Intent i= new Intent(MainActivity.this,InfoActivity.class);
            i.putExtra("生产厂商",devinfo.Manufacturer);
            i.putExtra("产品SN号",devinfo.SerialNumber);
            startActivity(i);
        } catch (IOError e)
        {
            Toast.makeText(this,"通讯异常请重新放入",Toast.LENGTH_SHORT).show();
            return;
        }
        return;
    }
}
