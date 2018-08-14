package com.ccore;

import android.util.Log;

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
 * @DATE 2018/8/13 14:52
 * @Description This Class for
 **/
public class SKFJni {
    /*---------------------------------------------SKF Jni Func-----------------------------------------*/
    private String TAG = "SKFJni";

    /**
     * @Function: SKFJNI 若使用蓝牙和NFC,需在构造时将Java类传入
     * @param cls
     */
    public SKFJni(Object cls){
        if(cls != null){
            Log.e(TAG,"SKF Init With Java Class");
            SKF_SetJavaClass(cls);
        }
    }

    /**
     * @Function: SKFJNI 普通调用SKF.so
    **/
    public SKFJni(){
        Log.e(TAG,"SKF Init With No Java Class");
    }

    /**
     * @Function: 设置需要反调访问的JAVA类
     * @param pclass
     * @return
     */
    private native long SKF_SetJavaClass(Object pclass);

    /**
     * @Function: 枚举设备
     * @param bPresent
     * @param pbDevNameList
     * @return
     */
    public native long SKF_EnumDev(boolean bPresent,char[] pbDevNameList);

    /**
     * @Function: 连接设备
     * @return
     */
    public native long SKF_ConnectDev(String DevName,Integer phDev);

    /**
     * @Function: 断开设备
     * @param hDev
     * @return
     */
    public native long SKF_DisConnect(int hDev);

    /**
     * @Function: 获取设备状态
     * @param szDevName
     * @param ulDevState
     * @return
     */
    public native long SKF_GetDevState(String szDevName,Integer ulDevState);

    /**
     * @Function: 设置标签
     * @param szLabelName
     * @return
     */
    public native long SKF_SetLabel(int hDev,String szLabelName);

    /**
     * @Function: 获取设备信息
     * @param info
     * @return
     */
    public native long SKF_GetDevInfo(int hDev, SKFType.DEVINFO info);

    /**
     * @Function: 锁定设备
     * @param ulTimeOut
     * @return
     */
    public native long SKF_LockDev(int hDev,int ulTimeOut);

    /**
     * @Function: 解锁设备
     * @return
     */
    public native long SKF_UnlockDev(int hDev);

    /**
     * @Function: 透传指令
     * @param pbCommand
     * @param ulCommandLen
     * @param pbData
     * @param pulDataLen
     * @return
     */
    public native long SKF_Transmit(int hDev,byte[] pbCommand,long ulCommandLen,byte[] pbData,long pulDataLen);

    /**
     * @Function: 设置应用路径
     * @param szAppPath
     * @return
     */
    //public native long SKF_SetAppPath(int hDev,String szAppPath);

    /**
     * @Function: 改变设备认证密钥
     * @param pbKeyValue
     * @param ulKeyLen
     * @return
     */
    public native long SKF_ChangeDevAuthKey(int hDev,byte[] pbKeyValue,int ulKeyLen);

    /**
     * @Function: 设备认证
     * @param pbAuthData
     * @param ulLen
     * @return
     */
    public native long SKF_DevAuth(int hDev,byte[] pbAuthData,int ulLen);

    /**
     * @Function: 改变PIN码
     * @param ulPinType
     * @param szOldPin
     * @param szNewPin
     * @param pulRetry
     * @return
     */
    public native long SKF_ChangePIN(int hApp,int ulPinType,String szOldPin,String szNewPin,Integer pulRetry);

    /**
     * @Function: 获取PIN码信息
     * @param ulPinType
     * @param pulMaxRetryCount
     * @param pulRemainRetryCount
     * @param pbDefaultPin
     * @return
     */
    public native long SKF_GetPINInfo(int hApp,int ulPinType,Integer pulMaxRetryCount,Integer pulRemainRetryCount,Integer pbDefaultPin);

    /**
     * @Function: 验证PIN码
     * @param ulPinType
     * @param szOldPin
     * @param pulRetry
     * @return
     */
    public native long SKF_VerifyPIN(int hApp,int ulPinType,String szOldPin,Integer pulRetry);

    /**
     * @Function: 复原PIN 码
     * @param szAdminPin
     * @param szNewUserPin
     * @param pulRetry
     * @return
     */
    public native long SKF_UnblockPIN(int hApp,byte[] szAdminPin,String szNewUserPin,Integer pulRetry);

    /**
     * @Function: 清楚安全状态
     * @return
     */
    public native long SKF_ClearSecureState(int hApp);

    /**
     * @Function: 创建应用
     * @param szAppName
     * @param szNewUserPin
     * @param ulAdminPinRetry
     * @param szAdminPin
     * @param ulUserPinRetry
     * @param ulCreateFileRights
     * @return
     */
    public native long SKF_CreateApplication(int hDev,String szAppName,String szNewUserPin,int ulAdminPinRetry,String szAdminPin,int ulUserPinRetry,int ulCreateFileRights,Integer phApp);

    /**
     * @Function: 枚举应用
     * @param szAppName
     * @param pulSize
     * @return
     */
    public native long SKF_EnumApplication(int hDev,char[] szAppName,Integer pulSize);

    /**
     * @Function: 删除应用
     * @param szAppName
     * @return
     */
    public native long SKF_DeleteApplication(int hDev,String szAppName);

    /**
     * @Function: 打开应用
     * @param szAppName
     * @return
     */
    public native long SKF_OpenApplication(int hDev,String szAppName,Integer phApp);

    /**
     * @Function: 关闭应用
     * @return
     */
    public native long SKF_CloseApplication(int hApp);

    /**
     * @Function: 创建文件
     * @param szFileName
     * @param ulFileSize
     * @param ulReadRights
     * @param ulWriteRights
     * @return
     */
    public native long SKF_CreateFile(int hApp,String szFileName,int ulFileSize,int ulReadRights,int ulWriteRights);

    /**
     * @Function: 删除文件
     * @param szFileName
     * @return
     */
    public native long SKF_DeleteFile(int hApp,String szFileName);

    /**
     * @Function: 枚举文件
     * @param szFileList
     * @param FileListSize
     * @return
     */
    public native long SKF_EnumFiles(int hApp,char[] szFileList,Integer FileListSize);

    /**
     * @Function: 获取文件属性
     * @param szFileName
     * @param FileInfo
     * @return
     */
    public native long SKF_GetFileInfo(int hApp, String szFileName, SKFType.FILEATTRIBUTE FileInfo);

    /**
     * @Function: 读取文件内容
     * @param szFileName
     * @param offSet
     * @param Size
     * @param pbOutData
     * @param OutDataLen
     * @return
     */
    public native long SKF_ReadFile(int hApp,String szFileName,int offSet,int Size,byte[] pbOutData,Integer OutDataLen);

    /**
     * @Function: 写入文件内容
     * @param szFileName
     * @param ulOffset
     * @param pbData
     * @param ulSize
     * @return
     */
    public native long SKF_WriteFile(int hApp,String szFileName,int ulOffset,byte[] pbData,int ulSize);


    /**
     * @Function: 创建容器
     * @param szContainerName
     * @return
     */
    public native long SKF_CreateContainer(int hApp,String szContainerName,Integer phCtn);

    /**
     * @Function: 删除容器
     * @param szContainerName
     * @return
     */
    public native long SKF_DeleteContainer(int hApp,String szContainerName);

    /**
     * @Function: 打开容器
     * @param szContainerName
     * @return
     */
    public native long SKF_OpenContainer(int hApp,String szContainerName,Integer phCtn);

    /**
     * @Function: 关闭容器
     * @return
     */
    public native long SKF_CloseContainer(int hCtn);

    /**
     * @Function: 枚举容器
     * @param szContainerName
     * @param CountainerSize
     * @return
     */
    public native long SKF_EnumContainer(int hApp,char[] szContainerName,Integer CountainerSize);

    /**
     * @Function: 获取容器类型
     * @param ContainerType
     * @return
     */
    public native long SKF_GetContainerType(int hCtn,Integer ContainerType);

    /**
     * @Function: 导入证书
     * @param hCtn
     * @param bSignFlag
     * @param pbCert
     * @param cbCert
     * @return
     */
    public native long SKF_ImportCertificate(int hCtn,boolean bSignFlag,byte[] pbCert,int cbCert);

    /**
     * @Function: 导出证书
     * @param hCtn
     * @param bSignFlag
     * @param pbCert
     * @param cbCert
     * @return
     */
    public native long SKF_ExportCertificate(int hCtn,boolean bSignFlag,byte[] pbCert,Integer cbCert);


    /**
     * @Function: 获取随机数
     * @param pbRandom
     * @param ContainerType
     * @return
     */
    public native long SKF_GenRandom(int hDev,byte[] pbRandom,int ContainerType);

    /**
     * @Function: 获取外部密钥
     * @param ulBitlen
     * @param Blob
     * @return
     */
    public native long SKF_GenExtRSAKey(int hDev, int ulBitlen, SKFType.RSAPRIVATEKEYBLOB Blob);

    /**
     * @Function: 生成RSA密钥对
     * @param ulBitlen
     * @param Blob
     * @return
     */
    public native long SKF_GenRSAKeyPair(int hCtn, int ulBitlen, SKFType.RSAPUBLICKEYBLOB Blob);

    /**
     * @Function: 导入RSA密钥对
     * @param ulSymAlgId
     * @param pbWrappedKey
     * @param ulWrappedKeyLen
     * @param pbEncryptedData
     * @param ulEncryptedDataLen
     * @return
     */
    public native long SKF_ImportRSAKeyPair(int hCtn,int ulSymAlgId,byte[] pbWrappedKey,int ulWrappedKeyLen,byte[] pbEncryptedData,int ulEncryptedDataLen);

    /**
     * @Function: 生成RSA签名值
     * @param pbData
     * @param ulDataLen
     * @param pbSignature
     * @param pulSignLen
     * @return
     */
    public native long SKF_RSASignData(int hCtn,byte[] pbData,int ulDataLen,byte[] pbSignature,Integer pulSignLen);

    /**
     * @Function: RSA验签
     * @param Blob
     * @param pbData
     * @param ulDatalen
     * @param pbSignature
     * @param ulSignLen
     * @return
     */
    public native long SKF_RSAVerify(int hDev, SKFType.RSAPUBLICKEYBLOB Blob, byte[] pbData, int ulDatalen, byte[] pbSignature, int ulSignLen);

    /**
     * @Function: 导出SessionKey
     * @param hCtn
     * @param ulAlgId
     * @param pPubKey
     * @param pbData
     * @param pulDataLen
     * @param phSessionKey
     * @return
     */
    public native long SKF_RSAExportSessionKey(int hCtn, int ulAlgId, SKFType.RSAPUBLICKEYBLOB pPubKey, byte[] pbData, Integer pulDataLen, Integer phSessionKey);

    /**
     * @Function: 外部公钥操作
     * @param hDev
     * @param pRSAPubKeyBlob
     * @param pbInput
     * @param ulInputLen
     * @param pbOutput
     * @param pulOutputLen
     * @return
     */
    public native long SKF_ExtRSAPubKeyOperation(int hDev, SKFType.RSAPUBLICKEYBLOB pRSAPubKeyBlob, byte[] pbInput, int ulInputLen, byte[] pbOutput, Integer pulOutputLen);

    /**
     * @Function: 外部私钥操作
     * @param hDev
     * @param pRSAPriKeyBlob
     * @param pbInput
     * @param ulInputLen
     * @param pbOutput
     * @param pulOutputLen
     * @return
     */
    public native long SKF_ExtRSAPriKeyOperation(int hDev, SKFType.RSAPRIVATEKEYBLOB pRSAPriKeyBlob, byte[] pbInput, int ulInputLen, byte[] pbOutput, Integer pulOutputLen);

    /**
     * @Function: 生成ECC密钥对
     * @param hCtn
     * @param AlgoId
     * @param Blob
     * @return
     */
    public native long SKF_GenECCKeyPair(int hCtn, int AlgoId, SKFType.ECCPUBLICKEYBLOB Blob);

    /**
     * @Function: 导入ECC密钥对
     * @param hCtn
     * @param Blob
     * @return
     */
    public native long SKF_ImportECCKeyPair(int hCtn, SKFType.ENVELOPEDKEYBLOB Blob);

    /**
     * @Function: ECC签名
     * @param hCtn
     * @param pbData
     * @param ulDatalen
     * @param pbSignature
     * @return
     */
    public native long SKF_ECCSignData(int hCtn, byte[] pbData, int ulDatalen, SKFType.ECCSIGNATUREBLOB pbSignature);

    /**
     * @Function: ECC验签
     * @param hDev
     * @param pEccBlob
     * @param pbData
     * @param ulDatalen
     * @param pbSignature
     * @return
     */
    public native long SKF_ECCVerify(int hDev, SKFType.ECCPUBLICKEYBLOB pEccBlob, byte[] pbData, int ulDatalen, SKFType.ECCSIGNATUREBLOB pbSignature);

    /**
     * @Function: 导出ECC SessionKey
     * @param hCrn
     * @param ulAlgId
     * @param pPubKey
     * @param pData
     * @param phSessionKey
     * @return
     */
    public native long SKF_ECCExportSessionKey(int hCrn, int ulAlgId, SKFType.ECCPUBLICKEYBLOB pPubKey, SKFType.ECCCIPHERBLOB pData, Integer phSessionKey);

    /**
     * @Function: ECC外部加密
     * @param hDev
     * @param pECCPubKeyBlob
     * @param pbPlainText
     * @param ulPlainTextLen
     * @param pCipherText
     * @return
     */
    public native long SKF_ExtECCEncrypt(int hDev, SKFType.ECCPUBLICKEYBLOB pECCPubKeyBlob, byte[] pbPlainText, int ulPlainTextLen, SKFType.ECCCIPHERBLOB pCipherText);

    /**
     * @Function: ECC外部解密
     * @param hDev
     * @param pECCPriKeyBlob
     * @param pCipherText
     * @param pbPlainText
     * @param pulPlainTextLen
     * @return
     */
    public native long SKF_ExtECCDecrypt(int hDev, SKFType.ECCPRIVATEKEYBLOB pECCPriKeyBlob, SKFType.ECCCIPHERBLOB pCipherText, byte[] pbPlainText, Integer pulPlainTextLen);

    /**
     * @Function: ECC外部签名
     * @param hDev
     * @param pECCPriKeyBlob
     * @param pbData
     * @param ulDataLen
     * @param pSignature
     * @return
     */
    public native long SKF_ExtECCSign(int hDev, SKFType.ECCPRIVATEKEYBLOB pECCPriKeyBlob, byte[] pbData, int ulDataLen, SKFType.ECCSIGNATUREBLOB pSignature);

    /**
     * @Function: ECC外部验签
     * @param hDev
     * @param pECCPubKeyBlob
     * @param pbData
     * @param ulDataLen
     * @param pSignature
     * @return
     */
    public native long SKF_ExtECCVerify(int hDev, SKFType.ECCPUBLICKEYBLOB pECCPubKeyBlob, byte[] pbData, int ulDataLen, SKFType.ECCSIGNATUREBLOB pSignature);

    /**
     * @Function: 生成ECC密钥协商参数
     * @param hCtn
     * @param ulAlgId
     * @param pTempECCPubKeyBlob
     * @param pbID
     * @param ulIDLen
     * @param phAgreementHandle
     * @return
     */
    public native long SKF_GenerateAgreementDataWithECC(int hCtn, int ulAlgId, SKFType.ECCPUBLICKEYBLOB pTempECCPubKeyBlob, byte[] pbID, int ulIDLen, Integer phAgreementHandle);

    /**
     * @Function: 产生密钥协商数据并计算会话密钥
     * @param hCtn
     * @param ulAlgId
     * @param pSponsorECCPubKeyBlob
     * @param pSponsorTempECCPubKeyBlob
     * @param pTempECCPubKeyBlob
     * @param pbID
     * @param ulIDLen
     * @param pbSponsorID
     * @param ulSponsorIDLen
     * @param phKeyHandle
     * @return
     */
    public native long SKF_GenerateAgreementDataAndKeyWithECC(int hCtn, int ulAlgId, SKFType.ECCPUBLICKEYBLOB pSponsorECCPubKeyBlob, SKFType.ECCPUBLICKEYBLOB pSponsorTempECCPubKeyBlob,
                                                              SKFType.ECCPUBLICKEYBLOB pTempECCPubKeyBlob, byte[] pbID, int ulIDLen, byte[] pbSponsorID, int ulSponsorIDLen, Integer phKeyHandle);

    /**
     * @Function: 计算会话密钥
     * @param hAgreementHandle
     * @param pECCPubKeyBlob
     * @param pTempECCPubKeyBlob
     * @param pbID
     * @param ulIDLen
     * @param phKeyHandle
     * @return
     */
    public native long SKF_GenerateKeyWithECC(int hAgreementHandle, SKFType.ECCPUBLICKEYBLOB pECCPubKeyBlob,
                                              SKFType.ECCPUBLICKEYBLOB pTempECCPubKeyBlob, byte[] pbID, int ulIDLen, Integer phKeyHandle);

    /**
     * @Function: 导出公钥
     * @param hCtn
     * @param bSignFlag
     * @param pbBlob
     * @param pulBlobLen
     * @return
     */
    public native long SKF_ExportPublicKey(int hCtn,boolean bSignFlag,byte[] pbBlob,Integer pulBlobLen);

    /**
     * @param hCtn 导入SessionKey
     * @param ulAlgId
     * @param pbWrapedData
     * @param ulWrapedLen
     * @param phKey
     * @return
     */
    public native long SKF_ImportSessionKey(int hCtn,int ulAlgId,byte[] pbWrapedData,int ulWrapedLen,Integer phKey);

    /**
     * @Function: 设置密钥
     * @param key
     * @param algID
     * @return
     */
    public native long SKF_SetSymmKey(int hDev,byte[] key,int algID,Integer phKey);

    /**
     * @Function: 对称算法初始化
     * @param param
     * @return
     */
    public native long SKF_EncryptInit(int hKey, SKFType.BLOCKCIPHERPARAM param);

    /**
     * @Function: 单组对称加密
     * @param pbData
     * @param ulDataLen
     * @param pbEncryptedData
     * @param pulEncryptedLen
     * @return
     */
    public native long SKF_Encrypt(int hKey,byte[] pbData,int ulDataLen,byte[] pbEncryptedData,Integer pulEncryptedLen);


    /**
     * @Function: 对称加密Update
     * @param pbData
     * @param ulDataLen
     * @param pbEncryptedData
     * @param pulEncryptedLen
     * @return
     */
    public native long SKF_EncryptUpdate(int hKey,byte[] pbData,int ulDataLen,byte[] pbEncryptedData,Integer pulEncryptedLen);

    /**
     * @Function: 对称加密Final
     * @param pbEncryptedData
     * @param pulEncryptedLen
     * @return
     */
    public native long SKF_EncryptFinal(int hKey,byte[] pbEncryptedData,Integer pulEncryptedLen);

    /**
     * @Function: 对称解密初始化
     * @param param
     * @return
     */
    public native long SKF_DecryptInit(int hKey, SKFType.BLOCKCIPHERPARAM param);

    /**
     * @Function: 单组解密
     * @param pbData
     * @param ulDataLen
     * @param pbEncryptedData
     * @param pulEncryptedLen
     * @return
     */
    public native long SKF_Decrypt(int hKey,byte[] pbData,int ulDataLen,byte[] pbEncryptedData,Integer pulEncryptedLen);

    /**
     * @Function: 对称解密Update
     * @param pbData
     * @param ulDataLen
     * @param pbEncryptedData
     * @param pulEncryptedLen
     * @return
     */
    public native long SKF_DecryptUpdate(int hKey,byte[] pbData,int ulDataLen,byte[] pbEncryptedData,Integer pulEncryptedLen);

    /**
     * @Function: 对称解密Final
     * @param pbEncryptedData
     * @param pulEncryptedLen
     * @return
     */
    public native long SKF_DecryptFinal(int hKey,byte[] pbEncryptedData,Integer pulEncryptedLen);

    /**
     * @Function: HASH初始化
     * @param hDev
     * @param ulAlgID
     * @param pPubKey
     * @param pucID
     * @param ulIDLen
     * @param phHash
     * @return
     */
    public native long SKF_DigestInit(int hDev, int ulAlgID, SKFType.ECCPUBLICKEYBLOB pPubKey, byte[] pucID, int ulIDLen, Integer phHash);

    /**
     * @Function: HASH Update
     * @param hHash
     * @param pbData
     * @param ulDataLen
     * @return
     */
    public native long SKF_DigestUpdate(int hHash,byte[] pbData,int ulDataLen);

    /**
     * @Function: HASH Final
     * @param hHash
     * @param pbDigest
     * @param pulDigestLen
     * @return
     */
    public native long SKF_DigestFinal(int hHash,byte[] pbDigest,Integer pulDigestLen);

    /**
     * @Function: HASH 单组运算
     * @param hHash
     * @param pbData
     * @param ulDataLen
     * @param pbDigest
     * @param pulDigestLen
     * @return
     */
    public native long SKF_Digest(int hHash,byte[] pbData,int ulDataLen,byte[] pbDigest,Integer pulDigestLen);

    /**
     * @Function: Mac 初始化
     * @param hKey
     * @param pMacParam
     * @param phMac
     * @return
     */
    public native long SKF_MacInit(int hKey, SKFType.BLOCKCIPHERPARAM pMacParam, Integer phMac);

    /**
     * @Function: Mac Update
     * @param hMac
     * @param pbData
     * @param ulDataLen
     * @return
     */
    public native long SKF_MacUpdate(int hMac,byte[] pbData,int ulDataLen);

    /**
     * @Function: Mac Final
     * @param hMac
     * @param pbMac
     * @param pulMacLen
     * @return
     */
    public native long SKF_MacFinal(int hMac,byte[] pbMac,Integer pulMacLen);

    /**
     * @Function: Mac单组运算
     * @param hMac
     * @param pbData
     * @param ulDataLen
     * @param pbMac
     * @param pulMacLen
     * @return
     */
    public native long SKF_Mac(int hMac,byte[] pbData,int ulDataLen,byte[] pbMac,Integer pulMacLen);


    /**
     * @Function: 关闭句柄
     * @param hHandle
     * @return
     */
    public native long SKF_CloseHandle(int hHandle);

    /**
     * @Function: SD 卡设置访问卡路径
     * @param szAppPath
     * @return
     */
    public native long V_SetAppPath(String szAppPath);


    static {
        System.loadLibrary("SKFJni");
    }
}
