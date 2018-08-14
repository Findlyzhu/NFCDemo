/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_ccore_SKFJni */

#ifndef _Included_com_ccore_SKFJni
#define _Included_com_ccore_SKFJni
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_SetJavaClass
 * Signature: (Ljava/lang/Object;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1SetJavaClass
  (JNIEnv *, jobject, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_EnumDev
 * Signature: (Z[C)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1EnumDev
  (JNIEnv *, jobject, jboolean, jcharArray);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_ConnectDev
 * Signature: (Ljava/lang/String;Ljava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ConnectDev
  (JNIEnv *, jobject, jstring, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_DisConnect
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1DisConnect
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_GetDevState
 * Signature: (Ljava/lang/String;Ljava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GetDevState
  (JNIEnv *, jobject, jstring, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_SetLabel
 * Signature: (ILjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1SetLabel
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_GetDevInfo
 * Signature: (ILcom/ccore/SKFType/DEVINFO;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GetDevInfo
  (JNIEnv *, jobject, jint, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_LockDev
 * Signature: (II)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1LockDev
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_UnlockDev
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1UnlockDev
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_Transmit
 * Signature: (I[BJ[BJ)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1Transmit
  (JNIEnv *, jobject, jint, jbyteArray, jlong, jbyteArray, jlong);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_ChangeDevAuthKey
 * Signature: (I[BI)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ChangeDevAuthKey
  (JNIEnv *, jobject, jint, jbyteArray, jint);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_DevAuth
 * Signature: (I[BI)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1DevAuth
  (JNIEnv *, jobject, jint, jbyteArray, jint);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_ChangePIN
 * Signature: (IILjava/lang/String;Ljava/lang/String;Ljava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ChangePIN
  (JNIEnv *, jobject, jint, jint, jstring, jstring, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_GetPINInfo
 * Signature: (IILjava/lang/Integer;Ljava/lang/Integer;Ljava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GetPINInfo
  (JNIEnv *, jobject, jint, jint, jobject, jobject, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_VerifyPIN
 * Signature: (IILjava/lang/String;Ljava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1VerifyPIN
  (JNIEnv *, jobject, jint, jint, jstring, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_UnblockPIN
 * Signature: (I[BLjava/lang/String;Ljava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1UnblockPIN
  (JNIEnv *, jobject, jint, jbyteArray, jstring, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_ClearSecureState
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ClearSecureState
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_CreateApplication
 * Signature: (ILjava/lang/String;Ljava/lang/String;ILjava/lang/String;IILjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1CreateApplication
  (JNIEnv *, jobject, jint, jstring, jstring, jint, jstring, jint, jint, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_EnumApplication
 * Signature: (I[CLjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1EnumApplication
  (JNIEnv *, jobject, jint, jcharArray, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_DeleteApplication
 * Signature: (ILjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1DeleteApplication
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_OpenApplication
 * Signature: (ILjava/lang/String;Ljava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1OpenApplication
  (JNIEnv *, jobject, jint, jstring, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_CloseApplication
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1CloseApplication
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_CreateFile
 * Signature: (ILjava/lang/String;III)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1CreateFile
  (JNIEnv *, jobject, jint, jstring, jint, jint, jint);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_DeleteFile
 * Signature: (ILjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1DeleteFile
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_EnumFiles
 * Signature: (I[CLjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1EnumFiles
  (JNIEnv *, jobject, jint, jcharArray, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_GetFileInfo
 * Signature: (ILjava/lang/String;Lcom/ccore/SKFType/FILEATTRIBUTE;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GetFileInfo
  (JNIEnv *, jobject, jint, jstring, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_ReadFile
 * Signature: (ILjava/lang/String;II[BLjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ReadFile
  (JNIEnv *, jobject, jint, jstring, jint, jint, jbyteArray, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_WriteFile
 * Signature: (ILjava/lang/String;I[BI)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1WriteFile
  (JNIEnv *, jobject, jint, jstring, jint, jbyteArray, jint);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_CreateContainer
 * Signature: (ILjava/lang/String;Ljava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1CreateContainer
  (JNIEnv *, jobject, jint, jstring, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_DeleteContainer
 * Signature: (ILjava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1DeleteContainer
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_OpenContainer
 * Signature: (ILjava/lang/String;Ljava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1OpenContainer
  (JNIEnv *, jobject, jint, jstring, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_CloseContainer
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1CloseContainer
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_EnumContainer
 * Signature: (I[CLjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1EnumContainer
  (JNIEnv *, jobject, jint, jcharArray, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_GetContainerType
 * Signature: (ILjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GetContainerType
  (JNIEnv *, jobject, jint, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_ImportCertificate
 * Signature: (IZ[BI)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ImportCertificate
  (JNIEnv *, jobject, jint, jboolean, jbyteArray, jint);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_ExportCertificate
 * Signature: (IZ[BLjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ExportCertificate
  (JNIEnv *, jobject, jint, jboolean, jbyteArray, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_GenRandom
 * Signature: (I[BI)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GenRandom
  (JNIEnv *, jobject, jint, jbyteArray, jint);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_GenExtRSAKey
 * Signature: (IILcom/ccore/SKFType/RSAPRIVATEKEYBLOB;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GenExtRSAKey
  (JNIEnv *, jobject, jint, jint, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_GenRSAKeyPair
 * Signature: (IILcom/ccore/SKFType/RSAPUBLICKEYBLOB;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GenRSAKeyPair
  (JNIEnv *, jobject, jint, jint, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_ImportRSAKeyPair
 * Signature: (II[BI[BI)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ImportRSAKeyPair
  (JNIEnv *, jobject, jint, jint, jbyteArray, jint, jbyteArray, jint);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_RSASignData
 * Signature: (I[BI[BLjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1RSASignData
  (JNIEnv *, jobject, jint, jbyteArray, jint, jbyteArray, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_RSAVerify
 * Signature: (ILcom/ccore/SKFType/RSAPUBLICKEYBLOB;[BI[BI)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1RSAVerify
  (JNIEnv *, jobject, jint, jobject, jbyteArray, jint, jbyteArray, jint);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_RSAExportSessionKey
 * Signature: (IILcom/ccore/SKFType/RSAPUBLICKEYBLOB;[BLjava/lang/Integer;Ljava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1RSAExportSessionKey
  (JNIEnv *, jobject, jint, jint, jobject, jbyteArray, jobject, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_ExtRSAPubKeyOperation
 * Signature: (ILcom/ccore/SKFType/RSAPUBLICKEYBLOB;[BI[BLjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ExtRSAPubKeyOperation
  (JNIEnv *, jobject, jint, jobject, jbyteArray, jint, jbyteArray, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_ExtRSAPriKeyOperation
 * Signature: (ILcom/ccore/SKFType/RSAPRIVATEKEYBLOB;[BI[BLjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ExtRSAPriKeyOperation
  (JNIEnv *, jobject, jint, jobject, jbyteArray, jint, jbyteArray, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_GenECCKeyPair
 * Signature: (IILcom/ccore/SKFType/ECCPUBLICKEYBLOB;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GenECCKeyPair
  (JNIEnv *, jobject, jint, jint, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_ImportECCKeyPair
 * Signature: (ILcom/ccore/SKFType/ENVELOPEDKEYBLOB;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ImportECCKeyPair
  (JNIEnv *, jobject, jint, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_ECCSignData
 * Signature: (I[BILcom/ccore/SKFType/ECCSIGNATUREBLOB;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ECCSignData
  (JNIEnv *, jobject, jint, jbyteArray, jint, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_ECCVerify
 * Signature: (ILcom/ccore/SKFType/ECCPUBLICKEYBLOB;[BILcom/ccore/SKFType/ECCSIGNATUREBLOB;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ECCVerify
  (JNIEnv *, jobject, jint, jobject, jbyteArray, jint, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_ECCExportSessionKey
 * Signature: (IILcom/ccore/SKFType/ECCPUBLICKEYBLOB;Lcom/ccore/SKFType/ECCCIPHERBLOB;Ljava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ECCExportSessionKey
  (JNIEnv *, jobject, jint, jint, jobject, jobject, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_ExtECCEncrypt
 * Signature: (ILcom/ccore/SKFType/ECCPUBLICKEYBLOB;[BILcom/ccore/SKFType/ECCCIPHERBLOB;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ExtECCEncrypt
  (JNIEnv *, jobject, jint, jobject, jbyteArray, jint, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_ExtECCDecrypt
 * Signature: (ILcom/ccore/SKFType/ECCPRIVATEKEYBLOB;Lcom/ccore/SKFType/ECCCIPHERBLOB;[BLjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ExtECCDecrypt
  (JNIEnv *, jobject, jint, jobject, jobject, jbyteArray, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_ExtECCSign
 * Signature: (ILcom/ccore/SKFType/ECCPRIVATEKEYBLOB;[BILcom/ccore/SKFType/ECCSIGNATUREBLOB;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ExtECCSign
  (JNIEnv *, jobject, jint, jobject, jbyteArray, jint, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_ExtECCVerify
 * Signature: (ILcom/ccore/SKFType/ECCPUBLICKEYBLOB;[BILcom/ccore/SKFType/ECCSIGNATUREBLOB;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ExtECCVerify
  (JNIEnv *, jobject, jint, jobject, jbyteArray, jint, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_GenerateAgreementDataWithECC
 * Signature: (IILcom/ccore/SKFType/ECCPUBLICKEYBLOB;[BILjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GenerateAgreementDataWithECC
  (JNIEnv *, jobject, jint, jint, jobject, jbyteArray, jint, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_GenerateAgreementDataAndKeyWithECC
 * Signature: (IILcom/ccore/SKFType/ECCPUBLICKEYBLOB;Lcom/ccore/SKFType/ECCPUBLICKEYBLOB;Lcom/ccore/SKFType/ECCPUBLICKEYBLOB;[BI[BILjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GenerateAgreementDataAndKeyWithECC
  (JNIEnv *, jobject, jint, jint, jobject, jobject, jobject, jbyteArray, jint, jbyteArray, jint, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_GenerateKeyWithECC
 * Signature: (ILcom/ccore/SKFType/ECCPUBLICKEYBLOB;Lcom/ccore/SKFType/ECCPUBLICKEYBLOB;[BILjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1GenerateKeyWithECC
  (JNIEnv *, jobject, jint, jobject, jobject, jbyteArray, jint, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_ExportPublicKey
 * Signature: (IZ[BLjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ExportPublicKey
  (JNIEnv *, jobject, jint, jboolean, jbyteArray, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_ImportSessionKey
 * Signature: (II[BILjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1ImportSessionKey
  (JNIEnv *, jobject, jint, jint, jbyteArray, jint, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_SetSymmKey
 * Signature: (I[BILjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1SetSymmKey
  (JNIEnv *, jobject, jint, jbyteArray, jint, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_EncryptInit
 * Signature: (ILcom/ccore/SKFType/BLOCKCIPHERPARAM;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1EncryptInit
  (JNIEnv *, jobject, jint, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_Encrypt
 * Signature: (I[BI[BLjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1Encrypt
  (JNIEnv *, jobject, jint, jbyteArray, jint, jbyteArray, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_EncryptUpdate
 * Signature: (I[BI[BLjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1EncryptUpdate
  (JNIEnv *, jobject, jint, jbyteArray, jint, jbyteArray, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_EncryptFinal
 * Signature: (I[BLjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1EncryptFinal
  (JNIEnv *, jobject, jint, jbyteArray, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_DecryptInit
 * Signature: (ILcom/ccore/SKFType/BLOCKCIPHERPARAM;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1DecryptInit
  (JNIEnv *, jobject, jint, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_Decrypt
 * Signature: (I[BI[BLjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1Decrypt
  (JNIEnv *, jobject, jint, jbyteArray, jint, jbyteArray, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_DecryptUpdate
 * Signature: (I[BI[BLjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1DecryptUpdate
  (JNIEnv *, jobject, jint, jbyteArray, jint, jbyteArray, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_DecryptFinal
 * Signature: (I[BLjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1DecryptFinal
  (JNIEnv *, jobject, jint, jbyteArray, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_DigestInit
 * Signature: (IILcom/ccore/SKFType/ECCPUBLICKEYBLOB;[BILjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1DigestInit
  (JNIEnv *, jobject, jint, jint, jobject, jbyteArray, jint, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_DigestUpdate
 * Signature: (I[BI)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1DigestUpdate
  (JNIEnv *, jobject, jint, jbyteArray, jint);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_DigestFinal
 * Signature: (I[BLjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1DigestFinal
  (JNIEnv *, jobject, jint, jbyteArray, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_Digest
 * Signature: (I[BI[BLjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1Digest
  (JNIEnv *, jobject, jint, jbyteArray, jint, jbyteArray, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_MacInit
 * Signature: (ILcom/ccore/SKFType/BLOCKCIPHERPARAM;Ljava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1MacInit
  (JNIEnv *, jobject, jint, jobject, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_MacUpdate
 * Signature: (I[BI)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1MacUpdate
  (JNIEnv *, jobject, jint, jbyteArray, jint);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_MacFinal
 * Signature: (I[BLjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1MacFinal
  (JNIEnv *, jobject, jint, jbyteArray, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_Mac
 * Signature: (I[BI[BLjava/lang/Integer;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1Mac
  (JNIEnv *, jobject, jint, jbyteArray, jint, jbyteArray, jobject);

/*
 * Class:     com_ccore_SKFJni
 * Method:    SKF_CloseHandle
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_SKF_1CloseHandle
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_ccore_SKFJni
 * Method:    V_SetAppPath
 * Signature: (Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_com_ccore_SKFJni_V_1SetAppPath
  (JNIEnv *, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif