#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>

/* �v���g�^�C�v�錾*/
int search(char str[]);						//�f�[�^�񐔂̌v�Z

int main(int argc, char *argv[]) {

	/* ���ʂɃ_�u���N���b�N����ċN�������ꍇ�̉�������i��͂���f�[�^�����݂��Ȃ��j */
	if (argc < 2) {
		printf("�\�����Ȃ��t�@�C�������ǂݍ��܂�܂����D#debug: filinum = %d\n", argc);
		exit(-1);
	}

	printf("D&D���ꂽ�t�@�C������%d�ł�\n\n", (argc - 1));

	char buf[1000] = { '\0' };				//�����o�b�t�@
	char str[2000] = { '\0' };				//�����ǂݎ��

	double data[100] = { 0.0 };				//�e�f�[�^�̊i�[(�f�[�^�񐔂��z�񐔂�������邱�Ƃɒ���)

	int ret;								//EOF
	int t = 0;								//�J��Ԃ�
	int i = 0;								//for���Ƃ��̌J��Ԃ�
	int DATA_NUM = 0;						//�f�[�^�̗�
	double NUM = 1;							//�f�[�^�̍s��
	int point;								//�Ԉ����Ԋu

	FILE *fp1;
	FILE *fp2;

	/* �Ԉ����Ԋu����� */
	printf("�Ԉ����Ԋu:");
	scanf("%d", &point);
	printf("\n\n");

	/* D&D���ꂽ���������s */
	for (int k = 1; k < argc; k++) {

		/* D&D���ꂽ�t�@�C�����I�[�v�� */
		fp1 = fopen(argv[k], "r");
		if (fp1 == NULL) {
			printf("�t�@�C�����J���܂���\n");
			return -1;
		}

		printf("������( %d / %d )\n", k, (argc - 1));


		/* ��̐����v�Z */
		memset(str, '\0', sizeof(str));
		fscanf(fp1, "%s\n", str);
		DATA_NUM = search(str) + 1;	//�f�[�^��ނ̌v�Z
		printf("�f�[�^�̎�ނ�%d�ł�\n", DATA_NUM);

		memset(buf, '\0', sizeof(buf));

		/* �����o���pCSV��ݒ� */
		sprintf(buf, "%s_cut.csv", argv[k]);
		fp2 = fopen(buf, "w");
		fprintf(fp2, "%s\n", str);

		NUM = 1;
		ret = 0;
		t = 0;
		i = 0;

		while ((ret = fscanf(fp1, "%lf,", &data[0])) != EOF) {
			/*�f�[�^�ǂݍ���*/
			for (t = 1; t < (DATA_NUM - 1); t++)
				fscanf(fp1, "%lf,", &data[t]);
			fscanf(fp1, "%lf\n", &data[t]);

			printf("\rReading data num = %5.0f", NUM);

			i++;

			/* �Ԉ��� */
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
		/* �I�� */
	}
	printf("\nFinish!!\n");
	printf("\n�����L�[�������ďI�����Ă�������...");
	while (_kbhit() == 0) {}
	return 0;
}

/*�f�[�^�񐔂̌v�Z�֐�*/
int search(char str[]) {
	int i;
	int num = 0;

	/*�J���}�̐��𐔂��邾��*/
	for (i = 0; i < 2000; i++) {
		if (str[i] == ',') {
			num++;
		}
	}
	return num;
}