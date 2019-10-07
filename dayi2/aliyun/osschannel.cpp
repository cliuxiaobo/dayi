#include "./osschannel.h"
#include <QThread>
#pragma comment(lib,"ws2_32.lib")

const char *endpoint = "oss-cn-hangzhou-internal.aliyuncs.com";
const char *access_key_id = "LTAI4FxjHuSamfyYck98M5Lo";
const char *access_key_secret = "458ROGuRLDgSzqaz53V3lyKyMnYelg";
const char *bucket_name = "dayi-audio-file";
const char *object_name = "123.wav";
const char *local_filename = "E:\1.json";

OssChannel::OssChannel()
{
     qDebug()<<"sart OssChannel";
    aos_pool_create(&pool, NULL);
     oss_client_options = oss_request_options_create(pool);
    oss_client_options->config = oss_config_create(oss_client_options->pool);
    /* 用char*类型的字符串初始化aos_string_t类型。*/
    aos_str_set(&oss_client_options->config->endpoint, endpoint);
    aos_str_set(&oss_client_options->config->access_key_id, access_key_id);
    aos_str_set(&oss_client_options->config->access_key_secret, access_key_secret);
    /* 是否使用了CNAME。0表示不使用。*/
    oss_client_options->config->is_cname = 0;
    /* 设置网络相关参数，比如超时时间等。*/
    oss_client_options->ctl = aos_http_controller_create(oss_client_options->pool, 0);
}

OssChannel::~OssChannel()
{
    aos_pool_destroy(pool);
}

int OssChannel::PushFile(QString file)
{
    aos_string_t bucket;
    aos_string_t object;
    aos_string_t file1;
    aos_table_t *headers = NULL;
    aos_table_t *resp_headers = NULL;
    aos_status_t *resp_status = NULL;
    aos_str_set(&bucket, bucket_name);
    aos_str_set(&object, object_name);
    aos_str_set(&file1, local_filename);
    /* 上传文件。*/
    resp_status = oss_put_object_from_file(oss_client_options, &bucket, &object, &file1, headers, &resp_headers);
    /* 判断上传是否成功。*/
    if (aos_status_is_ok(resp_status)) {
        printf("put object from file succeeded\n");
    } else {
        printf("put object from file failed\n");
    }
    return 0;
}
