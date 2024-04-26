#include "mcc_generated_files/system/system.h"
#include "wav_data.h"
#include "score.h"


// 間引き間隔のテーブル。88鍵のピアノと同じ音域。
uint16_t tone_step[88] = {
    112, 119, 126, 133, 141, 150, 159, 168, 178, 189, 200, 212, 225, 238, 252,
    267, 283, 300, 318, 337, 357, 378, 401, 425, 450, 477, 505, 535, 567, 601,
    637, 675, 715, 757, 802, 850, 901, 954, 1011, 1071, 1135, 1202, 1274, 1350,
    1430, 1515, 1605, 1701, 1802, 1909, 2022, 2143, 2270, 2405, 2548, 2700, 2860,
    3030, 3211, 3402, 3604, 3818, 4045, 4286, 4541, 4811, 5097, 5400, 5721, 6061,
    6422, 6804, 7208, 7637, 8091, 8572, 9082, 9622, 10195, 10801, 11443, 12123,
    12844, 13608, 14417, 15275, 16183, 17145
};

// 楽譜の読み取りインデックス
uint16_t score_index = 1;
// 楽譜のポインタ
uint8_t *score;

// 4ch分の音程を保持
uint8_t tone[4] = {0, 0, 0, 0};
// 4ch分のノートオンを保持
bool start[4] = {false, false, false, false};

// 割り込みフラグ
bool fs_flag = false;
bool env_flag = false;

// サンプリング周波数で割り込み(32kHz)
void Fs() {
    static uint16_t theta1 = 0;
    static uint16_t i1 = 255;

    static uint16_t theta2 = 0;
    static uint16_t i2 = 255;

    static uint16_t theta3 = 0;
    static uint16_t i3 = 255;

    static uint16_t theta4 = 0;
    static uint16_t i4 = 255;

    if (start[0]) {
        theta1 = 0;
        i1 = 0;
        start[0] = false;
    }
    if (start[1]) {
        theta2 = 0;
        i2 = 0;
        start[1] = false;
    }
    if (start[2]) {
        theta3 = 0;
        i3 = 0;
        start[2] = false;
    }
    if (start[3]) {
        theta4 = 0;
        i4 = 0;
        start[3] = false;
    }

    if (env_flag && i1 != 255) {
        i1++;
    }
    if (env_flag && i2 != 255) {
        i2++;
    }
    if (env_flag && i3 != 255) {
        i3++;
    }
    if (env_flag && i4 != 255) {
        i4++;
    }

    theta1 += tone_step[tone[0]];
    theta2 += tone_step[tone[1]];
    theta3 += tone_step[tone[2]];
    theta4 += tone_step[tone[3]];

    uint8_t t1 = theta1 >> 8;
    uint8_t t2 = theta2 >> 8;
    uint8_t t3 = theta3 >> 8;
    uint8_t t4 = theta4 >> 8;

    uint16_t data = 0;
    uint16_t tmp = sin_table[t1] * env_table2[i1];
    data = tmp >> 8;
    tmp = sin_table[t2] * env_table2[i2];
    data += tmp >> 8;
    tmp = sin_table[t3] * env_table2[i3];
    data += tmp >> 8;
    tmp = sin_table[t4] * env_table2[i4];
    data += tmp >> 8;

    PWM1S1P1H = 0;
    PWM1S1P1L = (uint8_t) (data >> 4);
    PWM1CONbits.LD = 1;
    env_flag = false;
}

// エンベロープインデックス増加用割り込み(125Hz)
void Env() {
    env_flag = true;
}

// 楽譜の処理(任意周波数)
void Score() {
    static uint8_t part_n;
    static uint8_t bpm;
    static uint8_t div;

    if (score_index == 0) {
        score_index = 1;
    }

    // パート数読み取り
    if (score_index == 1) {
        part_n = score[0];
    }

    // 楽譜の解釈
    uint8_t cmd = score[score_index];
    switch (cmd) {
        case 90:// 最小分割音価
            score_index++;
            if (score[score_index] == 0)
                div = 1; //4分
            else if (score[score_index] == 1)
                div = 2; //8分
            else if (score[score_index] == 1)
                div = 4; //16分
            else
                div = 8; //32分
            score_index++;
            break;
        case 91:// 終了
            break;
        case 92:// テンポ設定
            score_index++;
            bpm = score[score_index] << 8;
            score_index++;
            bpm += score[score_index];
            score_index++;
            ScoreTMR_Stop();
            ScoreTMR_PeriodCountSet((uint8_t) (7265.625 / (float) bpm / (float) div));
            ScoreTMR_Write(0);
            ScoreTMR_Start();
            break;
        case 93:// 任意インデックスへジャンプ
            score_index++;
            uint16_t tmp = score[score_index] << 8;
            score_index++;
            tmp += score[score_index];
            score_index = tmp;
            break;
        default:// 音符の読み取り
            for (int8_t i = 0; i < part_n; i++) {
                if (cmd != 0) {
                    tone[i] = cmd - 1;
                    start[i] = true;
                }
                score_index++;
                cmd = score[score_index];
            }
    }
}

// 選曲用スイッチ割り込み
void SW_Next() {
    static uint8_t i = 1;
    uint8_t score_num = 2;
    uint8_t * score_list[] = {
        hotaru,
        ChopinWalzer
    };
    score = score_list[i % score_num];
    score_index = 0;
    i++;
    __delay_ms(10);
}

int main(void) {
    SYSTEM_Initialize();

    INTERRUPT_GlobalInterruptEnable();

    SW_Next_SetInterruptHandler(SW_Next);
    ScoreTMR_OverflowCallbackRegister(Score);
    FsTMR_OverflowCallbackRegister(Fs);
    EnvTMR_OverflowCallbackRegister(Env);

    score = hotaru;
    while (1) {

    }
}