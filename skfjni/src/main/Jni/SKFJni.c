//
// Created by Findly on 2018/7/16.
//

#include "until.h"
#ifndef ANDROID
#define ANDROID
#endif
typedef struct __android_nfc_dev {
	JNIEnv*			env;
    jobject        obj;
} NFC_DEV;
static jobject nfcglobalobj = NULL;
static jclass  nfcglobalcls = NULL;
NFC_DEV nfc_res = {0};
//DEVHANDLE hDev = NULL_PTR;
//HANDLE    hKey = NULL_PTR;
//HAPPLICATION hAppHandle = NULL_PTR;
//HCONTAINER   hContainerHandle = NULL_PTR;
/*
int connect()
{
    JNIEnv *env = nfc_res.env;
    jobject obj = nfc_res.obj;
    int       ret = 0;
	jclass    clazz;
	jmethodID fid;
    clazz = (*env)->GetObjectClass(env,nfcglobalobj);
    LOGE("clazz:%p",clazz);
    //clazz = (*env)->FindClass(env,"com/ccore/nfcjni/NFCJni");//获取该对象的类
    if(clazz == 0) return EIO;
    fid =(*env)->GetMethodID(env,clazz,"opendev","()I");//获取JAVA方法的ID
    LOGE("jmethodID:%p",fid);
    if(fid == 0) return EIO;
    ret = (*env)->CallIntMethod(env,obj,fid);
    if(ret) return ret;
    LOGE("GetJavaClass out");
    return ret;
}

int disconnect(){
    JNIEnv *env = nfc_res.env;
    jobject obj = nfc_res.obj;
	jclass    clazz;
	jmethodID fid;
	int ret = 0;
	//clazz = (*env)->FindClass(env,"com/ccore/nfcjni/NFCJni");//获取该对象的类
	clazz = (*env)->GetObjectClass(env,nfcglobalobj);//获取该对象的类
	LOGE("clazz:%p",clazz);
	if(clazz == 0) return EIO;
	fid =(*env)->GetMethodID(env,clazz,"closedev","()I");//获取JAVA方法的ID
	LOGE("jmethodID:%p",fid);
	if(fid == 0) return EIO;
	//jobject obj = (*env)->NewObject(clazz ,fid);
	ret = (*env)->CallIntMethod(env,obj,fid);
	if(ret) return ret;
    (*env)->DeleteGlobalRef(env,nfcglobalobj);
	return ret;
}
*/
/*
 * 枚举设备
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1EnumDev
		(JNIEnv *env,jobject thiz,jboolean Present,jcharArray NameList){
	unsigned long uiRet = 0;
	LOGE("SKF_EnumDev_JNI----Enter");
	while(TRUE){
		uiRet = SAR_NOTSUPPORTYETERR;
        //Do SomeThing Here
		break;
	}	
err:
    LOGE("SKF_EnumDev_JNI----End,uiRet = 0x%lx",uiRet);	
	return uiRet;		
}

JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1SetJavaClass
		(JNIEnv *env,jobject thiz,jobject jobjcls){
	unsigned long uiRet = 0;
	LOGE("SKF_SetJavaClass_JNI----Enter");
	nfc_res.env = env;
    //LOGE("env:%p",nfc_res.env);
	if(jobjcls){
		nfcglobalobj = (*env)->NewGlobalRef(env,jobjcls);
		nfc_res.obj = nfcglobalobj;
		if(nfcglobalobj == NULL){
		   LOGE("glo obj fail");
		}
		uiRet = V_SetDevRes(&nfc_res);
		if(uiRet) return uiRet; 
	}    
err:
    LOGE("SKF_SetJavaClass_JNI----End,uiRet = 0x%lx",uiRet);
	return uiRet;	
}

/*
 * 连接设备
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ConnectDev
		(JNIEnv *env,jobject thiz,jstring Name,jobject phDev) {
	unsigned long uiRet = 0;
	DEVHANDLE hDev = 0;
    char* szName = (char*)(*env)->GetStringUTFChars(env,Name,JNI_FALSE);
    LOGE("SKF_ConnectDev_JNI----Enter:%s",szName);
	uiRet = SKF_ConnectDev((LPSTR)szName,&hDev);
    if(uiRet) {
        LOGE("SKF_ConnectDev Fail,uiRet = 0x%lx",uiRet);
        return uiRet;
    }
    uiRet = SetIntegerValue(env,phDev,(int)hDev);
    if (uiRet) goto err;
    LOGE("SKF_ConnectDev_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseStringUTFChars(env,Name,szName);
   	return uiRet;
err:
    LOGE("SKF_ConnectDev_JNI----End,uiRet = 0x%lx",uiRet);	
    (*env)->ReleaseStringUTFChars(env,Name,szName);	
    SKF_DisConnectDev((DEVHANDLE)hDev);
	return uiRet;
}

/*
 * 断开设备
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1DisConnect
		(JNIEnv *env,jobject thiz,jint hDev) {
    unsigned long uiRet = 0;
    LOGE("SKF_DisconnectDev_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (DEVHANDLE)hDev){
            uiRet = SAR_DEVICE_REMOVED;
            break;
        }
        uiRet = SKF_DisconnectDev((DEVHANDLE)hDev);
        if(uiRet) {
            LOGE("SKF_DisconnectDev Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
        break;
    }
err:
    LOGE("SKF_DisconnectDev_JNI----End,uiRet = 0x%lx",uiRet);
	return uiRet;
}

/*
 * 获取设备状态
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GetDevState
		(JNIEnv *env,jobject thiz,jstring DevName,jobject pulDevState){
	unsigned long uiRet = 0;
	u32 ulDevState = 0;
    char* szDevName=(char*)(*env)->GetStringUTFChars(env,DevName,JNI_FALSE);	
    LOGE("SKF_GetDevState_JNI----Enter");		
	while(TRUE){
        uiRet = SKF_GetDevState((LPSTR)szDevName,&ulDevState);
        if(uiRet) {
            LOGE("SKF_SetLabel Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //do SomeThing Here
        break;
    }	
    uiRet = SetIntegerValue(env,pulDevState,ulDevState);
    if (uiRet) goto err;		
err:
    LOGE("SKF_GetDevState_JNI----End,uiRet = 0x%lx",uiRet);	
    (*env)->ReleaseStringUTFChars(env,DevName,szDevName);	
	return uiRet;	
}

/*
 * 设置设备标签
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1SetLabel
        (JNIEnv *env,jobject thiz,jint hDev,jstring Label){
    unsigned long uiRet = 0;
    char* szLabel=(char*)(*env)->GetStringUTFChars(env,Label,JNI_FALSE);
    LOGE("SKF_SetLabel_JNI----Enter:%d",hDev);
    while(TRUE){
        if(NULL_PTR == (DEVHANDLE)hDev){
            uiRet = SAR_DEVICE_REMOVED;
            break;
        }
        uiRet = SKF_SetLabel((DEVHANDLE)hDev,szLabel);
        if(uiRet) {
            LOGE("SKF_SetLabel Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //do SomeThing Here
        break;
    }
err:
    LOGE("SKF_SetLabel_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseStringUTFChars(env,Label,szLabel);
    return uiRet;
}

/*
 * 获取设备信息
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GetDevInfo
        (JNIEnv *env,jobject thiz,jint hDev,jobject pInfo){
    unsigned long uiRet = 0;
    LPSTR szNameList = (LPSTR)malloc(1024);
    DEVINFO devinfo = {0};
    LOGE("SKF_GetDevInfo_JNI----START");
    while(TRUE) {
        if(NULL_PTR == (DEVHANDLE)hDev){
            uiRet = SAR_DEVICE_REMOVED;
            break;
        }
        uiRet = SKF_GetDevInfo((DEVHANDLE)hDev,&devinfo);
        if (uiRet) {
            LOGE("SKF_GetDevInfo Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //do SomeThing Here
        break;
    }
    uiRet = SetDevInfo(env,pInfo,&devinfo);
    if(uiRet) goto err;
err:
    LOGE("SKF_GetDevInfo_JNI----return = 0x%lx",uiRet);
    return uiRet;
}

/*
 * 锁定设备
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1LockDev
        (JNIEnv *env,jobject thiz,jint hDev,jint ulTimeOut){
    unsigned long uiRet = 0;
    LOGE("SKF_LockDev_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (DEVHANDLE)hDev){
            uiRet = SAR_DEVICE_REMOVED;
            break;
        }
        uiRet = SKF_LockDev((DEVHANDLE)hDev,ulTimeOut);
        if(uiRet) {
            LOGE("SKF_LockDev Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
        break;
    }
err:
    LOGE("SKF_LockDev_JNI----End,uiRet = 0x%lx",uiRet);
    return uiRet;
}

/*
 * 解锁设备
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1UnlockDev
        (JNIEnv *env,jobject thiz,jint hDev){
    unsigned long uiRet = 0;
    LOGE("SKF_UnlockDev_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (DEVHANDLE)hDev){
            uiRet = SAR_DEVICE_REMOVED;
            break;
        }
        uiRet = SKF_UnlockDev((DEVHANDLE)hDev);
        if(uiRet) {
            LOGE("SKF_UnlockDev Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
        break;
    }
err:
    LOGE("SKF_UnlockDev_JNI----End,uiRet = 0x%lx",uiRet);
    return uiRet;
}

/*
 * 透传数据
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1Transmit
        (JNIEnv *env,jobject thiz,jint hDev,jbyteArray pbCommand,jlong ulCommandLen,jbyteArray pbData,jlong pulDataLen){
			
    unsigned long uiRet = 0;
    LOGE("SKF_Transmit_JNI----Enter");
#if 1
	uiRet = SAR_NOTSUPPORTYETERR;
#else
    while(TRUE){
        if(NULL_PTR == (DEVHANDLE)hDev){
            uiRet = SAR_DEVICE_REMOVED;
            break;
        }
        //uiRet = SKF_Transmit((DEVHANDLE)hDev);
        //if (uiRet) goto err;
        //Do SomeThing Here
        break;
    }
#endif
    LOGE("SKF_Transmit_JNI----End,uiRet = 0x%lx",uiRet);
    return uiRet;
}

/*
 * 改变外部认证密钥
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ChangeDevAuthKey
        (JNIEnv *env,jobject thiz,jint hDev,jbyteArray jpbKeyValue,jint ulKeyLen){
    unsigned long uiRet = 0;
    //将JAVA层传过来的JByteArry对象转换成char*，然后传递给库接口
    jbyte * byteTemp =(*env)->GetByteArrayElements(env,jpbKeyValue,0);	
    LOGE("SKF_ChangeDevAuthKey_JNI----Enter");
    while(TRUE){
        //Do SomeThing Here
        if(NULL_PTR == (DEVHANDLE)hDev){
            uiRet = SAR_DEVICE_REMOVED;
            break;
        }
        uiRet = SKF_ChangeDevAuthKey((DEVHANDLE)hDev,(u8*)byteTemp,(u32)ulKeyLen);
        if (uiRet) goto err;
        break;
    }
err:
    LOGE("SKF_ChangeDevAuthKey_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseByteArrayElements(env,jpbKeyValue,byteTemp,0);
    return uiRet;
}

/*
 * 外部认证
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1DevAuth
        (JNIEnv *env,jobject thiz,jint hDev,jbyteArray jpbAuthData,jint ulLen){
    unsigned long uiRet = 0;
    //将JAVA层传过来的JByteArry对象转换成char*，然后传递给库接口
    jbyte * pbAuthData =(*env)->GetByteArrayElements(env,jpbAuthData,0);	
    LOGE("SKF_DevAuth_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (DEVHANDLE)hDev){
            uiRet = SAR_DEVICE_REMOVED;
            break;
        }
        //LOGE("SKF_DevAuthKey-ulLen = %d,sizeof(pbAuthData) = %d",(u32)ulLen,strlen(pbAuthData));
        //LOGE("pbAuthData:%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n",
        //pbAuthData[0],pbAuthData[1],pbAuthData[2],pbAuthData[3],
        //pbAuthData[4],pbAuthData[5],pbAuthData[6],pbAuthData[7],
        //pbAuthData[8],pbAuthData[9],pbAuthData[10],pbAuthData[11],
        //pbAuthData[12],pbAuthData[13],pbAuthData[14],pbAuthData[15]);
        uiRet = SKF_DevAuth((DEVHANDLE)hDev,(u8*)pbAuthData,(u32)ulLen);
        if (uiRet) goto err;
        //Do SomeThing Here
        break;
    }
err:
    LOGE("SKF_DevAuth_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseByteArrayElements(env,jpbAuthData,pbAuthData,0);	
    return uiRet;
}

/*
 * 修改密码
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ChangePIN
        (JNIEnv *env,jobject thiz,jint hApp,jint ulPinType,jstring OldPin,jstring NewPin,jobject pulRetry){
    unsigned long uiRet = 0;
    u32 ulRetry = 0;	
	char* szOldPin =(char*) (*env)->GetStringUTFChars(env,OldPin,JNI_FALSE);		
	char* szNewPin =(char*) (*env)->GetStringUTFChars(env,NewPin,JNI_FALSE);		
    LOGE("SKF_ChangePIN_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (HAPPLICATION)hApp){
            uiRet = SAR_APPLICATION_NOT_EXISTS;
            break;
        }
        LOGE("SKF_ChangePIN_JNI-szOldPin = %s,szNewPin = %s",szOldPin,szNewPin);
        //通过调用修改密码接口，会返回重试次数，将该重试次数保持在Integer对象中并返回给JAVA曾
        uiRet = SKF_ChangePIN((HAPPLICATION)hApp,ulPinType,szOldPin,szNewPin,&ulRetry);
        if (uiRet) {
            LOGE("SKF_ChangePIN Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
        break;
    }
    uiRet = SetIntegerValue(env,pulRetry,ulRetry);
    if (uiRet) goto err;		
err:
    LOGE("SKF_ChangePIN_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseStringUTFChars(env,OldPin,szOldPin);
    (*env)->ReleaseStringUTFChars(env,NewPin,szOldPin);
    return uiRet;
}

/*
 * 获取PIN码信息
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GetPINInfo
        (JNIEnv *env,jobject thiz,jint hApp,jint ulPINType,jobject pulMaxRetryCount,jobject pulRemainRetryCount,jobject pbDefaultPin){
    unsigned long uiRet = 0;
    PININFO pinInfo;
    memset(&pinInfo,0,sizeof(PININFO));
    LOGE("SKF_GetPINInfo_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (HAPPLICATION)hApp){
            uiRet = SAR_APPLICATION_NOT_EXISTS;
            break;
        }
        uiRet = SKF_GetPINInfo((HAPPLICATION)hApp,(u32)ulPINType,&pinInfo.pulMaxRetryCount,&pinInfo.pulRemainRetryCount,&pinInfo.pbDefaultPin);
        if (uiRet) {
            LOGE("SKF_GetPINInfo Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
        break;
    }
    uiRet = SetIntegerValue(env,pulMaxRetryCount,pinInfo.pulMaxRetryCount);
    if (uiRet) goto err;

    uiRet = SetIntegerValue(env,pulRemainRetryCount,pinInfo.pulRemainRetryCount);
    if (uiRet) goto err;

    uiRet = SetIntegerValue(env,pbDefaultPin,pinInfo.pbDefaultPin);
    if (uiRet) goto err;	
err:
    LOGE("SKF_GetPINInfo_JNI----End,uiRet = 0x%lx",uiRet);
    return uiRet;
}

/*
 * PIN码校验
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1VerifyPIN
        (JNIEnv *env,jobject thiz,jint hApp,jint ulPINType,jstring Pin,jobject pulRetry){
    unsigned long uiRet = 0;
    u32 ulRetry = 0;	
    char* szPin=(char*)(*env)->GetStringUTFChars(env,Pin,JNI_FALSE);
    LOGE("SKF_VerifyPIN_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (HAPPLICATION)hApp){
            uiRet = SAR_APPLICATION_NOT_EXISTS;
            break;
        }
        uiRet = SKF_VerifyPIN((HAPPLICATION)hApp,(u32)ulPINType,szPin,&ulRetry);
        if (uiRet) {
            LOGE("SKF_GetPINInfo Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
        break;
    }
    uiRet = SetIntegerValue(env,pulRetry,ulRetry);
    if (uiRet) goto err;	
err:
    LOGE("SKF_VerifyPIN_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseStringUTFChars(env,Pin,szPin);
    return uiRet;
}

/*
 * 复位PIN码
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1UnblockPIN
        (JNIEnv *env,jobject thiz,jint hApp,jstring AdminPin,jstring NewUserPin,jobject pulRetry){
    unsigned long uiRet = 0;
    u32 ulRetry = 0;	
    char* szAdminPin=(char*)(*env)->GetStringUTFChars(env,AdminPin,JNI_FALSE);
    char* szNewUserPin=(char*)(*env)->GetStringUTFChars(env,NewUserPin,JNI_FALSE);
    LOGE("SKF_UnlockDev_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (HAPPLICATION)hApp){
            uiRet = SAR_APPLICATION_NOT_EXISTS;
            break;
        }
        uiRet = SKF_UnblockPIN((HAPPLICATION)hApp,szAdminPin,szNewUserPin,&ulRetry);
        if (uiRet) {
            LOGE("SKF_UnblockPIN Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
        break;
    }
    uiRet = SetIntegerValue(env,pulRetry,ulRetry);
    if (uiRet) goto err;	
err:
    LOGE("SKF_UnlockDev_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseStringUTFChars(env,AdminPin,szAdminPin);
    (*env)->ReleaseStringUTFChars(env,NewUserPin,szNewUserPin);
    return uiRet;
}

/*
 * 清除安全状态
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ClearSecureState
        (JNIEnv *env,jobject thiz,jint hApp){
    unsigned long uiRet = 0;
    LOGE("SKF_UnlockDev_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (HAPPLICATION)hApp){
            uiRet = SAR_APPLICATION_NOT_EXISTS;
            break;
        }
        uiRet = SKF_ClearSecureState((HAPPLICATION)hApp);
        if (uiRet) {
            LOGE("SKF_ClearSecureState Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
        break;
    }
err:
    LOGE("SKF_UnlockDev_JNI----End,uiRet = 0x%lx",uiRet);
    return uiRet;
}

/*
 * 创建应用
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1CreateApplication
        (JNIEnv *env,jobject thiz,jint hDev,jstring AppName,jstring AdminPin,jint AdminPinRetry,jstring UserPin,jint UserPinRetry,jint CreateFileRights,jobject phApp) {
    unsigned long uiRet = 0;
    HAPPLICATION  hApp = 0;
    char* szAppName=(char*)(*env)->GetStringUTFChars(env,AppName,JNI_FALSE);
    char* szAdminPin=(char*)(*env)->GetStringUTFChars(env,AdminPin,JNI_FALSE);
    char* szUserPin=(char*)(*env)->GetStringUTFChars(env,UserPin,JNI_FALSE);
    LOGE("SKF_CreateApplication_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (DEVHANDLE)hDev){
            uiRet = SAR_DEVICE_REMOVED;
            break;
        }
        uiRet = SKF_CreateApplication((DEVHANDLE)hDev,szAppName,szAdminPin,(u32)AdminPinRetry,szUserPin,(u32)UserPinRetry,(u32)CreateFileRights,&hApp);
        if (uiRet) {
            LOGE("SKF_ClearSecureState Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
        break;
    }
    uiRet = SetIntegerValue(env,phApp,(int)hApp);
    if (uiRet) goto err;
err:
    LOGE("SKF_CreateApplication_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseStringUTFChars(env,AppName,szAppName);
    (*env)->ReleaseStringUTFChars(env,AdminPin,szAdminPin);
    (*env)->ReleaseStringUTFChars(env,UserPin,szUserPin);
    return uiRet;
}

/*
 * 枚举应用
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1EnumApplication
        (JNIEnv *env,jobject thiz,jint hDev,jcharArray szAppName,jobject objAppListSize){
    unsigned long uiRet = 0;
    u32 ulSize = 0;
    char* szAppNameList = NULL;
    jchar *plist= (*env)->GetCharArrayElements(env,szAppName,NULL);
    jsize len = (*env)->GetArrayLength(env,szAppName);
    LOGE("SKF_EnumApplication_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (DEVHANDLE)hDev){
            uiRet = SAR_DEVICE_REMOVED;
            break;
        }
        uiRet = SKF_EnumApplication((DEVHANDLE)hDev,NULL_PTR,&ulSize);
        if (uiRet) {
            LOGE("SKF_EnumApplication Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        if(ulSize > len){
            uiRet = SAR_BUFFER_TOO_SMALL;
            if (uiRet) goto err;
        }		
        szAppNameList = (char*)malloc(ulSize);
        memset(szAppNameList,0,ulSize+1);
        uiRet = SKF_EnumApplication((DEVHANDLE)hDev,szAppNameList,&ulSize);
        if (uiRet) {
            LOGE("SKF_EnumApplication Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
        break;
    }
    //LOGE("SKF_EnumApplication Sucess：%s,ulSize = %d",SKF_EnumApplication,ulSize);
    uiRet = SetIntegerValue(env,objAppListSize,ulSize);
    if (uiRet) goto err;
    if( len > ulSize+1){
        memcpy(plist,szAppNameList,ulSize);
    }
    else
    {
        memcpy(plist,"Buffer is Too SAMLL",strlen("Buffer is Too SAMLL"));
    }
err:
    LOGE("SKF_EnumApplication_JNI----End,uiRet = 0x%lx",uiRet);
    if(szAppNameList)    free(szAppNameList);
    (*env)->ReleaseCharArrayElements(env,szAppName,plist,0);
    return uiRet;
}

/*
 * 删除应用
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1DeleteApplication
        (JNIEnv *env,jobject thiz,jint hDev,jstring AppName){
    unsigned long uiRet = 0;
    char* szAppName=(char*)(*env)->GetStringUTFChars(env,AppName,JNI_FALSE);
    LOGE("SKF_DeleteApplication_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (DEVHANDLE)hDev){
            uiRet = SAR_DEVICE_REMOVED;
            break;
        }
        uiRet = SKF_DeleteApplication((DEVHANDLE)hDev,szAppName);
        if (uiRet) {
            LOGE("SKF_DeleteApplication Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
        break;
    }
err:
    LOGE("SKF_DeleteApplication_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseStringUTFChars(env,AppName,szAppName);
    return uiRet;
}

/*
 * 打开应用
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1OpenApplication
        (JNIEnv *env,jobject thiz,jint hDev,jstring AppName,jobject phApp){
    unsigned long uiRet = 0;
    HAPPLICATION hApp = 0;
    char* szAppName=(char*)(*env)->GetStringUTFChars(env,AppName,JNI_FALSE);
    LOGE("SKF_OpenApplication_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (DEVHANDLE)hDev){
            uiRet = SAR_DEVICE_REMOVED;
            break;
        }
        uiRet = SKF_OpenApplication((DEVHANDLE)hDev,szAppName,&hApp);
        if (uiRet) {
            LOGE("SKF_OpenApplication Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
        break;
    }
    uiRet = SetIntegerValue(env,phApp,(int)hApp);
    if (uiRet) goto err;	
err:
    LOGE("SKF_OpenApplication_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseStringUTFChars(env,AppName,szAppName);
    return uiRet;
}

/*
 * 关闭应用
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1CloseApplication
        (JNIEnv *env,jobject thiz,jint hApp){
    unsigned long uiRet = 0;
    LOGE("SKF_CloseApplication_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (HAPPLICATION)hApp){
            uiRet = SAR_APPLICATION_NOT_EXISTS;
            break;
        }		
        uiRet = SKF_CloseApplication((HAPPLICATION)hApp);
        if (uiRet) {
            LOGE("SKF_CloseApplication Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
        break;
    }
err:
    LOGE("SKF_CloseApplication_JNI----End,uiRet = 0x%lx",uiRet);
    return uiRet;
}

/*
 * 创建文件
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1CreateFile
		(JNIEnv *env,jobject thiz,jint hApp,jstring filename,jint filesize,jint readrights,jint writerights){
	unsigned long uiRet = 0;
	char* szfilename=(char*)(*env)->GetStringUTFChars(env,filename,JNI_FALSE);	
	LOGE("SKF_CreateFile_JNI----Enter");
#if 1
	uiRet = SAR_NOTSUPPORTYETERR;
#else	
	while(TRUE){
		//uiRet = SAR_NOTSUPPORTYETERR;
		if(NULL_PTR == (HAPPLICATION)hApp){
            uiRet = SAR_APPLICATION_NOT_EXISTS;
            break;
        }
        uiRet = SKF_CreateFile((HAPPLICATION)hApp,szfilename,(u32)filesize,(u32)readrights,(u32)writerights);
        if (uiRet) {
            LOGE("SKF_CreateFile Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }		
        //Do SomeThing Here
		break;
	}	
err:
#endif
    LOGE("SKF_CreateFile_JNI----End,uiRet = 0x%lx",uiRet);	
    (*env)->ReleaseStringUTFChars(env,filename,szfilename);	
	return uiRet;		  
}

/*
 * 删除文件
 */ 
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1DeleteFile
		(JNIEnv *env,jobject thiz,jint hApp,jstring filename){
	unsigned long uiRet = 0;
	char* szfilename=(char*)(*env)->GetStringUTFChars(env,filename,JNI_FALSE);		
	LOGE("SKF_DeleteFile_JNI----Enter");
#if 1
	uiRet = SAR_NOTSUPPORTYETERR;
#else		
	while(TRUE){
		//uiRet = SAR_NOTSUPPORTYETERR;
		if(NULL_PTR == (HAPPLICATION)hApp){
            uiRet = SAR_APPLICATION_NOT_EXISTS;
            break;
        }
        uiRet = SKF_DeleteFile((HAPPLICATION)hApp,szfilename);
        if (uiRet) {
            LOGE("SKF_DeleteFile Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
		break;
	}	
err:
#endif
    LOGE("SKF_DeleteFile_JNI----End,uiRet = 0x%lx",uiRet);	
	return uiRet;		  
} 

/*
 * 枚举文件
 */ 
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1EnumFiles
		(JNIEnv *env,jobject thiz,jint hApp,jcharArray filelist,jobject listlen){
	unsigned long uiRet = 0;
    u32 ulSize = 0;
    char* szfilelist = NULL;
    jchar *plist= (*env)->GetCharArrayElements(env,filelist,NULL);	
    jsize len = (*env)->GetArrayLength(env,filelist);		
	LOGE("SKF_EnumFiles_JNI----Enter");
#if 1
	uiRet = SAR_NOTSUPPORTYETERR;
#else		
	while(TRUE){
		//uiRet = SAR_NOTSUPPORTYETERR;
		if(NULL_PTR == (HAPPLICATION)hApp){
            uiRet = SAR_DEVICE_REMOVED;
            break;
        }
        uiRet = SKF_EnumFiles((HAPPLICATION)hApp,NULL_PTR,&ulSize);
        if (uiRet) {
            LOGE("SKF_EnumFiles Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        if(ulSize > len){
            uiRet = SAR_BUFFER_TOO_SMALL;
            if (uiRet) goto err;
        }		
        szfilelist = (char*)malloc(ulSize);
        memset(szfilelist,0,ulSize+1);
        uiRet = SKF_EnumApplication((DEVHANDLE)hApp,szfilelist,&ulSize);
        if (uiRet) {
            LOGE("SKF_EnumApplication Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
		break;
	}	
	uiRet = SetIntegerValue(env,listlen,ulSize);
    if (uiRet) goto err;
    if( len > ulSize+1){
        memcpy(plist,szfilelist,ulSize);
    }
    else
    {
        memcpy(plist,"Buffer is Too SAMLL",strlen("Buffer is Too SAMLL"));
    }
err:
#endif
    if(szfilelist)    free(szfilelist);
    (*env)->ReleaseCharArrayElements(env,filelist,plist,0);
    LOGE("SKF_EnumFiles_JNI----End,uiRet = 0x%lx",uiRet);	
	return uiRet;		  
} 

/*
 * 实现获取文件信息接口
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GetFileInfo
         (JNIEnv *env,jobject thiz,jint hApp,jstring fileName,jobject objFileInfo){
    unsigned long uiRet = 0;

    FILEATTRIBUTE fileAttribute;
    char* file=(char*)(*env)->GetStringUTFChars(env,fileName,JNI_FALSE);
    LOGE("SKF_GetFileInfo_JNI----START");
#if 1
	uiRet = SAR_NOTSUPPORTYETERR;
#else
    memset(&fileAttribute,0,sizeof(FILEATTRIBUTE));
    strcpy(fileAttribute.FileName,file);
    fileAttribute.FileSize = 10;
    fileAttribute.ReadRights = 10;
    fileAttribute.WriteRights = 10;
    while(TRUE){
        if(NULL_PTR == (HAPPLICATION)hApp){
            uiRet = SAR_APPLICATION_NOT_EXISTS;
            goto err;
        }
        uiRet = SKF_GetFileInfo((HAPPLICATION)hApp,file,&fileAttribute);
        if(uiRet) goto err;
        //Do SomeThing Here
        break;
    }
    //设置FileAttribute对象属性
    uiRet = SetFileAttribute(env,objFileInfo,&fileAttribute);
    if(uiRet) goto err; 
err:
#endif	
	LOGE("SKF_GetFileInfo_JNI----End,uiRet = 0x%lx",uiRet); 
    (*env)->ReleaseStringUTFChars(env,fileName,file);
    return uiRet;
 }

/*
 * 读取文件内容
 */ 
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ReadFile
		(JNIEnv *env,jobject thiz,jint hApp,jstring filename,jint offset,jint size,jbyteArray pbData,jobject preadlen){
	unsigned long uiRet = 0;
	u32 readlen = 0;
	jbyte *bData = (*env)->GetByteArrayElements(env,pbData,NULL);	
	char* file=(char*)(*env)->GetStringUTFChars(env,filename,JNI_FALSE);	
	LOGE("SKF_ReadFile_JNI----Enter");
#if 1
	uiRet = SAR_NOTSUPPORTYETERR;
#else	
	while(TRUE){
		uiRet = SAR_NOTSUPPORTYETERR;
		if(NULL_PTR == (HAPPLICATION)hApp){
            uiRet = SAR_APPLICATION_NOT_EXISTS;
            goto err;
        }
		uiRet = SKF_ReadFile((HAPPLICATION)hApp,file,(u32)offset,(u32)size,(u8*)bData,&readlen);
		if(uiRet) goto err;
        //Do SomeThing Here
		break;
	}	
	uiRet = SetIntegerValue(env,preadlen,readlen);
    if (uiRet) goto err;	
err:
#endif
    LOGE("SKF_ReadFile_JNI----End,uiRet = 0x%lx",uiRet);	
    (*env)->ReleaseByteArrayElements(env,pbData,bData,0);	
    (*env)->ReleaseStringUTFChars(env,filename,file);
	return uiRet;		  
} 

/*
 * 写入文件内容
 */ 
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1WriteFile
		(JNIEnv *env,jobject thiz,jint hApp,jstring filename,jint offset,jbyteArray pbData,jint sizelen){
	unsigned long uiRet = 0;
	jbyte *bData = (*env)->GetByteArrayElements(env,pbData,NULL);		
	char* file=(char*)(*env)->GetStringUTFChars(env,filename,JNI_FALSE);		
	LOGE("SKF_WriteFile_JNI----Enter");
#if 1
	uiRet = SAR_NOTSUPPORTYETERR;
#else	
	while(TRUE){
		uiRet = SAR_NOTSUPPORTYETERR;
		if(NULL_PTR == (HAPPLICATION)hApp){
            uiRet = SAR_APPLICATION_NOT_EXISTS;
            goto err;
        }
		uiRet = SKF_WriteFile((HAPPLICATION)hApp,file,(u32)offset,(u8*)bData,(u32)sizelen);
		if(uiRet) goto err;
        //Do SomeThing Here
		break;
	}	
err:
#endif
    LOGE("SKF_WriteFile_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseByteArrayElements(env,pbData,bData,0);		
    (*env)->ReleaseStringUTFChars(env,filename,file);	
	return uiRet;		  
} 

/*
 * 创建容器
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1CreateContainer
        (JNIEnv *env,jobject thiz,jint hApp,jstring ContainerName,jobject phCtn){
    unsigned long uiRet = 0;
    HCONTAINER    hCtn = 0;
    char* szContainerName=(char*)(*env)->GetStringUTFChars(env,ContainerName,JNI_FALSE);
    LOGE("SKF_CreateContainer_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (HAPPLICATION)hApp){
            uiRet = SAR_APPLICATION_NOT_EXISTS;
            break;
        }
        uiRet =  SKF_CreateContainer((HAPPLICATION)hApp,szContainerName,&hCtn);
        if (uiRet) {
            LOGE("SKF_CreateContainer Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
        break;
    }
    uiRet = SetIntegerValue(env,phCtn,(int)hCtn);
    if (uiRet) goto err;	
err:
    LOGE("SKF_CreateContainer_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseStringUTFChars(env,ContainerName,szContainerName);
    return uiRet;
}

/*
 * 删除容器
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1DeleteContainer
        (JNIEnv *env,jobject thiz,jint hApp,jstring ContainerName){
    unsigned long uiRet = 0;
    char* szContainerName=(char*)(*env)->GetStringUTFChars(env,ContainerName,JNI_FALSE);
    LOGE("SKF_DeleteContainer_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (HAPPLICATION)hApp){
            uiRet = SAR_APPLICATION_NOT_EXISTS;
            break;
        }
        uiRet = SKF_DeleteContainer((HAPPLICATION)hApp,szContainerName);
        if (uiRet) {
            LOGE("SKF_DeleteContainer Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
        break;
    }
err:
    LOGE("SKF_DeleteContainer_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseStringUTFChars(env,ContainerName,szContainerName);
    return uiRet;
}

/*
 * 打开容器
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1OpenContainer
        (JNIEnv *env,jobject thiz,jint hApp,jstring ContainerName,jobject phCtn){
    unsigned long uiRet = 0;
    HCONTAINER    hCtn = 0;
    char* szContainerName=(char*)(*env)->GetStringUTFChars(env,ContainerName,JNI_FALSE);
    LOGE("SKF_OpenContainer_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (HAPPLICATION)hApp){
            uiRet = SAR_APPLICATION_NOT_EXISTS;
            break;
        }
        uiRet = SKF_OpenContainer((HAPPLICATION)hApp,szContainerName,&hCtn);
        if (uiRet) {
            LOGE("SKF_OpenContainer Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
        break;
    }
    uiRet = SetIntegerValue(env,phCtn,(int)hCtn);
    if (uiRet) goto err;		
err:
    LOGE("SKF_OpenContainer_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseStringUTFChars(env,ContainerName,szContainerName);
    return uiRet;
}

/*
 * 枚举容器
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1CloseContainer
        (JNIEnv *env,jobject thiz,jint hCtn){
    unsigned long uiRet = 0;
    LOGE("SKF_CloseContainer_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (HCONTAINER)hCtn){
            uiRet = SAR_UNKOWNERR;
            break;
        }
        uiRet = SKF_CloseContainer((HCONTAINER)hCtn);
        if (uiRet) {
            LOGE("SKF_CloseContainer Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
        break;
    }
err:
    LOGE("SKF_CloseContainer_JNI----End,uiRet = 0x%lx",uiRet);
    return uiRet;
}

/*
 * 枚举容器
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1EnumContainer
        (JNIEnv *env,jobject thiz,jint hApp,jcharArray ContainerName,jobject objNameListSize){
    unsigned long uiRet = 0;
    u32 pulSize = 0;	
    char* szContainerList = NULL;	
    jchar *plist = (*env)->GetCharArrayElements(env,ContainerName,NULL);
    jsize len  =   (*env)->GetArrayLength(env,ContainerName);
    LOGE("SKF_EnumContainer_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (HAPPLICATION)hApp){
            uiRet = SAR_APPLICATION_NOT_EXISTS;
            break;
        }
		
        uiRet = SKF_EnumContainer((HAPPLICATION)hApp,NULL,&pulSize);
        if (uiRet) goto err;
        if(pulSize > len){
            uiRet = SAR_BUFFER_TOO_SMALL;
            if (uiRet) goto err;
        }
		szContainerList = (char*)malloc(pulSize);
        memset(szContainerList,0,pulSize+1);		
        uiRet = SKF_EnumContainer((HAPPLICATION)hApp,szContainerList,&pulSize);
        if (uiRet) {
            LOGE("SKF_EnumContainer Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
        break;
    }
    if( len > pulSize+1){
        memcpy(plist,szContainerList,10);
    }
    else
    {
        memcpy(plist,"Buffer is Too SAMLL",strlen("Buffer is Too SAMLL"));
    }	
    uiRet = SetIntegerValue(env,objNameListSize,pulSize);
    if (uiRet) goto err;	
err:
    LOGE("SKF_EnumContainer_JNI----End,uiRet = 0x%lx",uiRet);
    if(szContainerList)    free(szContainerList);	
    (*env)->ReleaseCharArrayElements(env,ContainerName,plist,0);
    return uiRet;
}

/*
 * 获取容器类型
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GetContainerType
        (JNIEnv *env,jobject thiz,jint hCtn,jobject objContainerType){
    unsigned long uiRet = 0;
    u32 ulContainerType = 0;	
    LOGE("SKF_GetContainerType_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (HCONTAINER)hCtn){
            uiRet = SAR_UNKOWNERR;
            break;
        }
        uiRet = SKF_GetContainerType((HCONTAINER)hCtn,&ulContainerType);
        if (uiRet) {
            LOGE("SKF_GetContainerType Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
        break;
    }
    uiRet = SetIntegerValue(env,objContainerType,ulContainerType);
    if (uiRet) goto err;	
err:
    LOGE("SKF_GetContainerType_JNI----End,uiRet = 0x%lx",uiRet);
    return uiRet;
}

/*
 * 导入证书
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ImportCertificate
		(JNIEnv *env,jobject thiz,jint hCtn,jboolean jSignFlag,jbyteArray jbCert,jint jCertLen){
    unsigned long uiRet = 0;
    BOOL bSignFlag = jSignFlag;
    jbyte *pbCert = (*env)->GetByteArrayElements(env,jbCert,NULL);
    LOGE("SKF_ImportRSAKeyPair_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (HCONTAINER)hCtn){
            uiRet = SAR_UNKOWNERR;
            break;
        }
        uiRet = SKF_ImportCertificate((HCONTAINER)hCtn,bSignFlag,(u8*)pbCert,(u32)jCertLen);
        if (uiRet) {
            LOGE("SKF_ImportCertificate Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        break;
    }
err:
    LOGE("SKF_ImportRSAKeyPair_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseByteArrayElements(env,jbCert,pbCert,0);
    return uiRet;
}

/*
 * 导出证书
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ExportCertificate
		(JNIEnv *env,jobject thiz,jint hCtn,jboolean jSignFlag,jbyteArray jbCert,jobject jCertLen){
    unsigned long uiRet = 0;
    u32 cbcert = 2048;
    BOOL bSignFlag = jSignFlag;
    jbyte *pbCert = (*env)->GetByteArrayElements(env,jbCert,NULL);
    LOGE("SKF_ExportCertificate_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (HCONTAINER)hCtn){
            uiRet = SAR_UNKOWNERR;
            break;
        }
        uiRet = SKF_ExportCertificate((HCONTAINER)hCtn,bSignFlag,(u8*)pbCert,&cbcert);
        if (uiRet) {
            LOGE("SKF_ExportCertificate Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        break;
    }
    uiRet = SetIntegerValue(env,jCertLen,cbcert);
    if (uiRet) goto err;	
err:
    LOGE("SKF_ExportCertificate_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseByteArrayElements(env,jbCert,pbCert,0);
    return uiRet;
}

/*
 * 获取随机数
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GenRandom
        (JNIEnv *env,jobject thiz,jint hDev,jbyteArray pbRandomData,jint randomLen){
    unsigned long uiRet = 0;
	LPSTR szNameList = (LPSTR)malloc(1024);
    jbyte * pRandom = (*env)->GetByteArrayElements(env,pbRandomData,NULL);
    LOGE("SKF_GenRandom_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (DEVHANDLE)hDev){
            uiRet = SAR_DEVICE_REMOVED;
            break;
        }
        uiRet = SKF_GenRandom((DEVHANDLE)hDev,(u8*)pRandom,randomLen);
        if(uiRet) {
            LOGE("SKF_GenRandom Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        LOGE("SKF_GenRandom  pRandom = %p,ulSize = %d",pRandom,randomLen);
        //do SomeThing Here
        break;
    }
err:
    LOGE("SKF_GenRandom_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseByteArrayElements(env,pbRandomData,pRandom,0);
    return uiRet;
}

/*
 * 生成外部密钥
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GenExtRSAKey
        (JNIEnv *env,jobject thiz,jint hDev,jint iBitLen,jobject objBlob){
    unsigned long uiRet = 0;
    RSAPRIVATEKEYBLOB keyblob = {0};
    //memset(&keyblob,0,sizeof(PRSAPRIVATEKEYBLOB));
    LOGE("SKF_GenExtRSAKey_JNI----Enter");
#if 1
	uiRet = SAR_NOTSUPPORTYETERR;
#else	
    while(TRUE){
        if(NULL_PTR == (DEVHANDLE)hDev){
            uiRet = SAR_DEVICE_REMOVED;
            break;
        }

        LOGE("SKF_GenExtRSAKey Enter,bitlen = %d",iBitLen);
        uiRet = SKF_GenExtRSAKey((DEVHANDLE)hDev,iBitLen,&keyblob);
		if (uiRet) {
            LOGE("SKF_GenExtRSAKey Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        break;
    }
    //将导出的RSA公玥结构，通过函数填充到对象objBlob的成员变量中去
    uiRet = SetRsaPriKey(env,objBlob,&keyblob);
    if (uiRet) goto err;
err:
#endif
    LOGE("SKF_GenExtRSAKey_JNI----End,uiRet = 0x%lx",uiRet);
    return uiRet;

}

/*
 * 生成RSA密钥对
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GenRSAKeyPair
        (JNIEnv *env,jobject thiz,jint hCtn,jint bitlen,jobject RsaPublickKey){
    unsigned long uiRet = 0;
    RSAPUBLICKEYBLOB keyblob = {0};
    //memset(keyblob,0,sizeof(PRSAPUBLICKEYBLOB));
    LOGE("SKF_GenRSAKeyPair_JNI----Enter");
#if 1
	uiRet = SAR_NOTSUPPORTYETERR;
#else	
    while(TRUE){
        if(NULL_PTR == (HCONTAINER)hCtn){
            uiRet = SAR_UNKOWNERR;
            break;
        }
        uiRet = SKF_GenRSAKeyPair((HCONTAINER)hCtn,bitlen,&keyblob);
		if (uiRet) {
            LOGE("SKF_GenRSAKeyPair Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        break;
    }
    uiRet = SetRsaPubKey(env,RsaPublickKey,&keyblob);
    if (uiRet) goto err;
err:
#endif
    LOGE("SKF_GenRSAKeyPair_JNI----End,uiRet = 0x%lx",uiRet);
    return uiRet;
}

/*
 * 导入密钥对
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ImportRSAKeyPair
        (JNIEnv *env,jobject thiz,jint hCtn,jint jiSymAlgId,jbyteArray jbWrappendKey,jint jiWrappendKeyLen,jbyteArray jbEncryptedData,jint jiEncryptedDataLen){
    unsigned long uiRet = 0;
    jbyte *wrappendKey = (*env)->GetByteArrayElements(env,jbWrappendKey,NULL);
    jbyte *encryptedData = (*env)->GetByteArrayElements(env,jbEncryptedData,NULL);
    LOGE("SKF_ImportRSAKeyPair_JNI----Enter");
#if 1
	uiRet = SAR_NOTSUPPORTYETERR;
#else	
    while(TRUE){
        if(NULL_PTR == (HCONTAINER)hCtn){
            uiRet = SAR_UNKOWNERR;
            break;
        }
        LOGE("SKF_ImportRSAKeyPair Enter,jiEncryptDataLen = %d,encryptedData = %s",jiEncryptedDataLen,encryptedData);
        uiRet = SKF_ImportRSAKeyPair((HCONTAINER)hCtn,(u32)jiSymAlgId,(u8*)wrappendKey,(u32)jiWrappendKeyLen,(u8*)encryptedData,(u32)jiEncryptedDataLen);
		if (uiRet) {
            LOGE("SKF_ImportRSAKeyPair Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        break;
    }
err:
#endif
    (*env)->ReleaseByteArrayElements(env,jbWrappendKey,wrappendKey,0);
    (*env)->ReleaseByteArrayElements(env,jbEncryptedData,encryptedData,0);
    LOGE("SKF_ImportRSAKeyPair_JNI----End,uiRet = 0x%lx",uiRet);
    return uiRet;
}

/*
 * 签名运算
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1RSASignData
        (JNIEnv *env,jobject thiz,jint hCtn,jbyteArray jbData,jint jiDataLen,jbyteArray jbSignature,jobject objIntSignLen){
    unsigned long uiRet = 0;
    u32 ulSignDataLen = 0;	
    jbyte *pbData = (*env)->GetByteArrayElements(env,jbData,NULL);
    jbyte *pbSignature = (*env)->GetByteArrayElements(env,jbSignature,NULL);
    LOGE("SKF_RSASignData_JNI----Enter");
#if 1
	uiRet = SAR_NOTSUPPORTYETERR;
#else	
    while(TRUE){
        if(NULL_PTR == (HCONTAINER)hCtn){
            uiRet = SAR_UNKOWNERR;
            break;
        }
        LOGE("SKF_RSASignData Enter,jiDataLen = %d,pbData = %s",jiDataLen,pbData);
        uiRet = SKF_RSASignData((HCONTAINER)hCtn,(u8*)pbData,(u32)jiDataLen,(u8*)pbSignature,&ulSignDataLen);
		if (uiRet) {		
            LOGE("SKF_RSASignData Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        break;
    }
    uiRet = SetIntegerValue(env,objIntSignLen,(int)ulSignDataLen);
    if (uiRet) goto err;	
err:
#endif
    LOGE("SKF_RSASignData_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseByteArrayElements(env,jbData,pbData,0);
    (*env)->ReleaseByteArrayElements(env,jbSignature,pbSignature,0);
    return uiRet;
}

/*
 * 验签运算
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1RSAVerify
        (JNIEnv *env,jobject thiz,jint hDev,jobject objRSAPublicKeyBlob,jbyteArray jbData,jint jiDataLen,jbyteArray jbSignature,jint jiSignLen){
    unsigned long uiRet = 0;
    RSAPUBLICKEYBLOB rsaPublicKeyBlob;
    memset(&rsaPublicKeyBlob,0,sizeof(RSAPUBLICKEYBLOB));
    jbyte *pbData = (*env)->GetByteArrayElements(env,jbData,NULL);
    jbyte *pbSignature = (*env)->GetByteArrayElements(env,jbSignature,NULL);
    LOGE("SKF_RSAVerify_JNI----Enter");
#if 1
	uiRet = SAR_NOTSUPPORTYETERR;
#else	
    //从相应的对象中，获取各个成员变量的值，并赋值到结构体中；
    uiRet = GetRsaPubKey(env,objRSAPublicKeyBlob,&rsaPublicKeyBlob);
    if (uiRet) goto err;
    while(TRUE){
        if(NULL_PTR == (DEVHANDLE)hDev){
            uiRet = SAR_DEVICE_REMOVED;
            break;
        }
        LOGE("SKF_RSAVerify Enter,jiDataLen = %d,pbData = %s",jiDataLen,pbData);

        uiRet = SKF_RSAVerify((DEVHANDLE)hDev,&rsaPublicKeyBlob,(u8*)pbData,(u32)jiDataLen,(u8*)pbSignature,(u32)jiSignLen);
		if (uiRet) {		
            LOGE("SKF_RSAVerify Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        break;
    }	
err:
#endif
    LOGE("SKF_RSAVerify_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseByteArrayElements(env,jbData,pbData,0);
    (*env)->ReleaseByteArrayElements(env,jbSignature,pbSignature,0);
    return uiRet;
}

/*
 * RSA导出SessionKey
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1RSAExportSessionKey
		(JNIEnv *env,jobject thiz,jint hCtn,jint ulAlgId,jobject jpPubKey,jbyteArray jpbData,jobject jpulDataLen,jobject phSessionKey){
	unsigned long uiRet = 0;
	LOGE("SKF_RSAExportSessionKey_JNI----Enter");
#if 1
	uiRet = SAR_NOTSUPPORTYETERR;
#else
	while(TRUE){
		uiRet = SAR_NOTSUPPORTYETERR;
        //Do SomeThing Here
		break;
	}	
err:
#endif
    LOGE("SKF_RSAExportSessionKey_JNI----End,uiRet = 0x%lx",uiRet);	
	return uiRet;	  
}

/*
 * RSA外部公钥操作
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ExtRSAPubKeyOperation
		(JNIEnv *env,jobject thiz,jint hDev,jobject jRSAPubKeyBlob,jbyteArray jpbInput,jint julInputLen,jbyteArray jpbOutput,jobject jpulOutputLen){
	unsigned long uiRet = 0;
	LOGE("SKF_ExtRSAPubKeyOperation_JNI----Enter");
#if 1
	uiRet = SAR_NOTSUPPORTYETERR;
#else	
	while(TRUE){
		uiRet = SAR_NOTSUPPORTYETERR;
        //Do SomeThing Here
		break;
	}	
err:
#endif
    LOGE("SKF_ExtRSAPubKeyOperation_JNI----End,uiRet = 0x%lx",uiRet);	
	return uiRet;	  	  
}

/*
 * RSA外部私钥操作
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ExtRSAPriKeyOperation
		(JNIEnv *env,jobject thiz,jint hDev,jobject pRSAPriKeyBlob,jbyteArray jpbInput,jint julInputLen,jbyteArray jpbOutput,jobject jpulOutputLen){
	unsigned long uiRet = 0;
	LOGE("SKF_ExtRSAPriKeyOperation_JNI----Enter");
#if 1
	uiRet = SAR_NOTSUPPORTYETERR;
#else	
	while(TRUE){
		uiRet = SAR_NOTSUPPORTYETERR;
        //Do SomeThing Here
		break;
	}	
err:
#endif
    LOGE("SKF_ExtRSAPriKeyOperation_JNI----End,uiRet = 0x%lx",uiRet);	
	return uiRet;		  
}

/*
 * 生成ECC密钥对
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GenECCKeyPair
		(JNIEnv *env,jobject thiz,jint hCtn,jint ulAlgId,jobject EccPublickKey){
	unsigned long uiRet = 0;
    ECCPUBLICKEYBLOB keyblob = {0};
    //memset(keyblob,0,sizeof(PRSAPUBLICKEYBLOB));
	//unsigned char keydata[] = {0x012,0x34,0x45,0x67}; 
	//memcpy(keyblob.XCoordinate,keydata,4);
	//memcpy(keyblob.YCoordinate,keydata,4);	
	//keyblob.BitLen = 10;
    LOGE("SKF_GenECCKeyPair_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (HCONTAINER)hCtn){
            uiRet = SAR_UNKOWNERR;
            break;
        }
        uiRet = SKF_GenECCKeyPair((HCONTAINER)hCtn,(int)ulAlgId,&keyblob);
		if (uiRet) {
            LOGE("SKF_GenECCKeyPair Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        break;
    }	
    uiRet = SetEccPubKey(env,EccPublickKey,&keyblob);
    if (uiRet) goto err;
err:
    LOGE("SKF_GenECCKeyPair_JNI----End,uiRet = 0x%lx",uiRet);	
	return uiRet;		  
}

/*
 * 导入ECC密钥对
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ImportECCKeyPair
		(JNIEnv *env,jobject thiz,jint hCtn,jobject jpBlob){
	unsigned long uiRet = 0;
	ENVELOPEDKEYBLOB keyblob = {0};
    LOGE("SKF_ImportRSAKeyPair_JNI----Enter");
    uiRet = GetEccKeyPair(env,jpBlob,&keyblob);
    if (uiRet) goto err;	
	//LOGE("Version:%d SymAlg:0x%08 bits:%d",keyblob.Version,keyblob.ulSymmAlgID,keyblob.ulBits);
	//LOGE("%02X %02X %02X %02X",keyblob.cbEncryptedPriKey[0],keyblob.cbEncryptedPriKey[2],keyblob.cbEncryptedPriKey[2],keyblob.cbEncryptedPriKey[3]);
    //LOGE("PubKey.BitLen:%d X %02X %02X Y %02X %02X",keyblob.PubKey.BitLen,keyblob.PubKey.XCoordinate[0],keyblob.PubKey.XCoordinate[1],keyblob.PubKey.YCoordinate[0],keyblob.PubKey.YCoordinate[1]);
	//LOGE("ECCCipherBlob.CipherLen:%d X %02X %02X Y %02X %02X",keyblob.ECCCipherBlob.CipherLen,keyblob.ECCCipherBlob.XCoordinate[0],keyblob.ECCCipherBlob.XCoordinate[1],keyblob.ECCCipherBlob.YCoordinate[0],keyblob.ECCCipherBlob.YCoordinate[1]);
	//LOGE("ECCCipherBlob.CipherLen2: hash %02X %02X Cipher %02X",keyblob.ECCCipherBlob.HASH[0],keyblob.ECCCipherBlob.HASH[1],keyblob.ECCCipherBlob.Cipher[0]);
	while(TRUE){
        if(NULL_PTR == (HCONTAINER)hCtn){
            uiRet = SAR_UNKOWNERR;
            break;
        }
				
        uiRet = SKF_ImportECCKeyPair((HCONTAINER)hCtn,&keyblob);
		if (uiRet) {
            LOGE("SKF_ImportECCKeyPair Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        break;
    }
err:
    LOGE("SKF_ImportECCKeyPair_JNI----End,uiRet = 0x%lx",uiRet);	
	return uiRet;		  
}
 
/*
 * ECC签名
 */ 
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ECCSignData
		(JNIEnv *env,jobject thiz,jint hCtn,jbyteArray jpbData,jint julDataLen,jobject jpSignature){
	unsigned long uiRet = 0;
	ECCSIGNATUREBLOB signblob = {0};
    jbyte *pbData = (*env)->GetByteArrayElements(env,jpbData,NULL);
	//unsigned char sign[] = {0x012,0x34,0x45,0x67}; 
	//memcpy(signblob.r,sign,4);
	//memcpy(signblob.s,sign,4);
    LOGE("SKF_ECCSignData_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (HCONTAINER)hCtn){
            uiRet = SAR_UNKOWNERR;
            break;
        }
        LOGE("SKF_RSASignData Enter,jiDataLen = %d,pbData = %s",julDataLen,pbData);
        uiRet = SKF_ECCSignData((HCONTAINER)hCtn,(u8*)pbData,(u32)julDataLen,&signblob);
		if (uiRet) {		
            LOGE("SKF_RSASignData Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        break;
    }
    uiRet = SetEccSign(env,jpSignature,&signblob);
    if (uiRet) goto err;	
err:
    LOGE("SKF_ECCSignData_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseByteArrayElements(env,jpbData,pbData,0);
    return uiRet;	
}

/*
 * ECC验签
 */ 
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ECCVerify
		(JNIEnv *env,jobject thiz,jint hDev,jobject jpECCPubKeyBlob,jbyteArray jpbData,jint julDataLen,jobject jpSignature){
	unsigned long uiRet = 0;
    ECCPUBLICKEYBLOB eccPublicKeyBlob = {0};
	ECCSIGNATUREBLOB eccSignBlob = {0};
    jbyte *pbData = (*env)->GetByteArrayElements(env,jpbData,NULL);
    LOGE("SKF_ECCVerify_JNI----Enter");
    //从相应的对象中，获取各个成员变量的值，并赋值到结构体中；
    uiRet = GetEccPubKey(env,jpECCPubKeyBlob,&eccPublicKeyBlob);
    if (uiRet) goto err;
    uiRet = GetEccSign(env,jpSignature,&eccSignBlob);
    if (uiRet) goto err;	
	//LOGE("PubKey.BitLen:%d X %02X %02X Y %02X %02X",eccPublicKeyBlob.BitLen,eccPublicKeyBlob.XCoordinate[0],eccPublicKeyBlob.XCoordinate[1],eccPublicKeyBlob.YCoordinate[0],eccPublicKeyBlob.YCoordinate[1]);
	//LOGE("Sign: r %02X %02X s %02X %02X",eccSignBlob.r[0],eccSignBlob.r[1],eccSignBlob.s[0],eccSignBlob.s[1]);	
    while(TRUE){
        if(NULL_PTR == (DEVHANDLE)hDev){
            uiRet = SAR_DEVICE_REMOVED;
            break;
        }
        LOGE("SKF_ECCVerify Enter,jiDataLen = %d,pbData = %p",julDataLen,pbData);

        uiRet = SKF_ECCVerify((DEVHANDLE)hDev,&eccPublicKeyBlob,(u8*)pbData,(u32)julDataLen,&eccSignBlob);
		if (uiRet) {		
            LOGE("SKF_ECCVerify Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        break;
    }	
err:
    LOGE("SKF_ECCVerify_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseByteArrayElements(env,jpbData,pbData,0);
    return uiRet;	  
}

/*
 * ECC导出SessionKey
 */ 
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ECCExportSessionKey
		(JNIEnv *env,jobject thiz,jint hCtn,jint ulAlgId,jobject jpPubKey,jobject jpData,jobject phSessionKey){
	unsigned long uiRet = 0;
	HANDLE 		  hKey = 0;
	ECCPUBLICKEYBLOB keyblob = {0};
	ECCCIPHERBLOB    ciphertext = {0};	
    LOGE("SKF_ECCExportSessionKey_JNI----Enter");
    //从相应的对象中，获取各个成员变量的值，并赋值到结构体中；
    uiRet = GetEccPubKey(env,jpPubKey,&keyblob);
    if (uiRet) goto err;
    uiRet = GetEccChipher(env,jpData,&ciphertext);
    if (uiRet) goto err;
	//LOGE("ECCCipherBlob.CipherLen:%d X %02X %02X Y %02X %02X",ciphertext.CipherLen,ciphertext.XCoordinate[0],ciphertext.XCoordinate[1],ciphertext.YCoordinate[0],ciphertext.YCoordinate[1]);
	//LOGE("ECCCipherBlob.CipherLen2: hash %02X %02X Cipher %02X",ciphertext.HASH[0],ciphertext.HASH[1],ciphertext.Cipher[0]);
    while(TRUE){
        if(NULL_PTR == (HCONTAINER)hCtn){
            uiRet = SAR_UNKOWNERR;
            break;
        }
        uiRet = SKF_ECCExportSessionKey((HCONTAINER)hCtn,(u32)ulAlgId,&keyblob,&ciphertext,&hKey);
		if (uiRet) {		
            LOGE("SKF_ECCExportSessionKey Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        break;
    }
    uiRet = SetIntegerValue(env,phSessionKey,(int)hKey);
    if (uiRet) goto err;
err:
    LOGE("SKF_ECCExportSessionKey_JNI----End,uiRet = 0x%lx",uiRet);
    return uiRet;	  
}

/*
 * ECC外部加密
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ExtECCEncrypt
		(JNIEnv *env,jobject thiz,jint hDev,jobject jpECCPubKeyBlob,jbyteArray jpbPlainText,jint ulPlainTextLen,jobject jpCipherText){
	unsigned long uiRet = 0;
	HANDLE 		  hKey = 0;
	ECCPUBLICKEYBLOB keyblob = {0};
	ECCCIPHERBLOB ciphertext = {0};
    jbyte *pbPlainText = (*env)->GetByteArrayElements(env,jpbPlainText,NULL);	
    LOGE("SKF_ExtECCEncrypt_JNI----Enter");
    //从相应的对象中，获取各个成员变量的值，并赋值到结构体中；
    uiRet = GetEccPubKey(env,jpECCPubKeyBlob,&keyblob);
    if (uiRet) goto err;	
    while(TRUE){
        if(NULL_PTR == (DEVHANDLE)hDev){
            uiRet = SAR_UNKOWNERR;
            break;
        }
        uiRet = SKF_ExtECCEncrypt((DEVHANDLE)hDev,&keyblob,(u8*)pbPlainText,(u32)ulPlainTextLen,&ciphertext);
		if (uiRet) {
            LOGE("SKF_ExtECCEncrypt Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        break;
    }
    uiRet = SetEccChipher(env,jpCipherText,&ciphertext);
    if (uiRet) goto err;	
err:
    LOGE("SKF_ExtECCEncrypt_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseByteArrayElements(env,jpbPlainText,pbPlainText,0);	
    return uiRet;	  		  
}

/*
 * ECC外部解密
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ExtECCDecrypt
		(JNIEnv *env,jobject thiz,jint hDev,jobject jpECCPriKeyBlob,jobject jpCipherText,jbyteArray jpbPlainText,jobject jpulPlainTextLen){
	unsigned long uiRet = 0;
	HANDLE 		  hKey = 0;
	u32 		  ulPlainTextLen = 0;
	ECCPRIVATEKEYBLOB keyblob = {0};
	ECCCIPHERBLOB ciphertext = {0};
    jbyte *pbPlainText = (*env)->GetByteArrayElements(env,jpbPlainText,NULL);	
    LOGE("SKF_ExtECCDecrypt_JNI----Enter");
    //从相应的对象中，获取各个成员变量的值，并赋值到结构体中；
    uiRet = GetEccPriKey(env,jpECCPriKeyBlob,&keyblob);
    if (uiRet) goto err;
    uiRet = GetEccChipher(env,jpCipherText,&ciphertext);
    if (uiRet) goto err;		
    while(TRUE){
        if(NULL_PTR == (DEVHANDLE)hDev){
            uiRet = SAR_UNKOWNERR;
            break;
        }
        uiRet = SKF_ExtECCDecrypt((DEVHANDLE)hDev,&keyblob,&ciphertext,(u8*)pbPlainText,&ulPlainTextLen);
		if (uiRet) {
            LOGE("SKF_ExtECCDecrypt Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        break;
    }
    uiRet = SetIntegerValue(env,jpulPlainTextLen,(int)ulPlainTextLen);
    if (uiRet) goto err;
err:
    LOGE("SKF_ExtECCDecrypt_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseByteArrayElements(env,jpbPlainText,pbPlainText,0);	
    return uiRet;		  
}

/*
 * ECC外部签名
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ExtECCSign
		(JNIEnv *env,jobject thiz,jint hDev,jobject jpECCPriKeyBlob,jbyteArray jpbData,jint ulDataLen,jobject jpSignature){
	unsigned long uiRet = 0;
	HANDLE 		  hKey = 0;
	int 		  ulPlainTextLen = 0;
	ECCPRIVATEKEYBLOB keyblob = {0};
	ECCSIGNATUREBLOB signblob = {0};
    jbyte *pbData = (*env)->GetByteArrayElements(env,jpbData,NULL);	
    LOGE("SKF_ExtECCSign_JNI----Enter");
    //从相应的对象中，获取各个成员变量的值，并赋值到结构体中；
    uiRet = GetEccPriKey(env,jpECCPriKeyBlob,&keyblob);
    if (uiRet) goto err;
    while(TRUE){
        if(NULL_PTR == (DEVHANDLE)hDev){
            uiRet = SAR_UNKOWNERR;
            break;
        }
        uiRet = SKF_ExtECCSign((DEVHANDLE)hDev,&keyblob,(u8*)pbData,(u32)ulDataLen,&signblob);
		if (uiRet) {
            LOGE("SKF_ExtECCSign Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        break;
    }
    uiRet = SetEccSign(env,jpSignature,&signblob);
    if (uiRet) goto err;	
err:
    LOGE("SKF_ExtECCSign_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseByteArrayElements(env,jpbData,pbData,0);	
    return uiRet;	  
}

/*
 * ECC外部验签
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ExtECCVerify
		(JNIEnv *env,jobject thiz,jint hDev,jobject jpECCPubKeyBlob,jbyteArray jpbData ,jint julDataLen,jobject jpSignature){
	unsigned long uiRet = 0;
    ECCPUBLICKEYBLOB eccPublicKeyBlob = {0};
	ECCSIGNATUREBLOB eccSignBlob = {0};
    jbyte *pbData = (*env)->GetByteArrayElements(env,jpbData,NULL);
    LOGE("SKF_ExtECCVerify_JNI----Enter");
    //从相应的对象中，获取各个成员变量的值，并赋值到结构体中；
    uiRet = GetEccPubKey(env,jpECCPubKeyBlob,&eccPublicKeyBlob);
    if (uiRet) goto err;
    uiRet = GetEccSign(env,jpSignature,&eccSignBlob);
    if (uiRet) goto err;	
    while(TRUE){
        if(NULL_PTR == (DEVHANDLE)hDev){
            uiRet = SAR_DEVICE_REMOVED;
            break;
        }
        LOGE("SKF_ExtECCVerify Enter,julDataLen = %d,pbData = %s",julDataLen,pbData);
        uiRet = SKF_ExtECCVerify((DEVHANDLE)hDev,&eccPublicKeyBlob,(u8*)pbData,(u32)julDataLen,&eccSignBlob);
		if (uiRet) {		
            LOGE("SKF_ExtECCVerify Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        break;
    }	
err:
    LOGE("SKF_ExtECCVerify_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseByteArrayElements(env,jpbData,pbData,0);
    return uiRet;	  	  
}

/*
 * 生成ECC密钥协商参数
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GenerateAgreementDataWithECC
		(JNIEnv *env,jobject thiz,jint hCtn,jint ulAlgId,jobject jpTempECCPubKeyBlob,jbyteArray jpbID,jint ulIDLen,jobject jphAgreementHandle){
	unsigned long uiRet = 0;
	LOGE("SKF_GenerateAgreementDataWithECC_JNI----Enter");
#if 1
	uiRet = SAR_NOTSUPPORTYETERR;
#else	
	while(TRUE){
		uiRet = SAR_NOTSUPPORTYETERR;
        //Do SomeThing Here
		break;
	}	
err:
#endif
    LOGE("SKF_GenerateAgreementDataWithECC_JNI----End,uiRet = 0x%lx",uiRet);	
	return uiRet;		  
}

/*
 * 产生密钥协商数据并计算会话密钥
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GenerateAgreementDataAndKeyWithECC
		(JNIEnv *env,jobject thiz,jint hCtn,jint ulAlgId,jobject jpSponsorECCPubKeyBlob,jobject jpSponsorTempECCPubKeyBlob,jobject pTempECCPubKeyBlob,jbyteArray jpbID,jint ulIDLen,jbyteArray jpbSponsorID,jint ulSponsorIDLen,jobject phKeyHandle){
	unsigned long uiRet = 0;
	LOGE("SKF_GenerateAgreementDataAndKeyWithECC_JNI----Enter");
#if 1
	uiRet = SAR_NOTSUPPORTYETERR;
#else	
	while(TRUE){
		uiRet = SAR_NOTSUPPORTYETERR;
        //Do SomeThing Here
		break;
	}	
err:
#endif
    LOGE("SKF_GenerateAgreementDataAndKeyWithECC_JNI----End,uiRet = 0x%lx",uiRet);	
	return uiRet;		  
}

/*
 * 计算会话密钥
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GenerateKeyWithECC
		(JNIEnv *env,jobject thiz,jint hAgreementHandle,jobject jpECCPubKeyBlob,jobject jpTempECCPubKeyBlob,jbyteArray jpbID,jint ulIDLen,jobject phKeyHandle){
	unsigned long uiRet = 0;
	LOGE("SKF_GenerateKeyWithECC_JNI----Enter");
#if 1
	uiRet = SAR_NOTSUPPORTYETERR;
#else	
	while(TRUE){
		uiRet = SAR_NOTSUPPORTYETERR;
        //Do SomeThing Here
		break;
	}	
err:
#endif
    LOGE("SKF_GenerateKeyWithECC_JNI----End,uiRet = 0x%lx",uiRet);	
	return uiRet;		  
}

/*
 * 导出公钥
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ExportPublicKey
		(JNIEnv *env,jobject thiz,jint hCtn,jboolean SignFlag,jbyteArray jpbBlob,jobject pulBlobLen){
	unsigned long uiRet = 0;
	u32 ulBlobLen = 1028;
	BOOL bSignFlag = SignFlag;
	jbyte *pbBlob = (*env)->GetByteArrayElements(env,jpbBlob,NULL);	
	LOGE("SKF_ExportPublicKey_JNI----Enter");
	while(TRUE){
        if(NULL_PTR == (HCONTAINER)hCtn){
           uiRet = SAR_NOTSUPPORTYETERR;
           goto err;
        }
		uiRet = SKF_ExportPublicKey((HCONTAINER)hCtn,bSignFlag,(u8*)pbBlob,&ulBlobLen);
		if(uiRet) goto err;
        //Do SomeThing Here
		break;
	}	
	uiRet = SetIntegerValue(env,pulBlobLen,(int)ulBlobLen);
    if (uiRet) goto err;	
err:
    LOGE("SKF_ExportPublicKey_JNI----End,uiRet = 0x%lx",uiRet);	
	(*env)->ReleaseByteArrayElements(env,jpbBlob,pbBlob,0);	
	return uiRet;		  
}

/*
 * 导入SessionKey
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ImportSessionKey
		(JNIEnv *env,jobject thiz,jint hCtn,jint ulAlgId,jbyteArray jpbWrapedData,jint ulWrapedLen,jobject phKey){
	unsigned long uiRet = 0;
	HANDLE hKey = 0;
	jbyte *pbWrapedData = (*env)->GetByteArrayElements(env,jpbWrapedData,NULL);		
	LOGE("SKF_ImportSessionKey_JNI----Enter");
	while(TRUE){
		if(NULL_PTR == (HCONTAINER)hCtn){
           uiRet = SAR_NOTSUPPORTYETERR;
           goto err;
        }
		uiRet = SKF_ImportSessionKey((HCONTAINER)hCtn,(u32)ulAlgId,(u8*)pbWrapedData,(u32)ulWrapedLen,&hKey);
		if(uiRet) goto err;		
        //Do SomeThing Here
		break;
	}	
	uiRet = SetIntegerValue(env,phKey,(int)hKey);
    if (uiRet) goto err;		
err:
    LOGE("SKF_ImportSessionKey_JNI----End,uiRet = 0x%lx",uiRet);	
	(*env)->ReleaseByteArrayElements(env,jpbWrapedData,pbWrapedData,0);		
	return uiRet;		  
}
  
/*
 * 设置密钥
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1SetSymmKey
		(JNIEnv *env,jobject thiz,jint hDev,jbyteArray pbKey,jint ulAlgID,jobject phKey) {

	unsigned long uiRet = 0;
	HANDLE hkey = 0;
	jbyte *bKey = (*env)->GetByteArrayElements(env,pbKey,NULL);
    LOGE("SKF_SetSymmKey_JNI----START");
    while(TRUE) {
        if(NULL_PTR == (DEVHANDLE)hDev){
           uiRet = SAR_DEVICE_REMOVED;
           goto err;
        }
        uiRet = SKF_SetSymmKey((DEVHANDLE)hDev,(u8*)bKey,(u32)ulAlgID,&hkey);
        if (uiRet) goto err;
        break;
    }
    uiRet = SetIntegerValue(env,phKey,(int)hkey);
    if (uiRet) goto err;	
   	LOGE("SKF_SetSymmKey,hKey Address=%p",hkey);
err:
    LOGE("SKF_SetSymmKey----return:0x%lx",uiRet);
	(*env)->ReleaseByteArrayElements(env,pbKey,bKey,0);	
	return uiRet;
}

/*
 * 对称算法初始化
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1EncryptInit
		(JNIEnv *env,jobject thiz,jint hKey,jobject paramObj) {
	unsigned long uiRet = 0;
	BLOCKCIPHERPARAM encryptParam;
	memset(&encryptParam,0,sizeof(BLOCKCIPHERPARAM));

    LOGE("SKF_EncryptInit_JNI----START:%d",hKey);
	while(TRUE) {
            if(NULL_PTR == (HANDLE)hKey ){
               uiRet = SAR_KEYNOTFOUNTERR;
               goto err;
            }

            uiRet = GetSymParam(env,paramObj,&encryptParam);
            if (uiRet) goto err;

            //LOGE("SKF_EncryptInit----Function Address=%p,hKey Address=%p",SKF_EncryptInit,hKey);
            uiRet = SKF_EncryptInit((HANDLE)hKey,encryptParam);
            if (uiRet) goto err;
            break;
    }
err:
    LOGE("SKF_EncryptInit_JNI----return:0x%lx",uiRet);
	return uiRet;
}

/*
 * 单组对称加密
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1Encrypt
		(JNIEnv *env,jobject thiz,jint hKey,jbyteArray pbData,jint ulDataLen,jbyteArray pbEncryptedData,jobject pulEncryptedLen) {
	unsigned long uiRet = 0;
	u32  outDataLen = 0;
    LOGE("SKF_Encrypt_JNI----START:%d",hKey);
	jbyte *pInData = (*env)->GetByteArrayElements(env,pbData,NULL);
	jbyte *pOutData = (*env)->GetByteArrayElements(env,pbEncryptedData,NULL);
	while(TRUE) {
            if(NULL_PTR == (HANDLE)hKey ){
               uiRet = SAR_KEYNOTFOUNTERR;
               goto err;
            }
            //if(*outDataLen<ulDataLen){
            //   uiRet = SAR_BUFFER_TOO_SMALL;
            //   goto err;
            //}
            //LOGE("Param:%d inlen:%d outlen:%d",hKey,ulDataLen,outDataLen);
            uiRet = SKF_Encrypt((HANDLE)hKey,(u8*)pInData,(u32)ulDataLen,(u8*)pOutData,&outDataLen);
            if (uiRet) goto err;
            break;
    }
	uiRet = SetIntegerValue(env,pulEncryptedLen,(int)outDataLen);
    if (uiRet) goto err;	
err:
	(*env)->ReleaseByteArrayElements(env,pbData,pInData,0);
	(*env)->ReleaseByteArrayElements(env,pbEncryptedData,pOutData,0);
    LOGE("SKF_Encrypt_JNI----return = 0x%lx",uiRet);
	return uiRet;
}

/*
 * 对称加密Update
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1EncryptUpdate
		(JNIEnv *env,jobject thiz,jint hKey,jbyteArray pbData,jint ulDataLen,jbyteArray pbEncryptedData,jobject pulEncryptedLen) {
	unsigned long uiRet = 0;
	u32  outDataLen = 0;	
    LOGE("SKF_EncryptUpdate_JNI----START:%d",hKey);
	jbyte *pInData = (*env)->GetByteArrayElements(env,pbData,NULL);
	jbyte *pOutData = (*env)->GetByteArrayElements(env,pbEncryptedData,NULL);
	while(TRUE) {
            if(NULL_PTR == (HANDLE)hKey ){
               uiRet = SAR_KEYNOTFOUNTERR;
               goto err;
            }

	        uiRet = SKF_EncryptUpdate((HANDLE)hKey,(u8*)pInData,(u32)ulDataLen,(u8*)pOutData,&outDataLen);
            if (uiRet) goto err;
            break;
    }
	uiRet = SetIntegerValue(env,pulEncryptedLen,(int)outDataLen);
    if (uiRet) goto err;	
err:
	(*env)->ReleaseByteArrayElements(env,pbData,pInData,0);
	(*env)->ReleaseByteArrayElements(env,pbEncryptedData,pOutData,0);
    LOGE("SKF_EncryptUpdate_JNI----return = 0x%lx",uiRet);
	return uiRet;
}

/*
 * 对称加密Final
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1EncryptFinal
		(JNIEnv *env,jobject thiz,jint hKey,jbyteArray pbEncryptedData,jobject pulEncryptedLen) {
	unsigned long uiRet = 0;
	u32  outDataLen = 0;	
    LOGE("SKF_EncryptFinal_JNI----START:%d",hKey);
	jbyte *pOutData = (*env)->GetByteArrayElements(env,pbEncryptedData,NULL);
	//jlong *outDataLen = (*env)->GetLongArrayElements(env,pulEncryptedLen,NULL);
    while(TRUE) {
            if(NULL_PTR == (HANDLE)hKey ){
               uiRet = SAR_KEYNOTFOUNTERR;
               goto err;
            }

            uiRet = SKF_EncryptFinal((HANDLE)hKey,(u8*)pOutData,&outDataLen);
            if (uiRet) goto err;
			break;
    }
	uiRet = SetIntegerValue(env,pulEncryptedLen,(int)outDataLen);
    if (uiRet) goto err;		
err:
	(*env)->ReleaseByteArrayElements(env,pbEncryptedData,pOutData,0);
	//(*env)->ReleaseLongArrayElements(env,pulEncryptedLen,outDataLen,0);
    LOGE("SKF_EncryptFinal_JNI----return = 0x%lx",uiRet);
	return uiRet;
}

/*
 * 对称解密初始化
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1DecryptInit
		(JNIEnv *env,jobject thiz,jint hKey,jobject paramObj) {
	unsigned long uiRet = 0;
	BLOCKCIPHERPARAM encryptParam;
	memset(&encryptParam,0,sizeof(BLOCKCIPHERPARAM));

    LOGE("SKF_DecryptInit_JNI----START:%d",hKey);
	while(TRUE) {
            if(NULL_PTR == (HANDLE)hKey ){
               uiRet = SAR_KEYNOTFOUNTERR;
               goto err;
            }

            uiRet = GetSymParam(env,paramObj,&encryptParam);
            if (uiRet) goto err;

            //LOGE("SKF_DecryptInit----Function Address=%p,phKey Address=%p",SKF_EncryptInit,hKey);
            uiRet = SKF_DecryptInit((HANDLE)hKey,encryptParam);
            if (uiRet) goto err;
            break;
    }
err:
    LOGE("SKF_DecryptInit_JNI----return:0x%lx",uiRet);
	return uiRet;
}

/*
 * 单组解密
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1Decrypt
		(JNIEnv *env,jobject thiz,jint hKey,jbyteArray pbData,jint ulDataLen,jbyteArray pbDecryptedData,jobject pulDecryptedLen) {
	unsigned long uiRet = 0;
	u32 outDataLen = 0;
    LOGE("SKF_Decrypt_JNI----START:%d",hKey);
	jbyte *pInData = (*env)->GetByteArrayElements(env,pbData,NULL);
	jbyte *pOutData = (*env)->GetByteArrayElements(env,pbDecryptedData,NULL);
	//jlong *outDataLen = (*env)->GetLongArrayElements(env,pulEncryptedLen,NULL);
	while(TRUE) {
            if(NULL_PTR == (HANDLE)hKey ){
               uiRet = SAR_KEYNOTFOUNTERR;
               goto err;
            }
            uiRet = SKF_Decrypt((HANDLE)hKey,(u8*)pInData,(u32)ulDataLen,(u8*)pOutData,&outDataLen);
            if (uiRet) goto err;
            break;
    }
	uiRet = SetIntegerValue(env,pulDecryptedLen,(int)outDataLen);
    if (uiRet) goto err;		
err:
	(*env)->ReleaseByteArrayElements(env,pbData,pInData,0);
	(*env)->ReleaseByteArrayElements(env,pbDecryptedData,pOutData,0);
    LOGE("SKF_Decrypt_JNI----return = 0x%lx",uiRet);
	return uiRet;
}

/*
 * 对称解密Update
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1DecryptUpdate
		(JNIEnv *env,jobject thiz,jint hKey,jbyteArray pbData,jint ulDataLen,jbyteArray pbDecryptedData,jobject pulDecryptedLen) {
	unsigned long uiRet = 0;
	u32 outDataLen = 0;	
    LOGE("SKF_DecryptUpdate_JNI----Enter");
	jbyte *pInData = (*env)->GetByteArrayElements(env,pbData,NULL);
	jbyte *pOutData = (*env)->GetByteArrayElements(env,pbDecryptedData,NULL);
	//jlong *outDataLen = (*env)->GetLongArrayElements(env,pulEncryptedLen,NULL);
	while(TRUE) {
            if(NULL_PTR == (HANDLE)hKey ){
               uiRet = SAR_KEYNOTFOUNTERR;
               goto err;
            }
            uiRet = SKF_DecryptUpdate((HANDLE)hKey,(u8*)pInData,(u32)ulDataLen,(u8*)pOutData,&outDataLen);
	        if (uiRet) goto err;
            break;
    }
	uiRet = SetIntegerValue(env,pulDecryptedLen,(int)outDataLen);
    if (uiRet) goto err;	
err:
	(*env)->ReleaseByteArrayElements(env,pbData,pInData,0);
	(*env)->ReleaseByteArrayElements(env,pbDecryptedData,pOutData,0);
    LOGE("SKF_DecryptUpdate_JNI----return = 0x%lx",uiRet);
	return uiRet;
}

/*
 * 对称解密Final
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1DecryptFinal
		(JNIEnv *env,jobject thiz,jint hKey,jbyteArray pbDecryptedData,jobject pulDecryptedLen) {
	unsigned long uiRet = 0;
	u32 outDataLen = 0;		
    LOGE("SKF_DecryptFinal_JNI----Enter");
	jbyte *pOutData = (*env)->GetByteArrayElements(env,pbDecryptedData,NULL);
	//jlong *outDataLen = (*env)->GetLongArrayElements(env,pulEncryptedLen,NULL);
	while(TRUE) {
            if(NULL_PTR == (HANDLE)hKey ){
               uiRet = SAR_KEYNOTFOUNTERR;
               goto err;
            }
        	uiRet = SKF_DecryptFinal((HANDLE)hKey,(u8*)pOutData,&outDataLen);
            if (uiRet) goto err;
            break;
    }
	uiRet = SetIntegerValue(env,pulDecryptedLen,(int)outDataLen);
    if (uiRet) goto err;		
err:
	(*env)->ReleaseByteArrayElements(env,pbDecryptedData,pOutData,0);
    LOGE("SKF_DecryptFinal_JNI----return = 0x%lx",uiRet);
	return uiRet;
}

/*
 * HASH初始化
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1DigestInit
		(JNIEnv *env,jobject thiz,jint hDev,jint ulAlgID,jobject jpPubKey,jbyteArray jpucID,jint ulIDLen,jobject phHash){
	unsigned long uiRet = 0;
	HANDLE hHash = 0;
	jbyte *pucID = (*env)->GetByteArrayElements(env,jpucID,NULL);	
	PECCPUBLICKEYBLOB eccPublicKeyBlob = NULL;
	LOGE("SKF_DigestInit_JNI----Enter");
	LOGE("jpPubKey:%p",jpPubKey);
	if(jpPubKey)
	{
		LOGE("Get pubkey:%p",jpPubKey);		
		eccPublicKeyBlob = calloc(1,sizeof(ECCPUBLICKEYBLOB));
		uiRet = GetEccPubKey(env,jpPubKey,eccPublicKeyBlob);
		if (uiRet) goto err;
	}
	while(TRUE){
        if(NULL_PTR == (DEVHANDLE)hDev){
           uiRet = SAR_DEVICE_REMOVED;
           goto err;
        }	
		uiRet = SKF_DigestInit((DEVHANDLE)hDev,(u32)ulAlgID,eccPublicKeyBlob,(u8*)pucID,(u32)ulIDLen,&hHash);
        if (uiRet) goto err;
		//Do SomeThing Here
		break;
	}
    uiRet = SetIntegerValue(env,phHash,(int)hHash);
    if (uiRet) goto err;	
   	LOGE("SKF_DigestInit,hHash Address=%p",hHash);	
err:
    LOGE("SKF_DigestInit_JNI----End,uiRet = 0x%lx",uiRet);	
	if(eccPublicKeyBlob) free(eccPublicKeyBlob);
	(*env)->ReleaseByteArrayElements(env,jpucID,pucID,0);	
	return uiRet;		  
}

/*
 * HASH Update
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1DigestUpdate
		(JNIEnv *env,jobject thiz,jint hHash,jbyteArray jpbData,jint ulDataLen){
	unsigned long uiRet = 0;
	jbyte *pbData = (*env)->GetByteArrayElements(env,jpbData,NULL);	
	LOGE("SKF_DigestUpdate_JNI----Enter");
	while(TRUE){
        if(NULL_PTR == (HANDLE)hHash){
           uiRet = SAR_DEVICE_REMOVED;
           goto err;
        }	
		uiRet = SKF_DigestUpdate((HANDLE)hHash,(u8*)pbData,(u32)ulDataLen);
        if (uiRet) goto err;
		//Do SomeThing Here
		break;
	}
err:
    LOGE("SKF_DigestUpdate_JNI----End,uiRet = 0x%lx",uiRet);	
	(*env)->ReleaseByteArrayElements(env,jpbData,pbData,0);	
	return uiRet;		  
}

/*
 * HASH Final
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1DigestFinal
		(JNIEnv *env,jobject thiz,jint hHash,jbyteArray jpbDigest,jobject pulDigestLen){
	unsigned long uiRet = 0;
	u32 outlen = 0;
    LOGE("SKF_DigestFinal_JNI----Enter");
	jbyte *pOutData = (*env)->GetByteArrayElements(env,jpbDigest,NULL);
	//jlong *outDataLen = (*env)->GetLongArrayElements(env,pulEncryptedLen,NULL);
	while(TRUE) {
            if(NULL_PTR == (HANDLE)hHash ){
               uiRet = SAR_KEYNOTFOUNTERR;
               goto err;
            }
        	uiRet = SKF_DecryptFinal((HANDLE)hHash,(u8*)pOutData,&outlen);
            if (uiRet) goto err;
            break;
    }
	uiRet = SetIntegerValue(env,pulDigestLen,(int)outlen);
    if (uiRet) goto err;	
err:
    LOGE("SKF_DigestFinal_JNI----return = 0x%lx",uiRet);
	(*env)->ReleaseByteArrayElements(env,jpbDigest,pOutData,0);
	return uiRet;		  
}

/*
 * HASH 单组运算
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1Digest
		(JNIEnv *env,jobject thiz,jint hHash,jbyteArray jpbData,jint ulDataLen,jbyteArray jpbDigest,jobject pulDigestLen){
	unsigned long uiRet = 0;
	u32 outlen = 0;
    LOGE("SKF_Decrypt_JNI----START:%d",hHash);
	jbyte *pbData = (*env)->GetByteArrayElements(env,jpbData,NULL);
	jbyte *pbDigest = (*env)->GetByteArrayElements(env,jpbDigest,NULL);
	while(TRUE) {
            if(NULL_PTR == (HANDLE)hHash ){
               uiRet = SAR_KEYNOTFOUNTERR;
               goto err;
            }
            uiRet = SKF_Decrypt((HANDLE)hHash,(u8*)pbData,(ULONG)ulDataLen,(u8*)pbDigest,&outlen);
            if (uiRet) goto err;
            break;
    }
	uiRet = SetIntegerValue(env,pulDigestLen,(int)outlen);
    if (uiRet) goto err;		
err:
	(*env)->ReleaseByteArrayElements(env,jpbData,pbData,0);
	(*env)->ReleaseByteArrayElements(env,jpbDigest,pbDigest,0);
	LOGE("SKF_Decrypt_JNI----return = 0x%lx",uiRet);
	return uiRet;	  
}

/*
 * Mac 初始化
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1MacInit
		(JNIEnv *env,jobject thiz,jint hKey,jobject paramObj,jobject phMac){
	unsigned long uiRet = 0;
	HANDLE		  hMac = 0;
	BLOCKCIPHERPARAM macParam;
	memset(&macParam,0,sizeof(BLOCKCIPHERPARAM));

    LOGE("SKF_MacInit_JNI----START:%d",hKey);
	while(TRUE) {
            if(NULL_PTR == (HANDLE)hKey ){
               uiRet = SAR_KEYNOTFOUNTERR;
               goto err;
            }

            uiRet = GetSymParam(env,paramObj,&macParam);
            if (uiRet) goto err;

            //LOGE("SKF_MacInit----Function Address=%p,phKey Address=%p",SKF_MacInit,hKey);
            uiRet = SKF_MacInit((HANDLE)hKey,&macParam,&hMac);
            if (uiRet) goto err;
            break;
    }
    uiRet = SetIntegerValue(env,phMac,(int)hMac);
    if (uiRet) goto err;	
   	LOGE("SKF_MacInit,hMac Address=%p",hMac);	
err:
    LOGE("SKF_MacInit_JNI----return:0x%lx",uiRet);
	return uiRet;	  
}

/*
 * Mac Update
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1MacUpdate
		(JNIEnv *env,jobject thiz,jint hMac,jbyteArray jpbData,jint ulDataLen){
	unsigned long uiRet = 0;
	LOGE("SKF_MacUpdate_JNI----Enter");
	while(TRUE){
		uiRet = SAR_NOTSUPPORTYETERR;
        //Do SomeThing Here
		break;
	}	
err:
    LOGE("SKF_MacUpdate_JNI----End,uiRet = 0x%lx",uiRet);	
	return uiRet;		  
}

/*
 * Mac Final
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1MacFinal
		(JNIEnv *env,jobject thiz,jint hMac,jbyteArray jpbMac,jobject pulMacLen){
	unsigned long uiRet = 0;
	LOGE("SKF_MacFinal_JNI----Enter");
	while(TRUE){
		uiRet = SAR_NOTSUPPORTYETERR;
        //Do SomeThing Here
		break;
	}	
err:
    LOGE("SKF_MacFinal_JNI----End,uiRet = 0x%lx",uiRet);	
	return uiRet;		  
}

/*
 * Mac单组运算
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1Mac
		(JNIEnv *env,jobject thiz,jint hMac,jbyteArray jpbData,jint ulDataLen,jbyteArray jpbMac,jobject jpulMacLen){
	unsigned long uiRet = 0;
	u32 ulMacLen = 0;
    LOGE("SKF_EMac_JNI----START:%d",hMac);
	jbyte *pbData = (*env)->GetByteArrayElements(env,jpbData,NULL);
	jbyte *pbMac = (*env)->GetByteArrayElements(env,jpbMac,NULL);
    while(TRUE) {
            if(NULL_PTR == (HANDLE)hMac ){
               uiRet = SAR_KEYNOTFOUNTERR;
               goto err;
            }

	        uiRet = SKF_Mac((HANDLE)hMac,(u8*)pbData,(u32)ulDataLen,(u8*)pbMac,&ulMacLen);
            if (uiRet) goto err;
            break;
    }
    uiRet = SetIntegerValue(env,jpulMacLen,(int)ulMacLen);
    if (uiRet) goto err;		
err:
	(*env)->ReleaseByteArrayElements(env,jpbData,pbData,0);
	(*env)->ReleaseByteArrayElements(env,jpbMac,pbMac,0);
    LOGE("SKF_Mac_JNI----return = 0x%lx",uiRet);
	return uiRet; 
}

/*
 * 关闭句柄
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1CloseHandle(
		JNIEnv *env,jobject thiz,int hHandle) {
    unsigned long uiRet = 0;
    LOGE("SKF_CloseHandle_JNI----Enter");
    while(TRUE){
        if(NULL_PTR == (HANDLE)hHandle){
            uiRet = SAR_DEVICE_REMOVED;
            break;
        }
        uiRet = SKF_CloseHandle((HANDLE)hHandle);
        if(uiRet) {
            LOGE("SKF_CloseHandle Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
        break;
    }
err:
    LOGE("SKF_CloseHandle_JNI----End,uiRet = 0x%lx",uiRet);
	return uiRet;
}

JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_V_1SetAppPath(
		JNIEnv *env,jobject thiz, jstring szAppPath) {
	unsigned long uiRet = 0;
    char* appPath=(char*)(*env)->GetStringUTFChars(env,szAppPath,JNI_FALSE);	
    LOGE("SKF_SetAppPath_JNI----Enter");
	while(TRUE){
	    LOGE("V_SetAppPath:%s",appPath);
        uiRet = V_SetAppPath(appPath);
        if(uiRet) {
            LOGE("V_SetAppPath Fail,uiRet = 0x%lx",uiRet);
            goto err;
        }
        //Do SomeThing Here
        break;
    }
err:
    LOGE("SKF_SetAppPath_JNI----End,uiRet = 0x%lx",uiRet);
    (*env)->ReleaseStringUTFChars(env,szAppPath,appPath);	
	return uiRet;
}