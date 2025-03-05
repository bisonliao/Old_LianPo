import json
import types
from tencentcloud.common import credential
from tencentcloud.common.profile.client_profile import ClientProfile
from tencentcloud.common.profile.http_profile import HttpProfile
from tencentcloud.common.exception.tencent_cloud_sdk_exception import TencentCloudSDKException
from tencentcloud.asr.v20190614 import asr_client
from tencentcloud.asr.v20190614 import models as asrmodels
import base64
from tencentcloud.tts.v20190823 import tts_client
from tencentcloud.tts.v20190823 import  models as ttsmodels
import sounddevice as sd
import numpy as np
from scipy.io.wavfile import write, read
import os
from openai import OpenAI

'''
# install dependency
pip3 install openai
pip install --upgrade tencentcloud-sdk-python-tts
pip install --upgrade tencentcloud-sdk-python-asr
pip install --upgrade tencentcloud-sdk-python-common
'''


# set the proper key to use tencent cloud ASR and TTS
SecretId = "AKIDjTZq"
SecretKey = "itxoa"
# set the proper key to use aliyun TONGYI
BaiLianKey = "sk-c4"

def recognize(audio_file, SecretId, SecretKey):
    try:
        # 读取本地音频文件并转换为Base64
        with open(audio_file, "rb") as f:
            audio_data = base64.b64encode(f.read()).decode("utf-8")
        # 实例化一个认证对象，入参需要传入腾讯云账户 SecretId 和 SecretKey，此处还需注意密钥对的保密
        # 代码泄露可能会导致 SecretId 和 SecretKey 泄露，并威胁账号下所有资源的安全性。以下代码示例仅供参考，建议采用更安全的方式来使用密钥，请参见：https://cloud.tencent.com/document/product/1278/85305
        # 密钥可前往官网控制台 https://console.cloud.tencent.com/cam/capi 进行获取
        cred = credential.Credential(SecretId, SecretKey)
        # 实例化一个http选项，可选的，没有特殊需求可以跳过
        httpProfile = HttpProfile()
        httpProfile.endpoint = "asr.tencentcloudapi.com"

        # 实例化一个client选项，可选的，没有特殊需求可以跳过
        clientProfile = ClientProfile()
        clientProfile.httpProfile = httpProfile
        # 实例化要请求产品的client对象,clientProfile是可选的
        client = asr_client.AsrClient(cred, "", clientProfile)

        # 实例化一个请求对象,每个接口都会对应一个request对象
        req = asrmodels.SentenceRecognitionRequest()
        params = {
            "EngSerViceType": "16k_en",
            "SourceType": 1,
            "VoiceFormat": "wav",
            "Data": audio_data,
            "DataLen": len(audio_data)
        }
        req.from_json_string(json.dumps(params))

        # 返回的resp是一个SentenceRecognitionResponse的实例，与请求对象对应
        resp = client.SentenceRecognition(req)
        # 输出json格式的字符串回包
        #print(resp.to_json_string())
        return resp.Result

    except TencentCloudSDKException as err:
        print(err)
def text2wav(text, SecretId, SecretKey, savefile):
    try:
        # 实例化一个认证对象，入参需要传入腾讯云账户 SecretId 和 SecretKey，此处还需注意密钥对的保密
        # 代码泄露可能会导致 SecretId 和 SecretKey 泄露，并威胁账号下所有资源的安全性。以下代码示例仅供参考，建议采用更安全的方式来使用密钥，请参见：https://cloud.tencent.com/document/product/1278/85305
        # 密钥可前往官网控制台 https://console.cloud.tencent.com/cam/capi 进行获取
        cred = credential.Credential(SecretId, SecretKey)
        # 实例化一个http选项，可选的，没有特殊需求可以跳过
        httpProfile = HttpProfile()
        httpProfile.endpoint = "tts.tencentcloudapi.com"

        # 实例化一个client选项，可选的，没有特殊需求可以跳过
        clientProfile = ClientProfile()
        clientProfile.httpProfile = httpProfile
        # 实例化要请求产品的client对象,clientProfile是可选的
        client = tts_client.TtsClient(cred, "", clientProfile)

        # 实例化一个请求对象,每个接口都会对应一个request对象
        req = ttsmodels.TextToVoiceRequest()
        params = {
            "Text": text,
            "SessionId": "session-123456",
            "PrimaryLanguage": 2
        }
        req.from_json_string(json.dumps(params))

        # 返回的resp是一个TextToVoiceResponse的实例，与请求对象对应
        resp = client.TextToVoice(req)
        with open(savefile, "wb") as f:
            f.write(base64.b64decode(resp.Audio))
        # 输出json格式的字符串回包
        #print(resp.to_json_string())


    except TencentCloudSDKException as err:
        print(err)
def record_audio(filename, fs=16000):
    """
    录制音频并保存为WAV文件
    :param filename: 保存的文件名（如 "output.wav"）
    :param fs: 采样频率（默认16000Hz）
    """
    print("按下回车键开始录音...")
    input()  # 等待用户按下回车键
    print("录音中... 按下回车键停止录音")

    # 创建一个标志位，用于控制录音的停止
    stop_recording = False

    def callback(indata, frames, time, status):
        """
        录音回调函数，将数据写入列表
        """
        nonlocal stop_recording
        if stop_recording:
            raise sd.CallbackStop  # 停止录音
        recording.append(indata.copy())  # 将音频数据添加到列表中

    # 初始化录音数据列表
    recording = []

    # 开始录音（单声道，16000Hz采样率）
    with sd.InputStream(samplerate=fs, channels=1, dtype='int16', callback=callback):
        input()  # 等待用户按下回车键
        stop_recording = True  # 设置标志位，停止录音

    # 将录音数据转换为NumPy数组
    # 单声道数据需要展平为一维数组
    recording = np.concatenate(recording, axis=0).flatten()

    # 保存录音为WAV文件
    write(filename, fs, recording)
    print(f"录音已保存为 {filename}")

def play_audio(filename):
    """
    播放WAV文件
    :param filename: 要播放的WAV文件名（如 "output.wav"）
    """
    # 读取WAV文件
    fs, data = read(filename)

    print("开始播放...")
    sd.play(data, fs)
    sd.wait()  # 等待播放完成
    print("播放结束")

messages = [
        {
            "role": "system",
            "content":
                """you are a mentor at graduate school, now you are discuss with a young graduate student.
                   you can give him advice or challenge him with scolar quesytions.""",
        }
    ]


def get_response(messages):
    client = OpenAI(
        api_key=BaiLianKey,
        base_url="https://dashscope.aliyuncs.com/compatible-mode/v1",
    )
    # 模型列表：https://help.aliyun.com/zh/model-studio/getting-started/models
    completion = client.chat.completions.create(model="qwen-plus", messages=messages)
    return completion

def chat_with_AI():
    while True:
        filename = "output.wav"
        record_audio(filename)
        text = recognize(filename, SecretId, SecretKey)
        print(f"user:{text}\n")
        messages.append({"role": "user", "content": text})
        assistant_output = get_response(messages).choices[0].message.content
        print(f"assistant：{assistant_output}")
        # 每次TTS不能太长，所以切割为多次转化和播放
        words = assistant_output.split()
        start = 0
        while start < len(words):
            end = start+50
            if end > len(words):
                end = len(words)

            subtext = " ".join([w for w in words[start:end]])
            text2wav(subtext, SecretId, SecretKey, filename)
            play_audio(filename)
            start = end
        # 将大模型的回复信息添加到messages列表中
        messages.append({"role": "assistant", "content": assistant_output})

chat_with_AI()
