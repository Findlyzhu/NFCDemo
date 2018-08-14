//
// Created by Findly on 2018/7/13.
//

#include <stdlib.h>
#include <malloc.h>
#include "com_ccore_SKFJni.h"
#include "prebuilt/include/SKF.h"
#include <android/log.h>
#include <string.h>
#ifndef CCORENFC_UNTIL_H
#define CCORENFC_UNTIL_H

#define TAG "SKF_JNI"
#ifdef DEBUG_LOG
// 定义info信息
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
// 定义debug信息
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
// 定义error信息
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
#define IF_ERROR_GOTO_END(x) if(x!=0) goto END;
#else
#define LOGI(...)
#define LOGD(...) 
#define LOGE(...)
#define IF_ERROR_GOTO_END(x)
#endif
typedef struct{
    u32     pulMaxRetryCount;
    u32     pulRemainRetryCount;
    BOOL    pbDefaultPin;
}PININFO;
typedef PININFO * PPININFO;

long SetStringValue(JNIEnv*  env,jobject jobj,char *paramchar);
long SetIntegerValue(JNIEnv*  env,jobject jobj,jint paramInt);
long SetDevInfo(JNIEnv* env ,jobject paramObj,PDEVINFO pdevinfo);
long GetSymParam(JNIEnv* env ,jobject paramObj,PBLOCKCIPHERPARAM psysparam);
long SetFileAttribute(JNIEnv* env ,jobject paramObj,PFILEATTRIBUTE pfileattribute);

//long GetRsaPriKey(JNIEnv* env ,jobject paramObj,PRSAPRIVATEKEYBLOB rsaprikey);
//long GetRsaPubKey(JNIEnv* env ,jobject paramObj,PRSAPUBLICKEYBLOB rsapubkey);

long GetRsaPubKey(JNIEnv* env ,jobject paramObj,PRSAPUBLICKEYBLOB rsapubkey);

long SetRsaPubKey(JNIEnv* env ,jobject paramObj,PRSAPUBLICKEYBLOB rsapubkey);
long SetRsaPriKey(JNIEnv* env ,jobject paramObj,PRSAPRIVATEKEYBLOB rsaprikey);

long SetEccPubKey(JNIEnv* env ,jobject paramObj,PECCPUBLICKEYBLOB eccpubkey);
long SetEccSign(JNIEnv* env ,jobject paramObj,PECCSIGNATUREBLOB eccsign);
long SetEccChipher(JNIEnv* env ,jobject paramObj,PECCCIPHERBLOB ecccipher);

long GetEccPubKey(JNIEnv* env ,jobject paramObj,PECCPUBLICKEYBLOB eccpubkey);
long GetEccPriKey(JNIEnv* env ,jobject paramObj,PECCPRIVATEKEYBLOB eccprikey);
long GetEccSign(JNIEnv* env ,jobject paramObj,PECCSIGNATUREBLOB eccsign);
long GetEccChipher(JNIEnv* env ,jobject paramObj,PECCCIPHERBLOB ecccipher);

long GetEccKeyPair(JNIEnv* env ,jobject paramObj,PENVELOPEDKEYBLOB ecckeypair);

jstring CStr2Jstring( JNIEnv* env,const char* str );

char* Jstring2CStr( JNIEnv * env, jstring jstr );

#endif //CCORENFC_UNTIL_H
