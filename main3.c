#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int Max_rooms = 10;
int Max_guest = 20;
struct rooms_info {
	int roomNumber;
	char roomType[20];
	float price;
	int isBooked;
	char host[20];
};
struct guest {
	char name[50];
	char gender[4];
	int sum;
	char whether_VIP[5];
};
//2.��ʼ��������Ϣ
void initializeRooms(struct rooms_info room[], int *numRooms) {
	int i;
	*numRooms = 0;
	for (i = 0; i < Max_rooms; i++) {
		room[i].roomNumber = 101 + i;
		strcpy(room[i].host, "����" );
		if (i < Max_rooms / 2) {
			strcpy(room[i].roomType, "���˼�");
			room[i].price = 200.0;
			

		} else {
			strcpy(room[i].roomType, "˫�˼�");

			room[i].price = 300.0;

		}
		room[i].isBooked = 0;
		(*numRooms)++;

	}

}
//��ʾ������Ϣ
void extra_displayingRooms(struct rooms_info room[], int *numRooms) {
	int i;
	printf("����Ϊ���Ƶ��Ѷ������������\n");
	printf("����   ");
	printf("��������  ");
	printf("����۸�  ");
	printf("����״̬\n");
	for (i = 0; i < *numRooms; i++) {
		printf("%d   ", room[i].roomNumber);
		printf("%s    ", room[i].roomType);
		printf("%.2lf    ", room[i].price);
		printf("%d\n", room[i].isBooked);
	}
}
//1.�Ƶ�ר����ʾ������Ϣ
void displayingRooms(struct rooms_info room[], int *numRooms) {
	int i;
	printf("����Ϊ���Ƶ��Ѷ������������\n");
	printf("����   ");
	printf("��������  ");
	printf("����۸�  ");
	printf("����״̬  ");
	printf("�����⻧\n");
	for (i = 0; i < *numRooms; i++) {
		printf("%d   ", room[i].roomNumber);
		printf("%s    ", room[i].roomType);
		printf("%.2lf      ", room[i].price);
		printf("%d    ", room[i].isBooked);
		printf("     %s\n", room[i].host);
	}
}
//�˿�ϵͳ
//1.ע��
void regist_name(struct guest name[], int *numGuest) {
	printf("��ӭ���ٱ��Ƶ꣡\n");
	printf("����������������");
	scanf("%s", name[*numGuest].name);
	printf("�����������Ա�");
	scanf("%s", name[*numGuest].gender);
	name[*numGuest].sum = 0;
	strcpy(name[*numGuest].whether_VIP, "��VIP");
	(*numGuest)++;
}


//3.��ʾ�ͻ���Ϣ
void displaying_guest(struct guest VIP[], int index) {
	printf("������%s\t", VIP[index].name);
	printf("�Ա�%s\t", VIP[index].gender);
	printf("�˻���%d\t", VIP[index].sum);
	printf("�û��ȼ���%s\t", VIP[index].whether_VIP);
	printf("\n");
}


//2.VIPϵͳ
void VIP_system(struct guest VIP[], int index) {
	printf("����VIP�û������ã�\n");
	displaying_guest(VIP, index);
}


//4.�ж��Ƿ�ΪVIP
void whether_VIP(struct guest VIP[], int *numGuest, struct rooms_info name[], int *numRooms) {
	int i, j;
	int isVIP = 0;
	if (*numGuest != 0) {
		for (i = 0; i < *numGuest; i++) {
			for (j = 0; j < *numRooms; j++) {
				//����ʹ�á�==�����д�����strcmp
				if (strcmp(VIP[i].name, name[j].host) == 0) {
					strcpy(VIP[i].whether_VIP, "VIP");
					VIP_system(VIP, i);
					isVIP = 1;
					break;
				}
			}
			if (!isVIP) {
				strcpy(VIP[i].whether_VIP, "��VIP");
				displaying_guest(VIP, i);
			}
		}
	}

}
//5.����ϵͳ
void book_room(struct rooms_info room[], int *numRooms, struct guest guest[], int *numGuest) {
	displayingRooms(room, numRooms); //��Ҫ����int *���͵�
	int roomNumber;
	printf("������ҪԤ���ķ���ţ�");
	scanf("%d", &roomNumber);
	for (int i = 0; i < *numRooms; i++) {
		if (room[i].roomNumber == roomNumber) {
			if (room[i].isBooked == 0) {
				room[i].isBooked = 1;
				strcpy(room[i].host, guest[*numGuest - 1].name);
				printf("����Ԥ���ɹ���\n");
				if(roomNumber/2!=0){
					guest[i].sum-=200;
				}else{
					guest[i].sum-=300;
				}
				
				extra_displayingRooms(room, numRooms);
				return;
			} else {
				printf("�÷����ѱ�Ԥ������ѡ���������䡣\n");
				return;
			}
		}
	}
	printf("δ�ҵ��÷���ţ����������룺");
}
//�˷�ϵͳ
void check_out(struct rooms_info room[], int *numRooms) {
	int roomNumber;
	printf("������Ҫ�˷��ķ���ţ�");
	scanf("%d", &roomNumber);
	for (int i = 0; i < *numRooms; i++) {
		if (room[i].roomNumber == roomNumber) {
			if (room[i].isBooked == 1) {
				room[i].isBooked = 0;
				strcpy(room[i].host, "����");
				printf("�˷��ɹ���\n");
				extra_displayingRooms(room, numRooms);
				return;
			} else {
				printf("�÷���δ��Ԥ���������˷���\n");
				return;
			}
		}
	}
	printf("δ�ҵ��÷���ţ����������롣\n");
}
//��ֵ
void charge(struct guest guest[], int index) {
	displaying_guest(guest, index);
	int s;
	int choice;
	printf("1.��ֵ\n");
	printf("2.ȡ��\n");
	scanf("%d", &choice);
	while (choice != 1 && choice != 2) {
		printf("��Ч���룬������ѡ��");
		scanf("%d", &choice);
	}
	if (choice == 1) {
		printf("��������Ҫ��ֵ�����");
		scanf("%d", &s);
		guest[index].sum += s;
		if (guest[index].sum > 500) {
			strcpy(guest[index].whether_VIP, "VIP");
			displaying_guest(guest, index);
		}
	} else {
		printf("��ȡ����ֵ������\n");
	}
}

// �������guest_system����
void guest_system(struct guest guest[], struct rooms_info room[], int *numGuest, int *numRooms) {
	int choice;
	regist_name(guest, numGuest); // ����ָ��
	whether_VIP(guest, numGuest, room, numRooms); // ����˳������
	do {
		displayingRooms(room, numRooms); //��Ҫ����int *���͵�
		printf("1. Ԥ������\n");
		printf("2. �˷�\n");
		printf("3.��ֵ\n");
		printf("0. �˳��ÿ�ϵͳ\n");
		printf("������ѡ��");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				book_room(room, numRooms, guest, numGuest); // ��������
				break;
			case 2:
				check_out(room, numRooms); // ��������
				break;
			case 3:
				charge(guest, *numGuest - 1);
				break;
			case 0:
				printf("�ѳɹ��˳��ÿ�ϵͳ��\n");
				break;
			default: // ����ƴд����
				printf("��Ч���룬���������룡\n");
		}
	} while (choice != 0);
}
int main(int argc, char *argv[]) {

	struct guest guest[Max_rooms];
	struct rooms_info room[Max_guest];
	int numGuest = 0;
	int numRooms;
	initializeRooms(room, &numRooms);//���ȱ���ⲽ����������ķ�����ϢΪ����
	guest_system(guest, room, &numGuest, &numRooms);
	return 0;
}
