 /*
 * Module:   TRTCCloudCallback @ TXLiteAVSDK
 *
 * Function: 腾讯云视频通话功能的回调接口类
 *
 */
 
#ifndef __TRTCENGINECALLBACK_H__
#define __TRTCENGINECALLBACK_H__

#include "TRTCCloudDef.h"
#include "TRTCStatistics.h"
#include "TXLiteAVCode.h"

class ITRTCCloudCallback
{
public:
    virtual ~ITRTCCloudCallback() {}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      （一）通用事件回调
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name 通用事件回调
    /// @{
    /**
    * \brief 1.1 错误回调，SDK不可恢复的错误，一定要监听，并分情况给用户适当的界面提示
    *
    * \param errCode 错误码
    * \param errMsg 错误信息
    * \param arg 保留参数
    */
    virtual void onError(TXLiteAVError errCode, const char* errMsg, void* arg) = 0;

    /**
    * \brief 1.2 警告回调
    *
    * \param warningCode 错误码
    * \param warningMsg 警告信息
    * \param arg 保留参数
    */
    virtual void onWarning(TXLiteAVWarning warningCode, const char* warningMsg, void* arg) = 0;
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      （二）房间事件回调
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name 房间事件回调
    /// @{
    /**
    * \brief 2.1 进房成功通知
    *
    * \param elapsed 进房耗时
    */
    virtual void onEnterRoom(uint64_t elapsed) = 0;

    /**
    * \brief 2.2 退房通知
    *
    * \param reason 退出原因
    */
    virtual void onExitRoom(int reason) = 0;
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      （三）成员事件回调
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name 成员事件回调
    /// @{
    /**
    * \brief 3.1 房间成员进房通知，在这个回调中调用 startRemoteView 接口
    *
    * \param userId 用户标识
    */
    virtual void onUserEnter(const char* userId) = 0;

    /**
    * \brief 3.2 房间成员退房通知，在这个回调中调用 stopRemoteView 接口
    *
    * \param userId 用户标识
    * \param reason 退出原因
    */
    virtual void onUserExit(const char* userId, int reason) = 0;

    /**
    * \brief 3.3 远端用户屏蔽自己的画面
    *
    * \param userId 用户标识
    * \param available true：视频可播放，false：视频被关闭
    */
    virtual void onUserVideoAvailable(const char* userId, bool available) {}

    /**
    * \brief 3.4 远端用户屏蔽自己的声音
    *
    * \param userId 用户标识
    * \param available true：音频可播放，false：音频被关闭
    */
    virtual void onUserAudioAvailable(const char* userId, bool available) {}

    /**
    * \brief 3.5 成员语音音量回调，通过调用 TRTCCloud enableAudioVolumeEvaluation 来触发这个回调
    *
    * \param userVolumes  每位发言者的语音音量，取值范围 [0, 100]
    * \param userVolumesCount  发言者的人数，即userVolumes数组的大小
    * \param totalVolume  总的语音音量, 取值范围 [0, 100]
    */
    virtual void onUserVoiceVolume(TRTCVolumeInfo* userVolumes, uint32_t userVolumesCount, uint32_t totalVolume) {}
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      （四）统计和质量回调
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name 统计和质量回调
    /// @{
    /**
    * \brief 4.1 网络质量: 该回调每 2 秒触发一次，统计当前网络的上行和下行质量
    *
    * \param localQuality 上行网络质量
    * \param remoteQuality 下行网络质量的数组
    * \param remoteQualityCount 下行网络质量的数组大小
    */
    virtual void onNetworkQuality(TRTCQualityInfo localQuality, TRTCQualityInfo* remoteQuality, uint32_t remoteQualityCount) {}

    /**
    * \brief 4.2 技术指标统计回调，每2秒回调一次
    *
    *     如果您是熟悉音视频领域相关术语，可以通过这个回调获取SDK的所有技术指标，
    *     如果您是首次开发音视频相关项目，可以只关注 onNetworkQuality 回调
    * \param statis 状态数据
    */
    virtual void onStatistics(const TRTCStatistics& statis) {}
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      （五）音视频事件回调
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name 音视频事件回调
    /// @{
    /**
    * \brief 5.1 首帧视频画面到达，界面此时可以结束loading，并开始显示视频画面
    *
    * \param userId 用户标识
    * \param width  画面宽度
    * \param height 画面高度
    */
    virtual void onFirstVideoFrame(const char* userId, uint32_t width, uint32_t height) {}

    /**
    * \brief 5.2 首帧音频数据到达
    *
    * \param userId 用户标识
    */
    virtual void onFirstAudioFrame(const char* userId) {}

    /**
    * \brief 5.3 开始播放背景音乐
    *
    * \param errCode 错误码
    */
    virtual void onPlayBGMBegin(TXLiteAVError errCode) {}

    /**
    * \brief 5.3 播放背景音乐的进度
    *
    * \param progressMS 已播放时间
    * \param durationMS 总时间
    */
    virtual void onPlayBGMProgress(uint32_t progressMS, uint32_t durationMS) {}

    /**
    * \brief 5.4 播放背景音乐结束
    *
    * \param errCode 错误码
    */
    virtual void onPlayBGMComplete(TXLiteAVError errCode) {}
    /// @}
    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      （六）服务器事件回调
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name 服务器事件回调
    /// @{
    /**
    * \brief 6.1 SDK 跟服务器的连接断开
    */
    virtual void onConnectionLost() {}

    /**
    * \brief 6.2 SDK 尝试重新连接到服务器
    */
    virtual void onTryToReconnect() {}

    /**
    * \brief 6.3 SDK 跟服务器的连接恢复
    */
    virtual void onConnectionRecovery() {}

    /**
    * \brief 6.4 服务器测速的回调，SDK 对多个服务器IP做测速，每个IP的测速结果通过这个回调通知
    *
    * \param currentResult 当前完成的测速结果
    * \param finishedCount 已完成测速的服务器数量
    * \param totalCount 需要测速的服务器总数量
    */
    virtual void onSpeedTest(const TRTCSpeedTestResult& currentResult, uint32_t finishedCount, uint32_t totalCount) {}
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      （七）硬件设备事件回调
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name 硬件设备事件回调
    /// @{
    /**
    * \brief 7.1 摄像头准备就绪，表示摄像头打开成功，如果打开失败，在 onError 中通知
    */
    virtual void onCameraDidReady() {}

    /**
    * \brief 7.2 麦克风准备就绪
    */
    virtual void onMicDidReady() {}

    /**
    * \brief 7.3 设备事件的回调
    *
    * \param deviceId 设备ID
    * \param type 设备类型
    * \param state 事件类型
    */
    virtual void onDeviceChange(const char* deviceId, TRTCDeviceType type, TRTCDeviceState state) {}

    /**
    * \brief 7.4 麦克风测试音量回调，麦克风测试接口 startMicDeviceTest 会触发这个回调
    *
    * \param volume 音量值，取值范围 [0, 100]
    */
    virtual void onTestMicVolume(uint32_t volume) {}

    /**
    * \brief 7.5 扬声器测试音量回调，扬声器测试接口 startSpeakerDeviceTest 会触发这个回调
    *
    * \param volume 音量值，取值范围 [0, 100]
    */
    virtual void onTestSpeakerVolume(uint32_t volume) {}
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      （八）自定义消息的接收回调
	//
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name 自定义消息的接收回调
    /// @{
    /**
    * \brief 8.1 当房间中的某个用户使用 sendCustomCmdMsg 发送自定义消息时，房间中的其它用户可以通过 onRecvCustomCmdMsg 接口接收消息
    *
    * \param userId 用户标识
    * \param cmdId 命令ID
    * \param seq   消息序号
    * \param msg 消息数据
    * \param msgSize 消息数据大小
    */
    virtual void onRecvCustomCmdMsg(const char* userId, int32_t cmdId, uint32_t seq, const uint8_t* msg, uint32_t msgSize) {}

    /**
    * \brief 8.2 TRTC所使用的传输通道为UDP通道，所以即使设置了 reliable，也做不到100%不丢失，只是丢消息概率极低，能满足常规可靠性要求。
    * \brief 在过去的一段时间内（通常为5s），自定义消息在传输途中丢失的消息数量的统计，SDK 都会通过此回调通知出来
    *
    * \param userId 用户标识
    * \param cmdId 命令ID
    * \param errCode 错误码，当前版本为-1
    * \param missed 丢失的消息数量
    * \note  只有在发送端设置了可靠传输(reliable)，接收方才能收到消息的丢失回调
    */
    virtual void onMissCustomCmdMsg(const char* userId, int32_t cmdId, int32_t errCode, int32_t missed) {}
    /// @}

    /////////////////////////////////////////////////////////////////////////////////
    //
    //                      （九）旁路转推和混流回调
    //
    /////////////////////////////////////////////////////////////////////////////////
    /// @name 旁路转推和混流回调
    /// @{
    /**
    * \brief 9.1 接口startPublishCDNStream的状态回调
    *
    * \param errCode 错误码，参考 TXLiteAVCode.h
    * \param errMsg  错误详细信息
    */
    void onStartPublishCDNStream(int errCode, const char* errMsg) {};

    /**
    * \brief 9.2 接口stopPublishCDNStream的状态回调
    *
    * \param errCode 错误码，参考 TXLiteAVCode.h
    * \param errMsg  错误详细信息
    */
    void onStopPublishCDNStream(int errCode, const char* errMsg) {};

    /**
    * \brief 9.3 接口startCloudMixTranscoding的状态回调
    *
    * \param errCode 错误码，参考 TXLiteAVCode.h
    * \param errMsg  错误详细信息
    */
    void onStartCloudMixTranscoding(int errCode, const char* errMsg) {};

    /**
    * \brief 9.3 接口stopCloudMixTranscoding的状态回调
    *
    * \param errCode 错误码，参考 TXLiteAVCode.h
    * \param errMsg  错误详细信息
    */
    void onStopCloudMixTranscoding(int errCode, const char* errMsg) {};
    /// @}
};


/////////////////////////////////////////////////////////////////////////////////
//
//                      （十）自定义音视频处理
//
/////////////////////////////////////////////////////////////////////////////////

class ITRTCVideoRenderCallback
{
public:
    virtual ~ITRTCVideoRenderCallback() {}
    /// @name 自定义视频的渲染回调
    /// @{
    /**
    * \brief 10.1 可以通过 setLocalVideoRenderCallback 和 setRemoteVideoRenderCallback 接口设置自定义渲染回调
    *
    * \param userId     用户标识
    * \param streamType	流类型：即摄像头还是屏幕分享
    * \param frame      视频帧数据
    */
    virtual void onRenderVideoFrame(const char* userId, TRTCVideoStreamType streamType, TRTCVideoFrame* frame) {}
    /// @}
};

class ITRTCVideoPreprocessCallback
{
public:
    virtual ~ITRTCVideoPreprocessCallback() {}
    /// @name 本地视频的二次加工回调
    /// @{
    /**
    * \brief 10.2 经过 SDK 前处理后的视频数据，前处理包括对摄像头采集到的视频进行美颜、裁剪、缩放和旋转
    *
    * \param textureId     回调的 OpenGL 纹理ID
    * \param width         画面宽度
    * \param height        画面长度
    * \param streamType    流类型：即摄像头还是屏幕分享
    * \attention 返回用户自定义预处理后的纹理 textureId; 需要判断当前的 streamType 大画面视频流、小画面视频流、辅流（屏幕分享）
    */
    virtual int onVideoPreprocessFrame(int textureId, int width, int height, TRTCVideoStreamType streamType)
    {
        return textureId;
    }
    /// @}
};

/////////////////////////////////////////////////////////////////////////////////
//
//                      （十一）Log 信息回调
//
/////////////////////////////////////////////////////////////////////////////////

class ITRTCLogCallback
{
public:
    virtual ~ITRTCLogCallback() {}
    /// @name Log 信息回调
    /// @{
    /**
    * \brief 11.1 日志回调
    *
    * \param log 日志内容
    * \param level 日志类型
    * \param module 暂无具体意义，目前为固定值TXLiteAVSDK
    */
    virtual void onLog(const char* log, TRTCLogLevel level, const char* module) {}
    /// @}
};

#endif /* __TRTCENGINECALLBACK_H__ */
