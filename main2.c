#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//�þƵ귿�����������ֵ
int Max_rooms = 10;
int Max_guest = 20;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//������Ҫ��Ϣ
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
	int bookedRoom;
};

//��ʾ������Ϣ
// 3. ��ʾ�ͻ���Ϣ
void displaying_guest(struct guest VIP[], int index) {
	printf("������%s\t", VIP[index].name);
	printf("�Ա�%s\t", VIP[index].gender);
	printf("�˻���%d\t", VIP[index].sum);
	printf("�û��ȼ���%s\t", VIP[index].whether_VIP);
	printf("Ԥ������ţ�%d\n", VIP[index].bookedRoom);
}

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







//�Ƶ�ϵͳ


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



//3.ɾ������
void delete_room(struct rooms_info room[], int *numRooms,struct guest guest[],int numGuest) {
	int i, j;
	int deletedRoom;
	printf("������Ҫɾ���ķ����룺");
	scanf("%d", &deletedRoom);
	for (i = 0; i < *numRooms; i++) {
		if (room[i].roomNumber == deletedRoom) {
			if (room[i].isBooked == 1) {
				printf("�÷����ѱ�Ԥ��������ɾ����\n");
				return;
			}
			for (j = i; j < *numRooms - 1; j++) {
				room[j].roomNumber = room[j + 1].roomNumber;
				strcpy(room[j].roomType, room[j + 1].roomType);
				room[j].isBooked = room[j + 1].isBooked;
				room[j].price = room[j + 1].price;
				strcpy(room[j].host, room[j + 1].host);
			}
			//����˿�Ԥ����¼
			for(int k=0;k<numGuest;k++){
				if(guest[k].bookedRoom==deletedRoom){
					guest[k].bookedRoom=-1;
				}
			}
			(*numRooms)--;
			printf("ɾ���ɹ���\n");
			break;
		}
	}
	if (i == *numRooms) {
		printf("δ�ҵ��÷���ţ�ɾ��ʧ�ܣ�\n");
	}
	extra_displayingRooms(room, numRooms);
}



//4.���ӷ���
void add_room(struct rooms_info room[], int *numRooms) {
	int choice;
	int addedRoom;
	char addedroomType[20];
	double price;
	int isBooked;
	char host[20];
	do {
		printf("������Ҫ�������ӵķ��š��������͡�����۸��Լ�����״��:");
		scanf("%d", &addedRoom);
		scanf("%s", &addedroomType);
		scanf("%lf", &price);
		scanf("%d", &isBooked);
		scanf("%s", &host);
		if (*numRooms < Max_rooms) {
			room[*numRooms].roomNumber = addedRoom;
			strcpy(room[*numRooms].roomType, addedroomType);
			room[*numRooms].isBooked = isBooked;
			room[*numRooms].price = (float)price;
			strcpy(room[*numRooms].host, host);
			(*numRooms)++;
			printf("��ӷ��ųɹ���\n");
		} else {
			printf("���������Ѵ����ޣ��޷���ӣ�\n");
		}
		extra_displayingRooms(room, *numRooms);
		printf("�����Ƿ���Ҫ�����ӣ�");
		printf("1.ȷ��\n2.����\n");
		printf("���ѡ���ǣ�");
		scanf("%d", &choice);
		if (choice != 1 && choice != 2) {
			printf("�����������������");
			system("pause");
		}
	} while (choice != 2);
}

//5.��ѯ
void hotel_system_search(struct rooms_info room[], int *numRooms) {
	printf("����Ϊ���Ƶ��Ѷ������������\n");
	extra_displayingRooms(room, numRooms);
}


// ���ҹ˿���Ϣ
void search_guest_info(struct guest guest[], int numGuest) {
	char targetName[50];
	printf("������Ҫ���ҵĹ˿�������");
	scanf("%s", targetName);
	int found = 0;
	for (int i = 0; i < numGuest; i++) {
		if (strcmp(guest[i].name, targetName) == 0) {
			displaying_guest(guest, i);
			found = 1;
			break;
		}
	}
	if (!found) {
		printf("δ�ҵ��ù˿���Ϣ��\n");
	}
}

//6.�Ƶ��ڲ�ϵͳ
void hotel_system(struct rooms_info room[], int *numRooms, struct guest guest[], int numGuest) {
	int choice;
	do {
		printf("\t*1.��ѯ���䶩�����*\t\n");
		printf("\t*2.ɾ������*\t\n");
		printf("\t*3.���ӷ���*\t\n");
		printf("\t*4.��ѯ�˿���Ϣ*\t\n");
		printf("\t*0.�˳�*\t\n");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				hotel_system_search(room, numRooms);//int*���͵�
				break;
			case 2:
				delete_room(room, numRooms,guest,numGuest);
				break;
			case 3:
				add_room(room, numRooms);
				break;
			case 4:
				search_guest_info(guest, numGuest);
				break;
			case 0:
				printf("�ѳɹ��˳�\n");
				break;
			default:
				printf("��Ч���룬���������룡\n");
		}
	} while (choice != 0);
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


////3.��ʾ�ͻ���Ϣ
//void displaying_guest(struct guest VIP[], int index) {
//	printf("������%s\t", VIP[index].name);
//	printf("�Ա�%s\t", VIP[index].gender);
//	printf("�˻���%d\t", VIP[index].sum);
//	printf("�û��ȼ���%s\t", VIP[index].whether_VIP);
//	printf("\n");
//}


//2.VIPϵͳ
void VIP_system(struct guest VIP[], int index) {
	printf("\t*����VIP�û������ã�*\t\n");
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
	extra_displayingRooms(room, numRooms); //��Ҫ����int *���͵�
	int roomNumber;
	printf("������ҪԤ���ķ���ţ�");
	scanf("%d", &roomNumber);
	for (int i = 0; i < *numRooms; i++) {
		if (room[i].roomNumber == roomNumber) {
			if (room[i].isBooked == 0) {
				room[i].isBooked = 1;
				strcpy(room[i].host, guest[*numGuest - 1].name);
				guest[*numGuest - 1].bookedRoom = roomNumber; // ����Ԥ���ķ����
				printf("\t*����Ԥ���ɹ���*\t\n");
				if (strcmp(room[i].roomType, "���˼�") == 0) {
					guest[*numGuest - 1].sum -= 200;
				} else {
					guest[*numGuest - 1].sum -= 300;
				}

				extra_displayingRooms(room, numRooms);
				return;
			} else {
				printf("\t*�÷����ѱ�Ԥ������ѡ���������䡣*\t\n");
				return;
			}
		}
	}
	printf("δ�ҵ��÷���ţ����������룺");
}
//�˷�ϵͳ
void check_out(struct rooms_info room[], int *numRooms, struct guest guest[], int numGuest) {
	int roomNumber;
	printf("������Ҫ�˷��ķ���ţ�");
	scanf("%d", &roomNumber);
	for (int i = 0; i < *numRooms; i++) {
		if (room[i].roomNumber == roomNumber) {
			if (room[i].isBooked == 1) {
				room[i].isBooked = 0;
				strcpy(room[i].host, "����");
				for (int j = 0; j < numGuest; j++) {
					if (guest[j].bookedRoom == roomNumber) {
						guest[j].bookedRoom = -1;
					}
				}
				printf("�˷��ɹ���\n");
				extra_displayingRooms(room, &numRooms);
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
	printf("\t*1.��ֵ*\t\n");
	printf("\t*2.ȡ��*\t\n");
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
		printf("\t*��ȡ����ֵ������*\t\n");
	}
}
// �������guest_system����
void guest_system(struct guest guest[], struct rooms_info room[], int *numGuest, int *numRooms) {
	int choice;
	regist_name(guest, numGuest); // ����ָ��
	whether_VIP(guest, numGuest, room, numRooms); // ����˳������
	do {
		displayingRooms(room, numRooms); //��Ҫ����int *���͵�
		printf("\t*1. Ԥ������*\t\n");
		printf("\t*2. �˷�*\t\n");
		printf("\t*3.��ֵ*\t\n");
		printf("\t*0. �˳��ÿ�ϵͳ*\t\n");
		printf("������ѡ��:");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				book_room(room, numRooms, guest, numGuest); // ��������
				break;
			case 2:
				check_out(room, numRooms, guest, numGuest); // ��������
				break;
			case 3:
				charge(guest, *numGuest - 1);
				break;
			case 0:
				printf("\t*�ѳɹ��˳��ÿ�ϵͳ��*\t\n");
				break;
			default: // ����ƴд����
				printf("\t*��Ч���룬���������룡*\t\n");
		}
	} while (choice != 0);
}

int main(int argc, char *argv[]) {
	int choice;
	int numRooms;
	int numGuest = 0;
	struct rooms_info room[Max_rooms];
	struct guest guest[Max_guest];
	initializeRooms(room, &numRooms);//���ȱ���ⲽ����������ķ�����ϢΪ����
	do {
		printf("\t*��ӭ���ٱ��Ƶ�*\t\n");
		printf("\t*�ܸ���Ϊ������*\t\n");
		printf("\t*1.������Ա*\t\n");
		printf("\t*2.�ο͵�¼*\t\n");
		printf("\t*0.�˳�*\t\n");
		printf("������ѡ��:");
		scanf("%d", &choice);
		switch (choice) {
			case 1:
				//���ú���Ҫ�����Ѷ���õı���������������
				hotel_system(room, &numRooms, guest, numGuest);
				//��numRooms�����ĵ�ַ���������ں����ڲ��޸�ֵ
				break;
			case 2:
				guest_system(guest, room, &numGuest, &numRooms);
				break;
			case 0:
				printf("��лʹ�ã��ټ���\n");
				break;
			default:
				printf("��������");
				system("pause");//��ͣ�������������
				system("cls");//����
		}
	} while (choice != 0);
	return 0;
}
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
////�þƵ귿�����������ֵ
//int Max_rooms = 10;
//int Max_guest = 20;
//
///* run this program using the console pauser or add your own getch, system("pause") or input loop */
////������Ҫ��Ϣ
//struct rooms_info {
//    int roomNumber;
//    char roomType[20];
//    float price;
//    int isBooked;
//    char host[20];
//};
//struct guest {
//    char name[50];
//    char gender[4];
//    int sum;
//    char whether_VIP[5];
//    int bookedRoom;
//};
//
////��ʾ������Ϣ
//// 3. ��ʾ�ͻ���Ϣ
//void displaying_guest(struct guest VIP[], int index) {
//    printf("������%s\t", VIP[index].name);
//    printf("�Ա�%s\t", VIP[index].gender);
//    printf("�˻���%d\t", VIP[index].sum);
//    printf("�û��ȼ���%s\t", VIP[index].whether_VIP);
//    printf("Ԥ������ţ�%d\n", VIP[index].bookedRoom);
//}
//
//// �Ľ������ʾ��Ԥ��������Ϣ����
//void displayBookedRooms(struct rooms_info room[], int *numRooms) {
//    int i;
//    printf("����Ϊ���Ƶ��Ѷ������������\n");
//    printf("%-8s%-12s%-12s%-12s\n", "����", "��������", "����۸�", "����״̬");
//    for (i = 0; i < *numRooms; i++) {
//        printf("%-8d%-12s%-12.2f%-12d\n", room[i].roomNumber, room[i].roomType, room[i].price, room[i].isBooked);
//    }
//}
//
////�Ƶ�ϵͳ
//
////1.�Ƶ�ר����ʾ������Ϣ
//void displayingRooms(struct rooms_info room[], int *numRooms) {
//    int i;
//    printf("����Ϊ���Ƶ��Ѷ������������\n");
//    printf("%-8s%-12s%-12s%-12s%-12s\n", "����", "��������", "����۸�", "����״̬", "�����⻧");
//    for (i = 0; i < *numRooms; i++) {
//        printf("%-8d%-12s%-12.2f%-12d%-12s\n", room[i].roomNumber, room[i].roomType, room[i].price, room[i].isBooked, room[i].host);
//    }
//}
//
////2.��ʼ��������Ϣ
//void initializeRooms(struct rooms_info room[], int *numRooms) {
//    int i;
//    *numRooms = 0;
//    for (i = 0; i < Max_rooms; i++) {
//        room[i].roomNumber = 101 + i;
//        strcpy(room[i].host, "����");
//        if (i < Max_rooms / 2) {
//            strcpy(room[i].roomType, "���˼�");
//            room[i].price = 200.0;
//        } else {
//            strcpy(room[i].roomType, "˫�˼�");
//            room[i].price = 300.0;
//        }
//        room[i].isBooked = 0;
//        (*numRooms)++;
//    }
//}
//
////3.ɾ������
//void delete_room(struct rooms_info room[], int *numRooms, struct guest guest[], int numGuest) {
//    int i, j;
//    int deletedRoom;
//    printf("������Ҫɾ���ķ����룺");
//    scanf("%d", &deletedRoom);
//    for (i = 0; i < *numRooms; i++) {
//        if (room[i].roomNumber == deletedRoom) {
//            if (room[i].isBooked == 1) {
//                printf("�÷����ѱ�Ԥ��������ɾ����\n");
//                return;
//            }
//            for (j = i; j < *numRooms - 1; j++) {
//                room[j].roomNumber = room[j + 1].roomNumber;
//                strcpy(room[j].roomType, room[j + 1].roomType);
//                room[j].isBooked = room[j + 1].isBooked;
//                room[j].price = room[j + 1].price;
//                strcpy(room[j].host, room[j + 1].host);
//            }
//            //����˿�Ԥ����¼
//            for (int k = 0; k < numGuest; k++) {
//                if (guest[k].bookedRoom == deletedRoom) {
//                    guest[k].bookedRoom = -1;
//                }
//            }
//            (*numRooms)--;
//            printf("ɾ���ɹ���\n");
//            break;
//        }
//    }
//    if (i == *numRooms) {
//        printf("δ�ҵ��÷���ţ�ɾ��ʧ�ܣ�\n");
//    }
//    displayBookedRooms(room, numRooms);
//}
//
////4.���ӷ���
//void add_room(struct rooms_info room[], int *numRooms) {
//    int choice;
//    int addedRoom;
//    char addedroomType[20];
//    double price;
//    int isBooked;
//    char host[20];
//    do {
//        printf("������Ҫ�������ӵķ��š��������͡�����۸��Լ�����״��:");
//        scanf("%d", &addedRoom);
//        scanf("%s", addedroomType);
//        scanf("%lf", &price);
//        scanf("%d", &isBooked);
//        scanf("%s", host);
//        if (*numRooms < Max_rooms) {
//            room[*numRooms].roomNumber = addedRoom;
//            strcpy(room[*numRooms].roomType, addedroomType);
//            room[*numRooms].isBooked = isBooked;
//            room[*numRooms].price = (float)price;
//            strcpy(room[*numRooms].host, host);
//            (*numRooms)++;
//            printf("��ӷ��ųɹ���\n");
//        } else {
//            printf("���������Ѵ����ޣ��޷���ӣ�\n");
//        }
//        displayBookedRooms(room, numRooms);
//        printf("�����Ƿ���Ҫ�����ӣ�");
//        printf("1.ȷ��\n2.����\n");
//        printf("���ѡ���ǣ�");
//        scanf("%d", &choice);
//        if (choice != 1 && choice != 2) {
//            printf("�����������������");
//            system("pause");
//        }
//    } while (choice != 2);
//}
//
////5.��ѯ
//void hotel_system_search(struct rooms_info room[], int *numRooms) {
//    printf("����Ϊ���Ƶ��Ѷ������������\n");
//    displayBookedRooms(room, numRooms);
//}
//
//// ���ҹ˿���Ϣ
//void search_guest_info(struct guest guest[], int numGuest) {
//    char targetName[50];
//    printf("������Ҫ���ҵĹ˿�������");
//    scanf("%s", targetName);
//    int found = 0;
//    for (int i = 0; i < numGuest; i++) {
//        if (strcmp(guest[i].name, targetName) == 0) {
//            displaying_guest(guest, i);
//            found = 1;
//            break;
//        }
//    }
//    if (!found) {
//        printf("δ�ҵ��ù˿���Ϣ��\n");
//    }
//}
//
////6.�Ƶ��ڲ�ϵͳ
//void hotel_system(struct rooms_info room[], int *numRooms, struct guest guest[], int numGuest) {
//    int choice;
//    do {
//        printf("\t*1.��ѯ���䶩�����*\t\n");
//        printf("\t*2.ɾ������*\t\n");
//        printf("\t*3.���ӷ���*\t\n");
//        printf("\t*4.��ѯ�˿���Ϣ*\t\n");
//        printf("\t*0.�˳�*\t\n");
//        scanf("%d", &choice);
//        switch (choice) {
//            case 1:
//                hotel_system_search(room, numRooms);
//                break;
//            case 2:
//                delete_room(room, numRooms, guest, numGuest);
//                break;
//            case 3:
//                add_room(room, numRooms);
//                break;
//            case 4:
//                search_guest_info(guest, numGuest);
//                break;
//            case 0:
//                printf("�ѳɹ��˳�\n");
//                break;
//            default:
//                printf("��Ч���룬���������룡\n");
//        }
//    } while (choice != 0);
//}
//
////�˿�ϵͳ
////1.ע��
//void regist_name(struct guest name[], int *numGuest) {
//    printf("��ӭ���ٱ��Ƶ꣡\n");
//    printf("����������������");
//    scanf("%s", name[*numGuest].name);
//    printf("�����������Ա�");
//    scanf("%s", name[*numGuest].gender);
//    name[*numGuest].sum = 0;
//    strcpy(name[*numGuest].whether_VIP, "��VIP");
//    (*numGuest)++;
//}
//
////2.VIPϵͳ
//void VIP_system(struct guest VIP[], int index) {
//    printf("\t*����VIP�û������ã�*\t\n");
//    displaying_guest(VIP, index);
//}
//
////4.�ж��Ƿ�ΪVIP
//void whether_VIP(struct guest VIP[], int *numGuest, struct rooms_info name[], int *numRooms) {
//    int i, j;
//    int isVIP = 0;
//    if (*numGuest != 0) {
//        for (i = 0; i < *numGuest; i++) {
//            for (j = 0; j < *numRooms; j++) {
//                //����ʹ�á�==�����д�����strcmp
//                if (strcmp(VIP[i].name, name[j].host) == 0) {
//                    strcpy(VIP[i].whether_VIP, "VIP");
//                    VIP_system(VIP, i);
//                    isVIP = 1;
//                    break;
//                }
//            }
//            if (!isVIP) {
//                strcpy(VIP[i].whether_VIP, "��VIP");
//                displaying_guest(VIP, i);
//            }
//        }
//    }
//}
//
////5.����ϵͳ
//void book_room(struct rooms_info room[], int *numRooms, struct guest guest[], int *numGuest) {
//    displayBookedRooms(room, numRooms);
//    int roomNumber;
//    printf("������ҪԤ���ķ���ţ�");
//    scanf("%d", &roomNumber);
//    for (int i = 0; i < *numRooms; i++) {
//        if (room[i].roomNumber == roomNumber) {
//            if (room[i].isBooked == 0) {
//                room[i].isBooked = 1;
//                strcpy(room[i].host, guest[*numGuest - 1].name);
//                guest[*numGuest - 1].bookedRoom = roomNumber; // ����Ԥ���ķ����
//                printf("\t*����Ԥ���ɹ���*\t\n");
//                if (strcmp(room[i].roomType, "���˼�") == 0) {
//                    guest[*numGuest - 1].sum -= 200;
//                } else {
//                    guest[*numGuest - 1].sum -= 300;
//                }
//                displayBookedRooms(room, numRooms);
//                return;
//            } else {
//                printf("\t*�÷����ѱ�Ԥ������ѡ���������䡣*\t\n");
//                return;
//            }
//        }
//    }
//    printf("δ�ҵ��÷���ţ����������룺");
//}
//
////�˷�ϵͳ
//void check_out(struct rooms_info room[], int *numRooms, struct guest guest[], int numGuest) {
//    int roomNumber;
//    printf("������Ҫ�˷��ķ���ţ�");
//    scanf("%d", &roomNumber);
//    for (int i = 0; i < *numRooms; i++) {
//        if (room[i].roomNumber == roomNumber) {
//            if (room[i].isBooked == 1) {
//                room[i].isBooked = 0;
//                strcpy(room[i].host, "����");
//                for (int j = 0; j < numGuest; j++) {
//                    if (guest[j].bookedRoom == roomNumber) {
//                        guest[j].bookedRoom = -1;
//                    }
//                }
//                printf("�˷��ɹ���\n");
//                displayBookedRooms(room, numRooms);
//                return;
//            } else {
//                printf("�÷���δ��Ԥ���������˷���\n");
//                return;
//            }
//        }
//    }
//    printf("δ�ҵ��÷���ţ����������롣\n");
//}
//
////��ֵ
//void charge(struct guest guest[], int index) {
//    displaying_guest(guest, index);
//    int s;
//    int choice;
//    printf("\t*1.��ֵ*\t\n");
//    printf("\t*2.ȡ��*\t\n");
//    scanf("%d", &choice);
//    while (choice != 1 && choice != 2) {
//        printf("��Ч���룬������ѡ��");
//        scanf("%d", &choice);
//    }
//    if (choice == 1) {
//        printf("��������Ҫ��ֵ�����");
//        scanf("%d", &s);
//        guest[index].sum += s;
//        if (guest[index].sum > 500) {
//            strcpy(guest[index].whether_VIP, "VIP");
//            displaying_guest(guest, index);
//        }
//    } else {
//        printf("\t*��ȡ����ֵ������*\t\n");
//    }
//}
//
//// �������guest_system����
//void guest_system(struct guest guest[], struct rooms_info room[], int *numGuest, int *numRooms) {
//    int choice;
//    regist_name(guest, numGuest); // ����ָ��
//    whether_VIP(guest, numGuest, room, numRooms); // ����˳������
//    do {
//        displayingRooms(room, numRooms);
//        printf("\t*1. Ԥ������*\t\n");
//        printf("\t*2. �˷�*\t\n");
//        printf("\t*3.��ֵ*\t\n");
//        printf("\t*0. �˳��ÿ�ϵͳ*\t\n");
//        printf("������ѡ��:");
//        scanf("%d", &choice);
//        switch (choice) {
//            case 1:
//                book_room(room, numRooms, guest, numGuest);
//                break;
//            case 2:
//                check_out(room, numRooms, guest, numGuest);
//                break;
//            case 3:
//                charge(guest, *numGuest - 1);
//                break;
//            case 0:
//                printf("\t*�ѳɹ��˳��ÿ�ϵͳ��*\t\n");
//                break;
//            default:
//                printf("\t*��Ч���룬���������룡*\t\n");
//        }
//    } while (choice != 0);
//}
//
//int main(int argc, char *argv[]) {
//    int choice;
//    int numRooms;
//    int numGuest = 0;
//    struct rooms_info room[Max_rooms];
//    struct guest guest[Max_guest];
//    initializeRooms(room, &numRooms);
//    do {
//        printf("\t*��ӭ���ٱ��Ƶ�*\t\n");
//        printf("\t*�ܸ���Ϊ������*\t\n");
//        printf("\t*1.������Ա*\t\n");
//        printf("\t*2.�ο͵�¼*\t\n");
//        printf("\t*0.�˳�*\t\n");
//        printf("������ѡ��:");
//        scanf("%d", &choice);
//        switch (choice) {
//            case 1:
//                hotel_system(room, &numRooms, guest, numGuest);
//                break;
//            case 2:
//                guest_system(guest, room, &numGuest, &numRooms);
//                break;
//            case 0:
//                printf("��лʹ�ã��ټ���\n");
//                break;
//            default:
//                printf("��������");
//                system("pause");
//                system("cls");
//        }
//    } while (choice != 0);
//    return 0;
//}
