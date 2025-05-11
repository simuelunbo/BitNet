#pragma once

#ifndef BITNET_ANDROID_H
#define BITNET_ANDROID_H

#ifdef __cplusplus
extern "C" {
#endif

// Android 로그 시스템이 정의되지 않은 경우에 대비
#ifndef LOGW
#include <android/log.h>
#define LOG_TAG "BitNetNative"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#endif

// 비트넷 컨텍스트 구조체 정의
typedef struct _bitnet_context {
    // 실제 llama.cpp context와 model을 담을 포인터
    void* llama_model;
    void* llama_context;
    // 필요한 기타 상태 변수들
    int n_threads;
    bool is_initialized;
    // C 호환성을 위한 마지막 생성 텍스트 저장
    char last_generated_text[256];
} bitnet_context;

// 모델 파일로부터 비트넷 초기화
// modelPath: 모델 파일 경로
// n_threads: 사용할 스레드 수
bitnet_context* bitnet_init_from_file(const char* modelPath, int n_threads);

// 다음 토큰 생성 함수 (C 호환 버전)
const char* bitnet_generate_next(bitnet_context* ctx);

// 리소스 해제
void bitnet_free(bitnet_context* ctx);

#ifdef __cplusplus
} // extern "C"
#endif

// C++ 전용 구현 부분
#ifdef __cplusplus
#include <string>

// 실제 BitNet 구현 (C++로만 접근)
namespace bitnet {
    // 내부 구현에 사용할 헬퍼 함수
    std::string generate_token_internal(bitnet_context* ctx);
}
#endif

#endif // BITNET_ANDROID_H
