#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>

/* プロトタイプ宣言*/
int search(char str[]);						//データ列数の計算

int main(int argc, char *argv[]) {

	/* 普通にダブルクリックされて起動した場合の回避処理（解析するデータが存在しない） */
	if (argc < 2) {
		printf("予期しないファイル数が読み込まれました．#debug: filinum = %d\n", argc);
		exit(-1);
	}

	printf("D&Dされたファイル数は%dです\n\n", (argc - 1));

	char buf[1000] = { '\0' };				//文字バッファ
	char str[2000] = { '\0' };				//文字読み取り

	double data[100] = { 0.0 };				//各データの格納(データ列数が配列数よりも下回ることに注意)

	int ret;								//EOF
	int t = 0;								//繰り返し
	int i = 0;								//for文とかの繰り返し
	int DATA_NUM = 0;						//データの列数
	double NUM = 1;							//データの行数
	int point;								//間引く間隔

	FILE *fp1;
	FILE *fp2;

	/* 間引く間隔を入力 */
	printf("間引く間隔:");
	scanf("%d", &point);
	printf("\n\n");

	/* D&Dされた数だけ実行 */
	for (int k = 1; k < argc; k++) {

		/* D&Dされたファイルをオープン */
		fp1 = fopen(argv[k], "r");
		if (fp1 == NULL) {
			printf("ファイルが開けません\n");
			return -1;
		}

		printf("処理中( %d / %d )\n", k, (argc - 1));


		/* 列の数を計算 */
		memset(str, '\0', sizeof(str));
		fscanf(fp1, "%s\n", str);
		DATA_NUM = search(str) + 1;	//データ種類の計算
		printf("データの種類は%d個です\n", DATA_NUM);

		memset(buf, '\0', sizeof(buf));

		/* 書き出し用CSVを設定 */
		sprintf(buf, "%s_cut.csv", argv[k]);
		fp2 = fopen(buf, "w");
		fprintf(fp2, "%s\n", str);

		NUM = 1;
		ret = 0;
		t = 0;
		i = 0;

		while ((ret = fscanf(fp1, "%lf,", &data[0])) != EOF) {
			/*データ読み込み*/
			for (t = 1; t < (DATA_NUM - 1); t++)
				fscanf(fp1, "%lf,", &data[t]);
			fscanf(fp1, "%lf\n", &data[t]);

			printf("\rReading data num = %5.0f", NUM);

			i++;

			/* 間引く */
			if(i > point - 1){
				for (t = 0; t < (DATA_NUM - 1); t++)
					fprintf(fp2, "%f,", data[t]);
				fprintf(fp2, "%f\n", data[t]);
				i = 0;
			}
			NUM += 1.0;
		}	//while end
		printf("\n\n");
		fclose(fp1);
		fclose(fp2);
		/* 終了 */
	}
	printf("\nFinish!!\n");
	printf("\n何かキーを押して終了してください...");
	while (_kbhit() == 0) {}
	return 0;
}

/*データ列数の計算関数*/
int search(char str[]) {
	int i;
	int num = 0;

	/*カンマの数を数えるだけ*/
	for (i = 0; i < 2000; i++) {
		if (str[i] == ',') {
			num++;
		}
	}
	return num;
}