/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QAudioProbe>
#include <QAudioRecorder>
#include <QDir>
#include <QFileDialog>
#include <QMediaRecorder>
#include <QtCore>
#include <QTime>
#include <QAudioDeviceInfo>
#include "basehelper.h"
#include "audiorecorder.h"
#include "qaudiolevel.h"
#include "../aliyun/cossupdate.h"
#include "JlCompress.h"
//static qreal getPeakValue(const QAudioFormat &format);
//static QVector<qreal> getBufferLevels(const QAudioBuffer &buffer);

template <class T>
static QVector<qreal> getBufferLevels(const T *buffer, int frames, int channels);

AudioRecorder::AudioRecorder()
{
    outputLocationSet =false;
    audioRecorder = new QAudioRecorder(this);
}

AudioRecorder::~AudioRecorder()
{
    delete audioRecorder;
}

void AudioRecorder::updateProgress(qint64 duration)
{
    if (audioRecorder->error() != QMediaRecorder::NoError || duration < 2000)
        return;
    qDebug()<< tr("Recorded %1 sec").arg(duration / 1000);
}

int AudioRecorder::recvAudioInfo(const QByteArray &messagee)
{

    // 取消掉接收函数
#if 0
    WebAudioData info;
    int ret = BaseHelper::getWebInfo(messagee,&info);
    if(ret < 0 ){
        return -1;
    }
    // 开始录音
    if(1 == info.code)
    {
       startRecorder(info);
    }else if(2 == info.code)
    {
        stopRecorder();
    }
#endif
    return 0;
}


void AudioRecorder::updateStatus(QMediaRecorder::Status status)
{
   // QString statusMessage;

    switch (status) {
    case QMediaRecorder::RecordingStatus:
        // 文件保存位置
        qDebug()<< tr("文件保存为： %1").arg(audioRecorder->actualLocation().toString());
        break;
    case QMediaRecorder::PausedStatus:
        qDebug()<< tr("暂停");
        break;
    case QMediaRecorder::UnloadedStatus:
    case QMediaRecorder::LoadedStatus:
        qDebug()<< tr("停止");
    default:
        break;
    }
}

// 压缩上传阿里云
int AudioRecorder::AudioComPress(QString order_id)
{
     QString srcFile = m_Audiofile;

     QString filePath = QCoreApplication::applicationDirPath() + "/audioFile" + QString("/zipFile");
  //    qDebug() << "file path:" << filePath;
      QDir tempDir;
     //如果filePath路径不存在，创建它
     if(!tempDir.exists(filePath))
     {
         qDebug()<<"创建路径"<<endl;
         tempDir.mkpath(filePath);
     }
     QString localObjName =m_objfile + ".zip";
     QString fileName =filePath +"/"+ localObjName;

    JlCompress::compressFile(fileName,srcFile);
    // 上传阿里云
   //  QString testfile = QStringLiteral(BUILD_DIR"/index.html");
   //  qDebug() << "start emit COSS";
    QDateTime current_time = QDateTime::currentDateTime();
    QString year = current_time.toString("yyyy");
    QString month = current_time.toString("MM");
    QString day = current_time.toString("dd");
    QString AliObjName = QString::number(BaseHelper::GetHospitalId()) + "/" + year +"/" + month + "/" \
            +day + "/" + m_objfile + ".zip";
    qDebug() << AliObjName;
    emit COSSUpdate::instance()->emit_OSSUpload(fileName, AliObjName,order_id);

    //COSSUpdate::instance()->OSSUpload(fileName);
    return 0;
}



int AudioRecorder::stopRecorder(const QByteArray &message)
{
    WebAudioData info;
    int ret = BaseHelper::getWebInfo(message,&info);
    if(ret < 0 ){
        return -1;
    }
    audioRecorder->stop();
    // 开始压缩软件
    AudioComPress(info.order_id);
    return 0;

}
int AudioRecorder::startRecorder(const QByteArray &message)
{
    WebAudioData info;
    int ret = BaseHelper::getWebInfo(message,&info);
    if(ret < 0 ){
        return -1;
    }
    m_Audiofile = "";
    QString timeString = QString::number(BaseHelper::getTimeStamp(), 10);//nowTime.toString();
    //QString timeString = BaseHelper::getStrTime();
    QString Name = timeString +"_" +QString::number(info.user_id) + ".wav";
    m_objfile = Name;
    setOutputLocation(Name);
    // 设置录音名字
    toggleRecord();
    return 0;
}




// 切换开始录音函数
void AudioRecorder::toggleRecord()
{
    foreach (const QString &device, audioRecorder->audioInputs()) {
        qDebug() << device;
    }
    audioRecorder->setAudioInput(audioRecorder->defaultAudioInput());
    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/amr");
  //  audioSettings.setSampleRate(16000);
   // audioSettings.setBitRate(16);
   // audioSettings.setChannelCount(1);
    audioSettings.setQuality(QMultimedia::HighQuality);
    audioSettings.setEncodingMode(QMultimedia::ConstantQualityEncoding);
    audioRecorder->setEncodingSettings(audioSettings);
    audioRecorder->record();
}

// 停止录音
void AudioRecorder::togglePause()
{
    return ;
}

//创建文件输出位置
void AudioRecorder::setOutputLocation(QString Name)
{
    QString filePath = QCoreApplication::applicationDirPath() + "/audioFile" + QString("/wavFile");
  //   qDebug() << "file path:" << filePath;


     QDir tempDir;
    //如果filePath路径不存在，创建它
    if(!tempDir.exists(filePath))
    {
        qDebug()<<"创建路径"<<endl;
        tempDir.mkpath(filePath);
    }

    QString fileName =filePath +"/"+ Name;
 //   qDebug() << "fileName:" << fileName;
    m_Audiofile = fileName;
    audioRecorder->setOutputLocation(QUrl::fromLocalFile(fileName));
    outputLocationSet = true;
}
