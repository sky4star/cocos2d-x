/*
 Copyright (c) 2015, LambdaCloud
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
 */

#include "LambdaDevice.h"
#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"

#include <stdlib.h>
#include <android/log.h>

USING_NS_CC;
using namespace lambdacloud;

std::string LambdaDevice::getCarrierName(void)
{
    try
    {
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo, "org/lambdacloud/sdk/LambdaDeviceUtil", "getOperationInfo",
                        "()Ljava/lang/String;"))
        {
            jstring jstr = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);

            return JniHelper::jstring2string(jstr);
        }
    } catch (const std::exception& ex) {
        CCLOGERROR("LambdaDevice got an exception while reading carrier name for android device, detail is %s", ex.what());
    } catch (const std::string& ex) {
        CCLOGERROR("LambdaDevice got a string exception while reading carrier name for android device, detail is %s", ex.c_str());
    } catch (...) {
        CCLOGERROR("LambdaDevice got an unknown exception while reading carrier name for android device");
    }
    return LAMBDA_DEVICE_INFO_UNKNOWN;

}

std::string LambdaDevice::getNetworkStatus(void)
{
    try
    {
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo, "org/lambdacloud/sdk/LambdaDeviceUtil", "getInternetConnectionStatus",
                        "()Ljava/lang/String;"))
        {
            jstring jstr = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
            return JniHelper::jstring2string(jstr);
        }
        return LAMBDA_NETWORK_STATUS_NOT_REACHABLE;
    } catch (const std::exception& ex) {
        CCLOGERROR("LambdaDevice got an exception while getting network status for android device, detail is %s", ex.what());
    } catch (const std::string& ex) {
        CCLOGERROR("LambdaDevice got a string exception while reading network status for android device, detail is %s", ex.c_str());
    } catch (...) {
        CCLOGERROR("LambdaDevice got an unknown exception while reading network status for android device");
    }
    return LAMBDA_DEVICE_INFO_UNKNOWN;
}

std::string LambdaDevice::getApplicationPlatform(void)
{
	return LAMBDA_PLATFORM_ANDROID;
}

std::string LambdaDevice::getDeviceName(void)
{
    try
    {
        JniMethodInfo methodInfo;
        if (JniHelper::getStaticMethodInfo(methodInfo, "org/lambdacloud/sdk/LambdaDeviceUtil", "getDeviceName", "()Ljava/lang/String;"))
        {
            jstring jstr = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
            return JniHelper::jstring2string(jstr);
        }
    } catch (const std::exception& ex) {
        CCLOGERROR("LambdaDevice got an exception while reading device name for android device, detail is %s", ex.what());
    } catch (const std::string& ex) {
        CCLOGERROR("LambdaDevice got a string exception while reading device name for android device, detail is %s", ex.c_str());
    } catch (...) {
        CCLOGERROR("LambdaDevice got an unknown exception while reading device name for android device");
    }
    return LAMBDA_DEVICE_INFO_UNKNOWN;
}

#endif