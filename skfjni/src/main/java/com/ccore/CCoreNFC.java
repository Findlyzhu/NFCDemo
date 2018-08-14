package com.ccore;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.nfc.NfcAdapter;
import android.nfc.Tag;
import android.nfc.tech.IsoDep;
import android.util.Log;

import java.io.IOException;

/**
 * ━━━━━━神兽出没━━━━━━
 * 　　 ┏┓     ┏┓
 * 　　┏┛┻━━━━━┛┻┓
 * 　　┃　　　　　 ┃
 * 　　┃　　━　　　┃
 * 　　┃　┳┛　┗┳  ┃
 * 　　┃　　　　　 ┃
 * 　　┃　　┻　　　┃
 * 　　┃　　　　　 ┃
 * 　　┗━┓　　　┏━┛　Code is far away from bug with the animal protecting
 * 　　　 ┃　　　┃    神兽保佑,代码无bug
 * 　　　　┃　　　┃
 * 　　　　┃　　　┗━━━┓
 * 　　　　┃　　　　　　┣┓
 * 　　　　┃　　　　　　┏┛
 * 　　　　┗┓┓┏━┳┓┏┛
 * 　　　　 ┃┫┫ ┃┫┫
 * 　　　　 ┗┻┛ ┗┻┛
 * <p>
 * ━━━━━━感觉萌萌哒━━━━━━
 *
 * @Author Findly_zhu
 * @DATE 2018/7/16 10:24
 * @Description This Class for NFC Write and Read And SKF Func
 **/
public class CCoreNFC extends Object {
    private final String TAG = "NFC JAVA";
    private Context       context = null;
    private String        nfcAction      = "";
    private NfcAdapter nfcAdapter = null;
    private PendingIntent pendingIntent = null;
    private Tag           tag           = null;
    private IsoDep        currentisodep = null;
    public  boolean       recvIsoDep    = false;
    private IntentFilter[]  intentFilters;
    private byte[] 		    mRecvData;

    /**
     * @Function: 构造函数 初始化NFC资源
     * @param context_new NFC所依托的Activity资源
     */
    public CCoreNFC(final Context context_new){
        super();
        Log.e(TAG,"NFC JAVA IN:");
        context = context_new;
        nfcAdapter = NfcAdapter.getDefaultAdapter(context);
        if(nfcAdapter==null){
            Log.e(TAG, "device is not support NFC!");
            return;
        }

        intentFilters = new IntentFilter[] { new IntentFilter(NfcAdapter.ACTION_TAG_DISCOVERED),};
        //check NFC function is open
        if (!nfcAdapter.isEnabled()){
            Log.e(TAG, "Not open function NFC!");
            return;
        }
        //create PendingIntent, when tag received, get a intent
        pendingIntent=PendingIntent.getActivity(context,0,new Intent(context,context.getClass()).addFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP),0);
    }

    /**
     * @Function: 接收NFC资源的详细信息
     * @param intent 有NFC设备在的时候接收到的INTENT
     */
    public void recvNewTag(Intent intent)
    {
        String[] 	  techList;
        tag = intent.getParcelableExtra(NfcAdapter.EXTRA_TAG);
        recvIsoDep = false;
        techList = tag.getTechList();
        for (String tech:techList){
            if(tech.indexOf("IsoDep")>0){
                recvIsoDep = true;
                Log.v(TAG, "recv new IsoDep tag");
            }
        }
        //get intent nfc action
        nfcAction = intent.getAction();
    }

    /**
     * @Function: 关闭前端发布
    **/
    public void disableDispatch() {
        if(nfcAdapter!=null){
            nfcAdapter.disableForegroundDispatch((Activity) context);//关闭前台发布系统
        }
    }

    /**
     * @Function: 开启前端发布
    **/
    public void enableDispatch() {
        if (nfcAdapter!=null){
            //            mNfcAdapter.enableForegroundDispatch(this,mPendingIntent,null,null);
            nfcAdapter.enableForegroundDispatch((Activity) context,pendingIntent,null,null);//打开前台发布系统，使页面优于其它nfc处理.当检测到一个Tag标签就会执行mPendingItent
        }
    }

    /**
     * @Function: 打开设备
    **/
    public int opendev(){
        try{
            Log.e(TAG,"opendev ...");
            if (tag==null){
                return -1;
            }
            if(recvIsoDep == false)
            {
                return -1;
            }
            if(nfcAdapter.ACTION_TAG_DISCOVERED.equals(nfcAction)){
                currentisodep = IsoDep.get(tag);
                currentisodep.connect();
            }
            Log.e(TAG,"opendev ok");
            return 0;
        }
        catch (IOException e){
            Log.e(TAG, "Ccore Tag is not discovered!");
            e.printStackTrace();
        }
        return -1;
    }

    /**
     * @Function: 关闭设备
    **/
    public int closedev(){
        try{
            Log.e(TAG,"closedev ...");
            currentisodep.close();
            Log.e(TAG,"closedev ok");
            return 0;
        }
        catch (IOException e){
            Log.e(TAG, "Ccore Tag is not discovered!");
            e.printStackTrace();
        }
        return -1;
    }

    /**
     * @Function: 发送数据
     * @param sendData
     * @param sendlen
     * @return
     */
    public int senddata(byte[] sendData,int sendlen){
        if(sendData != null && sendData.length > 4&&sendData.length==sendlen)
        {
            try {
                if (tag==null){
                    return -1;
                }
                if(recvIsoDep == false)
                {
                    return -1;
                }
                String s = DCUtil.bytes2HexStr(sendData);
                Log.e(TAG,"senddata :"+s);
                mRecvData = currentisodep.transceive(sendData);

                if(mRecvData.length>=2)
                {
                    Log.e(TAG,"senddata ok");
                    return 0;
                }
                return -1;
            } catch (IOException e) {
                // TODO Auto-generated catch block
                Log.e(TAG, "Ccore Tag send data error!");
                e.printStackTrace();
                return -1;
            }
        } else {
            return -1;
        }
    }

    /**
     * @Function: 读取长度
    **/
    public int readlen(){
        if (tag==null){
            return -1;
        }
        if(recvIsoDep == false)
        {
            return -1;
        }
        if(mRecvData.length<2){
            return -1;
        }
        return mRecvData.length;
    }

    /**
     * @Function: 读取长度
    **/
    public byte[] readdata(){
        if (tag==null){
            return null;
        }
        if(recvIsoDep == false)
        {
            return null;
        }
        if(mRecvData.length<2){
            return null;
        }
        String r = DCUtil.bytes2HexStr(mRecvData);
        Log.e(TAG,"readdata :"+r);
        return mRecvData;
    }
}