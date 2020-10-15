#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const int DATA_COUNT = 30;
static const int COMPANT_COUNT = 10;

/*
 1. 무작위로 랜덤 패턴을 생성(createRandomAnswerSheet). 이때 패턴은 숫자 0, 1, 2 사용(2는 와일드카드)
 2. 생성된 랜덤 패턴과 과거 데이터 기록과 유사성 비교. 유사성이 있으면 score + 1
 3. 가장 높은 score를 획득한 AnswerSheet 추출
 
 - 과거 데이터 기록의 패턴은 0 또는 1의 값을 가지지만 항상 일정한 규칙을 갖고 있는 것은 아니기 때문에 와일드카드 2 사용
 - 랜덤 패턴과 과거 데이터 기록 유사성은 A부터 J까지 각 값들을 비교해서 유사성이 있으면 point 변수를 1씩 증가
 - 그리고 해당 패턴과 일치하면서 value 값이 1 이 되거나, 해당 패턴과 일치하지 않으면서 value 값이 0이 되는 경우에 score 값을 1 증가시킴
 */




/* File 로부터 데이터를 읽어들임 */
void loadData(int data[DATA_COUNT][COMPANT_COUNT], int value[DATA_COUNT]) {
    freopen("data.txt", "r", stdin);
    setbuf(stdout, NULL);
    
    for(int i = 0; i < DATA_COUNT; i++) {
        for(int j = 0; j < COMPANT_COUNT; j++) {
            scanf("%d", &data[i][j]); // 패턴 저장
        }
        scanf("%d", &value[i]); // 각 패턴에 따른 value 저장
    }
}


/* 초기 AnswerSheet 은 랜덤으로 설정 */
void createRandomAnswerSheet(int answer[COMPANT_COUNT]) {
    for(int i=0; i < COMPANT_COUNT; i++) {
        answer[i] = (rand() % 3);
    }
}

/* 점수 계산 */
int getScore(int data[DATA_COUNT][COMPANT_COUNT], int value[DATA_COUNT], int answer[COMPANT_COUNT]) {
    int score = 0;
    
    for(int i = 0; i < DATA_COUNT; i++) {
        int point = 0;
        
        for(int j = 0; j <COMPANT_COUNT; j++) {
            if(answer[j] == 2)
                point++;
            else if(answer[j] == data[i][j])
                point++;
            
            if((point == COMPANT_COUNT) && (value[i] = 1))
                score++;
            else if((point != COMPANT_COUNT) && (value[i] == 0))
                score++;
        }
    }
    
    return score;
}


int main() {
    srand(time(NULL));
    
    int score;
    int data[DATA_COUNT][COMPANT_COUNT];
    int value[DATA_COUNT];
    int answer[COMPANT_COUNT];
    
    int bestScore = 0;
    int bestAnswer[COMPANT_COUNT];
    
    loadData(data, value);
    
    for(int i = 0; i < 100000; i++) {
        createRandomAnswerSheet(answer);
        
        score = getScore(data, value, answer);
        
        if(score > bestScore) {
            for(int j = 0; j < COMPANT_COUNT; j++)
                bestAnswer[j] = answer[j];
            
            bestScore = score;
            
            for(int j = 0; j < COMPANT_COUNT; j++)
                printf("%1d ", bestAnswer[j]);
            
            printf(" --> score: %d\n", bestScore);
        }
    }
    
    printf("\n\n");
    for(int j = 0; j < COMPANT_COUNT; j++)
        printf("%1d ", bestAnswer[j]);
    printf(" --> score: %d\n", bestScore);
    
    return 0;
}
