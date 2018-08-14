//
// Created by Findly on 2018/7/13.
//


#include"until.h"

//将char类型转换成jstring类型
jstring CStr2Jstring( JNIEnv* env,const char* str )
{

    jsize len = strlen(str);
    // 定义java String类 strClass
    jclass strClass = (*env)->FindClass(env, "java/lang/String");
    LOGE("CStr2Jstring Start");
    LOGE("strClass %p",strClass);
    //设置String, 保存语言类型,用于byte数组转换至String时的参数
    jstring encoding = (*env)->NewStringUTF(env, "UTF-8");
    LOGE("encoding %p",encoding);
    // 获取java String类方法String(byte[],String)的构造器,用于将本地byte[]数组转换为一个新String
    jmethodID ctorID = (*env)->GetMethodID(env, strClass, "<init>", "([BLjava/lang/String;)V");
     LOGE("ctorID %p",ctorID);
    // 建立byte数组
    jbyteArray bytes = (*env)->NewByteArray(env, len);
    LOGE("bytes %p",ctorID);
    // 将char* 转换为byte数组
    (*env)->SetByteArrayRegion(env, bytes, 0, len, (jbyte*)str);
    LOGE("SetByteArrayRegion,End");
    //将byte数组转换为java String,并输出
    return (jstring)(*env)->NewObject(env, strClass, ctorID, bytes, encoding);
}

//将jstring类型转换成char类型
char * Jstring2CStr( JNIEnv * env, jstring jstr )
{
    char * rtn = NULL;
    jclass clsstring = (*env)->FindClass(env, "java/lang/String");
    jstring strencode = (*env)->NewStringUTF(env, "GB2312");
    jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr= (jbyteArray)(*env)->CallObjectMethod(env, jstr,mid,strencode);
    jsize alen = (*env)->GetArrayLength(env, barr);
    jbyte * ba = (*env)->GetByteArrayElements(env, barr,JNI_FALSE);
    if(alen > 0)
    {
        rtn = (char*)malloc(alen+1); //new char[alen+1];
        memcpy(rtn,ba,alen);
        rtn[alen]=0;
    }
    (*env)->ReleaseByteArrayElements(env, barr,ba,0);

    return rtn;
}

long SetCharArryField(JNIEnv* env,jobject paramObj,jfieldID jfied,char* pSrcParam,int charlen)
{
    LOGE("SetCharArryField,Begin,pSrcParam = %s",pSrcParam);
    jcharArray tempArry = (*env)->NewCharArray(env,charlen);
    (*env)->SetCharArrayRegion(env,tempArry, 0, charlen, (jchar*)pSrcParam);
    (*env)->SetObjectField(env, paramObj, jfied,tempArry);
	(*env)->DeleteLocalRef(env, tempArry);	
    LOGE("SetCharArryField,End");
    return 0;
}

long SetStringValue(JNIEnv*  env,jobject jobj,char *paramchar)
{
    long uiRet = 0;
    LOGE("SetStringValue----Begin");

    jstring p = CStr2Jstring(env,paramchar);

    jclass jclaz = (*env)->FindClass(env,"java/lang/String");
    if (NULL == jclaz)
    {
        LOGE("FindClass----Fail");
        return SAR_UNKOWNERR;
    }
    jfieldID valueId = (*env)->GetFieldID(env,jclaz, "value", "(Ljava/lang/String)Ljava/lang/String");
    if (NULL == valueId)
    {
        LOGE("GetFiledID failed");
        return SAR_UNKOWNERR;
    }
	(*env)->DeleteLocalRef(env, jclaz);	
    //(*env)->SetStringField(env, jobj,valueId, p);
    LOGE("SetIntegerValue----End");
    return uiRet;
}

long SetIntegerValue(JNIEnv*  env,jobject jobj,jint paramInt)
{
    long uiRet = 0;
    LOGE("SetIntegerValue----Begin");
    jclass jclaz = (*env)->FindClass(env,"java/lang/Integer");
    if (NULL == jclaz)
    {
        LOGE("FindClass----Fail");
        return SAR_UNKOWNERR;
    }
    jfieldID valueId = (*env)->GetFieldID(env,jclaz, "value", "I");
    if (NULL == valueId)
    {
        LOGE("GetFiledID failed");
        return SAR_UNKOWNERR;
    }

    (*env)->SetIntField(env,jobj,valueId, paramInt);
	(*env)->DeleteLocalRef(env, jclaz);
    LOGE("SetIntegerValue----End");
    return uiRet;
}

long SetByteArryField(JNIEnv* env,jobject paramObj,jfieldID jfied,unsigned char* pSrcParam,int bytelen)
{
    LOGE("SetByteArryField,Begin,pSrcParam = %s",pSrcParam);
    jbyteArray tempArry = (*env)->NewByteArray(env,bytelen);
    (*env)->SetByteArrayRegion(env,tempArry, 0, bytelen, (jbyte*)pSrcParam);
    (*env)->SetObjectField(env, paramObj, jfied,tempArry);
	(*env)->DeleteLocalRef(env, tempArry);
    LOGE("SetByteArryField,End");
    return 0;
}

long GetByteArryField(JNIEnv* env,jobject paramObj,jfieldID jfied,unsigned char* pDstParam)
{
	jbyteArray byteattr = (jbyteArray)(*env)->GetObjectField(env,paramObj,jfied);
	jint bytelen = (*env)->GetArrayLength(env,byteattr);
	unsigned char* bBuffer = (unsigned char*)(*env)->GetByteArrayElements(env,byteattr, 0);
	memcpy(pDstParam, (unsigned char*)bBuffer, bytelen);
	(*env)->ReleaseByteArrayElements(env,byteattr,(jbyte *)bBuffer,0);	
	return 0;
}

long SetDevInfo(JNIEnv* env ,jobject paramObj,PDEVINFO pdevinfo)
{
    long uiRet = 0;
    jfieldID fid;
    jstring manufacturer = CStr2Jstring(env,pdevinfo->Manufacturer);
    jstring issuer = CStr2Jstring(env,pdevinfo->Issuer);
    jstring label = CStr2Jstring(env,pdevinfo->Label);
    jstring serialNumber = CStr2Jstring(env,pdevinfo->SerialNumber);
    LOGE("SetDevInfo----Begin");
    if(NULL == env || NULL == paramObj){
        LOGE("SetDevInfo----JNIEnv = Null OR jobj = Null");
        return SAR_UNKOWNERR;
    }
    jclass Class = (*env)->GetObjectClass(env,paramObj);
    LOGE("SetDevInfo----Class:%p",Class);

    fid = (*env)->GetFieldID(env, Class, "Manufacturer", "Ljava/lang/String;");
    LOGE("SetDevInfo----fid:%p",fid);
    (*env)->SetObjectField(env, paramObj, fid,manufacturer);
    fid = (*env)->GetFieldID(env, Class, "Issuer", "Ljava/lang/String;");
    LOGE("SetDevInfo----fid:%p",fid);
    (*env)->SetObjectField(env, paramObj, fid,issuer);
    fid = (*env)->GetFieldID(env, Class, "Label", "Ljava/lang/String;");
    LOGE("SetDevInfo----fid:%p",fid);
    (*env)->SetObjectField(env, paramObj, fid,label);
    fid = (*env)->GetFieldID(env, Class, "SerialNumber", "Ljava/lang/String;");
    LOGE("SetDevInfo----fid:%p",fid);
    (*env)->SetObjectField(env, paramObj, fid,serialNumber);
    LOGE("SetDevinfo---Set Type Int,Begin");
    fid = (*env)->GetFieldID(env, Class, "AlgSymCap", "I");
    LOGE("SetDevInfo----fid:%p",fid);
    (*env)->SetIntField(env, paramObj, fid,pdevinfo->AlgSymCap);
    fid = (*env)->GetFieldID(env, Class, "AlgASymCap", "I");
    LOGE("SetDevInfo----fid:%p",fid);
    (*env)->SetIntField(env, paramObj, fid,pdevinfo->AlgAsymCap);
    fid = (*env)->GetFieldID(env, Class, "AlgHashCap", "I");
    LOGE("SetDevInfo----fid:%p",fid);
    (*env)->SetIntField(env, paramObj, fid,pdevinfo->AlgHashCap);
    fid = (*env)->GetFieldID(env, Class, "DevAuthAlgId", "I");
    LOGE("SetDevInfo----fid:%p",fid);
    (*env)->SetIntField(env, paramObj, fid,pdevinfo->DevAuthAlgId);
    fid = (*env)->GetFieldID(env, Class, "TotalSpace", "I");
    LOGE("SetDevInfo----fid:%p",fid);
    (*env)->SetIntField(env, paramObj, fid,pdevinfo->TotalSpace);
    fid= (*env)->GetFieldID(env, Class, "FreeSpace", "I");
    LOGE("SetDevInfo----fid:%p",fid);
    (*env)->SetIntField(env, paramObj, fid,pdevinfo->FreeSpace);
    fid = (*env)->GetFieldID(env, Class, "MaxEccBufferSize", "I");
    LOGE("SetDevInfo----fid:%p",fid);
    (*env)->SetIntField(env, paramObj, fid,pdevinfo->MaxEccBufferSize);
    fid = (*env)->GetFieldID(env, Class, "MaxBufferSize", "I");
    LOGE("SetDevInfo----fid:%p",fid);
    (*env)->SetIntField(env, paramObj, fid,pdevinfo->MaxBufferSize);

    jmethodID setversion =  (*env)->GetMethodID(env,Class,"set_version","(IBB)V");
    LOGE("SetDevInfo----setversion:%p",setversion);
    (*env)->CallVoidMethod(env,paramObj,setversion,1,(jbyte)(pdevinfo->Version.major),(jbyte)(pdevinfo->Version.minor));
    (*env)->CallVoidMethod(env,paramObj,setversion,2,(jbyte)(pdevinfo->HWVersion.major),(jbyte)(pdevinfo->HWVersion.minor));
    (*env)->CallVoidMethod(env,paramObj,setversion,3,(jbyte)(pdevinfo->FirmwareVersion.major),(jbyte)(pdevinfo->FirmwareVersion.minor));
    LOGE("CallVoidMethod----ok");

    LOGE("SetDevInfo----GetFieldID End");

    (*env)->DeleteLocalRef(env,Class);
    return uiRet;
}

long SetFileAttribute(JNIEnv* env ,jobject paramObj,PFILEATTRIBUTE pfileattribute)
{
    long uiRet = 0;
    jfieldID fid;
    jstring filename = CStr2Jstring(env,pfileattribute->FileName);
    LOGE("SetFileAttribute----Begin");
    if(NULL == env || NULL == paramObj){
        LOGE("SetFileAttribute----JNIEnv = Null OR jobj = Null");
        return SAR_UNKOWNERR;
    }
    jclass Class = (*env)->GetObjectClass(env,paramObj);
    fid = (*env)->GetFieldID(env, Class, "FileSize", "I");
    (*env)->SetIntField(env, paramObj,fid,pfileattribute->FileSize);
    LOGE("SetFileAttribute----fid:%p",fid);
    fid = (*env)->GetFieldID(env, Class, "ReadRights", "I");
    (*env)->SetIntField(env, paramObj,fid,pfileattribute->ReadRights);
    LOGE("SetFileAttribute----fid:%p",fid);
    fid = (*env)->GetFieldID(env, Class, "WriteRights", "I");
    (*env)->SetIntField(env, paramObj,fid,pfileattribute->WriteRights);
    LOGE("SetFileAttribute----fid:%p",fid);
    fid = (*env)->GetFieldID(env, Class, "fileName", "Ljava/lang/String;");
    LOGE("SetFileAttribute----fid:%p",fid);
    (*env)->SetObjectField(env, paramObj, fid,filename);
    LOGE("SetFileAttribute----GetFieldID End");
    (*env)->DeleteLocalRef(env,Class);
    return uiRet;
}

long SetRsaPriKey(JNIEnv* env ,jobject paramObj,PRSAPRIVATEKEYBLOB rsaprikey)
{
    long uiRet = 0;
    jfieldID fid;
    LOGE("GetRsaPubKey----Begin");
    if(NULL == env || NULL == paramObj){
       LOGE("GetRsaPubKey----JNIEnv = Null OR jobj = Null");
       return SAR_UNKOWNERR;
    }
    jclass Class = (*env)->GetObjectClass(env,paramObj);
    fid = (*env)->GetFieldID(env, Class, "AlgoID", "I");
    (*env)->SetIntField(env, paramObj,fid,rsaprikey->AlgoID);
    fid = (*env)->GetFieldID(env, Class, "BitLen", "I");
    (*env)->SetIntField(env, paramObj,fid,rsaprikey->BitLen);
    fid = (*env)->GetFieldID(env, Class, "Modulus", "[B");
	SetByteArryField(env,paramObj,fid,rsaprikey->Modulus,MAX_RSA_MODULUS_LEN);	
    //(*env)->SetObjectField(env, paramObj, fid,rsaprikey->Modulus);
    fid = (*env)->GetFieldID(env, Class, "PubExp", "[B");
	SetByteArryField(env,paramObj,fid,rsaprikey->PublicExponent,MAX_RSA_EXPONENT_LEN);		
    //(*env)->SetObjectField(env, paramObj, fid,rsaprikey->PublicExponent);
    fid = (*env)->GetFieldID(env, Class, "PriExp", "[B");
	SetByteArryField(env,paramObj,fid,rsaprikey->PrivateExponent,MAX_RSA_MODULUS_LEN);	
    //(*env)->SetObjectField(env, paramObj, fid,rsaprikey->PrivateExponent);	
    fid = (*env)->GetFieldID(env, Class, "Prime1", "[B");
	SetByteArryField(env,paramObj,fid,rsaprikey->Prime1,MAX_RSA_MODULUS_LEN/2);		
    //(*env)->SetObjectField(env, paramObj, fid,rsaprikey->Prime1);
    fid = (*env)->GetFieldID(env, Class, "Prime2", "[B");
	SetByteArryField(env,paramObj,fid,rsaprikey->Prime2,MAX_RSA_MODULUS_LEN/2);	
    //(*env)->SetObjectField(env, paramObj, fid,rsaprikey->Prime2);	
    fid = (*env)->GetFieldID(env, Class, "Prime1Exp", "[B");
	SetByteArryField(env,paramObj,fid,rsaprikey->Prime1Exponent,MAX_RSA_MODULUS_LEN/2);		
    //(*env)->SetObjectField(env, paramObj, fid,rsaprikey->Prime1Exponent);
    fid = (*env)->GetFieldID(env, Class, "Prime2Exp", "[B");
	SetByteArryField(env,paramObj,fid,rsaprikey->Prime2Exponent,MAX_RSA_MODULUS_LEN/2);	
    //(*env)->SetObjectField(env, paramObj, fid,rsaprikey->Prime2Exponent);		
    fid = (*env)->GetFieldID(env, Class, "Coef", "[B");
	SetByteArryField(env,paramObj,fid,rsaprikey->Coefficient,MAX_RSA_MODULUS_LEN/2);	
    //(*env)->SetObjectField(env, paramObj, fid,rsaprikey->Coefficient);			
    (*env)->DeleteLocalRef(env,Class);
    return 0;
}

long SetRsaPubKey(JNIEnv* env ,jobject paramObj,PRSAPUBLICKEYBLOB rsapubkey)
{
    long uiRet = 0;
    jfieldID fid;
    LOGE("GetRsaPubKey----Begin");
    if(NULL == env || NULL == paramObj){
        LOGE("GetRsaPubKey----JNIEnv = Null OR jobj = Null");
        return SAR_UNKOWNERR;
    }
    jclass Class = (*env)->GetObjectClass(env,paramObj);
    fid = (*env)->GetFieldID(env, Class, "AlgID", "I");
    (*env)->SetIntField(env, paramObj,fid,rsapubkey->AlgID);
    fid = (*env)->GetFieldID(env, Class, "BitLen", "I");
    (*env)->SetIntField(env, paramObj,fid,rsapubkey->BitLen);
    fid = (*env)->GetFieldID(env, Class, "Modulus", "[B");
	SetByteArryField(env,paramObj,fid,rsapubkey->Modulus,MAX_RSA_MODULUS_LEN);
    //(*env)->SetObjectField(env, paramObj, fid,rsapubkey->Modulus);
    fid = (*env)->GetFieldID(env, Class, "PubExp", "[B");
	SetByteArryField(env,paramObj,fid,rsapubkey->PublicExponent,MAX_RSA_MODULUS_LEN);	
    //(*env)->SetObjectField(env, paramObj, fid,rsapubkey->PublicExponent);
    (*env)->DeleteLocalRef(env,Class);
    return 0;
}

long SetEccPubKey(JNIEnv* env ,jobject paramObj,PECCPUBLICKEYBLOB eccpubkey)
{
	long uiRet = 0;
    jfieldID fid;
    LOGE("GetEccPubKey----Begin");
    if(NULL == env || NULL == paramObj){
        LOGE("GetEccPubKey----JNIEnv = Null OR jobj = Null");
        return SAR_UNKOWNERR;
    }
	LOGE("eccpubkey->BitLen:%d eccpubkey->XCoordinate:%p %02X %02X %02X %02X",eccpubkey->BitLen,eccpubkey->XCoordinate,eccpubkey->XCoordinate[0],eccpubkey->XCoordinate[1],eccpubkey->XCoordinate[2],eccpubkey->XCoordinate[3]);	
    jclass Class = (*env)->GetObjectClass(env,paramObj);
	LOGE("Class:%p",Class);		
    fid = (*env)->GetFieldID(env, Class, "BitLen", "I");
	LOGE("fid:%p",fid);
    (*env)->SetIntField(env, paramObj,fid,eccpubkey->BitLen);
    fid = (*env)->GetFieldID(env, Class, "XCoordinate", "[B");
	LOGE("fid:%p",fid);
	SetByteArryField(env,paramObj,fid,eccpubkey->XCoordinate,ECC_MAX_XCOORDINATE_BITS_LEN/8);
    //(*env)->SetObjectField(env, paramObj, fid,eccpubkey->XCoordinate);
    fid = (*env)->GetFieldID(env, Class, "YCoordinate", "[B");
	LOGE("fid:%p",fid);
	SetByteArryField(env,paramObj,fid,eccpubkey->YCoordinate,ECC_MAX_XCOORDINATE_BITS_LEN/8);
    //(*env)->SetObjectField(env, paramObj, fid,eccpubkey->XCoordinate);
    (*env)->DeleteLocalRef(env,Class);
    return 0;
}

long SetEccSign(JNIEnv* env ,jobject paramObj,PECCSIGNATUREBLOB eccsign)
{
	long uiRet = 0;
    jfieldID fid;
    LOGE("GetEccSign----Begin");
    if(NULL == env || NULL == paramObj){
        LOGE("GetEccSign----JNIEnv = Null OR jobj = Null");
        return SAR_UNKOWNERR;
    }
   	LOGE("eccsign->r:%p %02X %02X %02X %02X",eccsign->r,eccsign->r[0],eccsign->r[1],eccsign->r[2],eccsign->r[3]);	
	jclass Class = (*env)->GetObjectClass(env,paramObj);
	LOGE("Class:%p",Class);	
    fid = (*env)->GetFieldID(env, Class, "r", "[B");
	LOGE("fid:%p",fid);	
	SetByteArryField(env,paramObj,fid,eccsign->r,ECC_MAX_XCOORDINATE_BITS_LEN/8);
    //(*env)->SetObjectField(env, paramObj, fid,eccsign->r);
    fid = (*env)->GetFieldID(env, Class, "s", "[B");
	LOGE("fid:%p",fid);		
	SetByteArryField(env,paramObj,fid,eccsign->s,ECC_MAX_XCOORDINATE_BITS_LEN/8);
    //(*env)->SetObjectField(env, paramObj, fid,eccsign->s);
    (*env)->DeleteLocalRef(env,Class);
    return 0;	
}

long SetEccChipher(JNIEnv* env ,jobject paramObj,PECCCIPHERBLOB ecccipher)
{
	long uiRet = 0;
    jfieldID fid;
    LOGE("GetEccPubKey----Begin");
    if(NULL == env || NULL == paramObj){
        LOGE("GetEccPubKey----JNIEnv = Null OR jobj = Null");
        return SAR_UNKOWNERR;
    }
    jclass Class = (*env)->GetObjectClass(env,paramObj);
    fid = (*env)->GetFieldID(env, Class, "XCoordinate", "[B");
	SetByteArryField(env,paramObj,fid,ecccipher->XCoordinate,ECC_MAX_XCOORDINATE_BITS_LEN/8);	
    //(*env)->SetObjectField(env, paramObj, fid,ecccipher->XCoordinate);
    fid = (*env)->GetFieldID(env, Class, "YCoordinate", "[B");
	SetByteArryField(env,paramObj,fid,ecccipher->YCoordinate,ECC_MAX_XCOORDINATE_BITS_LEN/8);	
    //(*env)->SetObjectField(env, paramObj, fid,ecccipher->YCoordinate);
    fid = (*env)->GetFieldID(env, Class, "HASH", "[B");
	SetByteArryField(env,paramObj,fid,ecccipher->HASH,32);		
    //(*env)->SetObjectField(env, paramObj, fid,ecccipher->HASH);
    fid = (*env)->GetFieldID(env, Class, "CipherLen", "I");
    (*env)->SetIntField(env, paramObj,fid,ecccipher->CipherLen);	
    fid = (*env)->GetFieldID(env, Class, "Cipher", "[B");
	SetByteArryField(env,paramObj,fid,ecccipher->Cipher,1);		
    //(*env)->SetObjectField(env, paramObj, fid,ecccipher->Cipher);
    (*env)->DeleteLocalRef(env,Class);
    return 0;	
}

long GetSymParam(JNIEnv* env ,jobject paramObj,PBLOCKCIPHERPARAM psysparam)
{
	unsigned long uiRet = 0;
    if(NULL == env || NULL == paramObj){
        LOGE("SetSymParam----JNIEnv = Null OR jobj = Null");
        return SAR_UNKOWNERR;
    }
    jclass clazz = (*env)->GetObjectClass(env, paramObj);
	jfieldID fid;
	fid = (*env)->GetFieldID(env, clazz, "IV", "[B");
	LOGE("GetObjectField----Enter :%p %p",clazz,fid);
	GetByteArryField(env,paramObj,fid,psysparam->IV);
	//jbyteArray jarrIV = (jbyteArray)(*env)->GetObjectField(env,paramObj,fid);
	//jint nArrLen = (*env)->GetArrayLength(env,jarrIV);
	//LOGE("GetObjectField----End,nArrLen = %d,nArrLen/8 = %d",nArrLen,nArrLen/8);
	//unsigned char* bBuffer = (unsigned char*)(*env)->GetByteArrayElements(env,jarrIV, 0);
	//memcpy(psysparam->IV, (unsigned char*)bBuffer, nArrLen);
    //LOGE("iv GetObjectField----end,encryptParam.IV = %s",psysparam->IV);

	fid = (*env)->GetFieldID(env, clazz, "IVLen", "I");
	psysparam->IVLen = (*env)->GetIntField(env, paramObj, fid);
    LOGE("ivLen GetObjectField----end,encryptParam.IVLen= %d",psysparam->IVLen);

	fid = (*env)->GetFieldID(env, clazz, "PaddingType", "I");
	psysparam->PaddingType = (*env)->GetIntField(env, paramObj, fid);
    LOGE("paddingType GetObjectField----end,encryptParam.PaddingType = %d",psysparam->PaddingType);

	fid = (*env)->GetFieldID(env, clazz, "FeedBitLen", "I");
	psysparam->FeedBitLen = (*env)->GetIntField(env, paramObj, fid);
    LOGE("feedBitLen GetIntField----end,encryptParam.FeedBitLen = %d",psysparam->FeedBitLen);
    (*env)->DeleteLocalRef(env,clazz);	
    return uiRet;
}

long GetRsaPubKey(JNIEnv* env ,jobject paramObj,PRSAPUBLICKEYBLOB rsapubkey)
{
    long uiRet = 0;
    jfieldID fid;
    LOGE("SetRsaPubKey----Begin");
    if(NULL == env || NULL == paramObj){
        LOGE("SetRsaPubKey----JNIEnv = Null OR jobj = Null");
        return SAR_UNKOWNERR;
    }
    jclass Class = (*env)->GetObjectClass(env,paramObj);
    fid = (*env)->GetFieldID(env,Class,"AlgID","I");
    rsapubkey->AlgID = (*env)->GetIntField(env,paramObj,fid);
    fid = (*env)->GetFieldID(env,Class,"BitLen","I");
    rsapubkey->BitLen = (*env)->GetIntField(env,paramObj,fid);
    fid = (*env)->GetFieldID(env, Class, "Modulus", "[B");
	GetByteArryField(env,paramObj,fid,rsapubkey->Modulus);	
    //jbyteArray Modulus = (jbyteArray)(*env)->GetObjectField(env,paramObj,fid);
    //jint nMArrLen = (*env)->GetArrayLength(env,Modulus);
    //unsigned char* bBuffer1 = (unsigned char*)(*env)->GetByteArrayElements(env,Modulus, 0);
	//memcpy(rsapubkey->Modulus, bBuffer1, nMArrLen);
    fid = (*env)->GetFieldID(env, Class, "PubExp", "[B");
	GetByteArryField(env,paramObj,fid,rsapubkey->PublicExponent);		
    //jbyteArray PublicExponent = (jbyteArray)(*env)->GetObjectField(env,paramObj,fid);
    //jint nPArrLen = (*env)->GetArrayLength(env,PublicExponent);
    //unsigned char* bBuffer2 = (unsigned char*)(*env)->GetByteArrayElements(env,PublicExponent, 0);
	//memcpy(rsapubkey->PublicExponent, (unsigned char*)bBuffer2, nPArrLen);
	(*env)->DeleteLocalRef(env,Class);
    return 0;
}

long GetEccPubKey(JNIEnv* env ,jobject paramObj,PECCPUBLICKEYBLOB eccpubkey)
{
	long uiRet = 0;
    jfieldID fid;
    LOGE("SetEccPubKey----Begin");
    if(NULL == env || NULL == paramObj){
        LOGE("SetEccPubKey----JNIEnv = Null OR jobj = Null");
        return SAR_UNKOWNERR;
    }
    jclass Class = (*env)->GetObjectClass(env,paramObj);
    fid = (*env)->GetFieldID(env,Class,"BitLen","I");
    eccpubkey->BitLen = (*env)->GetIntField(env,paramObj,fid);
    fid = (*env)->GetFieldID(env, Class, "XCoordinate", "[B");
	GetByteArryField(env,paramObj,fid,eccpubkey->XCoordinate);		
    //jbyteArray XCoordinate = (jbyteArray)(*env)->GetObjectField(env,paramObj,fid);
    //jint nXArrLen = (*env)->GetArrayLength(env,XCoordinate);
   // unsigned char* bBuffer1 = (unsigned char*)(*env)->GetByteArrayElements(env,XCoordinate, 0);
	//memcpy(eccpubkey->XCoordinate, bBuffer1, nXArrLen);
    fid = (*env)->GetFieldID(env, Class, "YCoordinate", "[B");
	GetByteArryField(env,paramObj,fid,eccpubkey->YCoordinate);	
    //jbyteArray YCoordinate = (jbyteArray)(*env)->GetObjectField(env,paramObj,fid);
    //jint nYArrLen = (*env)->GetArrayLength(env,YCoordinate);
    //unsigned char* bBuffer2 = (unsigned char*)(*env)->GetByteArrayElements(env,YCoordinate, 0);
	//memcpy(eccpubkey->YCoordinate, (unsigned char*)bBuffer2, nYArrLen);
	(*env)->DeleteLocalRef(env,Class);
    return 0;
}

long GetEccPriKey(JNIEnv* env ,jobject paramObj,PECCPRIVATEKEYBLOB eccprikey)
{
	long uiRet = 0;
    jfieldID fid;
    LOGE("SetEccPriKey----Begin");
    if(NULL == env || NULL == paramObj){
        LOGE("SetEccPriKey----JNIEnv = Null OR jobj = Null");
        return SAR_UNKOWNERR;
    }
    jclass Class = (*env)->GetObjectClass(env,paramObj);
    fid = (*env)->GetFieldID(env,Class,"BitLen","I");
    eccprikey->BitLen = (*env)->GetIntField(env,paramObj,fid);
    fid = (*env)->GetFieldID(env, Class, "PrivateKey", "[B");
	GetByteArryField(env,paramObj,fid,eccprikey->PrivateKey);		
    //jbyteArray PrivateKey = (jbyteArray)(*env)->GetObjectField(env,paramObj,fid);
    //jint nPriArrLen = (*env)->GetArrayLength(env,PrivateKey);
    //unsigned char* bBuffer1 = (unsigned char*)(*env)->GetByteArrayElements(env,PrivateKey, 0);
	//memcpy(eccprikey->PrivateKey, bBuffer1, nPriArrLen);
	(*env)->DeleteLocalRef(env,Class);
    return 0;
}

long GetEccSign(JNIEnv* env ,jobject paramObj,PECCSIGNATUREBLOB eccsign)
{
	long uiRet = 0;
    jfieldID fid;
    LOGE("SetEccSign----Begin");
    if(NULL == env || NULL == paramObj){
        LOGE("SetEccSign----JNIEnv = Null OR jobj = Null");
        return SAR_UNKOWNERR;
    }
    jclass Class = (*env)->GetObjectClass(env,paramObj);	
    fid = (*env)->GetFieldID(env, Class, "r", "[B");
	GetByteArryField(env,paramObj,fid,eccsign->r);		
    //jbyteArray r = (jbyteArray)(*env)->GetObjectField(env,paramObj,fid);
    //jint rArrLen = (*env)->GetArrayLength(env,r);
    //unsigned char* bBuffer1 = (unsigned char*)(*env)->GetByteArrayElements(env,r, 0);
	//memcpy(eccsign->r, bBuffer1, rArrLen);
    fid = (*env)->GetFieldID(env, Class, "s", "[B");
	GetByteArryField(env,paramObj,fid,eccsign->s);			
    //jbyteArray s = (jbyteArray)(*env)->GetObjectField(env,paramObj,fid);
    //jint sArrLen = (*env)->GetArrayLength(env,s);
    //unsigned char* bBuffer2 = (unsigned char*)(*env)->GetByteArrayElements(env,s, 0);
	//memcpy(eccsign->s, (unsigned char*)bBuffer2, sArrLen);
	(*env)->DeleteLocalRef(env,Class);
    return 0;
}

long GetEccChipher(JNIEnv* env ,jobject paramObj,PECCCIPHERBLOB ecccipher)
{
	long uiRet = 0;
    jfieldID fid;
    LOGE("SetEccChipher----Begin");
    if(NULL == env || NULL == paramObj){
        LOGE("SetEccChipher----JNIEnv = Null OR jobj = Null");
        return SAR_UNKOWNERR;
    }
    jclass Class = (*env)->GetObjectClass(env,paramObj);	
    fid = (*env)->GetFieldID(env, Class, "XCoordinate", "[B");
	GetByteArryField(env,paramObj,fid,ecccipher->XCoordinate);			
    //jbyteArray XCoordinate = (jbyteArray)(*env)->GetObjectField(env,paramObj,fid);
    //jint nXArrLen = (*env)->GetArrayLength(env,XCoordinate);
    //unsigned char* bBuffer1 = (unsigned char*)(*env)->GetByteArrayElements(env,XCoordinate, 0);
	//memcpy(ecccipher->XCoordinate, bBuffer1, nXArrLen);
    fid = (*env)->GetFieldID(env, Class, "YCoordinate", "[B");
	GetByteArryField(env,paramObj,fid,ecccipher->YCoordinate);	
    //jbyteArray YCoordinate = (jbyteArray)(*env)->GetObjectField(env,paramObj,fid);
    //jint nYArrLen = (*env)->GetArrayLength(env,YCoordinate);
    //unsigned char* bBuffer2 = (unsigned char*)(*env)->GetByteArrayElements(env,YCoordinate, 0);
	//memcpy(ecccipher->YCoordinate, (unsigned char*)bBuffer2, nYArrLen);
    fid = (*env)->GetFieldID(env, Class, "HASH", "[B");
	GetByteArryField(env,paramObj,fid,ecccipher->HASH);	
    //jbyteArray HASH = (jbyteArray)(*env)->GetObjectField(env,paramObj,fid);
    //jint HashArrLen = (*env)->GetArrayLength(env,HASH);
    //unsigned char* bBuffer3 = (unsigned char*)(*env)->GetByteArrayElements(env,HASH, 0);
	//memcpy(ecccipher->HASH, (unsigned char*)bBuffer3, HashArrLen);			
    fid = (*env)->GetFieldID(env,Class,"CipherLen","I");
    ecccipher->CipherLen = (*env)->GetIntField(env,paramObj,fid);
    fid = (*env)->GetFieldID(env, Class, "Cipher", "[B");
	GetByteArryField(env,paramObj,fid,ecccipher->Cipher);		
    //jbyteArray Cipher = (jbyteArray)(*env)->GetObjectField(env,paramObj,fid);
    //jint CipherArrLen = (*env)->GetArrayLength(env,Cipher);
    //unsigned char* bBuffer4 = (unsigned char*)(*env)->GetByteArrayElements(env,Cipher, 0);
	//memcpy(ecccipher->Cipher, (unsigned char*)bBuffer4, CipherArrLen);			
	(*env)->DeleteLocalRef(env,Class);
    return 0;
}

long GetEccKeyPair(JNIEnv* env ,jobject paramObj,PENVELOPEDKEYBLOB ecckeypair)
{
	long uiRet = 0;
    jfieldID fid;
    LOGE("GetEccKeyPair----Begin");
    if(NULL == env || NULL == paramObj){
        LOGE("SetEccKeyPair----JNIEnv = Null OR jobj = Null");
        return SAR_UNKOWNERR;
    }
    jclass Class = (*env)->GetObjectClass(env,paramObj);
    fid = (*env)->GetFieldID(env,Class,"Version","I");
    ecckeypair->Version = (*env)->GetIntField(env,paramObj,fid);
    fid = (*env)->GetFieldID(env,Class,"ulSymmAlgID","I");
    ecckeypair->ulSymmAlgID = (*env)->GetIntField(env,paramObj,fid);
    fid = (*env)->GetFieldID(env,Class,"ulBits","I");
    ecckeypair->ulBits = (*env)->GetIntField(env,paramObj,fid);	
    fid = (*env)->GetFieldID(env, Class, "cbEncryptedPriKey", "[B");
	GetByteArryField(env,paramObj,fid,ecckeypair->cbEncryptedPriKey);		
    //jbyteArray cbEncryptedPriKey = (jbyteArray)(*env)->GetObjectField(env,paramObj,fid);
    //jint nPriKeylen = (*env)->GetArrayLength(env,cbEncryptedPriKey);
    //unsigned char* bBuffer1 = (unsigned char*)(*env)->GetByteArrayElements(env,cbEncryptedPriKey, 0);
	//memcpy(ecckeypair->cbEncryptedPriKey, bBuffer1, nPriKeylen);   

	jmethodID get_pub_bit =  (*env)->GetMethodID(env,Class,"get_pubkey_bit","()I");
    LOGE("GetEccKeyPair----get_pub_bit:%p",get_pub_bit);
	ecckeypair->PubKey.BitLen = (*env)->CallIntMethod(env,paramObj,get_pub_bit);
	
	jmethodID get_pub_x =  (*env)->GetMethodID(env,Class,"get_pubkey_x","()[B");
    LOGE("GetEccKeyPair----get_pub_x:%p",get_pub_x);	
	jbyteArray xarr = (jbyteArray)(*env)->CallObjectMethod(env, paramObj, get_pub_x);
	int xarrlen = (*env)->GetArrayLength(env, xarr);
    unsigned char* bBuffer2 = (unsigned char*)(*env)->GetByteArrayElements(env,xarr, 0);
	memcpy(ecckeypair->PubKey.XCoordinate, (unsigned char*)bBuffer2, xarrlen);
	(*env)->ReleaseByteArrayElements(env,xarr,(jbyte *)bBuffer2,0);
	 
	jmethodID get_pub_y =  (*env)->GetMethodID(env,Class,"get_pubkey_y","()[B");
    LOGE("GetEccKeyPair----get_pub_y:%p",get_pub_y);	
	jbyteArray yarr = (jbyteArray)(*env)->CallObjectMethod(env, paramObj, get_pub_y);
	int yarrlen = (*env)->GetArrayLength(env, yarr);
    unsigned char* bBuffer3 = (unsigned char*)(*env)->GetByteArrayElements(env,yarr, 0);
	memcpy(ecckeypair->PubKey.YCoordinate, (unsigned char*)bBuffer3, xarrlen);	
	(*env)->ReleaseByteArrayElements(env,yarr,(jbyte *)bBuffer3,0);
	
	jmethodID get_cipher_cipherlen =  (*env)->GetMethodID(env,Class,"get_cipher_cipherlen","()I");
    LOGE("GetEccKeyPair----get_cipher_cipherlen:%p",get_cipher_cipherlen);
	ecckeypair->ECCCipherBlob.CipherLen = (*env)->CallIntMethod(env,paramObj,get_cipher_cipherlen);
	
	jmethodID get_cipher_x =  (*env)->GetMethodID(env,Class,"get_cipher_x","()[B");
    LOGE("GetEccKeyPair----get_cipher_x:%p",get_cipher_x);
	jbyteArray c_xarr = (jbyteArray)(*env)->CallObjectMethod(env, paramObj, get_cipher_x);
	int c_xarrlen = (*env)->GetArrayLength(env, c_xarr);
    unsigned char* bBuffer4 = (unsigned char*)(*env)->GetByteArrayElements(env,c_xarr, 0);
	memcpy(ecckeypair->ECCCipherBlob.XCoordinate, (unsigned char*)bBuffer4, c_xarrlen);
	(*env)->ReleaseByteArrayElements(env,c_xarr,(jbyte *)bBuffer4,0);
	
	jmethodID get_cipher_y =  (*env)->GetMethodID(env,Class,"get_cipher_y","()[B");
    LOGE("GetEccKeyPair----get_cipher_y:%p",get_cipher_y);	
	jbyteArray c_yarr = (jbyteArray)(*env)->CallObjectMethod(env, paramObj, get_cipher_y);
	int c_yarrlen = (*env)->GetArrayLength(env, c_yarr);
    unsigned char* bBuffer5 = (unsigned char*)(*env)->GetByteArrayElements(env,c_yarr, 0);
	memcpy(ecckeypair->ECCCipherBlob.YCoordinate, (unsigned char*)bBuffer5, c_yarrlen);	
	(*env)->ReleaseByteArrayElements(env,c_yarr,(jbyte *)bBuffer5,0);	
	
	jmethodID get_cipher_hash =  (*env)->GetMethodID(env,Class,"get_cipher_hash","()[B");
    LOGE("GetEccKeyPair----get_cipher_hash:%p",get_cipher_hash);
	jbyteArray c_hash = (jbyteArray)(*env)->CallObjectMethod(env, paramObj, get_cipher_hash);
	int c_hasharrlen = (*env)->GetArrayLength(env, c_hash);
    unsigned char* bBuffer6 = (unsigned char*)(*env)->GetByteArrayElements(env,c_hash, 0);
	memcpy(ecckeypair->ECCCipherBlob.HASH, (unsigned char*)bBuffer6, c_hasharrlen);
	(*env)->ReleaseByteArrayElements(env,c_hash,(jbyte *)bBuffer6,0);	
	
	jmethodID get_cipher_cipher =  (*env)->GetMethodID(env,Class,"get_cipher_cipher","()[B");
    LOGE("GetEccKeyPair----get_cipher_y:%p",get_cipher_cipher);	
	jbyteArray c_cipher = (jbyteArray)(*env)->CallObjectMethod(env, paramObj, get_cipher_cipher);
	int c_cipherarrlen = (*env)->GetArrayLength(env, c_cipher);
    unsigned char* bBuffer7 = (unsigned char*)(*env)->GetByteArrayElements(env,c_cipher, 0);
	memcpy(ecckeypair->ECCCipherBlob.Cipher, (unsigned char*)bBuffer7, c_cipherarrlen);	
	(*env)->ReleaseByteArrayElements(env,c_cipher,(jbyte *)bBuffer7,0);	
	
	(*env)->DeleteLocalRef(env,Class);
    return 0;
}