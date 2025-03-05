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
        # ��ȡ������Ƶ�ļ���ת��ΪBase64
        with open(audio_file, "rb") as f:
            audio_data = base64.b64encode(f.read()).decode("utf-8")
        # ʵ����һ����֤���������Ҫ������Ѷ���˻� SecretId �� SecretKey���˴�����ע����Կ�Եı���
        # ����й¶���ܻᵼ�� SecretId �� SecretKey й¶������в�˺���������Դ�İ�ȫ�ԡ����´���ʾ�������ο���������ø���ȫ�ķ�ʽ��ʹ����Կ����μ���https://cloud.tencent.com/document/product/1278/85305
        # ��Կ��ǰ����������̨ https://console.cloud.tencent.com/cam/capi ���л�ȡ
        cred = credential.Credential(SecretId, SecretKey)
        # ʵ����һ��httpѡ���ѡ�ģ�û�����������������
        httpProfile = HttpProfile()
        httpProfile.endpoint = "asr.tencentcloudapi.com"

        # ʵ����һ��clientѡ���ѡ�ģ�û�����������������
        clientProfile = ClientProfile()
        clientProfile.httpProfile = httpProfile
        # ʵ����Ҫ�����Ʒ��client����,clientProfile�ǿ�ѡ��
        client = asr_client.AsrClient(cred, "", clientProfile)

        # ʵ����һ���������,ÿ���ӿڶ����Ӧһ��request����
        req = asrmodels.SentenceRecognitionRequest()
        params = {
            "EngSerViceType": "16k_en",
            "SourceType": 1,
            "VoiceFormat": "wav",
            "Data": audio_data,
            "DataLen": len(audio_data)
        }
        req.from_json_string(json.dumps(params))

        # ���ص�resp��һ��SentenceRecognitionResponse��ʵ��������������Ӧ
        resp = client.SentenceRecognition(req)
        # ���json��ʽ���ַ����ذ�
        #print(resp.to_json_string())
        return resp.Result

    except TencentCloudSDKException as err:
        print(err)
def text2wav(text, SecretId, SecretKey, savefile):
    try:
        # ʵ����һ����֤���������Ҫ������Ѷ���˻� SecretId �� SecretKey���˴�����ע����Կ�Եı���
        # ����й¶���ܻᵼ�� SecretId �� SecretKey й¶������в�˺���������Դ�İ�ȫ�ԡ����´���ʾ�������ο���������ø���ȫ�ķ�ʽ��ʹ����Կ����μ���https://cloud.tencent.com/document/product/1278/85305
        # ��Կ��ǰ����������̨ https://console.cloud.tencent.com/cam/capi ���л�ȡ
        cred = credential.Credential(SecretId, SecretKey)
        # ʵ����һ��httpѡ���ѡ�ģ�û�����������������
        httpProfile = HttpProfile()
        httpProfile.endpoint = "tts.tencentcloudapi.com"

        # ʵ����һ��clientѡ���ѡ�ģ�û�����������������
        clientProfile = ClientProfile()
        clientProfile.httpProfile = httpProfile
        # ʵ����Ҫ�����Ʒ��client����,clientProfile�ǿ�ѡ��
        client = tts_client.TtsClient(cred, "", clientProfile)

        # ʵ����һ���������,ÿ���ӿڶ����Ӧһ��request����
        req = ttsmodels.TextToVoiceRequest()
        params = {
            "Text": text,
            "SessionId": "session-123456",
            "PrimaryLanguage": 2
        }
        req.from_json_string(json.dumps(params))

        # ���ص�resp��һ��TextToVoiceResponse��ʵ��������������Ӧ
        resp = client.TextToVoice(req)
        with open(savefile, "wb") as f:
            f.write(base64.b64decode(resp.Audio))
        # ���json��ʽ���ַ����ذ�
        #print(resp.to_json_string())


    except TencentCloudSDKException as err:
        print(err)
def record_audio(filename, fs=16000):
    """
    ¼����Ƶ������ΪWAV�ļ�
    :param filename: ������ļ������� "output.wav"��
    :param fs: ����Ƶ�ʣ�Ĭ��16000Hz��
    """
    print("���»س�����ʼ¼��...")
    input()  # �ȴ��û����»س���
    print("¼����... ���»س���ֹͣ¼��")

    # ����һ����־λ�����ڿ���¼����ֹͣ
    stop_recording = False

    def callback(indata, frames, time, status):
        """
        ¼���ص�������������д���б�
        """
        nonlocal stop_recording
        if stop_recording:
            raise sd.CallbackStop  # ֹͣ¼��
        recording.append(indata.copy())  # ����Ƶ������ӵ��б���

    # ��ʼ��¼�������б�
    recording = []

    # ��ʼ¼������������16000Hz�����ʣ�
    with sd.InputStream(samplerate=fs, channels=1, dtype='int16', callback=callback):
        input()  # �ȴ��û����»س���
        stop_recording = True  # ���ñ�־λ��ֹͣ¼��

    # ��¼������ת��ΪNumPy����
    # ������������ҪչƽΪһά����
    recording = np.concatenate(recording, axis=0).flatten()

    # ����¼��ΪWAV�ļ�
    write(filename, fs, recording)
    print(f"¼���ѱ���Ϊ {filename}")

def play_audio(filename):
    """
    ����WAV�ļ�
    :param filename: Ҫ���ŵ�WAV�ļ������� "output.wav"��
    """
    # ��ȡWAV�ļ�
    fs, data = read(filename)

    print("��ʼ����...")
    sd.play(data, fs)
    sd.wait()  # �ȴ��������
    print("���Ž���")

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
    # ģ���б�https://help.aliyun.com/zh/model-studio/getting-started/models
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
        print(f"assistant��{assistant_output}")
        # ÿ��TTS����̫���������и�Ϊ���ת���Ͳ���
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
        # ����ģ�͵Ļظ���Ϣ��ӵ�messages�б���
        messages.append({"role": "assistant", "content": assistant_output})

chat_with_AI()
